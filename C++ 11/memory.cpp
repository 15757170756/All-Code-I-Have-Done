// Filename:    memory  
  
// Comment By:  凝霜  
// E-mail:      mdl2009@vip.qq.com  
// Blog:        http://blog.csdn.net/mdl13412  
  
// 智能指针在STL中只有一个auto_ptr, 用于对原生指针的生命周期进行管理,  
// 但是其本身有许多另其不安全的特性, 例如以一个auto_ptr去构造另一个  
// auto_ptr会导致对象所有权的转移, 另外如果两个只能指针同时指向一个  
// 原声指针就可能导致指针被意外的提前释放, 另一个auto_ptr对其解引用时,  
// 就会导致错误  
//  
// C++0x已经通过了::Boost::scoped_ptr的决案, 所以任何使用auto_ptr的  
// 情景都应该使用scoped_ptr替代, 因为其更安全, 但是仍然不能解决多个  
// 智能指针同时拥有一个对象导致的提前释放问题, 要解决这个问题, 请使用  
// ::Boost::shared_ptr  
  
// 我博客中还有一个我实现的auto_ptr, 大家可以参考  
// http://blog.csdn.net/mdl13412/article/details/6244631  
  
/* 
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
 * 
 */  
  
#ifndef __SGI_STL_MEMORY  
#define __SGI_STL_MEMORY  
  
#include <stl_algobase.h>  
#include <stl_alloc.h>  
#include <stl_construct.h>  
#include <stl_tempbuf.h>  
#include <stl_uninitialized.h>  
#include <stl_raw_storage_iter.h>  
  
// Note: auto_ptr is commented out in this release because the details  
//  of the interface are still being discussed by the C++ standardization  
//  committee.  It will be included once the iterface is finalized.  
  
#if 1  
/*#if defined(_MUTABLE_IS_KEYWORD) && defined(_EXPLICIT_IS_KEYWORD) && \  
    defined(__STL_MEMBER_TEMPLATES)  
  
__STL_BEGIN_NAMESPACE */ 
  
template <class X> class auto_ptr  
{  
private:  
  X* ptr;               // 托管的原生指针  
  mutable bool owns;    // 是否拥有托管指针  
public:  
  typedef X element_type;  
  
  // 显式构造函数, 防止隐式转换  
  // 通常接收一个原生指针进行构造  
  // 构造函数不能失败, 故不能抛出异常  
  explicit auto_ptr(X* p = 0) __STL_NOTHROW : ptr(p), owns(p) {}  
  
  // auto_ptr 可以以相同类型的 auto_ptr 进行构造  
  // 注意: 对象所有权发生转移, 用于构造的只能指针释放对象所有权  
  auto_ptr(const auto_ptr& a) __STL_NOTHROW : ptr(a.ptr), owns(a.owns) {  
    a.owns = 0;  
  }  
  
  // auto_ptr 可以以另一种相关类型的 auto_ptr 进行构造  
  // 注意: T 必须能转换成 X 类型, 对象所有权发生转移  
  template <class T> auto_ptr(const auto_ptr<T>& a) __STL_NOTHROW  
    : ptr(a.ptr), owns(a.owns) {  
      a.owns = 0;  
  }  
  
  // 重载operator =, 首先判断是否是本身, 如果不是则进行对象所有权的转移  
  auto_ptr& operator=(const auto_ptr& a) __STL_NOTHROW {  
    if (&a != this) {  
      if (owns)  
        delete ptr;  
      owns = a.owns;  
      ptr = a.ptr;  
      a.owns = 0;  
    }  
    // 个人感觉应该在此加上  
    // return *this;  
  }  
  
  // 和上面的operator =功能一样, 但是提供了兼容类型的转换操作  
  template <class T> auto_ptr& operator=(const auto_ptr<T>& a) __STL_NOTHROW {  
    if (&a != this) {  
      if (owns)  
        delete ptr;  
      owns = a.owns;  
      ptr = a.ptr;  
      a.owns = 0;  
    }  
  
    // 个人感觉应该在此加上  
    // return *this;  
  }  
  
  // auto_ptr生命周期结束, 释放对象所有权, 实现资源释放目的  
  ~auto_ptr() {  
    if (owns)  
      delete ptr;  
  }  
  
  // 提供和原生指针一样的操作  
  X& operator*() const __STL_NOTHROW { return *ptr; }  
  X* operator->() const __STL_NOTHROW { return ptr; }  
  
  // 获取原生指针的地址, 主要用于一些只接受原生指针的函数  
  X* get() const __STL_NOTHROW { return ptr; }  
  // 释放指针所有权, 并返回原生指针  
  // 主要用于取消指针托管  
  X* release const __STL_NOTHROW { owns = false; return ptr }  
};  
  
__STL_END_NAMESPACE  
#endif /* mutable && explicit && member templates */  
#endif /* 0 */  
  
  
#endif /* __SGI_STL_MEMORY */  
  
  
// Local Variables:  
// mode:C++  
// End: