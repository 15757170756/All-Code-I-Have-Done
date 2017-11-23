// Filename:    stl_construct.h

// Comment By:  ��˪
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

#include <new.h>        // ��Ҫplacement new��ԭ��

__STL_BEGIN_NAMESPACE

// ���ó�Ա����������, ��Ҫ���;���non-trivial destructor
template <class T>
inline void destroy(T* pointer)
{
	pointer->~T();
}

// ʹ��placement new���Ѿ�������ڴ��Ϲ������
// ����㲻��Ϥplacement new, ��ο�
// http://msdn.microsoft.com/en-us/library/kewsb8ba.aspx
// http://blogs.msdn.com/b/jaredpar/archive/
//        2007/10/16/c-new-operator-and-placement-new.aspx
template <class T1, class T2>
inline void construct(T1* p, const T2& value)
{
	new (p)T1(value);
}

// ����һ�����, ���ھ���non-trivial destructor
template <class ForwardIterator>
inline void
__destroy_aux(ForwardIterator first, ForwardIterator last, __false_type)
{
	for (; first < last; ++first)
		destroy(&*first);
}

// ���û������non-trivial destructor, ��ʹ�ô˺���
template <class ForwardIterator>
inline void __destroy_aux(ForwardIterator, ForwardIterator, __true_type) {}

// ʹ��traits����, �ж������Ƿ����non-trivial destructor, Ȼ����ò�ͬ�ĺ���
template <class ForwardIterator, class T>
inline void __destroy(ForwardIterator first, ForwardIterator last, T*)
{
	typedef typename __type_traits<T>::has_trivial_destructor trivial_destructor;
	__destroy_aux(first, last, trivial_destructor());
}

////////////////////////////////////////////////////////////////////////////////
// ��������һ�����
////////////////////////////////////////////////////////////////////////////////
//                                                char *�ػ��汾
//                                               ---------- destroy����������
//                                               |
// destroy(first, last) -------------------------- �ػ�
//                                   |           |
//                                   |  ����     ----------- destroy����������
//                                   |           wchar_t *�ػ��汾
//                                   ��
//                ���� __destroy(first, last, value_type(first));
//                �����Ƿ����trivial destructor���к���ת��
//                                   |
//                                   |---------------- has trivial destructor?
//                                   |
//               -------------------------------------------
//        No     |                                         | Yes
//               |                                         |
//               ��                                         ��
// __destroy_aux(..., __true_type)           __destroy_aux(..., __false_type)
// ������Ҫ����������                          for ( ; first < last; ++first)
//                                              destroy(&*first);
////////////////////////////////////////////////////////////////////////////////

template <class ForwardIterator>
inline void destroy(ForwardIterator first, ForwardIterator last)
{
	__destroy(first, last, value_type(first));
}

// �ػ��汾
inline void destroy(char*, char*) {}
inline void destroy(wchar_t*, wchar_t*) {}

__STL_END_NAMESPACE

#endif /* __SGI_STL_INTERNAL_CONSTRUCT_H */

// Local Variables:
// mode:C++
// End: