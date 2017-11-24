   1. // Filename:    defalloc.h  
   2.   
   3. // Comment By:  凝霜  
   4. // E-mail:      mdl2009@vip.qq.com  
   5. // Blog:        http://blog.csdn.net/mdl13412  
   6.   
   7. /* 
   8.  * 
   9.  * Copyright (c) 1994 
  10.  * Hewlett-Packard Company 
  11.  * 
  12.  * Permission to use, copy, modify, distribute and sell this software 
  13.  * and its documentation for any purpose is hereby granted without fee, 
  14.  * provided that the above copyright notice appear in all copies and 
  15.  * that both that copyright notice and this permission notice appear 
  16.  * in supporting documentation.  Hewlett-Packard Company makes no 
  17.  * representations about the suitability of this software for any 
  18.  * purpose.  It is provided "as is" without express or implied warranty. 
  19.  * 
  20.  */  
  21.   
  22. // 这个文件提供原始的HP默认allocator, 仅仅是为了向后兼容  
  23. //  
  24. // 不要使用这个文件,除非你使用一个需要HP-style allocator的旧容器  
  25. // SGI STL使用一个不同的allocator接口  
  26. // SGI-style的allocator不针对对象类型进行参数化, 他使用void *指针  
  27.   
  28. #ifndef DEFALLOC_H  
  29. #define DEFALLOC_H  
  30.   
  31. #include <new.h>  
  32. #include <stddef.h>  
  33. #include <stdlib.h>  
  34. #include <limits.h>  
  35. #include <iostream.h>  
  36. #include <algobase.h>  
  37.   
  38. // 如果内存分配失败, 则直接退出程序  
  39. template <class T>  
  40. inline T* allocate(ptrdiff_t size, T*)  
  41. {  
  42.     set_new_handler(0);  
  43.     T* tmp = (T*)(::operator new((size_t)(size * sizeof(T))));  
  44.     if (tmp == 0) {  
  45.     cerr << "out of memory" << endl;  
  46.     exit(1);  
  47.     }  
  48.     return tmp;  
  49. }  
  50.   
  51. template <class T>  
  52. inline void deallocate(T* buffer)  
  53. {  
  54.     ::operator delete(buffer);  
  55. }  
  56.   
  57. // 标准的STL allocator接口  
  58. template <class T>  
  59. class allocator  
  60. {  
  61. public:  
  62.     // STL type_traits需要的标准定义  
  63.     typedef T value_type;  
  64.     typedef T* pointer;  
  65.     typedef const T* const_pointer;  
  66.     typedef T& reference;  
  67.     typedef const T& const_reference;  
  68.     typedef size_t size_type;  
  69.     typedef ptrdiff_t difference_type;  
  70.   
  71.   
  72.     pointer allocate(size_type n)  
  73.     {  
  74.     return ::allocate((difference_type)n, (pointer)0);  
  75.     }  
  76.     void deallocate(pointer p) { ::deallocate(p); }  
  77.     pointer address(reference x) { return (pointer)&x; }  
  78.     const_pointer const_address(const_reference x)  
  79.     {  
  80.     return (const_pointer)&x;  
  81.     }  
  82.     //   
  83.     size_type init_page_size()  
  84.     {  
  85.     return max(size_type(1), size_type(4096/sizeof(T)));  
  86.     }  
  87.     size_type max_size() const  
  88.     {  
  89.     return max(size_type(1), size_type(UINT_MAX/sizeof(T)));  
  90.     }  
  91. };  
  92.   
  93. // 仅使用void *类型的指针  
  94. class allocator<void>  
  95. {  
  96. public:  
  97.     typedef void* pointer;  
  98. };  
  99.   
 100. #endif