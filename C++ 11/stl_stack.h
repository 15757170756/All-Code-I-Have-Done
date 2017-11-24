// Filename:    stl_stack.h

// Comment By:  凝霜
// E-mail:      mdl2009@vip.qq.com
// Blog:        http://blog.csdn.net/mdl13412

////////////////////////////////////////////////////////////////////////////////
// stack是一种先进后出(First In Last Out, FILO)的数据结构, 其只有一个出口
// 支持对栈顶元素的追加, 弹出, 获取, 但是不提供对其它位置元素的访问
////////////////////////////////////////////////////////////////////////////////
// 以下为使用deque时的布局
//
// 栈底                      当前栈顶                         预留的内存边界
// ↓                            ↓                                 ↓
// --------------------------------------------------------------------
// |   |   | ...... |   |   |   |   |   |   |   | ......  |   |   | X |
// --------------------------------------------------------------------
//                              ↑   ↑                             ↑
//                              |   |                             |
//                              |   -------------------------------
//                              |    这里是尚未使用的预留内存, 可能为0
//                              |
//                       仅支持在这里进行push(), pop(), top()操作
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

#ifndef __SGI_STL_INTERNAL_STACK_H
#define __SGI_STL_INTERNAL_STACK_H

__STL_BEGIN_NAMESPACE

// 如果编译器不能根据前面模板参数推导出后面使用的默认参数类型,
// 那么就需要手工指定, 本实作stack内部容器默认使用deque
// 选用deque可以在存储空间不足时可以动态增加, 而且代价很低
#ifndef __STL_LIMITED_DEFAULT_TEMPLATES
template <class T, class Sequence = deque<T> >
#else
template <class T, class Sequence>
#endif
class stack
{
  // 特化的全局运算符, 提供operator==和<重载则构建出所有运算符
  // 其具体细节见<stl_pair.h>中的说明
  friend bool operator== __STL_NULL_TMPL_ARGS (const stack&, const stack&);
  friend bool operator< __STL_NULL_TMPL_ARGS (const stack&, const stack&);

public:
  // 由于stack仅支持对栈顶元素的操作, 所以不定义STL要求的
  // pointer, iterator, difference_type
  typedef typename Sequence::value_type value_type;
  typedef typename Sequence::size_type size_type;
  typedef typename Sequence::reference reference;
  typedef typename Sequence::const_reference const_reference;

protected:
  Sequence c;   // 这个是我们实际维护的容器

public:
  // 下面的操作完全使用内部容器的成员函数实现
  // 这再次体现了STL高度的可复用性:-)

  // 判断stack是否为空
  bool empty() const { return c.empty(); }

  // stack中元素个数
  size_type size() const { return c.size(); }

  // 返回栈顶元素, 注意这里返回的是引用!!!
  reference top() { return c.back(); }
  const_reference top() const { return c.back(); }

  // 在栈顶追加新元素
  void push(const value_type& x) { c.push_back(x); }

  // 移除栈顶元素, 注意不返回元素的引用,
  // 很多初学者随机用此容器时经常误认为pop()操作同时会返回栈顶元素的引用
  void pop() { c.pop_back(); }
};

// 判断两个stack是否相等, 就要测试其内部维护容器是否相等
// x.c == y.c会调用容器重载的operator ==
template <class T, class Sequence>
bool operator==(const stack<T, Sequence>& x, const stack<T, Sequence>& y)
{
  return x.c == y.c;
}

template <class T, class Sequence>
bool operator<(const stack<T, Sequence>& x, const stack<T, Sequence>& y)
{
  return x.c < y.c;
}

__STL_END_NAMESPACE

#endif /* __SGI_STL_INTERNAL_STACK_H */

// Local Variables:
// mode:C++
// End: