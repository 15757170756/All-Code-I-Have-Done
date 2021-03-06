/*-
* Copyright (c) 2013 Cosku Acay, http://www.coskuacay.com
*
* Permission is hereby granted, free of charge, to any person obtaining a
* copy of this software and associated documentation files (the "Software"),
* to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
* IN THE SOFTWARE.
*/

#ifndef MEMORY_POOL_H
#define MEMORY_POOL_H

#include <climits>
#include <cstddef>

template <typename T, size_t BlockSize = 4096>
class MemoryPool
{
public:
	/* Member types */
	typedef T               value_type;
	typedef T*              pointer;
	typedef T&              reference;
	typedef const T*        const_pointer;
	typedef const T&        const_reference;
	typedef size_t          size_type;
	typedef ptrdiff_t       difference_type;
	typedef std::false_type propagate_on_container_copy_assignment;
	typedef std::true_type  propagate_on_container_move_assignment;
	typedef std::true_type  propagate_on_container_swap;

	template <typename U> struct rebind {
		typedef MemoryPool<U> other;
	};

	/* Member functions */
	MemoryPool() noexcept;
	MemoryPool(const MemoryPool& memoryPool) noexcept;
	MemoryPool(MemoryPool&& memoryPool) noexcept;
	template <class U> MemoryPool(const MemoryPool<U>& memoryPool) noexcept;

	~MemoryPool() noexcept;

	MemoryPool& operator=(const MemoryPool& memoryPool) = delete;
	MemoryPool& operator=(MemoryPool&& memoryPool) noexcept;

	pointer address(reference x) const noexcept;
	const_pointer address(const_reference x) const noexcept;

	// Can only allocate one object at a time. n and hint are ignored
	pointer allocate(size_type n = 1, const_pointer hint = 0);
	void deallocate(pointer p, size_type n = 1);

	size_type max_size() const noexcept;

	template <class U, class... Args> void construct(U* p, Args&&... args);
	template <class U> void destroy(U* p);

	template <class... Args> pointer newElement(Args&&... args);
	void deleteElement(pointer p);

private:
	// 用于存储内存池中的对象槽, 
	// 要么被实例化为一个存放对象的槽, 
	// 要么被实例化为一个指向存放对象槽的槽指针
	union Slot_ {
		value_type element;
		Slot_* next;
	};
	// 数据指针
	typedef char* data_pointer_;
	// 对象槽
	typedef Slot_ slot_type_;
	// 对象槽指针
	typedef Slot_* slot_pointer_;

	// 指向当前内存区块
	slot_pointer_ currentBlock_;
	// 指向当前内存区块的一个对象槽
	slot_pointer_ currentSlot_;
	// 指向当前内存区块的最后一个对象槽
	slot_pointer_ lastSlot_;
	// 指向当前内存区块中的空闲对象槽
	slot_pointer_ freeSlots_;

	// 检查定义的内存池大小是否过小
	size_type padPointer(data_pointer_ p, size_type align) const noexcept;
	void allocateBlock();

	static_assert(BlockSize >= 2 * sizeof(slot_type_), "BlockSize too small.");
};

/*
在上面的类设计中可以看到，在这个内存池中，
其实是使用链表来管理整个内存池的内存区块的。
内存池首先会定义固定大小的基本内存区块(Block)，
然后在其中定义了一个可以实例化为存放对象内存槽的对象槽（Slot_）
和对象槽指针的一个联合。然后在区块中，
定义了四个关键性质的指针，它们的作用分别是：

currentBlock_: 指向当前内存区块的指针
currentSlot_: 指向当前内存区块中的对象槽
lastSlot_: 指向当前内存区块中的最后一个对象槽
freeSlots_: 指向当前内存区块中所有空闲的对象槽
*/

#include "MemoryPool.tcc"

#endif // MEMORY_POOL_H
