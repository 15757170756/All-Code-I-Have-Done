// Filename:    stl_map.h

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

#ifndef __SGI_STL_INTERNAL_MAP_H
#define __SGI_STL_INTERNAL_MAP_H

__STL_BEGIN_NAMESPACE

#if defined(__sgi) && !defined(__GNUC__) && (_MIPS_SIM != _MIPS_SIM_ABI32)
#pragma set woff 1174
#endif

// 如果编译器不能根据前面模板参数推导出后面使用的默认参数类型,
// 那么就需要手工指定, 本实作map内部元素默认使用less进行比较, 其排序以key作为参照
// 内部维护的数据结构是红黑树, 具有非常优秀的最坏情况的时间复杂度
// 注意: map内元素的key不可一重复, 但是value允许重复
#ifndef __STL_LIMITED_DEFAULT_TEMPLATES
template <class Key, class T, class Compare = less<Key>, class Alloc = alloc>
#else
template <class Key, class T, class Compare, class Alloc = alloc>
#endif
class map {
public:
  typedef Key key_type;                         // key类型
  typedef T data_type;                          // value类型
  typedef T mapped_type;
  typedef pair<const Key, T> value_type;        // 元素类型, 要保证key不被修改
  typedef Compare key_compare;                  // 用于key比较的函数

  // 关于为什么继承自binary_function见<stl_function.h>中的讲解
  // 被嵌套类提供key的比较操作
  class value_compare
    : public binary_function<value_type, value_type, bool>
  {
  friend class map<Key, T, Compare, Alloc>;
  protected :
    Compare comp;
    value_compare(Compare c) : comp(c) {}
  public:
    bool operator()(const value_type& x, const value_type& y) const {
      return comp(x.first, y.first);
    }
  };

private:
  // 内部采用红黑树为数据结构, 其实现在<stl_tree.h>
  // 由于我剖析的版本没有侯捷老师的详细, 给出的是侯捷老师的版本
  typedef rb_tree<key_type, value_type,
                  select1st<value_type>, key_compare, Alloc> rep_type;
  rep_type t;  // red-black tree representing map

public:
  // 标记为'STL标准强制要求'的typedefs用于提供iterator_traits<I>支持
  // 注意: 迭代器, 引用类型都设计为const, 这是由map的性质决定的,
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

  map() : t(Compare()) {}
  explicit map(const Compare& comp) : t(comp) {}

#ifdef __STL_MEMBER_TEMPLATES
  template <class InputIterator>
  map(InputIterator first, InputIterator last)
    : t(Compare()) { t.insert_unique(first, last); }

  template <class InputIterator>
  map(InputIterator first, InputIterator last, const Compare& comp)
    : t(comp) { t.insert_unique(first, last); }
#else
  map(const value_type* first, const value_type* last)
    : t(Compare()) { t.insert_unique(first, last); }
  map(const value_type* first, const value_type* last, const Compare& comp)
    : t(comp) { t.insert_unique(first, last); }

  map(const_iterator first, const_iterator last)
    : t(Compare()) { t.insert_unique(first, last); }
  map(const_iterator first, const_iterator last, const Compare& comp)
    : t(comp) { t.insert_unique(first, last); }
#endif /* __STL_MEMBER_TEMPLATES */

  map(const map<Key, T, Compare, Alloc>& x) : t(x.t) {}

  map<Key, T, Compare, Alloc>& operator=(const map<Key, T, Compare, Alloc>& x)
  {
    t = x.t;
    return *this;
  }


  // 返回用于key比较的函数
  key_compare key_comp() const { return t.key_comp(); }

  // 由于map的性质, value和key使用同一个比较函数, 实际上我们并不使用value比较函数
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

  // 注意: 这里有一个常见的陷阱, 如果访问的key不存在, 会新建立一个
  T& operator[](const key_type& k)
  {
    return (*((insert(value_type(k, T()))).first)).second;
  }

  // 返回的pair.second用于告知用户insert操作是否执行
  // 为true则表示真正进行插入, 为false则表示set中已存在待插入元素,
  // 不会重复插入
  void swap(map<Key, T, Compare, Alloc>& x) { t.swap(x.t); }

  // 对于相同的key, 只允许出现一次, bool标识
  pair<iterator,bool> insert(const value_type& x) { return t.insert_unique(x); }

  // 在position处插入元素, 但是position仅仅是个提示, 如果给出的位置不能进行插入,
  // STL会进行查找, 这会导致很差的效率
  iterator insert(iterator position, const value_type& x)
  {
    return t.insert_unique(position, x);
  }

#ifdef __STL_MEMBER_TEMPLATES
  template <class InputIterator>
  void insert(InputIterator first, InputIterator last) {
    t.insert_unique(first, last);
  }
#else
  void insert(const value_type* first, const value_type* last) {
    t.insert_unique(first, last);
  }
  void insert(const_iterator first, const_iterator last) {
    t.insert_unique(first, last);
  }
#endif /* __STL_MEMBER_TEMPLATES */

  // 擦除指定位置的元素, 会导致内部的红黑树重新排列
  void erase(iterator position) { t.erase(position); }

  // 会返回擦除元素的个数, 其实就是标识map内原来是否有指定的元素
  size_type erase(const key_type& x) { return t.erase(x); }
  void erase(iterator first, iterator last) { t.erase(first, last); }

  // 好吧, clear all, 再见吧红黑树
  void clear() { t.clear(); }

  // 查找指定key的元素
  iterator find(const key_type& x) { return t.find(x); }
  const_iterator find(const key_type& x) const { return t.find(x); }

  // 返回指定元素的个数, 其实就是测试元素是否在map中
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

  friend bool operator== __STL_NULL_TMPL_ARGS (const map&, const map&);
  friend bool operator< __STL_NULL_TMPL_ARGS (const map&, const map&);
};

// 比较两个multiset比较的是其内部的红黑树, 会触发红黑树的operator

template <class Key, class T, class Compare, class Alloc>
inline bool operator==(const map<Key, T, Compare, Alloc>& x,
                       const map<Key, T, Compare, Alloc>& y)
{
  return x.t == y.t;
}

template <class Key, class T, class Compare, class Alloc>
inline bool operator<(const map<Key, T, Compare, Alloc>& x,
                      const map<Key, T, Compare, Alloc>& y)
{
  return x.t < y.t;
}

#ifdef __STL_FUNCTION_TMPL_PARTIAL_ORDER

// 如果编译器支持模板函数特化优先级
// 那么将全局的swap实现为使用map私有的swap以提高效率
template <class Key, class T, class Compare, class Alloc>
inline void swap(map<Key, T, Compare, Alloc>& x,
                 map<Key, T, Compare, Alloc>& y)
{
  x.swap(y);
}

#endif /* __STL_FUNCTION_TMPL_PARTIAL_ORDER */

#if defined(__sgi) && !defined(__GNUC__) && (_MIPS_SIM != _MIPS_SIM_ABI32)
#pragma reset woff 1174
#endif

__STL_END_NAMESPACE

#endif /* __SGI_STL_INTERNAL_MAP_H */

// Local Variables:
// mode:C++
// End: