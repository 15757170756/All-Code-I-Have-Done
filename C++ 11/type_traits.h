// Filename:    type_traits.h

// Comment By:  凝霜
// E-mail:      mdl2009@vip.qq.com
// Blog:        http://blog.csdn.net/mdl13412

/*
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

#ifndef __TYPE_TRAITS_H
#define __TYPE_TRAITS_H

#ifndef __STL_CONFIG_H
#include <stl_config.h>
#endif

// 这个头文件提供了一个框架, 允许编译器在编译期根据类型属性派发函数的机制
// 这个框架对于编写模板代码非常有用
// 例如, 当我们需要拷贝一个未知类型的array, 它能帮助我们得知这个未知类型
// 是否具有一个trivial copy constructor, 以帮助我们决定memcpy()是否能使用

// __type_traits模板类提供了一些列的typedefs, 其值是__true_type或者__false_type
// __type_traits模板类可以接受任何类型的参数
// 模板类中的typedefs可以通过以下手段获取其正确值
//   1. general instantiation, 对于所有类型都要有保守值
//   2. 经过特化的版本
//   3. 一些编译器(例如Silicon Graphics N32 and N64 compilers)
//      会自动给所有类型提供合适的特化版本
//
// 例子:
// Copy an array of elements which have non-trivial copy constructors
// template <class T> void copy(T* source,T* destination,int n,__false_type);
// Copy an array of elements which have trivial copy constructors. Use memcpy.
// template <class T> void copy(T* source,T* destination,int n,__true_type);
//
// Copy an array of any type by using the most efficient copy mechanism
// template <class T> inline void copy(T* source,T* destination,int n)
// {
//      copy(source,destination,n,
//              typename __type_traits<T>::has_trivial_copy_constructor());
// }

struct __true_type
{
};

struct __false_type
{
};

template <class type>
struct __type_traits
{
    // 不要移除这个成员
    // 它通知能自动特化__type_traits的编译器, 现在这个__type_traits template是特化的
    // 这是为了确保万一编译器使用了__type_traits而与此处无任何关联的模板时
    // 一切也能顺利运作
   typedef __true_type     this_dummy_member_must_be_first;

   // 以下条款应当被遵守, 因为编译器有可能自动生成类型的特化版本
   //   - 你可以重新安排的成员次序
   //   - 你可以移除你想移除的成员
   //   - 一定不可以修改下列成员名称, 却没有修改编译器中的相应名称
   //   - 新加入的成员被当作一般成员, 除非编译器提供特殊支持

   typedef __false_type    has_trivial_default_constructor;
   typedef __false_type    has_trivial_copy_constructor;
   typedef __false_type    has_trivial_assignment_operator;
   typedef __false_type    has_trivial_destructor;
   typedef __false_type    is_POD_type;
};


// 以下针对C++内置的基本数据类型提供特化版本, 使其具有trivial default constructor,
// copy constructor, assignment operator, destructor
// 并标记其为POD类型
//
// 特化类型:
//         char, signed char, unsigned char,
//         short, unsigned short
//         int, unsigned int
//         long, unsigned long
//         float, double, long double

// Provide some specializations.  This is harmless for compilers that
//  have built-in __types_traits support, and essential for compilers
//  that don't.

__STL_TEMPLATE_NULL struct __type_traits<char>
{
   typedef __true_type    has_trivial_default_constructor;
   typedef __true_type    has_trivial_copy_constructor;
   typedef __true_type    has_trivial_assignment_operator;
   typedef __true_type    has_trivial_destructor;
   typedef __true_type    is_POD_type;
};

__STL_TEMPLATE_NULL struct __type_traits<signed char>
{
   typedef __true_type    has_trivial_default_constructor;
   typedef __true_type    has_trivial_copy_constructor;
   typedef __true_type    has_trivial_assignment_operator;
   typedef __true_type    has_trivial_destructor;
   typedef __true_type    is_POD_type;
};

__STL_TEMPLATE_NULL struct __type_traits<unsigned char>
{
   typedef __true_type    has_trivial_default_constructor;
   typedef __true_type    has_trivial_copy_constructor;
   typedef __true_type    has_trivial_assignment_operator;
   typedef __true_type    has_trivial_destructor;
   typedef __true_type    is_POD_type;
};

__STL_TEMPLATE_NULL struct __type_traits<short>
{
   typedef __true_type    has_trivial_default_constructor;
   typedef __true_type    has_trivial_copy_constructor;
   typedef __true_type    has_trivial_assignment_operator;
   typedef __true_type    has_trivial_destructor;
   typedef __true_type    is_POD_type;
};

__STL_TEMPLATE_NULL struct __type_traits<unsigned short>
{
   typedef __true_type    has_trivial_default_constructor;
   typedef __true_type    has_trivial_copy_constructor;
   typedef __true_type    has_trivial_assignment_operator;
   typedef __true_type    has_trivial_destructor;
   typedef __true_type    is_POD_type;
};

__STL_TEMPLATE_NULL struct __type_traits<int>
{
   typedef __true_type    has_trivial_default_constructor;
   typedef __true_type    has_trivial_copy_constructor;
   typedef __true_type    has_trivial_assignment_operator;
   typedef __true_type    has_trivial_destructor;
   typedef __true_type    is_POD_type;
};

__STL_TEMPLATE_NULL struct __type_traits<unsigned int>
{
   typedef __true_type    has_trivial_default_constructor;
   typedef __true_type    has_trivial_copy_constructor;
   typedef __true_type    has_trivial_assignment_operator;
   typedef __true_type    has_trivial_destructor;
   typedef __true_type    is_POD_type;
};

__STL_TEMPLATE_NULL struct __type_traits<long>
{
   typedef __true_type    has_trivial_default_constructor;
   typedef __true_type    has_trivial_copy_constructor;
   typedef __true_type    has_trivial_assignment_operator;
   typedef __true_type    has_trivial_destructor;
   typedef __true_type    is_POD_type;
};

__STL_TEMPLATE_NULL struct __type_traits<unsigned long>
{
   typedef __true_type    has_trivial_default_constructor;
   typedef __true_type    has_trivial_copy_constructor;
   typedef __true_type    has_trivial_assignment_operator;
   typedef __true_type    has_trivial_destructor;
   typedef __true_type    is_POD_type;
};

__STL_TEMPLATE_NULL struct __type_traits<float>
{
   typedef __true_type    has_trivial_default_constructor;
   typedef __true_type    has_trivial_copy_constructor;
   typedef __true_type    has_trivial_assignment_operator;
   typedef __true_type    has_trivial_destructor;
   typedef __true_type    is_POD_type;
};

__STL_TEMPLATE_NULL struct __type_traits<double>
{
   typedef __true_type    has_trivial_default_constructor;
   typedef __true_type    has_trivial_copy_constructor;
   typedef __true_type    has_trivial_assignment_operator;
   typedef __true_type    has_trivial_destructor;
   typedef __true_type    is_POD_type;
};

__STL_TEMPLATE_NULL struct __type_traits<long double>
{
   typedef __true_type    has_trivial_default_constructor;
   typedef __true_type    has_trivial_copy_constructor;
   typedef __true_type    has_trivial_assignment_operator;
   typedef __true_type    has_trivial_destructor;
   typedef __true_type    is_POD_type;
};

#ifdef __STL_CLASS_PARTIAL_SPECIALIZATION

// 针对指针提供特化
template <class T>
struct __type_traits<T*>
{
   typedef __true_type    has_trivial_default_constructor;
   typedef __true_type    has_trivial_copy_constructor;
   typedef __true_type    has_trivial_assignment_operator;
   typedef __true_type    has_trivial_destructor;
   typedef __true_type    is_POD_type;
};

#else /* __STL_CLASS_PARTIAL_SPECIALIZATION */

// 针对char *, signed char *, unsigned char *提供特化

struct __type_traits<char*>
{
   typedef __true_type    has_trivial_default_constructor;
   typedef __true_type    has_trivial_copy_constructor;
   typedef __true_type    has_trivial_assignment_operator;
   typedef __true_type    has_trivial_destructor;
   typedef __true_type    is_POD_type;
};

struct __type_traits<signed char*>
{
   typedef __true_type    has_trivial_default_constructor;
   typedef __true_type    has_trivial_copy_constructor;
   typedef __true_type    has_trivial_assignment_operator;
   typedef __true_type    has_trivial_destructor;
   typedef __true_type    is_POD_type;
};

struct __type_traits<unsigned char*>
{
   typedef __true_type    has_trivial_default_constructor;
   typedef __true_type    has_trivial_copy_constructor;
   typedef __true_type    has_trivial_assignment_operator;
   typedef __true_type    has_trivial_destructor;
   typedef __true_type    is_POD_type;
};

#endif /* __STL_CLASS_PARTIAL_SPECIALIZATION */


#endif /* __TYPE_TRAITS_H */

// Local Variables:
// mode:C++
// End: