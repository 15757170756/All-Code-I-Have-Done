// Filename:    defalloc.h  
      
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
*/  
     
// 这个文件提供原始的HP默认allocator, 仅仅是为了向后兼容  
//  
// 不要使用这个文件,除非你使用一个需要HP-style allocator的旧容器  
// SGI STL使用一个不同的allocator接口  
// SGI-style的allocator不针对对象类型进行参数化, 他使用void *指针  
#ifndef DEFALLOC_H  
#define DEFALLOC_H  
     
#include <new.h>  
#include <stddef.h>  
#include <stdlib.h>  
#include <limits.h>  
#include <iostream>  
#include <algobase>  
     
// 如果内存分配失败, 则直接退出程序  
template <class T>  
inline T* allocate(ptrdiff_t size, T*)  
{  
    set_new_handler(0);  
    T* tmp = (T*)(::operator new((size_t)(size * sizeof(T))));  
    if (tmp == 0) {  
		cerr << "out of memory" << endl;  
		exit(1);  
    }  
    return tmp;  
}  
     
template <class T>  
inline void deallocate(T* buffer)  
{  
    ::operator delete(buffer);  
}  
     
// 标准的STL allocator接口  
template <class T>  
class allocator  
{  
public:  
    // STL type_traits需要的标准定义  
    typedef T value_type;  
    typedef T* pointer;  
    typedef const T* const_pointer;  
    typedef T& reference;  
    typedef const T& const_reference;  
    typedef size_t size_type;  
    typedef ptrdiff_t difference_type;  
     
     
    pointer allocate(size_type n)  
    {  
		return ::allocate((difference_type)n, (pointer)0);  
    }  
    void deallocate(pointer p) { ::deallocate(p); }  
    pointer address(reference x) { return (pointer)&x; }  
    const_pointer const_address(const_reference x)  
    {  
		return (const_pointer)&x;  
    }  
    //   
    size_type init_page_size()  
    {  
		return max(size_type(1), size_type(4096/sizeof(T)));  
    }  
    size_type max_size() const  
    {  
		return max(size_type(1), size_type(UINT_MAX/sizeof(T)));  
    }  
};  
     
// 仅使用void *类型的指针  
class allocator<void>  
{  
public:  
    typedef void* pointer;  
};  
     
#endif