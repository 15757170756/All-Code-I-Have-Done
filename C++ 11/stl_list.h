// Filename:    stl_list.h

// Comment By:  凝霜
// E-mail:      mdl2009@vip.qq.com
// Blog:        http://blog.csdn.net/mdl13412

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
 * Copyright (c) 1996,1997
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

#ifndef __SGI_STL_INTERNAL_LIST_H
#define __SGI_STL_INTERNAL_LIST_H

__STL_BEGIN_NAMESPACE

#if defined(__sgi) && !defined(__GNUC__) && (_MIPS_SIM != _MIPS_SIM_ABI32)
#pragma set woff 1174
#endif

////////////////////////////////////////////////////////////////////////////////
// list结点, 提供双向访问能力
////////////////////////////////////////////////////////////////////////////////
//  --------           --------           --------           --------
//  | next |---------->| next |---------->| next |---------->| next |
//  --------           --------           --------           --------
//  | prev |<----------| prev |<----------| prev |<----------| prev |
//  --------           --------           --------           --------
//  | data |           | data |           | data |           | data |
//  --------           --------           --------           --------
////////////////////////////////////////////////////////////////////////////////

template <class T>
struct __list_node
{
  typedef void* void_pointer;
  void_pointer next;
  void_pointer prev;
  T data;
};

// 至于为什么不使用默认参数, 这个是因为有一些编译器不能提供推导能力,
// 而作者又不想维护两份代码, 故不使用默认参数
template<class T, class Ref, class Ptr>
struct __list_iterator
{
  // 标记为'STL标准强制要求'的typedefs用于提供iterator_traits<I>支持
  typedef __list_iterator<T, T&, T*>             iterator;   // STL标准强制要求
  typedef __list_iterator<T, const T&, const T*> const_iterator;
  typedef __list_iterator<T, Ref, Ptr>           self;

  typedef bidirectional_iterator_tag iterator_category;
  typedef T value_type;                                 // STL标准强制要求
  typedef Ptr pointer;                                  // STL标准强制要求
  typedef Ref reference;                                // STL标准强制要求
  typedef __list_node<T>* link_type;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;                    // STL标准强制要求

  // 这个是迭代器实际管理的资源指针
  link_type node;

  __list_iterator(link_type x) : node(x) {}
  __list_iterator() {}
  __list_iterator(const iterator& x) : node(x.node) {}

  // 在STL算法中需要迭代器提供支持
  bool operator==(const self& x) const { return node == x.node; }
  bool operator!=(const self& x) const { return node != x.node; }

  // 重载operator *, 返回实际维护的数据
  reference operator*() const { return (*node).data; }

#ifndef __SGI_STL_NO_ARROW_OPERATOR
  // 如果支持'->'则重载之
  // 解释一下为什么要返回地址
  // class A
  // {
  // public:
  //    // ...
  //    void fun();
  //    // ...
  // }
  // __list_iterator<A, A&, A*> iter(new A)
  // iter->fun();
  // 这就相当于调用(iter.operator())->fun();
  // 经过重载使其行为和原生指针一致
  pointer operator->() const { return &(operator*()); }
#endif /* __SGI_STL_NO_ARROW_OPERATOR */

  // 前缀自加
  self& operator++()
  {
    node = (link_type)((*node).next);
    return *this;
  }

  // 后缀自加, 需要先产生自身的一个副本, 然会再对自身操作, 最后返回副本
  self operator++(int)
  {
    self tmp = *this;
    ++*this;
    return tmp;
  }

  self& operator--()
  {
    node = (link_type)((*node).prev);
    return *this;
  }

  self operator--(int)
  {
    self tmp = *this;
    --*this;
    return tmp;
  }
};

// 如果编译器支持模板类偏特化那么就不需要提供以下traits函数
// 直接使用<stl_iterator.h>中的
// template <class Iterator>
// struct iterator_traits
#ifndef __STL_CLASS_PARTIAL_SPECIALIZATION

template <class T, class Ref, class Ptr>
inline bidirectional_iterator_tag
iterator_category(const __list_iterator<T, Ref, Ptr>&) {
  return bidirectional_iterator_tag();
}

template <class T, class Ref, class Ptr>
inline T*
value_type(const __list_iterator<T, Ref, Ptr>&) {
  return 0;
}

template <class T, class Ref, class Ptr>
inline ptrdiff_t*
distance_type(const __list_iterator<T, Ref, Ptr>&) {
  return 0;
}

#endif /* __STL_CLASS_PARTIAL_SPECIALIZATION */

////////////////////////////////////////////////////////////////////////////////
// 链表本身成环, 且是双向链表, 这样计算begin()和end()是常数时间
////////////////////////////////////////////////////////////////////////////////
//       end()              头结点             begin()
//         ↓                  ↓                  ↓
//      --------           --------           --------           --------
// ---->| next |---------->| next |---------->| next |---------->| next |------
// |    --------           --------           --------           --------     |
// |  --| prev |<----------| prev |<----------| prev |<----------| prev |<--| |
// |  | --------           --------           --------           --------   | |
// |  | | data |           | data |           | data |           | data |   | |
// |  | --------           --------           --------           --------   | |
// |  |                                                                     | |
// |  | --------           --------           --------           --------   | |
// ---|-| next |<----------| next |<----------| next |<----------| next |<--|--
//    | --------           --------           --------           --------   |
//    ->| prev |---------->| prev |---------->| prev |---------->| prev |----
//      --------           --------           --------           --------
//      | data |           | data |           | data |           | data |
//      --------           --------           --------           --------
////////////////////////////////////////////////////////////////////////////////

// 默认allocator为alloc, 其具体使用版本请参照<stl_alloc.h>
template <class T, class Alloc = alloc>
class list
{
protected:
  typedef void* void_pointer;
  typedef __list_node<T> list_node;

  // 这个提供STL标准的allocator接口
  typedef simple_alloc<list_node, Alloc> list_node_allocator;

public:
  typedef T value_type;
  typedef value_type* pointer;
  typedef const value_type* const_pointer;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef list_node* link_type;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;

public:
  typedef __list_iterator<T, T&, T*>             iterator;
  typedef __list_iterator<T, const T&, const T*> const_iterator;

#ifdef __STL_CLASS_PARTIAL_SPECIALIZATION
  typedef reverse_iterator<const_iterator> const_reverse_iterator;
  typedef reverse_iterator<iterator> reverse_iterator;
#else /* __STL_CLASS_PARTIAL_SPECIALIZATION */
  typedef reverse_bidirectional_iterator<const_iterator, value_type,
  const_reference, difference_type>
  const_reverse_iterator;
  typedef reverse_bidirectional_iterator<iterator, value_type, reference,
  difference_type>
  reverse_iterator;
#endif /* __STL_CLASS_PARTIAL_SPECIALIZATION */

protected:
  // 分配一个新结点, 注意这里并不进行构造,
  // 构造交给全局的construct, 见<stl_stl_uninitialized.h>
  link_type get_node() { return list_node_allocator::allocate(); }

  // 释放指定结点, 不进行析构, 析构交给全局的destroy,
  // 见<stl_stl_uninitialized.h>
  void put_node(link_type p) { list_node_allocator::deallocate(p); }

  // 创建结点, 首先分配内存, 然后进行构造
  // 注: commit or rollback
  link_type create_node(const T& x)
  {
    link_type p = get_node();
    __STL_TRY {
      construct(&p->data, x);
    }
    __STL_UNWIND(put_node(p));
    return p;
  }

  // 析构结点元素, 并释放内存
  void destroy_node(link_type p)
  {
    destroy(&p->data);
    put_node(p);
  }

protected:
  // 用于空链表的建立
  void empty_initialize()
  {
    node = get_node();
    node->next = node;
    node->prev = node;
  }

  // 创建值为value共n个结点的链表
  // 注: commit or rollback
  void fill_initialize(size_type n, const T& value)
  {
    empty_initialize();
    __STL_TRY {
      // 此处插入操作时间复杂度O(1)
      insert(begin(), n, value);
    }
    __STL_UNWIND(clear(); put_node(node));
  }

// 以一个区间初始化链表
// 注: commit or rollback
#ifdef __STL_MEMBER_TEMPLATES
  template <class InputIterator>
  void range_initialize(InputIterator first, InputIterator last)
  {
    empty_initialize();
    __STL_TRY {
      insert(begin(), first, last);
    }
    __STL_UNWIND(clear(); put_node(node));
  }
#else  /* __STL_MEMBER_TEMPLATES */
  void range_initialize(const T* first, const T* last) {
    empty_initialize();
    __STL_TRY {
      insert(begin(), first, last);
    }
    __STL_UNWIND(clear(); put_node(node));
  }
  void range_initialize(const_iterator first, const_iterator last) {
    empty_initialize();
    __STL_TRY {
      insert(begin(), first, last);
    }
    __STL_UNWIND(clear(); put_node(node));
  }
#endif /* __STL_MEMBER_TEMPLATES */

protected:
  // 好吧, 这个是链表头结点, 其本身不保存数据
  link_type node;

public:
  list() { empty_initialize(); }

  iterator begin() { return (link_type)((*node).next); }
  const_iterator begin() const { return (link_type)((*node).next); }

  // 链表成环, 当指所以头节点也就是end
  iterator end() { return node; }
  const_iterator end() const { return node; }
  reverse_iterator rbegin() { return reverse_iterator(end()); }
  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(end());
  }
  reverse_iterator rend() { return reverse_iterator(begin()); }
  const_reverse_iterator rend() const {
    return const_reverse_iterator(begin());
  }

  // 头结点指向自身说明链表中无元素
  bool empty() const { return node->next == node; }

  // 使用全局函数distance()进行计算, 时间复杂度O(n)
  size_type size() const
  {
    size_type result = 0;
    distance(begin(), end(), result);
    return result;
  }

  size_type max_size() const { return size_type(-1); }
  reference front() { return *begin(); }
  const_reference front() const { return *begin(); }
  reference back() { return *(--end()); }
  const_reference back() const { return *(--end()); }
  void swap(list<T, Alloc>& x) { __STD::swap(node, x.node); }

////////////////////////////////////////////////////////////////////////////////
// 在指定位置插入元素
////////////////////////////////////////////////////////////////////////////////
//       insert(iterator position, const T& x)
//                       ↓
//                 create_node(x)
//                 p = get_node();-------->list_node_allocator::allocate();
//                 construct(&p->data, x);
//                       ↓
//            tmp->next = position.node;
//            tmp->prev = position.node->prev;
//            (link_type(position.node->prev))->next = tmp;
//            position.node->prev = tmp;
////////////////////////////////////////////////////////////////////////////////

  iterator insert(iterator position, const T& x)
  {
    link_type tmp = create_node(x);
    tmp->next = position.node;
    tmp->prev = position.node->prev;
    (link_type(position.node->prev))->next = tmp;
    position.node->prev = tmp;
    return tmp;
  }

  iterator insert(iterator position) { return insert(position, T()); }
#ifdef __STL_MEMBER_TEMPLATES
  template <class InputIterator>
  void insert(iterator position, InputIterator first, InputIterator last);
#else /* __STL_MEMBER_TEMPLATES */
  void insert(iterator position, const T* first, const T* last);
  void insert(iterator position,
              const_iterator first, const_iterator last);
#endif /* __STL_MEMBER_TEMPLATES */

  // 指定位置插入n个值为x的元素, 详细解析见实现部分
  void insert(iterator pos, size_type n, const T& x);
  void insert(iterator pos, int n, const T& x)
  {
    insert(pos, (size_type)n, x);
  }
  void insert(iterator pos, long n, const T& x)
  {
    insert(pos, (size_type)n, x);
  }

  // 在链表前端插入结点
  void push_front(const T& x) { insert(begin(), x); }
  // 在链表最后插入结点
  void push_back(const T& x) { insert(end(), x); }

  // 擦除指定结点
  iterator erase(iterator position)
  {
    link_type next_node = link_type(position.node->next);
    link_type prev_node = link_type(position.node->prev);
    prev_node->next = next_node;
    next_node->prev = prev_node;
    destroy_node(position.node);
    return iterator(next_node);
  }

  // 擦除一个区间的结点, 详细解析见实现部分
  iterator erase(iterator first, iterator last);

  void resize(size_type new_size, const T& x);
  void resize(size_type new_size) { resize(new_size, T()); }
  void clear();

  // 删除链表第一个结点
  void pop_front() { erase(begin()); }
  // 删除链表最后一个结点
  void pop_back()
  {
    iterator tmp = end();
    erase(--tmp);
  }

  list(size_type n, const T& value) { fill_initialize(n, value); }
  list(int n, const T& value) { fill_initialize(n, value); }
  list(long n, const T& value) { fill_initialize(n, value); }

  explicit list(size_type n) { fill_initialize(n, T()); }

// 以一个区间元素为蓝本创建链表
#ifdef __STL_MEMBER_TEMPLATES
  template <class InputIterator>
  list(InputIterator first, InputIterator last)
  {
    range_initialize(first, last);
  }

#else /* __STL_MEMBER_TEMPLATES */
  list(const T* first, const T* last) { range_initialize(first, last); }
  list(const_iterator first, const_iterator last) {
    range_initialize(first, last);
  }
#endif /* __STL_MEMBER_TEMPLATES */

  // 复制构造
  list(const list<T, Alloc>& x)
  {
    range_initialize(x.begin(), x.end());
  }

  ~list()
  {
    // 释放所有结点  // 使用全局函数distance()进行计算, 时间复杂度O(n)
  size_type size() const
  {
    size_type result = 0;
    distance(begin(), end(), result);
    return result;
  }
    clear();
    // 释放头结点
    put_node(node);
  }

  list<T, Alloc>& operator=(const list<T, Alloc>& x);

protected:

////////////////////////////////////////////////////////////////////////////////
// 将[first, last)区间插入到position
// 如果last == position, 则相当于链表不变化, 不进行操作
////////////////////////////////////////////////////////////////////////////////
// 初始状态
//                   first                             last
//                     ↓                                 ↓
//      --------   --------   --------     --------   --------   --------
//      | next |-->| next |-->| next |     | next |-->| next |-->| next |
//  ... --------   --------   -------- ... --------   --------   -------- ...
//      | prev |<--| prev |<--| prev |     | prev |<--| prev |<--| prev |
//      --------   --------   --------     --------   --------   --------
//
//                           position
//                               ↓
//      --------   --------   --------   --------   --------   --------
//      | next |-->| next |-->| next |-->| next |-->| next |-->| next |
//  ... --------   --------   --------   --------   --------   -------- ...
//      | prev |<--| prev |<--| prev |<--| prev |<--| prev |<--| prev |
//      --------   --------   --------   --------   --------   --------
//
// 操作完成后状态
//                           first
//                             |
//               --------------|--------------------------------------
//               | ------------|------------------------------------ |   last
//               | |           ↓                                   | |     ↓
//      -------- | |        --------   --------     --------       | |  --------   --------
//      | next |-- |  ----->| next |-->| next |     | next |-----  | -->| next |-->| next |
//  ... --------   |  |     --------   -------- ... --------    |  |    --------   -------- ...
//      | prev |<---  |  ---| prev |<--| prev |     | prev |<-- |  -----| prev |<--| prev |
//      --------      |  |  --------   --------     --------  | |       --------   --------
//                    |  |                                    | |
//                    |  ------                               | |
//                    ------- |  ------------------------------ |
//                          | |  |                              |
//                          | |  |  -----------------------------
//                          | |  |  |
//                          | |  |  |  position
//                          | |  |  |     ↓
//      --------   -------- | |  |  |  --------   --------   --------   --------
//      | next |-->| next |-- |  |  -->| next |-->| next |-->| next |-->| next |
//  ... --------   --------   |  |     --------   --------   --------   -------- ...
//      | prev |<--| prev |<---  ------| prev |<--| prev |<--| prev |<--| prev |
//      --------   --------            --------   --------   --------   --------
////////////////////////////////////////////////////////////////////////////////
  void transfer(iterator position, iterator first, iterator last)
  {
    if (position != last)
    {
      (*(link_type((*last.node).prev))).next = position.node;
      (*(link_type((*first.node).prev))).next = last.node;
      (*(link_type((*position.node).prev))).next = first.node;
      link_type tmp = link_type((*position.node).prev);
      (*position.node).prev = (*last.node).prev;
      (*last.node).prev = (*first.node).prev;
      (*first.node).prev = tmp;
    }
  }

public:
  // 将链表x移动到position之前
  void splice(iterator position, list& x)
  {
    if (!x.empty())
      transfer(position, x.begin(), x.end());
  }

  // 将链表中i指向的内容移动到position之前
  void splice(iterator position, list&, iterator i)
  {
    iterator j = i;
    ++j;
    if (position == i || position == j) return;
    transfer(position, i, j);
  }

  // 将[first, last}元素移动到position之前
  void splice(iterator position, list&, iterator first, iterator last)
  {
    if (first != last)
      transfer(position, first, last);
  }

  void remove(const T& value);
  void unique();
  void merge(list& x);
  void reverse();
  void sort();

#ifdef __STL_MEMBER_TEMPLATES
  template <class Predicate> void remove_if(Predicate);
  template <class BinaryPredicate> void unique(BinaryPredicate);
  template <class StrictWeakOrdering> void merge(list&, StrictWeakOrdering);
  template <class StrictWeakOrdering> void sort(StrictWeakOrdering);
#endif /* __STL_MEMBER_TEMPLATES */

  friend bool operator== __STL_NULL_TMPL_ARGS (const list& x, const list& y);
};

// 判断两个链表是否相等
template <class T, class Alloc>
inline bool operator==(const list<T,Alloc>& x, const list<T,Alloc>& y)
{
  typedef typename list<T,Alloc>::link_type link_type;
  link_type e1 = x.node;
  link_type e2 = y.node;
  link_type n1 = (link_type) e1->next;
  link_type n2 = (link_type) e2->next;
  for ( ; n1 != e1 && n2 != e2 ;
          n1 = (link_type) n1->next, n2 = (link_type) n2->next)
    if (n1->data != n2->data)
      return false;
  return n1 == e1 && n2 == e2;
}

// 链表比较大小使用的是字典顺序
template <class T, class Alloc>
inline bool operator<(const list<T, Alloc>& x, const list<T, Alloc>& y)
{
  return lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
}

// 如果编译器支持模板函数特化优先级
// 那么将全局的swap实现为使用list私有的swap以提高效率
#ifdef __STL_FUNCTION_TMPL_PARTIAL_ORDER

template <class T, class Alloc>
inline void swap(list<T, Alloc>& x, list<T, Alloc>& y)
{
  x.swap(y);
}

#endif /* __STL_FUNCTION_TMPL_PARTIAL_ORDER */

// 将[first, last)区间插入到position之前
#ifdef __STL_MEMBER_TEMPLATES

template <class T, class Alloc> template <class InputIterator>
void list<T, Alloc>::insert(iterator position,
                            InputIterator first, InputIterator last)
{
  for ( ; first != last; ++first)
    insert(position, *first);
}

#else /* __STL_MEMBER_TEMPLATES */

template <class T, class Alloc>
void list<T, Alloc>::insert(iterator position, const T* first, const T* last) {
  for ( ; first != last; ++first)
    insert(position, *first);
}

template <class T, class Alloc>
void list<T, Alloc>::insert(iterator position,
                            const_iterator first, const_iterator last) {
  for ( ; first != last; ++first)
    insert(position, *first);
}

#endif /* __STL_MEMBER_TEMPLATES */

// 在position前插入n个值为x的元素
template <class T, class Alloc>
void list<T, Alloc>::insert(iterator position, size_type n, const T& x)
{
  for ( ; n > 0; --n)
    insert(position, x);
}

// 擦除[first, last)间的结点
template <class T, class Alloc>
list<T,Alloc>::iterator list<T, Alloc>::erase(iterator first, iterator last)
{
  while (first != last) erase(first++);
  return last;
}

// 重新设置容量大小
// 如果当前容量小于新容量, 则新增加值为x的元素, 使容量增加至新指定大小
// 如果当前容量大于新容量, 则析构出来的元素
template <class T, class Alloc>
void list<T, Alloc>::resize(size_type new_size, const T& x)
{
  iterator i = begin();
  size_type len = 0;
  for ( ; i != end() && len < new_size; ++i, ++len)
    ;
  if (len == new_size)
    erase(i, end());
  else                          // i == end()
    insert(end(), new_size - len, x);
}

// 销毁所有结点, 将链表置空
template <class T, class Alloc>
void list<T, Alloc>::clear()
{
  link_type cur = (link_type) node->next;
  while (cur != node) {
    link_type tmp = cur;
    cur = (link_type) cur->next;
    destroy_node(tmp);
  }
  node->next = node;
  node->prev = node;
}

// 链表赋值操作
// 如果当前容器元素少于x容器, 则析构多余元素,
// 否则将调用insert插入x中剩余的元素
template <class T, class Alloc>
list<T, Alloc>& list<T, Alloc>::operator=(const list<T, Alloc>& x)
{
  if (this != &x) {
    iterator first1 = begin();
    iterator last1 = end();
    const_iterator first2 = x.begin();
    const_iterator last2 = x.end();
    while (first1 != last1 && first2 != last2) *first1++ = *first2++;
    if (first2 == last2)
      erase(first1, last1);
    else
      insert(last1, first2, last2);
  }
  return *this;
}

// 移除特定值的所有结点
// 时间复杂度O(n)
template <class T, class Alloc>
void list<T, Alloc>::remove(const T& value)
{
  iterator first = begin();
  iterator last = end();
  while (first != last) {
    iterator next = first;
    ++next;
    if (*first == value) erase(first);
    first = next;
  }
}

// 移除容器内所有的相邻的重复结点
// 时间复杂度O(n)
// 用户自定义数据类型需要提供operator ==()重载
template <class T, class Alloc>
void list<T, Alloc>::unique()
{
  iterator first = begin();
  iterator last = end();
  if (first == last) return;
  iterator next = first;
  while (++next != last) {
    if (*first == *next)
      erase(next);
    else
      first = next;
    next = first;
  }
}

// 假设当前容器和x都已序, 保证两容器合并后仍然有序
template <class T, class Alloc>
void list<T, Alloc>::merge(list<T, Alloc>& x)
{
  iterator first1 = begin();
  iterator last1 = end();
  iterator first2 = x.begin();
  iterator last2 = x.end();
  while (first1 != last1 && first2 != last2)
    if (*first2 < *first1) {
      iterator next = first2;
      transfer(first1, first2, ++next);
      first2 = next;
    }
    else
      ++first1;
  if (first2 != last2) transfer(last1, first2, last2);
}

// 将链表倒置
// 其算法核心是历遍链表, 每次取出一个结点, 并插入到链表起始点
// 历遍完成后链表满足倒置
template <class T, class Alloc>
void list<T, Alloc>::reverse()
{
  if (node->next == node || link_type(node->next)->next == node) return;
  iterator first = begin();
  ++first;
  while (first != end()) {
    iterator old = first;
    ++first;
    transfer(begin(), old, first);
  }
}

// 按照升序排序
template <class T, class Alloc>
void list<T, Alloc>::sort()
{
  if (node->next == node || link_type(node->next)->next == node) return;
  list<T, Alloc> carry;
  list<T, Alloc> counter[64];
  int fill = 0;
  while (!empty()) {
    carry.splice(carry.begin(), *this, begin());
    int i = 0;
    while(i < fill && !counter[i].empty()) {
      counter[i].merge(carry);
      carry.swap(counter[i++]);
    }
    carry.swap(counter[i]);
    if (i == fill) ++fill;
  }

  for (int i = 1; i < fill; ++i) counter[i].merge(counter[i-1]);
  swap(counter[fill-1]);
}

#ifdef __STL_MEMBER_TEMPLATES

// 给定一个仿函数, 如果仿函数值为真则进行相应元素的移除
template <class T, class Alloc> template <class Predicate>
void list<T, Alloc>::remove_if(Predicate pred)
{
  iterator first = begin();
  iterator last = end();
  while (first != last) {
    iterator next = first;
    ++next;
    if (pred(*first)) erase(first);
    first = next;
  }
}

// 根据仿函数, 决定如何移除相邻的重复结点
template <class T, class Alloc> template <class BinaryPredicate>
void list<T, Alloc>::unique(BinaryPredicate binary_pred)
{
  iterator first = begin();
  iterator last = end();
  if (first == last) return;
  iterator next = first;
  while (++next != last) {
    if (binary_pred(*first, *next))
      erase(next);
    else
      first = next;
    next = first;
  }
}

// 假设当前容器和x均已序, 将x合并到当前容器中, 并保证在comp仿函数
// 判定下仍然有序
template <class T, class Alloc> template <class StrictWeakOrdering>
void list<T, Alloc>::merge(list<T, Alloc>& x, StrictWeakOrdering comp)
{
  iterator first1 = begin();
  iterator last1 = end();
  iterator first2 = x.begin();
  iterator last2 = x.end();
  while (first1 != last1 && first2 != last2)
    if (comp(*first2, *first1)) {
      iterator next = first2;
      transfer(first1, first2, ++next);
      first2 = next;
    }
    else
      ++first1;
  if (first2 != last2) transfer(last1, first2, last2);
}

// 根据仿函数comp据定如何排序
template <class T, class Alloc> template <class StrictWeakOrdering>
void list<T, Alloc>::sort(StrictWeakOrdering comp)
{
  if (node->next == node || link_type(node->next)->next == node) return;
  list<T, Alloc> carry;
  list<T, Alloc> counter[64];
  int fill = 0;
  while (!empty()) {
    carry.splice(carry.begin(), *this, begin());
    int i = 0;
    while(i < fill && !counter[i].empty()) {
      counter[i].merge(carry, comp);
      carry.swap(counter[i++]);
    }
    carry.swap(counter[i]);
    if (i == fill) ++fill;
  }

  for (int i = 1; i < fill; ++i) counter[i].merge(counter[i-1], comp);
  swap(counter[fill-1]);
}

#endif /* __STL_MEMBER_TEMPLATES */

#if defined(__sgi) && !defined(__GNUC__) && (_MIPS_SIM != _MIPS_SIM_ABI32)
#pragma reset woff 1174
#endif

__STL_END_NAMESPACE

#endif /* __SGI_STL_INTERNAL_LIST_H */

// Local Variables:
// mode:C++
// End: