// Filename:    stl_pair.h

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

#ifndef __SGI_STL_INTERNAL_PAIR_H
#define __SGI_STL_INTERNAL_PAIR_H

__STL_BEGIN_NAMESPACE

// pair只是一个wraper, 所以要提供最佳效率
// 使用struct的原因是我们要能方便的存取内部元素
// pair在关联式容器中的使用极为广泛, 其本身也可以嵌套使用
template <class T1, class T2>
struct pair
{
  typedef T1 first_type;
  typedef T2 second_type;

  T1 first;
  T2 second;
  pair() : first(T1()), second(T2()) {}
  pair(const T1& a, const T2& b) : first(a), second(b) {}

  // 此版本并未提供operator =()的支持, 个人认为应该提供

#ifdef __STL_MEMBER_TEMPLATES
  // 允许使用兼容的pair进行复制构造
  template <class U1, class U2>
  pair(const pair<U1, U2>& p) : first(p.first), second(p.second) {}
#endif
};

// 只有当pair中的两个成员均相等时, 才判定两个pair相等
// 使用自定义类型时最好提供operator ==重载
template <class T1, class T2>
inline bool operator==(const pair<T1, T2>& x, const pair<T1, T2>& y)
{
  return x.first == y.first && x.second == y.second;
}

// 连个pair进行比较操作时, 以第一个元素为主, 如果第一个元素不能决定表达式的值
// 那么再进行第二个元素的比较
// 使用自定义类型时最好提供operator <重载
template <class T1, class T2>
inline bool operator<(const pair<T1, T2>& x, const pair<T1, T2>& y)
{
  return x.first < y.first || (!(y.first < x.first) && x.second < y.second);
}

// 至于为什么没有提供operator !=, >, >=, <=
// 这个是因为其在<stl_relops.h>中有实现, 其只依赖operator <和==
// 所以在此特化operator ==, <就能满足要求
// 提供<stl_relops.h>的作用是如果需要特化operator XXX
// 那么我们仅需要特化operator ==和<即可同时重载所有operator

// 这里使用了RVO(Return Value Optimization)机制, 如果编译器支持,
// 则可以消除临时对象的构造和析构负担
// 详细细节见<Inside The C++ Object Model>
template <class T1, class T2>
inline pair<T1, T2> make_pair(const T1& x, const T2& y)
{
  return pair<T1, T2>(x, y);
}

__STL_END_NAMESPACE

#endif /* __SGI_STL_INTERNAL_PAIR_H */

// Local Variables:
// mode:C++
// End: