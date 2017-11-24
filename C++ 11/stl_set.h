// Filename:    stl_set.h

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

#ifndef __SGI_STL_INTERNAL_SET_H
#define __SGI_STL_INTERNAL_SET_H

__STL_BEGIN_NAMESPACE

#if defined(__sgi) && !defined(__GNUC__) && (_MIPS_SIM != _MIPS_SIM_ABI32)
#pragma set woff 1174
#endif

// 如果编译器不能根据前面模板参数推导出后面使用的默认参数类型,
// 那么就需要手工指定, 本实作set内部元素默认使用less进行比较
// 内部维护的数据结构是红黑树, 具有非常优秀的最坏情况的时间复杂度
// 注意: set内不允许重复元素的存在, 如果插入重复元素,
//      则会忽略插入操作
#ifndef __STL_LIMITED_DEFAULT_TEMPLATES
template <class Key, class Compare = less<Key>, class Alloc = alloc>
#else
template <class Key, class Compare, class Alloc = alloc>
#endif
class set
{
public:
  //  在set中key就是value, value同时也是key
  typedef Key key_type;
  typedef Key value_type;

  // 用于比较的函数
  typedef Compare key_compare;
  typedef Compare value_compare;

private:
  // 内部采用红黑树为数据结构, 其实现在<stl_tree.h>
  // 由于我剖析的版本没有侯捷老师的详细, 给出的是侯捷老师的版本
  typedef rb_tree<key_type, value_type,
                  identity<value_type>, key_compare, Alloc> rep_type;
  rep_type t;

public:
  // 标记为'STL标准强制要求'的typedefs用于提供iterator_traits<I>支持
  // 注意: 迭代器, 引用类型都设计为const, 这是由set的性质决定的,
  //      如果用户自行更改其数值, 可能会导致内部的红黑树出现问题
  typedef typename rep_type::const_pointer pointer;            // STL标准强制要求
  typedef typename rep_type::const_pointer const_pointer;
  typedef typename rep_type::const_reference reference;        // STL标准强制要求
  typedef typename rep_type::const_reference const_reference;
  typedef typename rep_type::const_iterator iterator;          // STL标准强制要求
  typedef typename rep_type::const_iterator const_iterator;
  typedef typename rep_type::const_reverse_iterator reverse_iterator;
  typedef typename rep_type::const_reverse_iterator const_reverse_iterator;
  typedef typename rep_type::size_type size_type;
  typedef typename rep_type::difference_type difference_type;  // STL标准强制要求

  set() : t(Compare()) {}
  explicit set(const Compare& comp) : t(comp) {}

#ifdef __STL_MEMBER_TEMPLATES
  template <class InputIterator>
  set(InputIterator first, InputIterator last)
    : t(Compare()) { t.insert_unique(first, last); }

  template <class InputIterator>
  set(InputIterator first, InputIterator last, const Compare& comp)
    : t(comp) { t.insert_unique(first, last); }
#else
  set(const value_type* first, const value_type* last)
    : t(Compare()) { t.insert_unique(first, last); }
  set(const value_type* first, const value_type* last, const Compare& comp)
    : t(comp) { t.insert_unique(first, last); }

  set(const_iterator first, const_iterator last)
    : t(Compare()) { t.insert_unique(first, last); }
  set(const_iterator first, const_iterator last, const Compare& comp)
    : t(comp) { t.insert_unique(first, last); }
#endif /* __STL_MEMBER_TEMPLATES */

  set(const set<Key, Compare, Alloc>& x) : t(x.t) {}

  set<Key, Compare, Alloc>& operator=(const set<Key, Compare, Alloc>& x)
  {
    t = x.t;
    return *this;
  }

  // 返回用于key比较的函数
  key_compare key_comp() const { return t.key_comp(); }

  // 由于set的性质, value比较和key使用同一个比较函数
  value_compare value_comp() const { return t.key_comp(); }

  iterator begin() const { return t.begin(); }
  iterator end() const { return t.end(); }
  reverse_iterator rbegin() const { return t.rbegin(); }
  reverse_iterator rend() const { return t.rend(); }
  bool empty() const { return t.empty(); }
  size_type size() const { return t.size(); }
  size_type max_size() const { return t.max_size(); }

  // 这里调用的是专用的swap, 不是全局的swap, 定于于<stl_tree.h>
  void swap(set<Key, Compare, Alloc>& x) { t.swap(x.t); }

  typedef  pair<iterator, bool> pair_iterator_bool;

  // 返回的pair.second用于告知用户insert操作是否执行
  // 为true则表示真正进行插入, 为false则表示set中已存在待插入元素,
  // 不会重复插入
  pair<iterator,bool> insert(const value_type& x)
  {
    pair<typename rep_type::iterator, bool> p = t.insert_unique(x);
    return pair<iterator, bool>(p.first, p.second);
  }

  // 在position处插入元素, 但是position仅仅是个提示, 如果给出的位置不能进行插入,
  // STL会进行查找, 这会导致很差的效率
  iterator insert(iterator position, const value_type& x)
  {
    typedef typename rep_type::iterator rep_iterator;
    return t.insert_unique((rep_iterator&)position, x);
  }

#ifdef __STL_MEMBER_TEMPLATES
  template <class InputIterator>
  void insert(InputIterator first, InputIterator last)
  {
    t.insert_unique(first, last);
  }
#else
  void insert(const_iterator first, const_iterator last) {
    t.insert_unique(first, last);
  }
  void insert(const value_type* first, const value_type* last) {
    t.insert_unique(first, last);
  }
#endif /* __STL_MEMBER_TEMPLATES */

  // 擦除指定位置的元素, 会导致内部的红黑树重新排列
  void erase(iterator position)
  {
    typedef typename rep_type::iterator rep_iterator;
    t.erase((rep_iterator&)position);
  }

  // 会返回擦除元素的个数, 其实就是标识set内原来是否有指定的元素
  size_type erase(const key_type& x)
  {
    return t.erase(x);
  }

  // 擦除指定区间的元素, 会导致红黑树有较大变化
  void erase(iterator first, iterator last)
  {
    typedef typename rep_type::iterator rep_iterator;
    t.erase((rep_iterator&)first, (rep_iterator&)last);
  }

  // 好吧, clear all, 再见吧红黑树
  void clear() { t.clear(); }

  // 查找指定的元素
  iterator find(const key_type& x) const { return t.find(x); }

  // 返回指定元素的个数, 其实就是测试元素是否在set中
  size_type count(const key_type& x) const { return t.count(x); }

  // 返回小于当前元素的第一个可插入的位置
  iterator lower_bound(const key_type& x) const
  {
    return t.lower_bound(x);
  }

  // 返回大于当前元素的第一个可插入的位置
  iterator upper_bound(const key_type& x) const
  {
    return t.upper_bound(x);
  }

  pair<iterator,iterator> equal_range(const key_type& x) const
  {
    return t.equal_range(x);
  }

  friend bool operator== __STL_NULL_TMPL_ARGS (const set&, const set&);
  friend bool operator< __STL_NULL_TMPL_ARGS (const set&, const set&);
};

// 比较两个set比较的是其内部的红黑树, 会触发红黑树的operator

template <class Key, class Compare, class Alloc>
inline bool operator==(const set<Key, Compare, Alloc>& x,
                       const set<Key, Compare, Alloc>& y) {
  return x.t == y.t;
}

template <class Key, class Compare, class Alloc>
inline bool operator<(const set<Key, Compare, Alloc>& x,
                      const set<Key, Compare, Alloc>& y) {
  return x.t < y.t;
}

// 如果编译器支持模板函数特化优先级
// 那么将全局的swap实现为使用set私有的swap以提高效率
#ifdef __STL_FUNCTION_TMPL_PARTIAL_ORDER

template <class Key, class Compare, class Alloc>
inline void swap(set<Key, Compare, Alloc>& x,
                 set<Key, Compare, Alloc>& y)
{
  x.swap(y);
}

#endif /* __STL_FUNCTION_TMPL_PARTIAL_ORDER */

#if defined(__sgi) && !defined(__GNUC__) && (_MIPS_SIM != _MIPS_SIM_ABI32)
#pragma reset woff 1174
#endif

__STL_END_NAMESPACE

#endif /* __SGI_STL_INTERNAL_SET_H */

// Local Variables:
// mode:C++
// End: