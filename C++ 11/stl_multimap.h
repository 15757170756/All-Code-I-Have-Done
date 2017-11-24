// Filename:    stl_multimap.h

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

#ifndef __SGI_STL_INTERNAL_MULTIMAP_H
#define __SGI_STL_INTERNAL_MULTIMAP_H

__STL_BEGIN_NAMESPACE

#if defined(__sgi) && !defined(__GNUC__) && (_MIPS_SIM != _MIPS_SIM_ABI32)
#pragma set woff 1174
#endif

// 如果编译器不能根据前面模板参数推导出后面使用的默认参数类型,
// 那么就需要手工指定, 本实作multimap内部元素默认使用less进行比较
// 内部维护的数据结构是红黑树, 具有非常优秀的最坏情况的时间复杂度
// 注意: 与map不同, multimap允许有重复的元素
#ifndef __STL_LIMITED_DEFAULT_TEMPLATES
template <class Key, class T, class Compare = less<Key>, class Alloc = alloc>
#else
template <class Key, class T, class Compare, class Alloc = alloc>
#endif
class multimap
{
public:
  // 这里和map定义相同, 见<setL_map.h>
  typedef Key key_type;
  typedef T data_type;
  typedef T mapped_type;
  typedef pair<const Key, T> value_type;
  typedef Compare key_compare;

  // 关于为什么继承自binary_function见<stl_function.h>中的讲解
  // 被嵌套类提供key的比较操作
  class value_compare : public binary_function<value_type, value_type, bool>
  {
  friend class multimap<Key, T, Compare, Alloc>;
  protected:
    Compare comp;
    value_compare(Compare c) : comp(c) {}
  public:
    bool operator()(const value_type& x, const value_type& y) const {
      return comp(x.first, y.first);
    }
  };

private:
  // 内部采用红黑树为数据结构, 其实现在<stl_tree.h>
  typedef rb_tree<key_type, value_type,
                  select1st<value_type>, key_compare, Alloc> rep_type;
  rep_type t;  // red-black tree representing multimap

public:
  // 标记为'STL标准强制要求'的typedefs用于提供iterator_traits<I>支持
  // 注意: 迭代器, 引用类型都设计为const, 这是由multimap的性质决定的,
  //      如果用户自行更改其数值, 可能会导致内部的红黑树出现问题
  typedef typename rep_type::pointer pointer;                  // STL标准强制要求
  typedef typename rep_type::const_pointer const_pointer;
  typedef typename rep_type::reference reference;              // STL标准强制要求
  typedef typename rep_type::const_reference const_reference;
  typedef typename rep_type::iterator iterator;                // STL标准强制要求
  typedef typename rep_type::const_iterator const_iterator;
  typedef typename rep_type::reverse_iterator reverse_iterator;
  typedef typename rep_type::const_reverse_iterator const_reverse_iterator;
  typedef typename rep_type::size_type size_type;
  typedef typename rep_type::difference_type difference_type;  // STL标准强制要求

  multimap() : t(Compare()) { }
  explicit multimap(const Compare& comp) : t(comp) { }

#ifdef __STL_MEMBER_TEMPLATES
  template <class InputIterator>
  multimap(InputIterator first, InputIterator last)
    : t(Compare()) { t.insert_equal(first, last); }

  template <class InputIterator>
  multimap(InputIterator first, InputIterator last, const Compare& comp)
    : t(comp) { t.insert_equal(first, last); }
#else
  multimap(const value_type* first, const value_type* last)
    : t(Compare()) { t.insert_equal(first, last); }
  multimap(const value_type* first, const value_type* last,
           const Compare& comp)
    : t(comp) { t.insert_equal(first, last); }

  multimap(const_iterator first, const_iterator last)
    : t(Compare()) { t.insert_equal(first, last); }
  multimap(const_iterator first, const_iterator last, const Compare& comp)
    : t(comp) { t.insert_equal(first, last); }
#endif /* __STL_MEMBER_TEMPLATES */

  multimap(const multimap<Key, T, Compare, Alloc>& x) : t(x.t) { }

  multimap<Key, T, Compare, Alloc>&
  operator=(const multimap<Key, T, Compare, Alloc>& x)
  {
    t = x.t;
    return *this;
  }

  // 返回用于key比较的函数
  key_compare key_comp() const { return t.key_comp(); }

  // 由于multimap的性质, value比较和key使用同一个比较函数
  value_compare value_comp() const { return value_compare(t.key_comp()); }

  iterator begin() { return t.begin(); }
  const_iterator begin() const { return t.begin(); }
  iterator end() { return t.end(); }
  const_iterator end() const { return t.end(); }
  reverse_iterator rbegin() { return t.rbegin(); }
  const_reverse_iterator rbegin() const { return t.rbegin(); }
  reverse_iterator rend() { return t.rend(); }
  const_reverse_iterator rend() const { return t.rend(); }
  bool empty() const { return t.empty(); }
  size_type size() const { return t.size(); }
  size_type max_size() const { return t.max_size(); }

  // 这里调用的是专用的swap, 不是全局的swap, 定于于<stl_tree.h>
  void swap(multimap<Key, T, Compare, Alloc>& x) { t.swap(x.t); }

  // 插入元素, 注意, 插入的元素key允许重复
  iterator insert(const value_type& x) { return t.insert_equal(x); }

  // 在position处插入元素, 但是position仅仅是个提示, 如果给出的位置不能进行插入,
  // STL会进行查找, 这会导致很差的效率
  iterator insert(iterator position, const value_type& x)
  {
    return t.insert_equal(position, x);
  }

#ifdef __STL_MEMBER_TEMPLATES
  template <class InputIterator>
  void insert(InputIterator first, InputIterator last)
  {
    t.insert_equal(first, last);
  }
#else
  void insert(const value_type* first, const value_type* last) {
    t.insert_equal(first, last);
  }
  void insert(const_iterator first, const_iterator last) {
    t.insert_equal(first, last);
  }
#endif /* __STL_MEMBER_TEMPLATES */

  // 擦除指定位置的元素, 会导致内部的红黑树重新排列
  void erase(iterator position) { t.erase(position); }

  // 会返回擦除元素的个数
  size_type erase(const key_type& x) { return t.erase(x); }

  // 擦除指定区间的元素, 会导致红黑树有较大变化
  void erase(iterator first, iterator last) { t.erase(first, last); }

  // 好吧, clear all, 再见吧红黑树
  void clear() { t.clear(); }

  // 查找指定的元素
  iterator find(const key_type& x) { return t.find(x); }
  const_iterator find(const key_type& x) const { return t.find(x); }

  // 返回指定元素的个数
  size_type count(const key_type& x) const { return t.count(x); }

  // 返回小于当前元素的第一个可插入的位置
  iterator lower_bound(const key_type& x) {return t.lower_bound(x); }
  const_iterator lower_bound(const key_type& x) const
  {
    return t.lower_bound(x);
  }

  // 返回大于当前元素的第一个可插入的位置
  iterator upper_bound(const key_type& x) {return t.upper_bound(x); }
  const_iterator upper_bound(const key_type& x) const
  {
    return t.upper_bound(x);
  }

  pair<iterator,iterator> equal_range(const key_type& x)
  {
    return t.equal_range(x);
  }

  pair<const_iterator,const_iterator> equal_range(const key_type& x) const
  {
    return t.equal_range(x);
  }

  friend bool operator== __STL_NULL_TMPL_ARGS (const multimap&,
                                               const multimap&);
  friend bool operator< __STL_NULL_TMPL_ARGS (const multimap&,
                                              const multimap&);
};

// 比较两个multimap比较的是其内部的红黑树, 会触发红黑树的operator

template <class Key, class T, class Compare, class Alloc>
inline bool operator==(const multimap<Key, T, Compare, Alloc>& x,
                       const multimap<Key, T, Compare, Alloc>& y)
{
  return x.t == y.t;
}

template <class Key, class T, class Compare, class Alloc>
inline bool operator<(const multimap<Key, T, Compare, Alloc>& x,
                      const multimap<Key, T, Compare, Alloc>& y)
{
  return x.t < y.t;
}

// 如果编译器支持模板函数特化优先级
// 那么将全局的swap实现为使用multimap私有的swap以提高效率
#ifdef __STL_FUNCTION_TMPL_PARTIAL_ORDER

template <class Key, class T, class Compare, class Alloc>
inline void swap(multimap<Key, T, Compare, Alloc>& x,
                 multimap<Key, T, Compare, Alloc>& y)
{
  x.swap(y);
}

#endif /* __STL_FUNCTION_TMPL_PARTIAL_ORDER */

#if defined(__sgi) && !defined(__GNUC__) && (_MIPS_SIM != _MIPS_SIM_ABI32)
#pragma reset woff 1174
#endif

__STL_END_NAMESPACE

#endif /* __SGI_STL_INTERNAL_MULTIMAP_H */

// Local Variables:
// mode:C++
// End: