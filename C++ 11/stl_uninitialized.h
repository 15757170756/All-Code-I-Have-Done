// Filename:    stl_uninitialized.h

// Comment By:  凝霜
// E-mail:      mdl2009@vip.qq.com
// Blog:        http://blog.csdn.net/mdl13412

// 主要接口:
//
//      template <class InputIterator, class ForwardIterator>
//      inline ForwardIterator
//      uninitialized_copy(InputIterator first, InputIterator last,
//                         ForwardIterator result)
//      将[first, last)的对象复制一份到[result, result + (last - first))
//      对于char和wchar_t提供特化版本, 以获取最佳效率
//      注: commit or rollback
//
//      template <class InputIterator, class Size, class ForwardIterator>
//      inline pair<InputIterator, ForwardIterator>
//      uninitialized_copy_n(InputIterator first, Size count,
//                           ForwardIterator result)
//      从first开始, 复制count个对象到[result, result + n)
//      注: commit or rollback
//
//      template <class ForwardIterator, class T>
//      inline void uninitialized_fill(ForwardIterator first,
//                                     ForwardIterator last,
//                                     const T& x)
//      将x复制到pfirst, last)
//      注: commit or rollback
//
//      template <class ForwardIterator, class Size, class T>
//      inline ForwardIterator uninitialized_fill_n(ForwardIterator first,
//                                                  Size n, const T& x)
//      复制n个x对象到[first, first + n)
//      注: commit or rollback

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

#ifndef __SGI_STL_INTERNAL_UNINITIALIZED_H
#define __SGI_STL_INTERNAL_UNINITIALIZED_H

__STL_BEGIN_NAMESPACE

////////////////////////////////////////////////////////////////////////////////
// uninitialized_copy()实现部分
////////////////////////////////////////////////////////////////////////////////
//                         特化char版本
//                      |---------------> (char *, ...)  <---    字串串专用版本
//                      |  特化wchar_t版本                   |--- 调用memmove()
// uninitialized_copy ------------------> (wchar_t, ...) <---    获取最佳效率
//                      |
//                      |
//                      | 泛化   调用 __uninitialized_copy()
//                      |----->  根据类型是否为POD进行函数派发
//                                           |
//                                           |---------------- Is POD?
//                                           |
//              -------------------------------------
//           No |                                   | Yes
//              ↓                                   |
// __uninitialized_copy_aux(..., __false_type)      |
// for ( ; first != last; ++first, ++cur)           |
//      construct(&*cur, *first);                   ↓
//                                   __uninitialized_copy_aux(..., __true_type)
//                                   copy(first, last, result)
////////////////////////////////////////////////////////////////////////////////

// 如果copy construction和operator =等效, 并且destructor is trivial
// 那么就可以使用本函数
// 返回值为目标地址的end
// 注: 使用copy()进行复制的时候, 调用的是对象的operator =,
//     所以要满足copy construction和operator =等效,
//     destructor is trivial保证在此版本中不会进行析构,
//     以保证效率
template <class InputIterator, class ForwardIterator>
inline ForwardIterator
__uninitialized_copy_aux(InputIterator first, InputIterator last,
                         ForwardIterator result,
                         __true_type)
{
  // 调用的是STL算法copy()
  return copy(first, last, result);
}

// 如果copy construction和operator =不等效, 那么就要调用construct()进行构造
template <class InputIterator, class ForwardIterator>
ForwardIterator
__uninitialized_copy_aux(InputIterator first, InputIterator last,
                         ForwardIterator result,
                         __false_type)
{
  ForwardIterator cur = result;
  __STL_TRY {
    // 因为copy construction和operator =不等效,
    // 则必须每个对象都以其它对象为蓝本进行构造
    // 本实作中使用的是placement new进行构造
    for ( ; first != last; ++first, ++cur)
      construct(&*cur, *first);
    return cur;
  }
  // commit or rollback
  // 如果分配失败就stack unwinding,
  // 保证所有对象都被析构
  __STL_UNWIND(destroy(result, cur));
}

// 派发函数, traits出T是否为POD, 然后进行派发
template <class InputIterator, class ForwardIterator, class T>
inline ForwardIterator
__uninitialized_copy(InputIterator first, InputIterator last,
                     ForwardIterator result, T*)
{
  // POD = Plain Old Data
  // 其具有trvial constructor/destructor/copy constructor/operator =
  // 所有的C++内置基本数据类型和传统C struct都属于POD
  typedef typename __type_traits<T>::is_POD_type is_POD;

  // 根据是否为POD类型进行派发, 以保证效率
  return __uninitialized_copy_aux(first, last, result, is_POD());
}

template <class InputIterator, class ForwardIterator>
inline ForwardIterator
  uninitialized_copy(InputIterator first, InputIterator last,
                     ForwardIterator result)
{
  // 调用派发函数, 根据是否为POD决议出最佳效率的函数
  return __uninitialized_copy(first, last, result, value_type(result));
}

// 提供给char专用, 效率最优化
inline char* uninitialized_copy(const char* first, const char* last,
                                char* result)
{
  memmove(result, first, last - first);
  return result + (last - first);
}

// 提供给wchar_t专用, 效率最优化
inline wchar_t* uninitialized_copy(const wchar_t* first, const wchar_t* last,
                                   wchar_t* result)
{
  memmove(result, first, sizeof(wchar_t) * (last - first));
  return result + (last - first);
}

////////////////////////////////////////////////////////////////////////////////
// uninitialized_copy_n()实现部分
////////////////////////////////////////////////////////////////////////////////
//                         uninitialized_copy_n
//                                  |
//                                  |------------ 判断迭代器first的类别
//                                  |
//               -----------------------------------------
// InputIterator |                                       | RandomAccessIterator
//               |                                       |
//               ↓                                       |
// __uninitialized_copy_n(..., input_iterator_tag)       |
// for ( ; count > 0 ; --count, ++first, ++cur)          |
//    construct(&*cur, *first);                          |
//                                                       ↓
//                    __uninitialized_copy_n(..., random_access_iterator_tag)
//                    last = first + count;
//                    uninitialized_copy(first, last, result)
////////////////////////////////////////////////////////////////////////////////

// POD版本
template <class InputIterator, class Size, class ForwardIterator>
pair<InputIterator, ForwardIterator>
__uninitialized_copy_n(InputIterator first, Size count,
                       ForwardIterator result,
                       input_iterator_tag)
{
  ForwardIterator cur = result;
  __STL_TRY {
    for ( ; count > 0 ; --count, ++first, ++cur)
      construct(&*cur, *first);
    return pair<InputIterator, ForwardIterator>(first, cur);
  }
  __STL_UNWIND(destroy(result, cur));
}

// 非POD版本
// 对于支持随机存取的迭代器, 可以直接使用uninitialized_copy()进行复制
template <class RandomAccessIterator, class Size, class ForwardIterator>
inline pair<RandomAccessIterator, ForwardIterator>
__uninitialized_copy_n(RandomAccessIterator first, Size count,
                       ForwardIterator result,
                       random_access_iterator_tag)
{
  RandomAccessIterator last = first + count;
  return make_pair(last, uninitialized_copy(first, last, result));
}

template <class InputIterator, class Size, class ForwardIterator>
inline pair<InputIterator, ForwardIterator>
uninitialized_copy_n(InputIterator first, Size count,
                     ForwardIterator result)
{
  return __uninitialized_copy_n(first, count, result,
                                iterator_category(first));
}

////////////////////////////////////////////////////////////////////////////////
// uninitialized_fill()实现部分
////////////////////////////////////////////////////////////////////////////////
//                           uninitialized_fill
//                                   |
//                                   |
//                                   ↓
//                       调用__uninitialized_fill()
//                       根据类型是否为POD进行函数派发
//                                   |
//                                   |---------------- Is POD?
//                   No 泛化版本      |      Yes 特化版本
//               -------------------------------------------
//               |                                         |
//               |                                         |
//               ↓                                         |
// __uninitialized_fill_aux(..., __false_type)             |
// for ( ; cur != last; ++cur)                             |
//    construct(&*cur, x);                                 ↓
//                                __uninitialized_fill_aux(..., __true_type)
//                                fill(first, last, x);
////////////////////////////////////////////////////////////////////////////////

// POD版本
// 如果copy construction和operator =等效, 并且destructor is trivial
// 那么就可以使用本函数
template <class ForwardIterator, class T>
inline void
__uninitialized_fill_aux(ForwardIterator first, ForwardIterator last,
                         const T& x, __true_type)
{
  fill(first, last, x);
}

// 非POD版本
template <class ForwardIterator, class T>
void
__uninitialized_fill_aux(ForwardIterator first, ForwardIterator last,
                         const T& x, __false_type)
{
  ForwardIterator cur = first;
  __STL_TRY {
    for ( ; cur != last; ++cur)
      construct(&*cur, x);
  }
  __STL_UNWIND(destroy(first, cur));
}

// 派发函数
template <class ForwardIterator, class T, class T1>
inline void __uninitialized_fill(ForwardIterator first, ForwardIterator last,
                                 const T& x, T1*)
{
  typedef typename __type_traits<T1>::is_POD_type is_POD;
  __uninitialized_fill_aux(first, last, x, is_POD());

}

template <class ForwardIterator, class T>
inline void uninitialized_fill(ForwardIterator first, ForwardIterator last,
                               const T& x)
{
  __uninitialized_fill(first, last, x, value_type(first));
}

////////////////////////////////////////////////////////////////////////////////
// uninitialized_fill_n()实现部分
////////////////////////////////////////////////////////////////////////////////
//                           uninitialized_fill_n
//                                   |
//                                   |
//                                   ↓
//                      调用__uninitialized_fill_n()
//                      根据类型是否为POD进行函数派发
//                                   |
//                                   |---------------- Is POD?
//                   No 泛化版本      |      Yes 特化版本
//               -------------------------------------------
//               |                                         |
//               |                                         |
//               ↓                                         |
// __uninitialized_fill_n_aux(..., __false_type)           |
// for ( ; n > 0; --n, ++cur)                              |
//    construct(&*cur, x);                                 |
//                                                         ↓
//                               __uninitialized_fill_n_aux(..., __true_type)
//                               fill_n(first, n, x);
////////////////////////////////////////////////////////////////////////////////

// 如果copy construction和operator =等效, 并且destructor is trivial
// 那么就可以使用本函数
template <class ForwardIterator, class Size, class T>
inline ForwardIterator
__uninitialized_fill_n_aux(ForwardIterator first, Size n,
                           const T& x, __true_type)
{
  return fill_n(first, n, x);
}

template <class ForwardIterator, class Size, class T>
ForwardIterator
__uninitialized_fill_n_aux(ForwardIterator first, Size n,
                           const T& x, __false_type)
{
  ForwardIterator cur = first;
  __STL_TRY {
    for ( ; n > 0; --n, ++cur)
      construct(&*cur, x);
    return cur;
  }
  __STL_UNWIND(destroy(first, cur));
}

template <class ForwardIterator, class Size, class T, class T1>
inline ForwardIterator __uninitialized_fill_n(ForwardIterator first, Size n,
                                              const T& x, T1*)
{
  typedef typename __type_traits<T1>::is_POD_type is_POD;
  return __uninitialized_fill_n_aux(first, n, x, is_POD());

}

template <class ForwardIterator, class Size, class T>
inline ForwardIterator uninitialized_fill_n(ForwardIterator first, Size n,
                                            const T& x)
{
  return __uninitialized_fill_n(first, n, x, value_type(first));
}

////////////////////////////////////////////////////////////////////////////////
// 其它函数实现
////////////////////////////////////////////////////////////////////////////////

// Copies [first1, last1) into [result, result + (last1 - first1)), and
// copies [first2, last2) into
// [result, result + (last1 - first1) + (last2 - first2)).

// 我认为应该是把[first2, last2)copy到
// [result + (last1 - first1), result + (last1 - first1) + (last2 - first2))
// 大家可以讨论一下
template <class InputIterator1, class InputIterator2, class ForwardIterator>
inline ForwardIterator
__uninitialized_copy_copy(InputIterator1 first1, InputIterator1 last1,
                          InputIterator2 first2, InputIterator2 last2,
                          ForwardIterator result)
{
  ForwardIterator mid = uninitialized_copy(first1, last1, result);
  __STL_TRY {
    return uninitialized_copy(first2, last2, mid);
  }
  __STL_UNWIND(destroy(result, mid));
}

// Fills [result, mid) with x, and copies [first, last) into
//  [mid, mid + (last - first)).
template <class ForwardIterator, class T, class InputIterator>
inline ForwardIterator
__uninitialized_fill_copy(ForwardIterator result, ForwardIterator mid,
                          const T& x,
                          InputIterator first, InputIterator last)
{
  uninitialized_fill(result, mid, x);
  __STL_TRY {
    return uninitialized_copy(first, last, mid);
  }
  __STL_UNWIND(destroy(result, mid));
}

// Copies [first1, last1) into [first2, first2 + (last1 - first1)), and
//  fills [first2 + (last1 - first1), last2) with x.
template <class InputIterator, class ForwardIterator, class T>
inline void
__uninitialized_copy_fill(InputIterator first1, InputIterator last1,
                          ForwardIterator first2, ForwardIterator last2,
                          const T& x)
{
  ForwardIterator mid2 = uninitialized_copy(first1, last1, first2);
  __STL_TRY {
    uninitialized_fill(mid2, last2, x);
  }
  __STL_UNWIND(destroy(first2, mid2));
}

__STL_END_NAMESPACE

#endif /* __SGI_STL_INTERNAL_UNINITIALIZED_H */

// Local Variables:
// mode:C++
// End: