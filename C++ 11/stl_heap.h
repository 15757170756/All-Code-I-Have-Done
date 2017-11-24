// Filename:    stl_heap.h

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

/* NOTE: This is an internal header file, included by other STL headers.
 *   You should not attempt to use it directly.
 */

#ifndef __SGI_STL_INTERNAL_HEAP_H
#define __SGI_STL_INTERNAL_HEAP_H

__STL_BEGIN_NAMESPACE

#if defined(__sgi) && !defined(__GNUC__) && (_MIPS_SIM != _MIPS_SIM_ABI32)
#pragma set woff 1209
#endif

////////////////////////////////////////////////////////////////////////////////
// 注意: push_heap()操作前要保证新添加的元素已经加入到容器末尾!!!
////////////////////////////////////////////////////////////////////////////////
// 下面是使用默认比较函数的一个实例, XXX代表需要调整结点的位置
// 执行插入前, 元素已经追加到容器尾, 其值为450, 这里我们只
// 关注其位置, 不表示出其数值
//                                 [500]
//                                   |
//                   ---------------------------------
//                   |                               |
//                 [300]                           [400]
//                   |                               |
//        -----------------------         -----------------------
//        |                     |         |                     |
//      [200]                 [270]     [350]                 [240]
//        |                     |
//   -----------           -----------
//   |         |           |         |
// [150]     [130]       [120]     [XXX]
//
// first                                                                      last
// ↓                                                                           ↓
// --------------------------------------------------------------------------------------------
// | Not Use | 500 | 300 | 400 | 200 | 270 | 350 | 240 | 150 | 130 | 120 | XXX | ...... | end |
// --------------------------------------------------------------------------------------------
//
// 下面是移动步骤及内存变化
//                                 [500]
//                                   |
//                   ---------------------------------
//                   |                               |
//                 [300]                           [400]
//                   |                               |
//        -----------------------                -----------------------
//        |                     |                |                     |
//      [200]                 [XXX]-------     [350]                 [240]
//        |                     |        |
//   -----------           -----------   |
//   |         |           |         |   |  调整元素位置
// [150]     [130]       [120]     [270]--
//
// first                                                                      last
// ↓                                                                           ↓
// --------------------------------------------------------------------------------------------
// | Not Use | 500 | 300 | 400 | 200 | XXX | 350 | 240 | 150 | 130 | 120 | 270 | ...... | end |
// --------------------------------------------------------------------------------------------
//
//                                 [500]
//                                   |
//                   ---------------------------------
//                   |                               |
//                 [XXX]------------- 交换         [400]
//                   |              |                |
//        -----------------------   |     -----------------------
//        |                     |   |     |                     |
//      [200]                 [300]--   [350]                 [240]
//        |                     |
//   -----------           -----------
//   |         |           |         |
// [150]     [130]       [120]     [270]
//
// first                                                                      last
// ↓                                                                           ↓
// --------------------------------------------------------------------------------------------
// | Not Use | 500 | XXX | 400 | 200 | 300 | 350 | 240 | 150 | 130 | 120 | 270 | ...... | end |
// --------------------------------------------------------------------------------------------
//
// 现在满足heap的要求了, 对[XXX]直接赋值即可
//
////////////////////////////////////////////////////////////////////////////////

template <class RandomAccessIterator, class Distance, class T>
void __push_heap(RandomAccessIterator first, Distance holeIndex,
                 Distance topIndex, T value)
{
  // 首先找出待处理元素的父结点
  Distance parent = (holeIndex - 1) / 2;

  // 判断当前待处理结点是否优先级高于其父结点, 如果是则将其父结点向下移动
  // 设置当前结点为父结点位置, 继续, 直到优先级小于父结点或者已经到达heap顶端
  while (holeIndex > topIndex && *(first + parent) < value) {
    *(first + holeIndex) = *(first + parent);
    holeIndex = parent;
    parent = (holeIndex - 1) / 2;
  }

  // 将找到的合适的位置设置成正确值
  *(first + holeIndex) = value;
}

template <class RandomAccessIterator, class Distance, class T>
inline void __push_heap_aux(RandomAccessIterator first,
                            RandomAccessIterator last, Distance*, T*)
{
  // 因为first所指的那个元素不是heap的组成元素, 所以计算距离要减去1
  __push_heap(first, Distance((last - first) - 1), Distance(0),
              T(*(last - 1)));
}

// 调用此函数前要先把待处理元素追加到容器末尾
template <class RandomAccessIterator>
inline void push_heap(RandomAccessIterator first, RandomAccessIterator last)
{
  __push_heap_aux(first, last, distance_type(first), value_type(first));
}

template <class RandomAccessIterator, class Distance, class T, class Compare>
void __push_heap(RandomAccessIterator first, Distance holeIndex,
                 Distance topIndex, T value, Compare comp)
{
  Distance parent = (holeIndex - 1) / 2;
  while (holeIndex > topIndex && comp(*(first + parent), value)) {
    *(first + holeIndex) = *(first + parent);
    holeIndex = parent;
    parent = (holeIndex - 1) / 2;
  }
  *(first + holeIndex) = value;
}

template <class RandomAccessIterator, class Compare, class Distance, class T>
inline void __push_heap_aux(RandomAccessIterator first,
                            RandomAccessIterator last, Compare comp,
                            Distance*, T*)
{
  __push_heap(first, Distance((last - first) - 1), Distance(0),
              T(*(last - 1)), comp);
}

// 这个除了用户自己指定优先级决策判别式外和默认的无区别
template <class RandomAccessIterator, class Compare>
inline void push_heap(RandomAccessIterator first, RandomAccessIterator last,
                      Compare comp)
{
  __push_heap_aux(first, last, comp, distance_type(first), value_type(first));
}

////////////////////////////////////////////////////////////////////////////////
// 注意: pop_heap()操作, 执行完操作后要自己将容器尾元素弹出
////////////////////////////////////////////////////////////////////////////////
// 这里以默认的heap优先级决策来说
// STL采用的是先将待pop的元素复制到heap尾部, 然后将整个heap向上调整
// 这样就会将最后空出一个hole, 将原来最后的元素在这里进行push()操作
// 这就是两个shift_up的过程
// 个人感觉使用使用shift_down的算法更高效, 虽然时间复杂度一样, 但是shift_down
// 进行操作的元素会更少,
// 之所以用shift_up这可能也是STL设计理念的问题吧, 能复用就不写新的^_^
////////////////////////////////////////////////////////////////////////////////
// 下面是使用默认比较函数的一个实例, 我们要弹出的是优先级最高的元素[500]
// 首先要把弹出的元素[500]复制到heap末尾
// 然后进行第一次shift_up, 完成后进行push()操作, 这个就是第二次shift_up了
//
//                                 [500]
//                                   |
//                   ---------------------------------
//                   |                               |
//                 [300]                           [400]
//                   |                               |
//        -----------------------         -----------------------
//        |                     |         |                     |
//      [200]                 [270]     [350]                 [240]
//        |                     |
//   -----------           -----------
//   |         |           |         |
// [150]     [130]       [120]     [100]
//
// first                                                                      last
// ↓                                                                           ↓
// --------------------------------------------------------------------------------------------
// | Not Use | 500 | 300 | 400 | 200 | 270 | 350 | 240 | 150 | 130 | 120 | 100 | ...... | end |
// --------------------------------------------------------------------------------------------
//
// 下面是移动步骤及内存变化                      复制
//                                 [500]----------------------------------
//                                   |                                   |
//                   ---------------------------------                   |
//                   |                               |                   |
//                 [300]                           [400]                 |
//                   |                               |                   |
//        -----------------------         -----------------------        |
//        |                     |         |                     |        |
//      [200]                 [270]     [350]                 [240]      |
//        |                     |                                        |
//   -----------           -----------                                   |
//   |         |           |         |                                   |
// [150]     [130]       [120]     [500]----------------------------------
//
// first                                                                      last
// ↓                                                                           ↓
// --------------------------------------------------------------------------------------------
// | Not Use | 500 | 300 | 400 | 200 | 270 | 350 | 240 | 150 | 130 | 120 | 500 | ...... | end |
// --------------------------------------------------------------------------------------------
//
//                                 [400]-----------------------
//                                   |                        |
//                   ---------------------------------        | shift_up
//                   |                               |        |
//                 [300]                           [400]-------
//                   |                               |
//        -----------------------         -----------------------
//        |                     |         |                     |
//      [200]                 [270]     [350]                 [240]
//        |                     |
//   -----------           -----------
//   |         |           |         |
// [150]     [130]       [120]     [500]
//
// first                                                                      last
// ↓                                                                           ↓
// --------------------------------------------------------------------------------------------
// | Not Use | 400 | 300 | 400 | 200 | 270 | 350 | 240 | 150 | 130 | 120 | 500 | ...... | end |
// --------------------------------------------------------------------------------------------
//
//                                 [400]
//                                   |
//                   ---------------------------------
//                   |                               |        shift_up
//                 [300]                           [350]-------------------
//                   |                               |                    |
//        -----------------------         -----------------------         |
//        |                     |         |                     |         |
//      [200]                 [270]     [350]                 [240]       |
//        |                     |         |                               |
//   -----------           -----------    ----------------------------------
//   |         |           |         |
// [150]     [130]       [120]     [500]
//
// first                                                                      last
// ↓                                                                           ↓
// --------------------------------------------------------------------------------------------
// | Not Use | 400 | 300 | 350 | 200 | 270 | 350 | 240 | 150 | 130 | 120 | 500 | ...... | end |
// --------------------------------------------------------------------------------------------
//
// 接下来就是push()操作了, 参考前面的push()
////////////////////////////////////////////////////////////////////////////////

template <class RandomAccessIterator, class Distance, class T>
void __adjust_heap(RandomAccessIterator first, Distance holeIndex,
                   Distance len, T value)
{
  Distance topIndex = holeIndex;
  Distance secondChild = 2 * holeIndex + 2;     // 弹出元素的有子孩

  // 调整heap元素位置
  while (secondChild < len) {
    // 选择两个子孩中较大的进行操作, 使用secondChild表示其偏移
    if (*(first + secondChild) < *(first + (secondChild - 1)))
      secondChild--;

    // 将较大元素向上填充, 并将整体偏移向下调整, 继续调整
    *(first + holeIndex) = *(first + secondChild);
    holeIndex = secondChild;
    secondChild = 2 * (secondChild + 1);
  }

  if (secondChild == len) {
    *(first + holeIndex) = *(first + (secondChild - 1));
    holeIndex = secondChild - 1;
  }

  // 这里就是shift_up过程了, 将最初的heap末尾元素向上调整
  // 侯捷老师对这里的理解有误, :-), 人非圣贤, 孰能无过, ^_^
  __push_heap(first, holeIndex, topIndex, value);
}

template <class RandomAccessIterator, class T, class Distance>
inline void __pop_heap(RandomAccessIterator first, RandomAccessIterator last,
                       RandomAccessIterator result, T value, Distance*)
{
  // 将弹出的元素调整到heap末尾, 这个元素需要用户手动弹出
  *result = *first;

  // 去掉末尾哪个弹出的元素, 调整heap
  __adjust_heap(first, Distance(0), Distance(last - first), value);
}

template <class RandomAccessIterator, class T>
inline void __pop_heap_aux(RandomAccessIterator first,
                           RandomAccessIterator last, T*)
{
  __pop_heap(first, last - 1, last - 1, T(*(last - 1)), distance_type(first));
}

template <class RandomAccessIterator>
inline void pop_heap(RandomAccessIterator first, RandomAccessIterator last)
{
  __pop_heap_aux(first, last, value_type(first));
}

template <class RandomAccessIterator, class Distance, class T, class Compare>
void __adjust_heap(RandomAccessIterator first, Distance holeIndex,
                   Distance len, T value, Compare comp)
{
  Distance topIndex = holeIndex;
  Distance secondChild = 2 * holeIndex + 2;
  while (secondChild < len) {
    if (comp(*(first + secondChild), *(first + (secondChild - 1))))
      secondChild--;
    *(first + holeIndex) = *(first + secondChild);
    holeIndex = secondChild;
    secondChild = 2 * (secondChild + 1);
  }
  if (secondChild == len) {
    *(first + holeIndex) = *(first + (secondChild - 1));
    holeIndex = secondChild - 1;
  }
  __push_heap(first, holeIndex, topIndex, value, comp);
}

template <class RandomAccessIterator, class T, class Compare, class Distance>
inline void __pop_heap(RandomAccessIterator first, RandomAccessIterator last,
                       RandomAccessIterator result, T value, Compare comp,
                       Distance*)
{
  *result = *first;
  __adjust_heap(first, Distance(0), Distance(last - first), value, comp);
}

template <class RandomAccessIterator, class T, class Compare>
inline void __pop_heap_aux(RandomAccessIterator first,
                           RandomAccessIterator last, T*, Compare comp)
{
  __pop_heap(first, last - 1, last - 1, T(*(last - 1)), comp,
             distance_type(first));
}

template <class RandomAccessIterator, class Compare>
inline void pop_heap(RandomAccessIterator first, RandomAccessIterator last,
                     Compare comp)
{
    __pop_heap_aux(first, last, value_type(first), comp);
}

// 这个没设么好说的, 参考上面的分析吧
template <class RandomAccessIterator, class T, class Distance>
void __make_heap(RandomAccessIterator first, RandomAccessIterator last, T*,
                 Distance*)
{
  if (last - first < 2) return;
  Distance len = last - first;
  Distance parent = (len - 2)/2;

  while (true) {
    __adjust_heap(first, parent, len, T(*(first + parent)));
    if (parent == 0) return;
    parent--;
  }
}

template <class RandomAccessIterator>
inline void make_heap(RandomAccessIterator first, RandomAccessIterator last)
{
  __make_heap(first, last, value_type(first), distance_type(first));
}

template <class RandomAccessIterator, class Compare, class T, class Distance>
void __make_heap(RandomAccessIterator first, RandomAccessIterator last,
                 Compare comp, T*, Distance*)
{
  if (last - first < 2) return;
  Distance len = last - first;
  Distance parent = (len - 2)/2;

  while (true) {
    __adjust_heap(first, parent, len, T(*(first + parent)), comp);
    if (parent == 0) return;
    parent--;
  }
}

template <class RandomAccessIterator, class Compare>
inline void make_heap(RandomAccessIterator first, RandomAccessIterator last,
                      Compare comp)
{
  __make_heap(first, last, comp, value_type(first), distance_type(first));
}

// 这个能保证heap有序, 其实个人感觉没啥必要, 这样还不如直接用平衡二叉树
template <class RandomAccessIterator>
void sort_heap(RandomAccessIterator first, RandomAccessIterator last)
{
  while (last - first > 1) pop_heap(first, last--);
}

template <class RandomAccessIterator, class Compare>
void sort_heap(RandomAccessIterator first, RandomAccessIterator last,
               Compare comp)
{
  while (last - first > 1) pop_heap(first, last--, comp);
}

#if defined(__sgi) && !defined(__GNUC__) && (_MIPS_SIM != _MIPS_SIM_ABI32)
#pragma reset woff 1209
#endif

__STL_END_NAMESPACE

#endif /* __SGI_STL_INTERNAL_HEAP_H */

// Local Variables:
// mode:C++
// End: