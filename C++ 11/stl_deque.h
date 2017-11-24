// Filename:    stl_deque.h

// Comment By:  凝霜
// E-mail:      mdl2009@vip.qq.com
// Blog:        http://blog.csdn.net/mdl13412

// 如果vector能满足你的需求, 那么就使用vector
// 如果不得不使用deque, 那么在进行一算法(尤其是sort)操作时
// 应该先把deque中的元素复制到vector中
// 执行完算法再复制回去
// 这样的效率往往要高于直接使用算法的效率

/*
 *
 * Copyright (c) 1994
 * Hewlett-Packard Company
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Hewlett-Packard Company makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 *
 *
 * Copyright (c) 1997
 * Silicon Graphics Computer Systems, Inc.
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Silicon Graphics makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 */

/* NOTE: This is an internal header file, included by other STL headers.
 *   You should not attempt to use it directly.
 */

#ifndef __SGI_STL_INTERNAL_DEQUE_H
#define __SGI_STL_INTERNAL_DEQUE_H

// 特性:
//   对于任何的非奇异(nonsingular)的迭代器i
//     i.node是map array中的某元素的地址. i.node的内容是一个指向某个结点的头的指针
//     i.first == *(i.node)
//     i.last  == i.first + node_size
//     i.cur是一个指向[i.first, i.last)之间的指针
//       注意: 这意味着i.cur永远是一个可以解引用的指针,
//            即使其是一个指向结尾后元素的迭代器
//
//   起点和终点总是非奇异(nonsingular)的迭代器.
//     注意: 这意味着空deque一定有一个node, 而一个具有N个元素的deque
//          (N是Buffer Size)一定有有两个nodes
//
//   对于除了start.node和finish.node之外的每一个node, 每一个node中的元素
//   都是一个初始化过的对象. 如果start.node == finish.node,
//   那么[start.cur, finish.cur)都是未初始化的空间.
//   否则, [start.cur, start.last)和[finish.first, finish.cur)都是初始化的对象,
//   而[start.first, start.cur)和[finish.cur, finish.last)是未初始化的空间
//
//   [map, map + map_size)是一个合法的非空区间
//   [start.node, finish.node]是内含在[map, map + map_size)区间的合法区间
//   一个在[map, map + map_size)区间内的指针指向一个分配过的node,
//   当且仅当此指针在[start.node, finish.node]区间内

// 在前一个版本的deque中, node_size被设定为定植.
// 然而在这个版本中, 用户可以自定义node_size的大小.
// deque有三个模板参数, 第三个参数为size_t类型, 代表每个结点内的元素数目.
// 如果第三个参数被设定为0(默认值), deque使用默认结点大小
//
// 使用不同结点大小的唯一理由是, 你的程序需要不同的效率, 并愿意为此付出代价,
// 例如, 如果你的程序中有许多deque, 但是每个deque都只包含很少的元素,
// 那么你可以使用较小的node_size来进行管理, 但是会对访问操作带来效率损失
//
// 不幸的是, 一些编译器不能正确处理non-type template parameters;
// 如果这样, 在<stl_config.h>会定义__STL_NON_TYPE_TMPL_PARAM_BUG
// 如果你的编译器不幸在列, 你只能使用默认的大小, 而不能更改

__STL_BEGIN_NAMESPACE

#if defined(__sgi) && !defined(__GNUC__) && (_MIPS_SIM != _MIPS_SIM_ABI32)
#pragma set woff 1174
#endif

// 这个函数是为了防止不同编译器在处理常量表达式时的Bug
// 如果n != 0, 那么就返回n, 表示buffer size为使用者自定义
// 如果n ==0, 就返回默认值表示buffer size,默认值计算方法如下
//    如果sz(元素类型大小sizeof(type))小于512, 返回512 / sz
//    否则返回1
inline size_t __deque_buf_size(size_t n, size_t sz)
{
  return n != 0 ? n : (sz < 512 ? size_t(512 / sz) : size_t(1));
}

// 注意这里未继承自std::iterator
#ifndef __STL_NON_TYPE_TMPL_PARAM_BUG
template <class T, class Ref, class Ptr, size_t BufSiz>
struct __deque_iterator {
  typedef __deque_iterator<T, T&, T*, BufSiz>             iterator;
  typedef __deque_iterator<T, const T&, const T*, BufSiz> const_iterator;
  static size_t buffer_size() {return __deque_buf_size(BufSiz, sizeof(T)); }
#else /* __STL_NON_TYPE_TMPL_PARAM_BUG */
template <class T, class Ref, class Ptr>
struct __deque_iterator {
  typedef __deque_iterator<T, T&, T*>             iterator;
  typedef __deque_iterator<T, const T&, const T*> const_iterator;
  static size_t buffer_size() {return __deque_buf_size(0, sizeof(T)); }
#endif

  typedef random_access_iterator_tag iterator_category;      // STL标准强制要求
  typedef T value_type;                                      // STL标准强制要求
  typedef Ptr pointer;                                       // STL标准强制要求
  typedef Ref reference;                                     // STL标准强制要求
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;                         // STL标准强制要求
  typedef T** map_pointer;

  typedef __deque_iterator self;

  // 保存容器中的结点
  T* cur;       // 指向当前缓冲区中的元素
  T* first;     // 当前缓冲区的起点
  T* last;      // 当前缓冲区的终点

////////////////////////////////////////////////////////////////////////////////
// 这个是deque内存管理的关键, 其模型如下
////////////////////////////////////////////////////////////////////////////////
//
//       ---------------------------------------------
// map-->|   |   |   |   |   |   | ..... |   |   |   |<------------------
//       ---------------------------------------------                  |
//             |                                                        |
//             |                                                        |
//             |   node                                                 |
//             |   缓冲区buffer, 这里实际存储元素                          |
//             |   ---------------------------------------------        |
//             --->|   |   |   |   |   |   | ..... |   |   | X |        |
//                 ---------------------------------------------        |
//                   ↑       ↑                             ↑            |
//             ------        |                             |            |
//             |             |                             |            |
//             |   -----------   ---------------------------            |
//             ----|-----        |                                      |
//                 |    |        |                                      |
//                 |    |        |                                      |
//                 |    |        |                                      |
//              ---------------------------                             |
//              | cur | first | end | map |------------------------------
//              ---------------------------
//              迭代器, 其内部维护着一个缓冲区状态
////////////////////////////////////////////////////////////////////////////////
  map_pointer node;

  __deque_iterator(T* x, map_pointer y)
    : cur(x), first(*y), last(*y + buffer_size()), node(y) {}
  __deque_iterator() : cur(0), first(0), last(0), node(0) {}
  __deque_iterator(const iterator& x)
    : cur(x.cur), first(x.first), last(x.last), node(x.node) {}

  reference operator*() const { return *cur; }

#ifndef __SGI_STL_NO_ARROW_OPERATOR
  // 如果编译器支持'->'则重载, 详细见我在<stl_list.h>中的剖析
  pointer operator->() const { return &(operator*()); }
#endif /* __SGI_STL_NO_ARROW_OPERATOR */

  // 判断两个迭代器间的距离

  difference_type operator-(const self& x) const
  {
    return difference_type(buffer_size()) * (node - x.node - 1) +
      (cur - first) + (x.last - x.cur);
  }

////////////////////////////////////////////////////////////////////////////////
// 下面重载的这些是运算符是让deque从外界看上去维护的是一段连续空间的关键!!!
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// 前缀自增
////////////////////////////////////////////////////////////////////////////////
// 如果当前迭代器指向元素是当前缓冲区的最后一个元素,
// 则将迭代器状态调整为下一个缓冲区的第一个元素
////////////////////////////////////////////////////////////////////////////////
// 不是当前缓冲区最后一个元素
//
// 执行前缀自增前的状态
// first          cur                     end
// ↓               ↓                       ↓
// ---------------------------------------------
// |   |   |   |   |   |   | ..... |   |   | X | <----- 当前缓冲区
// ---------------------------------------------
//
// 执行完成后的状态
// first              cur                 end
// ↓                   ↓                   ↓
// ---------------------------------------------
// |   |   |   |   |   |   | ..... |   |   | X | <----- 当前缓冲区
// ---------------------------------------------
//
////////////////////////////////////////////////////////////////////////////////
// 当前元素为当前缓冲区的最后一个元素
//
// 执行前缀自增前的状态
// first                              cur end
// ↓                                   ↓   ↓
// ---------------------------------------------
// |   |   |   |   |   |   | ..... |   |   | X | <----- 当前缓冲区
// ---------------------------------------------
//
// 执行完成后的状态
// first                                  end
// ↓                                       ↓
// ---------------------------------------------
// |   |   |   |   |   |   | ..... |   |   | X | <----- 下一缓冲区
// ---------------------------------------------
// ↑
// cur
//
////////////////////////////////////////////////////////////////////////////////
  self& operator++()
  {
    ++cur;
    if (cur == last) {
      set_node(node + 1);
      cur = first;
    }
    return *this;
  }

  // 后缀自增
  // 返回当前迭代器的一个副本, 并调用前缀自增运算符实现迭代器自身的自增
  self operator++(int)  {
    self tmp = *this;
    ++*this;
    return tmp;
  }

  // 前缀自减, 处理方式类似于前缀自增
  // 如果当前迭代器指向元素是当前缓冲区的第一个元素
  // 则将迭代器状态调整为前一个缓冲区的最后一个元素
  self& operator--()
  {
    if (cur == first) {
      set_node(node - 1);
      cur = last;
    }
    --cur;
    return *this;
  }

  self operator--(int)
  {
    self tmp = *this;
    --*this;
    return tmp;
  }

////////////////////////////////////////////////////////////////////////////////
// 将迭代器向前移动n个元素, n可以为负
////////////////////////////////////////////////////////////////////////////////
//                     operator+=(difference_type n)
//                                   ↓
//                      offset = n + (cur - first)
//                                   |
//                                   |---------- offset > 0 ? &&
//                                   |           移动后是否超出当前缓冲区?
//               ----------------------------
//           No  |                          |  Yes
//               |                          |
//               ↓                          |---------- offset > 0?
//           cur += n;                      |
//                              ----------------------------
//                          Yes |                          | No
//                              |                          |
//                              ↓                          |
//                   计算要向后移动多少个缓冲区                |
//                   node_offset =                         |
//                   offset / difference_type              |
//                   (buffer_size());                      ↓
//                              |           计算要向前移动多少个缓冲区
//                              |           node_offset = -difference_type
//                              |           ((-offset - 1) / buffer_size()) - 1;
//                              |                          |
//                              ----------------------------
//                                           |
//                                           |
//                                           ↓
//                                       调整缓冲区
//                              set_node(node + node_offset);
//                                    计算并调整cur指针
////////////////////////////////////////////////////////////////////////////////

  self& operator+=(difference_type n)
  {
    difference_type offset = n + (cur - first);
    if (offset >= 0 && offset < difference_type(buffer_size()))
      cur += n;
    else {
      difference_type node_offset =
        offset > 0 ? offset / difference_type(buffer_size())
                   : -difference_type((-offset - 1) / buffer_size()) - 1;
      set_node(node + node_offset);
      cur = first + (offset - node_offset * difference_type(buffer_size()));
    }
    return *this;
  }

  self operator+(difference_type n) const
  {
    self tmp = *this;

    // 这里调用了operator +=()可以自动调整指针状态
    return tmp += n;
  }

  // :-), 将n变为-n就可以使用operator +=()了,
  // 初等数学是神奇的, 还记得我们刚学编程时求绝对值是怎么写的吗? :P
  self& operator-=(difference_type n) { return *this += -n; }

  self operator-(difference_type n) const {
    self tmp = *this;
    return tmp -= n;
  }

  reference operator[](difference_type n) const { return *(*this + n); }

  bool operator==(const self& x) const { return cur == x.cur; }
  bool operator!=(const self& x) const { return !(*this == x); }
  bool operator<(const self& x) const {
    return (node == x.node) ? (cur < x.cur) : (node < x.node);
  }

  void set_node(map_pointer new_node)
  {
    node = new_node;
    first = *new_node;
    last = first + difference_type(buffer_size());
  }
};

#ifndef __STL_CLASS_PARTIAL_SPECIALIZATION

#ifndef __STL_NON_TYPE_TMPL_PARAM_BUG

template <class T, class Ref, class Ptr, size_t BufSiz>
inline random_access_iterator_tag
iterator_category(const __deque_iterator<T, Ref, Ptr, BufSiz>&) {
  return random_access_iterator_tag();
}

template <class T, class Ref, class Ptr, size_t BufSiz>
inline T* value_type(const __deque_iterator<T, Ref, Ptr, BufSiz>&) {
  return 0;
}

template <class T, class Ref, class Ptr, size_t BufSiz>
inline ptrdiff_t* distance_type(const __deque_iterator<T, Ref, Ptr, BufSiz>&) {
  return 0;
}

#else /* __STL_NON_TYPE_TMPL_PARAM_BUG */

template <class T, class Ref, class Ptr>
inline random_access_iterator_tag
iterator_category(const __deque_iterator<T, Ref, Ptr>&) {
  return random_access_iterator_tag();
}

template <class T, class Ref, class Ptr>
inline T* value_type(const __deque_iterator<T, Ref, Ptr>&) { return 0; }

template <class T, class Ref, class Ptr>
inline ptrdiff_t* distance_type(const __deque_iterator<T, Ref, Ptr>&) {
  return 0;
}

#endif /* __STL_NON_TYPE_TMPL_PARAM_BUG */

// 其实剖析到这里就没有什么难的了, deque的运算符才是核心
#endif /* __STL_CLASS_PARTIAL_SPECIALIZATION */

// See __deque_buf_size().  The only reason that the default value is 0
//  is as a workaround for bugs in the way that some compilers handle
//  constant expressions.
template <class T, class Alloc = alloc, size_t BufSiz = 0>
class deque {
public:                         // Basic types
  typedef T value_type;
  typedef value_type* pointer;
  typedef const value_type* const_pointer;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;

public:                         // Iterators
#ifndef __STL_NON_TYPE_TMPL_PARAM_BUG
  typedef __deque_iterator<T, T&, T*, BufSiz>              iterator;

  typedef __deque_iterator<T, const T&, const T&, BufSiz>  const_iterator;
#else /* __STL_NON_TYPE_TMPL_PARAM_BUG */
  typedef __deque_iterator<T, T&, T*>                      iterator;
  typedef __deque_iterator<T, const T&, const T*>          const_iterator;
#endif /* __STL_NON_TYPE_TMPL_PARAM_BUG */

#ifdef __STL_CLASS_PARTIAL_SPECIALIZATION
  typedef reverse_iterator<const_iterator> const_reverse_iterator;
  typedef reverse_iterator<iterator> reverse_iterator;
#else /* __STL_CLASS_PARTIAL_SPECIALIZATION */
  typedef reverse_iterator<const_iterator, value_type, const_reference,
                           difference_type>
          const_reverse_iterator;
  typedef reverse_iterator<iterator, value_type, reference, difference_type>
          reverse_iterator;
#endif /* __STL_CLASS_PARTIAL_SPECIALIZATION */

protected:                      // Internal typedefs

  typedef pointer* map_pointer;

  // 这个提供STL标准的allocator接口, 见<stl_alloc.h>
  typedef simple_alloc<value_type, Alloc> data_allocator;
  typedef simple_alloc<pointer, Alloc> map_allocator;

  // 获取缓冲区最大存储元素数量
  static size_type buffer_size()
  {
    return __deque_buf_size(BufSiz, sizeof(value_type));
  }

  static size_type initial_map_size() { return 8; }

protected:                      // Data members
  iterator start;               // 起始缓冲区
  iterator finish;              // 最后一个缓冲区

  // 指向map, map是一个连续的空间, 其每个元素都是一个指向缓冲区的指针
  // 其模型见前面的__deque_iterator
  map_pointer map;
  size_type map_size;   // map容量

public:                         // Basic accessors
  iterator begin() { return start; }
  iterator end() { return finish; }
  const_iterator begin() const { return start; }
  const_iterator end() const { return finish; }

  reverse_iterator rbegin() { return reverse_iterator(finish); }
  reverse_iterator rend() { return reverse_iterator(start); }
  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(finish);
  }
  const_reverse_iterator rend() const {
    return const_reverse_iterator(start);
  }

  // 提供随机访问能力, 其调用的是迭代器重载的operator []
  // 其实际地址需要进行一些列的计算, 效率有损失
  reference operator[](size_type n) { return start[difference_type(n)]; }
  const_reference operator[](size_type n) const {
    return start[difference_type(n)];
  }

  reference front() { return *start; }
  reference back() {
    iterator tmp = finish;
    --tmp;
    return *tmp;
  }
  const_reference front() const { return *start; }
  const_reference back() const {
    const_iterator tmp = finish;
    --tmp;
    return *tmp;
  }

  // 当前容器拥有的元素个数, 调用迭代器重载的operator -
  size_type size() const { return finish - start;; }
  size_type max_size() const { return size_type(-1); }

  // deque为空的时, 只有一个缓冲区
  bool empty() const { return finish == start; }

public:                         // Constructor, destructor.
  deque()
    : start(), finish(), map(0), map_size(0)
  {
    create_map_and_nodes(0);
  }

  // 注: commit or rollback
  deque(const deque& x)
    : start(), finish(), map(0), map_size(0)
  {
    create_map_and_nodes(x.size());
    __STL_TRY {
      uninitialized_copy(x.begin(), x.end(), start);  // <stl_uninitialized.h>
    }
    __STL_UNWIND(destroy_map_and_nodes());
  }

  deque(size_type n, const value_type& value)
    : start(), finish(), map(0), map_size(0)
  {
    fill_initialize(n, value);
  }

  deque(int n, const value_type& value)
    : start(), finish(), map(0), map_size(0)
  {
    fill_initialize(n, value);
  }

  deque(long n, const value_type& value)
    : start(), finish(), map(0), map_size(0)
  {
    fill_initialize(n, value);
  }

  explicit deque(size_type n)
    : start(), finish(), map(0), map_size(0)
  {
    fill_initialize(n, value_type());
  }

#ifdef __STL_MEMBER_TEMPLATES

  template <class InputIterator>
  deque(InputIterator first, InputIterator last)
    : start(), finish(), map(0), map_size(0)
  {
    range_initialize(first, last, iterator_category(first));
  }

#else /* __STL_MEMBER_TEMPLATES */

  deque(const value_type* first, const value_type* last)
    : start(), finish(), map(0), map_size(0)
  {
    create_map_and_nodes(last - first);
    __STL_TRY {
      uninitialized_copy(first, last, start);
    }
    __STL_UNWIND(destroy_map_and_nodes());
  }

  deque(const_iterator first, const_iterator last)
    : start(), finish(), map(0), map_size(0)
  {
    create_map_and_nodes(last - first);
    __STL_TRY {
      uninitialized_copy(first, last, start);
    }
    __STL_UNWIND(destroy_map_and_nodes());
  }

#endif /* __STL_MEMBER_TEMPLATES */

  ~deque()
  {
    destroy(start, finish);     // <stl_construct.h>
    destroy_map_and_nodes();
  }

  deque& operator= (const deque& x)
  {
    // 其实我觉得把这个操作放在if内效率更高
    const size_type len = size();
    if (&x != this) {
      // 当前容器比x容器拥有元素多, 析构多余元素
      if (len >= x.size())
        erase(copy(x.begin(), x.end(), start), finish);
      // 将x所有超出部分的元素使用insert()追加进去
      else {
        const_iterator mid = x.begin() + difference_type(len);
        copy(x.begin(), mid, start);
        insert(finish, mid, x.end());
      }
    }
    return *this;
  }

  // 其实要交换两个容器, 只需要交换其内部维护的指针即可^_^
  void swap(deque& x)
  {
    __STD::swap(start, x.start);
    __STD::swap(finish, x.finish);
    __STD::swap(map, x.map);
    __STD::swap(map_size, x.map_size);
  }

public:                         // push_* and pop_*

  void push_back(const value_type& t)
  {
    // STL使用前闭后开的区间, 所以如果还有剩余容量,
    // 则直接在finish.cur上构造对象即可, 然后更新迭代器
    if (finish.cur != finish.last - 1) {
      construct(finish.cur, t);
      ++finish.cur;
    }
    // 容量已满就要新申请内存了
    else
      push_back_aux(t);
  }

  void push_front(const value_type& t)
  {
    if (start.cur != start.first) {
      construct(start.cur - 1, t);
      --start.cur;
    }
    else
      push_front_aux(t);
  }

  void pop_back()
  {
    if (finish.cur != finish.first) {
      --finish.cur;
      destroy(finish.cur);
    }
    else
      pop_back_aux();
  }

  void pop_front() {
    if (start.cur != start.last - 1)
    {
      destroy(start.cur);
      ++start.cur;
    }
    else
      pop_front_aux();
  }

public:                         // Insert

////////////////////////////////////////////////////////////////////////////////
// 在指定位置前插入元素
////////////////////////////////////////////////////////////////////////////////
//             insert(iterator position, const value_type& x)
//                                   |
//                                   |---------------- 判断插入位置
//                                   |
//               -----------------------------------------------
// deque.begin() |          deque.emd() |                      |
//               |                      |                      |
//               ↓                      ↓                      |
//         push_front(x);         push_back(x);                |
//                                                             ↓
//                                                 insert_aux(position, x);
//                                                 具体剖析见后面实现
////////////////////////////////////////////////////////////////////////////////

  iterator insert(iterator position, const value_type& x)
  {
    // 如果是在deque的最前端插入, 那么直接push_front()即可
    if (position.cur == start.cur) {
      push_front(x);
      return start;
    }
    // 如果是在deque的末尾插入, 直接调用push_back()
    else if (position.cur == finish.cur) {
      push_back(x);
      iterator tmp = finish;
      --tmp;
      return tmp;
    }
    else {
      return insert_aux(position, x);
    }
  }

  iterator insert(iterator position) { return insert(position, value_type()); }

  // 详解见实现部分
  void insert(iterator pos, size_type n, const value_type& x);

  void insert(iterator pos, int n, const value_type& x)
  {
    insert(pos, (size_type) n, x);
  }
  void insert(iterator pos, long n, const value_type& x)
  {
    insert(pos, (size_type) n, x);
  }

#ifdef __STL_MEMBER_TEMPLATES

  template <class InputIterator>
  void insert(iterator pos, InputIterator first, InputIterator last)
  {
    insert(pos, first, last, iterator_category(first));
  }

#else /* __STL_MEMBER_TEMPLATES */

  void insert(iterator pos, const value_type* first, const value_type* last);
  void insert(iterator pos, const_iterator first, const_iterator last);

#endif /* __STL_MEMBER_TEMPLATES */

  // 如果new_size < size(), 那么就析构掉多余的元素,
  // 否则以x为蓝本进行剩余元素的填充
  void resize(size_type new_size, const value_type& x)
  {
    const size_type len = size();
    if (new_size < len)
      erase(start + new_size, finish);
    else
      insert(finish, new_size - len, x);
  }

  void resize(size_type new_size) { resize(new_size, value_type()); }

public:                         // Erase

  iterator erase(iterator pos)
  {
    iterator next = pos;
    ++next;

    // 计算待擦除点前的元素个数
    difference_type index = pos - start;

    // 判断待擦除结点前后元素的个数, 哪部分少就移动哪部分
    if (index < (size() >> 1))
    {
      // 前面部分的元素少
      copy_backward(start, pos, next);  // <stl_algobase.h>
      pop_front();
    }
    // 后面部分的元素少
    else {
      copy(next, finish, pos);          // <stl_algobase.h>
      pop_back();
    }
    return start + index;
  }

  // 详解见实现部分
  iterator erase(iterator first, iterator last);
  void clear();

protected:                        // Internal construction/destruction

  // 详解见实现部分
  void create_map_and_nodes(size_type num_elements);
  void destroy_map_and_nodes();
  void fill_initialize(size_type n, const value_type& value);

#ifdef __STL_MEMBER_TEMPLATES

  template <class InputIterator>
  void range_initialize(InputIterator first, InputIterator last,
                        input_iterator_tag);

  template <class ForwardIterator>
  void range_initialize(ForwardIterator first, ForwardIterator last,
                        forward_iterator_tag);

#endif /* __STL_MEMBER_TEMPLATES */

protected:                        // Internal push_* and pop_*

  // 详解见实现部分
  void push_back_aux(const value_type& t);
  void push_front_aux(const value_type& t);
  void pop_back_aux();
  void pop_front_aux();

protected:                        // Internal insert functions

#ifdef __STL_MEMBER_TEMPLATES

  template <class InputIterator>
  void insert(iterator pos, InputIterator first, InputIterator last,
              input_iterator_tag);

  template <class ForwardIterator>
  void insert(iterator pos, ForwardIterator first, ForwardIterator last,
              forward_iterator_tag);

#endif /* __STL_MEMBER_TEMPLATES */

  iterator insert_aux(iterator pos, const value_type& x);
  void insert_aux(iterator pos, size_type n, const value_type& x);

#ifdef __STL_MEMBER_TEMPLATES

  template <class ForwardIterator>
  void insert_aux(iterator pos, ForwardIterator first, ForwardIterator last,
                  size_type n);

#else /* __STL_MEMBER_TEMPLATES */

  void insert_aux(iterator pos,
                  const value_type* first, const value_type* last,
                  size_type n);

  void insert_aux(iterator pos, const_iterator first, const_iterator last,
                  size_type n);

#endif /* __STL_MEMBER_TEMPLATES */

  // 在起始缓冲区预留大小为n的空间
  // 如果缓冲区不足则重新分配
  iterator reserve_elements_at_front(size_type n)
  {
    size_type vacancies = start.cur - start.first;
    if (n > vacancies)
      new_elements_at_front(n - vacancies);
    return start - difference_type(n);
  }

  iterator reserve_elements_at_back(size_type n)
  {
    size_type vacancies = (finish.last - finish.cur) - 1;
    if (n > vacancies)
      new_elements_at_back(n - vacancies);
    return finish + difference_type(n);
  }

  void new_elements_at_front(size_type new_elements);
  void new_elements_at_back(size_type new_elements);

  void destroy_nodes_at_front(iterator before_start);
  void destroy_nodes_at_back(iterator after_finish);

protected:                      // Allocation of map and nodes

  // Makes sure the map has space for new nodes.  Does not actually
  //  add the nodes.  Can invalidate map pointers.  (And consequently,
  //  deque iterators.)

  void reserve_map_at_back (size_type nodes_to_add = 1)
  {
    if (nodes_to_add + 1 > map_size - (finish.node - map))
      reallocate_map(nodes_to_add, false);
  }

  void reserve_map_at_front (size_type nodes_to_add = 1)
  {
    if (nodes_to_add > start.node - map)
      reallocate_map(nodes_to_add, true);
  }

  void reallocate_map(size_type nodes_to_add, bool add_at_front);

  // 分配内存, 不进行构造
  pointer allocate_node() { return data_allocator::allocate(buffer_size()); }

  // 释放内存, 不进行析构
  void deallocate_node(pointer n)
  {
    data_allocator::deallocate(n, buffer_size());
  }

#ifdef __STL_NON_TYPE_TMPL_PARAM_BUG
public:
  bool operator==(const deque<T, Alloc, 0>& x) const {
    return size() == x.size() && equal(begin(), end(), x.begin());
  }
  bool operator!=(const deque<T, Alloc, 0>& x) const {
    return size() != x.size() || !equal(begin(), end(), x.begin());
  }
  bool operator<(const deque<T, Alloc, 0>& x) const {
    return lexicographical_compare(begin(), end(), x.begin(), x.end());
  }
#endif /* __STL_NON_TYPE_TMPL_PARAM_BUG */
};

////////////////////////////////////////////////////////////////////////////////
// 不进行内联的成员函数
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// 在指定位置前插入n个值为x的元素
////////////////////////////////////////////////////////////////////////////////
//           insert(iterator pos, size_type n, const value_type& x)
//                                   |
//                                   |---------------- 判断插入位置
//                                   |
//               ---------------------------------------------------------
// deque.begin() |                    deque.end() |                      |
//               |                                |                      |
//               ↓                                |                      |
// reserve_elements_at_front(n);                  |                      |
// uninitialized_fill(new_start, start, x);       |                      |
//                                                ↓                      |
//                          reserve_elements_at_back(n);                 |
//                          uninitialized_fill(finish, new_finish, x);   |
//                                                                       ↓
//                                                       insert_aux(pos, n, x);
//                                                       剖析见后面实现
////////////////////////////////////////////////////////////////////////////////

template <class T, class Alloc, size_t BufSize>
void deque<T, Alloc, BufSize>::insert(iterator pos,
                                      size_type n, const value_type& x)
{
  if (pos.cur == start.cur) {
    iterator new_start = reserve_elements_at_front(n);
    uninitialized_fill(new_start, start, x);
    start = new_start;
  }
  else if (pos.cur == finish.cur) {
    iterator new_finish = reserve_elements_at_back(n);
    uninitialized_fill(finish, new_finish, x);
    finish = new_finish;
  }
  else
    insert_aux(pos, n, x);
}

// 给不支持成员函数模板的编译器提供支持函数
#ifndef __STL_MEMBER_TEMPLATES

template <class T, class Alloc, size_t BufSize>
void deque<T, Alloc, BufSize>::insert(iterator pos,
                                      const value_type* first,
                                      const value_type* last) {
  size_type n = last - first;
  if (pos.cur == start.cur) {
    iterator new_start = reserve_elements_at_front(n);
    __STL_TRY {
      uninitialized_copy(first, last, new_start);
      start = new_start;
    }
    __STL_UNWIND(destroy_nodes_at_front(new_start));
  }
  else if (pos.cur == finish.cur) {
    iterator new_finish = reserve_elements_at_back(n);
    __STL_TRY {
      uninitialized_copy(first, last, finish);
      finish = new_finish;
    }
    __STL_UNWIND(destroy_nodes_at_back(new_finish));
  }
  else
    insert_aux(pos, first, last, n);
}

template <class T, class Alloc, size_t BufSize>
void deque<T, Alloc, BufSize>::insert(iterator pos,
                                      const_iterator first,
                                      const_iterator last)
{
  size_type n = last - first;
  if (pos.cur == start.cur) {
    iterator new_start = reserve_elements_at_front(n);
    __STL_TRY {
      uninitialized_copy(first, last, new_start);
      start = new_start;
    }
    __STL_UNWIND(destroy_nodes_at_front(new_start));
  }
  else if (pos.cur == finish.cur) {
    iterator new_finish = reserve_elements_at_back(n);
    __STL_TRY {
      uninitialized_copy(first, last, finish);
      finish = new_finish;
    }
    __STL_UNWIND(destroy_nodes_at_back(new_finish));
  }
  else
    insert_aux(pos, first, last, n);
}

#endif /* __STL_MEMBER_TEMPLATES */

////////////////////////////////////////////////////////////////////////////////
// 擦除[first, last)区间的元素
////////////////////////////////////////////////////////////////////////////////
//                  erase(iterator first, iterator last)
//                                   |
//                                   |---------------- 是否要删除整个区间?
//                                   |
//               ------------------------------------------
//           Yes |                                        | No
//               |                                        |
//               ↓                                        | --- 判断哪侧元素少
//            clear();                                    ↓
//       -----------------------------------------------------------------
// 左侧少 |                                                         右侧少 |
//       |                                                               |
//       ↓                                                               ↓
//   copy_backward(start, first, last);            copy(last, finish, first);
//   new_start = start + n;                        new_finish = finish - n;
//   析构多余的元素                                  析构多余的元素
//   destroy(start, new_start);                    destroy(new_finish, finish);
//   释放多余内存空间                                释放多余内存空间
//   for (...)                                     for (...)
//      ...                                             ...
//   更新map状态                                    更新map状态
////////////////////////////////////////////////////////////////////////////////
template <class T, class Alloc, size_t BufSize>
deque<T, Alloc, BufSize>::iterator
deque<T, Alloc, BufSize>::erase(iterator first, iterator last)
{
  if (first == start && last == finish) {
    clear();
    return finish;
  }
  else {
    difference_type n = last - first;
    difference_type elems_before = first - start;
    if (elems_before < (size() - n) / 2) {
      copy_backward(start, first, last);
      iterator new_start = start + n;
      destroy(start, new_start);
      for (map_pointer cur = start.node; cur < new_start.node; ++cur)
        data_allocator::deallocate(*cur, buffer_size());
      start = new_start;
    }
    else {
      copy(last, finish, first);
      iterator new_finish = finish - n;
      destroy(new_finish, finish);
      for (map_pointer cur = new_finish.node + 1; cur <= finish.node; ++cur)
        data_allocator::deallocate(*cur, buffer_size());
      finish = new_finish;
    }
    return start + elems_before;
  }
}

template <class T, class Alloc, size_t BufSize>
void deque<T, Alloc, BufSize>::clear()
{
  // 首先析构除起点和终点的所有元素, 并释放相应空间
  for (map_pointer node = start.node + 1; node < finish.node; ++node) {
    destroy(*node, *node + buffer_size());
    data_allocator::deallocate(*node, buffer_size());
  }

  // 如果deque本身不为空, 析构所有对象, 并释放掉结尾的内存
  if (start.node != finish.node) {
    destroy(start.cur, start.last);
    destroy(finish.first, finish.cur);
    data_allocator::deallocate(finish.first, buffer_size());
  }
  // 析构所有元素, 但是不释放空间, 因为deque要满足这个前置条件
  // 具体的细节见本文件开头'特性'
  else
    destroy(start.cur, finish.cur);

  finish = start;
}

// 创建内部使用的map
template <class T, class Alloc, size_t BufSize>
void deque<T, Alloc, BufSize>::create_map_and_nodes(size_type num_elements)
{
  // 需要的结点数, 元素个数 / 每个缓冲区能容纳的元素数 + 1
  size_type num_nodes = num_elements / buffer_size() + 1;

  // map要维护的结点, 这里最小的值为8, 见initial_map_size()
  map_size = max(initial_map_size(), num_nodes + 2);
  map = map_allocator::allocate(map_size);

  // 将[nstart, nfinish)区间设置在map的中间,
  // 这样就能保证前后增长而尽可能减少map的重新分配次数
  map_pointer nstart = map + (map_size - num_nodes) / 2;
  map_pointer nfinish = nstart + num_nodes - 1;

  // 分配结点空间
  map_pointer cur;
  __STL_TRY {
    for (cur = nstart; cur <= nfinish; ++cur)
      *cur = allocate_node();
  }
#     ifdef  __STL_USE_EXCEPTIONS
  catch(...) {
    for (map_pointer n = nstart; n < cur; ++n)
      deallocate_node(*n);
    map_allocator::deallocate(map, map_size);
    throw;
  }
#     endif /* __STL_USE_EXCEPTIONS */

  // 维护指针状态
  start.set_node(nstart);
  finish.set_node(nfinish);
  start.cur = start.first;
  finish.cur = finish.first + num_elements % buffer_size();
}

// This is only used as a cleanup function in catch clauses.
template <class T, class Alloc, size_t BufSize>
void deque<T, Alloc, BufSize>::destroy_map_and_nodes()
{
  for (map_pointer cur = start.node; cur <= finish.node; ++cur)
    deallocate_node(*cur);
  map_allocator::deallocate(map, map_size);
}

// 分配n个结点, 并以value为蓝本初始化
template <class T, class Alloc, size_t BufSize>
void deque<T, Alloc, BufSize>::fill_initialize(size_type n,
                                               const value_type& value)
{
  create_map_and_nodes(n);
  map_pointer cur;
  __STL_TRY {
    for (cur = start.node; cur < finish.node; ++cur)
      uninitialized_fill(*cur, *cur + buffer_size(), value);
    uninitialized_fill(finish.first, finish.cur, value);
  }
#       ifdef __STL_USE_EXCEPTIONS
  catch(...) {
    for (map_pointer n = start.node; n < cur; ++n)
      destroy(*n, *n + buffer_size());
    destroy_map_and_nodes();
    throw;
  }
#       endif /* __STL_USE_EXCEPTIONS */
}


#ifdef __STL_MEMBER_TEMPLATES

template <class T, class Alloc, size_t BufSize>
template <class InputIterator>
void deque<T, Alloc, BufSize>::range_initialize(InputIterator first,
                                                InputIterator last,
                                                input_iterator_tag) {
  create_map_and_nodes(0);
  for ( ; first != last; ++first)
    push_back(*first);
}

template <class T, class Alloc, size_t BufSize>
template <class ForwardIterator>
void deque<T, Alloc, BufSize>::range_initialize(ForwardIterator first,
                                                ForwardIterator last,
                                                forward_iterator_tag) {
  size_type n = 0;
  distance(first, last, n);
  create_map_and_nodes(n);
  __STL_TRY {
    uninitialized_copy(first, last, start);
  }
  __STL_UNWIND(destroy_map_and_nodes());
}

#endif /* __STL_MEMBER_TEMPLATES */

// 仅当finish.cur == finish.last - 1才调用
// 即最后一个缓冲区没有空间才调用
template <class T, class Alloc, size_t BufSize>
void deque<T, Alloc, BufSize>::push_back_aux(const value_type& t)
{
  value_type t_copy = t;
  reserve_map_at_back();
  *(finish.node + 1) = allocate_node();
  __STL_TRY {
    construct(finish.cur, t_copy);
    finish.set_node(finish.node + 1);
    finish.cur = finish.first;
  }
  __STL_UNWIND(deallocate_node(*(finish.node + 1)));
}

// Called only if start.cur == start.first.
template <class T, class Alloc, size_t BufSize>
void deque<T, Alloc, BufSize>::push_front_aux(const value_type& t)
{
  value_type t_copy = t;
  reserve_map_at_front();
  *(start.node - 1) = allocate_node();
  __STL_TRY {
    start.set_node(start.node - 1);
    start.cur = start.last - 1;
    construct(start.cur, t_copy);
  }
#     ifdef __STL_USE_EXCEPTIONS
  catch(...) {
    start.set_node(start.node + 1);
    start.cur = start.first;
    deallocate_node(*(start.node - 1));
    throw;
  }
#     endif /* __STL_USE_EXCEPTIONS */
}

// Called only if finish.cur == finish.first.
template <class T, class Alloc, size_t BufSize>
void deque<T, Alloc, BufSize>:: pop_back_aux()
{
  deallocate_node(finish.first);
  finish.set_node(finish.node - 1);
  finish.cur = finish.last - 1;
  destroy(finish.cur);
}

// Called only if start.cur == start.last - 1.  Note that if the deque
//  has at least one element (a necessary precondition for this member
//  function), and if start.cur == start.last, then the deque must have
//  at least two nodes.
template <class T, class Alloc, size_t BufSize>
void deque<T, Alloc, BufSize>::pop_front_aux()
{
  destroy(start.cur);
  deallocate_node(start.first);
  start.set_node(start.node + 1);
  start.cur = start.first;
}

#ifdef __STL_MEMBER_TEMPLATES

// 将[first, last)区间元素插入到pos前

template <class T, class Alloc, size_t BufSize>
template <class InputIterator>
void deque<T, Alloc, BufSize>::insert(iterator pos,
                                      InputIterator first, InputIterator last,
                                      input_iterator_tag)
{
  // 由于是Input Iterator, 则使用通用的inserter完成插入操作
  copy(first, last, inserter(*this, pos));
}


template <class T, class Alloc, size_t BufSize>
template <class ForwardIterator>
void deque<T, Alloc, BufSize>::insert(iterator pos,
                                      ForwardIterator first,
                                      ForwardIterator last,
                                      forward_iterator_tag)
{
  size_type n = 0;
  distance(first, last, n);
  if (pos.cur == start.cur) {
    iterator new_start = reserve_elements_at_front(n);
    __STL_TRY {
      uninitialized_copy(first, last, new_start);
      start = new_start;
    }
    __STL_UNWIND(destroy_nodes_at_front(new_start));
  }
  else if (pos.cur == finish.cur) {
    iterator new_finish = reserve_elements_at_back(n);
    __STL_TRY {
      uninitialized_copy(first, last, finish);
      finish = new_finish;
    }
    __STL_UNWIND(destroy_nodes_at_back(new_finish));
  }
  else
    insert_aux(pos, first, last, n);
}

#endif /* __STL_MEMBER_TEMPLATES */

////////////////////////////////////////////////////////////////////////////////
// 在指定位置前插入元素
////////////////////////////////////////////////////////////////////////////////
//              insert_aux(iterator pos, const value_type& x)
//                                   |
//                                   |----------- 判断pos前端元素少还是后端元素少
//                                   |
//               -----------------------------------------------
//         前端少 |                                       后端少 |
//               |                                             |
//               ↓                                             |
//           进行相关操作                                   进行相关操作
////////////////////////////////////////////////////////////////////////////////
// 下面以pos前面元素少的情形进行说明, 为了简化, 假设操作不会超过一个缓冲区区间
//
// 插入前状态
//           start            pos                                 end
//             ↓               ↓                                   ↓
// ---------------------------------------------------------------------
// |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   | X |
// ---------------------------------------------------------------------
//
// 需要进行操作的区间
//                需要拷贝的区间
//                 -------------
//       start     |           |                                  end
//         ↓       ↓           ↓                                   ↓
// ---------------------------------------------------------------------
// |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   | X |
// ---------------------------------------------------------------------
//             ↑   ↑       ↑   ↑
//        front1   |       |   |
//                 |       |   |
//            front2       |   |
//                         |   |
//                       pos   |
//                             |
//                          pos1
// 拷贝操作完成后
//
//         这是[front2, pos1)
//             ------------- --------- 这里是给待插入元素预留的空间
//       start |           | |                                    end
//         ↓   ↓           ↓ ↓                                     ↓
// ---------------------------------------------------------------------
// |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   | X |
// ---------------------------------------------------------------------
//         ↑
//   这里存储的是原来的front()
//
////////////////////////////////////////////////////////////////////////////////

template <class T, class Alloc, size_t BufSize>
typename deque<T, Alloc, BufSize>::iterator
deque<T, Alloc, BufSize>::insert_aux(iterator pos, const value_type& x)
{
  difference_type index = pos - start;
  value_type x_copy = x;

  // 前面的时候用的移位操作, 这里怎么不用了呢^_^?
  if (index < size() / 2) {
    push_front(front());
    iterator front1 = start;
    ++front1;
    iterator front2 = front1;
    ++front2;
    pos = start + index;
    iterator pos1 = pos;
    ++pos1;
    copy(front2, pos1, front1);
  }
  else {
    push_back(back());
    iterator back1 = finish;
    --back1;
    iterator back2 = back1;
    --back2;
    pos = start + index;
    copy_backward(pos, back2, back1);
  }
  *pos = x_copy;
  return pos;
}

////////////////////////////////////////////////////////////////////////////////
// 在pos前插入n个值为x的元素
////////////////////////////////////////////////////////////////////////////////
//         insert_aux(iterator pos, size_type n, const value_type& x)
//                                   ↓
//                      elems_before = pos - start;
//                            length = size();
//                                   |
//                                   |---------- elems_before < length / 2 ?
//                                   |           判断哪侧元素少, 就对哪侧进行操作
//               ---------------------------------------
//           Yes |                                     |  No
//               |                                     |
//               ↓                                     ↓
// reserve_elements_at_front(n);          reserve_elements_at_back(n);
// 根据具体情况进行元素的拷贝操作             根据具体情况进行元素的拷贝操作
////////////////////////////////////////////////////////////////////////////////

template <class T, class Alloc, size_t BufSize>
void deque<T, Alloc, BufSize>::insert_aux(iterator pos,
                                          size_type n, const value_type& x)
{
  const difference_type elems_before = pos - start;
  size_type length = size();
  value_type x_copy = x;
  if (elems_before < length / 2) {
    iterator new_start = reserve_elements_at_front(n);
    iterator old_start = start;
    pos = start + elems_before;
    __STL_TRY {
      if (elems_before >= difference_type(n)) {
        iterator start_n = start + difference_type(n);
        uninitialized_copy(start, start_n, new_start);
        start = new_start;
        copy(start_n, pos, old_start);
        fill(pos - difference_type(n), pos, x_copy);
      }
      else {
        __uninitialized_copy_fill(start, pos, new_start, start, x_copy);
        start = new_start;
        fill(old_start, pos, x_copy);
      }
    }
    __STL_UNWIND(destroy_nodes_at_front(new_start));
  }
  else {
    iterator new_finish = reserve_elements_at_back(n);
    iterator old_finish = finish;
    const difference_type elems_after = difference_type(length) - elems_before;
    pos = finish - elems_after;
    __STL_TRY {
      if (elems_after > difference_type(n)) {
        iterator finish_n = finish - difference_type(n);
        uninitialized_copy(finish_n, finish, finish);
        finish = new_finish;
        copy_backward(pos, finish_n, old_finish);
        fill(pos, pos + difference_type(n), x_copy);
      }
      else {
        __uninitialized_fill_copy(finish, pos + difference_type(n),
                                  x_copy,
                                  pos, finish);
        finish = new_finish;
        fill(pos, old_finish, x_copy);
      }
    }
    __STL_UNWIND(destroy_nodes_at_back(new_finish));
  }
}

#ifdef __STL_MEMBER_TEMPLATES

// 供给insert(iterator pos, ForwardIterator first, ForwardIterator last,)
// 处理通用情况
template <class T, class Alloc, size_t BufSize>
template <class ForwardIterator>
void deque<T, Alloc, BufSize>::insert_aux(iterator pos,
                                          ForwardIterator first,
                                          ForwardIterator last,
                                          size_type n)
{
  const difference_type elems_before = pos - start;
  size_type length = size();
  if (elems_before < length / 2) {
    iterator new_start = reserve_elements_at_front(n);
    iterator old_start = start;
    pos = start + elems_before;
    __STL_TRY {
      if (elems_before >= difference_type(n)) {
        iterator start_n = start + difference_type(n);
        uninitialized_copy(start, start_n, new_start);
        start = new_start;
        copy(start_n, pos, old_start);
        copy(first, last, pos - difference_type(n));
      }
      else {
        ForwardIterator mid = first;
        advance(mid, difference_type(n) - elems_before);
        __uninitialized_copy_copy(start, pos, first, mid, new_start);
        start = new_start;
        copy(mid, last, old_start);
      }
    }
    __STL_UNWIND(destroy_nodes_at_front(new_start));
  }
  else {
    iterator new_finish = reserve_elements_at_back(n);
    iterator old_finish = finish;
    const difference_type elems_after = difference_type(length) - elems_before;
    pos = finish - elems_after;
    __STL_TRY {
      if (elems_after > difference_type(n)) {
        iterator finish_n = finish - difference_type(n);
        uninitialized_copy(finish_n, finish, finish);
        finish = new_finish;
        copy_backward(pos, finish_n, old_finish);
        copy(first, last, pos);
      }
      else {
        ForwardIterator mid = first;
        advance(mid, elems_after);
        __uninitialized_copy_copy(mid, last, pos, finish, finish);
        finish = new_finish;
        copy(first, mid, pos);
      }
    }
    __STL_UNWIND(destroy_nodes_at_back(new_finish));
  }
}

#else /* __STL_MEMBER_TEMPLATES */

template <class T, class Alloc, size_t BufSize>
void deque<T, Alloc, BufSize>::insert_aux(iterator pos,
                                          const value_type* first,
                                          const value_type* last,
                                          size_type n)
{
  const difference_type elems_before = pos - start;
  size_type length = size();
  if (elems_before < length / 2) {
    iterator new_start = reserve_elements_at_front(n);
    iterator old_start = start;
    pos = start + elems_before;
    __STL_TRY {
      if (elems_before >= difference_type(n)) {
        iterator start_n = start + difference_type(n);
        uninitialized_copy(start, start_n, new_start);
        start = new_start;
        copy(start_n, pos, old_start);
        copy(first, last, pos - difference_type(n));
      }
      else {
        const value_type* mid = first + (difference_type(n) - elems_before);
        __uninitialized_copy_copy(start, pos, first, mid, new_start);
        start = new_start;
        copy(mid, last, old_start);
      }
    }
    __STL_UNWIND(destroy_nodes_at_front(new_start));
  }
  else {
    iterator new_finish = reserve_elements_at_back(n);
    iterator old_finish = finish;
    const difference_type elems_after = difference_type(length) - elems_before;
    pos = finish - elems_after;
    __STL_TRY {
      if (elems_after > difference_type(n)) {
        iterator finish_n = finish - difference_type(n);
        uninitialized_copy(finish_n, finish, finish);
        finish = new_finish;
        copy_backward(pos, finish_n, old_finish);
        copy(first, last, pos);
      }
      else {
        const value_type* mid = first + elems_after;
        __uninitialized_copy_copy(mid, last, pos, finish, finish);
        finish = new_finish;
        copy(first, mid, pos);
      }
    }
    __STL_UNWIND(destroy_nodes_at_back(new_finish));
  }
}

template <class T, class Alloc, size_t BufSize>
void deque<T, Alloc, BufSize>::insert_aux(iterator pos,
                                          const_iterator first,
                                          const_iterator last,
                                          size_type n)
{
  const difference_type elems_before = pos - start;
  size_type length = size();
  if (elems_before < length / 2) {
    iterator new_start = reserve_elements_at_front(n);
    iterator old_start = start;
    pos = start + elems_before;
    __STL_TRY {
      if (elems_before >= n) {
        iterator start_n = start + n;
        uninitialized_copy(start, start_n, new_start);
        start = new_start;
        copy(start_n, pos, old_start);
        copy(first, last, pos - difference_type(n));
      }
      else {
        const_iterator mid = first + (n - elems_before);
        __uninitialized_copy_copy(start, pos, first, mid, new_start);
        start = new_start;
        copy(mid, last, old_start);
      }
    }
    __STL_UNWIND(destroy_nodes_at_front(new_start));
  }
  else {
    iterator new_finish = reserve_elements_at_back(n);
    iterator old_finish = finish;
    const difference_type elems_after = length - elems_before;
    pos = finish - elems_after;
    __STL_TRY {
      if (elems_after > n) {
        iterator finish_n = finish - difference_type(n);
        uninitialized_copy(finish_n, finish, finish);
        finish = new_finish;
        copy_backward(pos, finish_n, old_finish);
        copy(first, last, pos);
      }
      else {
        const_iterator mid = first + elems_after;
        __uninitialized_copy_copy(mid, last, pos, finish, finish);
        finish = new_finish;
        copy(first, mid, pos);
      }
    }
    __STL_UNWIND(destroy_nodes_at_back(new_finish));
  }
}

#endif /* __STL_MEMBER_TEMPLATES */

// 在deque前端分配新结点
template <class T, class Alloc, size_t BufSize>
void deque<T, Alloc, BufSize>::new_elements_at_front(size_type new_elements)
{
  size_type new_nodes = (new_elements + buffer_size() - 1) / buffer_size();
  reserve_map_at_front(new_nodes);
  size_type i;
  __STL_TRY {
    for (i = 1; i <= new_nodes; ++i)
      *(start.node - i) = allocate_node();
  }
#       ifdef __STL_USE_EXCEPTIONS
  catch(...) {
    for (size_type j = 1; j < i; ++j)
      deallocate_node(*(start.node - j));
    throw;
  }
#       endif /* __STL_USE_EXCEPTIONS */
}

// 在deque末尾分配新结点
template <class T, class Alloc, size_t BufSize>
void deque<T, Alloc, BufSize>::new_elements_at_back(size_type new_elements) {
  size_type new_nodes = (new_elements + buffer_size() - 1) / buffer_size();
  reserve_map_at_back(new_nodes);
  size_type i;
  __STL_TRY {
    for (i = 1; i <= new_nodes; ++i)
      *(finish.node + i) = allocate_node();
  }
#       ifdef __STL_USE_EXCEPTIONS
  catch(...) {
    for (size_type j = 1; j < i; ++j)
      deallocate_node(*(finish.node + j));
    throw;
  }
#       endif /* __STL_USE_EXCEPTIONS */
}

// 释放[before_start.node, start.node)的结点
template <class T, class Alloc, size_t BufSize>
void deque<T, Alloc, BufSize>::destroy_nodes_at_front(iterator before_start)
{
  for (map_pointer n = before_start.node; n < start.node; ++n)
    deallocate_node(*n);
}

// 释放(finish.node, after_finish.node]的结点
template <class T, class Alloc, size_t BufSize>
void deque<T, Alloc, BufSize>::destroy_nodes_at_back(iterator after_finish)
{
  for (map_pointer n = after_finish.node; n > finish.node; --n)
    deallocate_node(*n);
}

// 重新配置map, 不会对缓冲区进行操作, map维护的是指向缓冲区的指针
template <class T, class Alloc, size_t BufSize>
void deque<T, Alloc, BufSize>::reallocate_map(size_type nodes_to_add,
                                              bool add_at_front)
{
  size_type old_num_nodes = finish.node - start.node + 1;
  size_type new_num_nodes = old_num_nodes + nodes_to_add;

  map_pointer new_nstart;
  if (map_size > 2 * new_num_nodes) {
    new_nstart = map + (map_size - new_num_nodes) / 2
                     + (add_at_front ? nodes_to_add : 0);
    if (new_nstart < start.node)
      copy(start.node, finish.node + 1, new_nstart);
    else
      copy_backward(start.node, finish.node + 1, new_nstart + old_num_nodes);
  }
  else {
    size_type new_map_size = map_size + max(map_size, nodes_to_add) + 2;

    map_pointer new_map = map_allocator::allocate(new_map_size);
    new_nstart = new_map + (new_map_size - new_num_nodes) / 2
                         + (add_at_front ? nodes_to_add : 0);
    copy(start.node, finish.node + 1, new_nstart);
    map_allocator::deallocate(map, map_size);

    map = new_map;
    map_size = new_map_size;
  }

  start.set_node(new_nstart);
  finish.set_node(new_nstart + old_num_nodes - 1);
}


// Nonmember functions.

#ifndef __STL_NON_TYPE_TMPL_PARAM_BUG

template <class T, class Alloc, size_t BufSiz>
bool operator==(const deque<T, Alloc, BufSiz>& x,
                const deque<T, Alloc, BufSiz>& y) {
  return x.size() == y.size() && equal(x.begin(), x.end(), y.begin());
}

template <class T, class Alloc, size_t BufSiz>
bool operator<(const deque<T, Alloc, BufSiz>& x,
               const deque<T, Alloc, BufSiz>& y) {
  return lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
}

#endif /* __STL_NON_TYPE_TMPL_PARAM_BUG */

#if defined(__STL_FUNCTION_TMPL_PARTIAL_ORDER) && \
    !defined(__STL_NON_TYPE_TMPL_PARAM_BUG)

template <class T, class Alloc, size_t BufSiz>
inline void swap(deque<T, Alloc, BufSiz>& x, deque<T, Alloc, BufSiz>& y) {
  x.swap(y);
}

#endif

#if defined(__sgi) && !defined(__GNUC__) && (_MIPS_SIM != _MIPS_SIM_ABI32)
#pragma reset woff 1174
#endif

__STL_END_NAMESPACE

#endif /* __SGI_STL_INTERNAL_DEQUE_H */

// Local Variables:
// mode:C++
// End: