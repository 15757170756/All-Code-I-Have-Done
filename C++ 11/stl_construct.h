// Filename:    stl_construct.h

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

#ifndef __SGI_STL_INTERNAL_CONSTRUCT_H
#define __SGI_STL_INTERNAL_CONSTRUCT_H

#include <new.h>        // 需要placement new的原型

__STL_BEGIN_NAMESPACE

// 调用成员的析构函数, 需要类型具有non-trivial destructor
template <class T>
inline void destroy(T* pointer)
{
	pointer->~T();
}

// 使用placement new在已经分配的内存上构造对象
// 如果你不熟悉placement new, 请参考
// http://msdn.microsoft.com/en-us/library/kewsb8ba.aspx
// http://blogs.msdn.com/b/jaredpar/archive/
//        2007/10/16/c-new-operator-and-placement-new.aspx
template <class T1, class T2>
inline void construct(T1* p, const T2& value)
{
	new (p)T1(value);
}

// 析构一组对象, 用于具有non-trivial destructor
template <class ForwardIterator>
inline void
__destroy_aux(ForwardIterator first, ForwardIterator last, __false_type)
{
	for (; first < last; ++first)
		destroy(&*first);
}

// 如果没有类型non-trivial destructor, 则使用此函数
template <class ForwardIterator>
inline void __destroy_aux(ForwardIterator, ForwardIterator, __true_type) {}

// 使用traits技术, 判断类型是否就有non-trivial destructor, 然后调用不同的函数
template <class ForwardIterator, class T>
inline void __destroy(ForwardIterator first, ForwardIterator last, T*)
{
	typedef typename __type_traits<T>::has_trivial_destructor trivial_destructor;
	__destroy_aux(first, last, trivial_destructor());
}

////////////////////////////////////////////////////////////////////////////////
// 用于销毁一组对象
////////////////////////////////////////////////////////////////////////////////
//                                                char *特化版本
//                                               ---------- destroy不进行析构
//                                               |
// destroy(first, last) -------------------------- 特化
//                                   |           |
//                                   |  泛化     ----------- destroy不进行析构
//                                   |           wchar_t *特化版本
//                                   ↓
//                调用 __destroy(first, last, value_type(first));
//                根据是否具有trivial destructor进行函数转发
//                                   |
//                                   |---------------- has trivial destructor?
//                                   |
//               -------------------------------------------
//        No     |                                         | Yes
//               |                                         |
//               ↓                                         ↓
// __destroy_aux(..., __true_type)           __destroy_aux(..., __false_type)
// 不进需要行析构操作                          for ( ; first < last; ++first)
//                                              destroy(&*first);
////////////////////////////////////////////////////////////////////////////////

template <class ForwardIterator>
inline void destroy(ForwardIterator first, ForwardIterator last)
{
	__destroy(first, last, value_type(first));
}

// 特化版本
inline void destroy(char*, char*) {}
inline void destroy(wchar_t*, wchar_t*) {}

__STL_END_NAMESPACE

#endif /* __SGI_STL_INTERNAL_CONSTRUCT_H */

// Local Variables:
// mode:C++
// End: