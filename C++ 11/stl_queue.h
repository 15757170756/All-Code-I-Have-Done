// Filename:    stl_queue.h

// Comment By:  凝霜
// E-mail:      mdl2009@vip.qq.com
// Blog:        http://blog.csdn.net/mdl13412

////////////////////////////////////////////////////////////////////////////////
// queue是一种先进先出(First In First Out, FIFO)的数据结构
// 它在前后有两个出口, 分别成为队头和队尾
// queue允许在队尾追加元素和访问队尾元素, 在队头获取和移除元素
// 除此之外其不支持其它元素的访问
////////////////////////////////////////////////////////////////////////////////
// 以下为使用deque时的布局
//
//               支持front()和pop()  支持back()和push()
//                      ↓                ↓
//                     队头,             队尾
//                      ↓                ↓
// ---------------------------------------------------------------------
// |   |   | ...... |   |   | ...... |   |   |   | ......  |   |   | X |
// ---------------------------------------------------------------------
// ↑                    ↑                    ↑                     ↑
// |                    |                    |                     |
// ----------------------                    -----------------------
// 这里是尚未使用的预留内存, 可能为0              这里是尚未使用的预留内存, 可能为0
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// priority_queue是一种允许用户以任何顺序将任何元素压入容器,
// 但是取出元素时一定是从最高优先级的元素开始取出
// 其默认使用的是vector作为容器, 默认的优先级比较使用less
// 其算法是使用binary-heap
////////////////////////////////////////////////////////////////////////////////
// 下面是其原理模型, 容器使用vector, 优先级比较决议用less
//
//                                       队尾, 支持push()
//                                              ↓
//                     --------------------------------------------------------
//  支持pop()和top()--->|   |   | ...... |   |   |   |   | ......  |   |   | X |
//                     --------------------------------------------------------
//                                 ↑                ↑                     ↑
//                                 |                -----------------------
//                          内部使用的是heap       这里是尚未使用的预留内存, 可能为0
////////////////////////////////////////////////////////////////////////////////
// 下面是容器使用vector, 优先级比较决议用less的情况下的一种实现技巧,
// 借用的是侯捷老师的例子, 本实作中使用的不是此技巧
//                                  [A]
//                                   |
//                   ---------------------------------
//                   |                               |
//                  [B]                             [C]
//                   |                               |
//        -----------------------         -----------------------
//        |                     |         |                     |
//       [D]                   [E]       [F]                   [G]
//        |                     |
//   -----------                |
//   |         |                |
//  [H]       [I]              [J]
//                                                vector中预留的内存, 了能为0
//                                                   ------------------
//                                                   ↓                ↓
// --------------------------------------------------------------------------
// | Not Use | A | B | C | D | E | F | G | H | I | J |   | ...... |   | end |
// --------------------------------------------------------------------------
//
// 具体算法请参看任意一本算法书, 如果没有, 扔了它:-)
////////////////////////////////////////////////////////////////////////////////

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

#ifndef __SGI_STL_INTERNAL_QUEUE_H
#define __SGI_STL_INTERNAL_QUEUE_H

__STL_BEGIN_NAMESPACE

// 如果编译器不能根据前面模板参数推导出后面使用的默认参数类型,
// 那么就需要手工指定, 本实作queue内部容器默认使用deque
// 由于queue要求在队尾追加元素, 在队头获取和移除元素
// 所以非常适合使用deque
#ifndef __STL_LIMITED_DEFAULT_TEMPLATES
template <class T, class Sequence = deque<T> >
#else
template <class T, class Sequence>
#endif
class queue
{
  // 讲解见<stl_pair.h>中的运算符剖析
  friend bool operator== __STL_NULL_TMPL_ARGS (const queue& x, const queue& y);
  friend bool operator< __STL_NULL_TMPL_ARGS (const queue& x, const queue& y);

public:
  // 由于queue仅支持对队头和队尾的操作, 所以不定义STL要求的
  // pointer, iterator, difference_type
  typedef typename Sequence::value_type value_type;
  typedef typename Sequence::size_type size_type;
  typedef typename Sequence::reference reference;
  typedef typename Sequence::const_reference const_reference;

protected:
  Sequence c;   // 这个是我们实际维护的容器

public:

  // 这些是STL queue的标准接口, 都调用容器的成员函数进行实现
  // 其接口和stack实现很接近, 参考<stl_stack.h>
  bool empty() const { return c.empty(); }
  size_type size() const { return c.size(); }
  reference front() { return c.front(); }
  const_reference front() const { return c.front(); }
  reference back() { return c.back(); }
  const_reference back() const { return c.back(); }
  void push(const value_type& x) { c.push_back(x); }
  void pop() { c.pop_front(); }
};

// 详细讲解见<stl_pair.h>
template <class T, class Sequence>
bool operator==(const queue<T, Sequence>& x, const queue<T, Sequence>& y)
{
  return x.c == y.c;
}

template <class T, class Sequence>
bool operator<(const queue<T, Sequence>& x, const queue<T, Sequence>& y)
{
  return x.c < y.c;
}

#ifndef __STL_LIMITED_DEFAULT_TEMPLATES
template <class T, class Sequence = vector<T>,
          class Compare = less<typename Sequence::value_type> >
#else
template <class T, class Sequence, class Compare>
#endif
class  priority_queue
{
public:
  typedef typename Sequence::value_type value_type;
  typedef typename Sequence::size_type size_type;
  typedef typename Sequence::reference reference;
  typedef typename Sequence::const_reference const_reference;

protected:
  Sequence c;           // 内部维护的容器
  Compare comp;         // 优先级决策判别式

public:
  priority_queue() : c() {}

  // 用户可以指定自己的优先级决策函数
  explicit priority_queue(const Compare& x) :  c(), comp(x) {}

// 使用[first, last)区间构造priority_queue
#ifdef __STL_MEMBER_TEMPLATES
  template <class InputIterator>
  priority_queue(InputIterator first, InputIterator last, const Compare& x)
    : c(first, last), comp(x) { make_heap(c.begin(), c.end(), comp); }
  template <class InputIterator>
  priority_queue(InputIterator first, InputIterator last)
    : c(first, last) { make_heap(c.begin(), c.end(), comp); }
#else /* __STL_MEMBER_TEMPLATES */
  priority_queue(const value_type* first, const value_type* last,
                 const Compare& x) : c(first, last), comp(x) {
    make_heap(c.begin(), c.end(), comp);
  }
  priority_queue(const value_type* first, const value_type* last)
    : c(first, last) { make_heap(c.begin(), c.end(), comp); }
#endif /* __STL_MEMBER_TEMPLATES */

  // STL priority_queue标准接口
  bool empty() const { return c.empty(); }
  size_type size() const { return c.size(); }

  // 返回优先级最高的元素
  const_reference top() const { return c.front(); }

  // 插入元素, 并调整heap
  void push(const value_type& x)
  {
    __STL_TRY {
      c.push_back(x);
      // 详细分析见<stl_heap.h>
      push_heap(c.begin(), c.end(), comp);
    }
    __STL_UNWIND(c.clear());
  }

  // 弹出优先级最高的元素
  void pop() {
    __STL_TRY {
      // 详细分析见<stl_heap.h>
      pop_heap(c.begin(), c.end(), comp);
      c.pop_back();
    }
    __STL_UNWIND(c.clear());
  }
};

// 不提供比较操作

__STL_END_NAMESPACE

#endif /* __SGI_STL_INTERNAL_QUEUE_H */

// Local Variables:
// mode:C++
// End: