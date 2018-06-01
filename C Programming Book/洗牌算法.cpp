/*
https://blog.csdn.net/robinjwong/article/details/18261393

该算法每次随机选取一个数，
然后将该数与数组中最后(或最前)的元素相交换(如果随机选中的是最后/最前的元素，
则相当于没有发生交换)；
然后缩小选取数组的范围，去掉最后的元素,即之前随机抽取出的数。
重复上面的过程，直到剩余数组的大小为1，即只有一个元素时结束：
*/

void shuffle(int* array, int len)
{
	int i = len;
	int j = 0;
	int temp = 0;

	if (i == 0)
	{
		return;
	}

	while (--i)
	{
		j = rand() % (i + 1);
		temp = array[i];
		array[i] = array[j];
		array[j] = temp;
	}
}

template< class RandomIt >
void random_shuffle(RandomIt first, RandomIt last)
{
	typename std::iterator_traits<RandomIt>::difference_type i, n;
	n = last - first;
	for (i = n - 1; i > 0; --i) {
		using std::swap;
		swap(first[i], first[std::rand() % (i + 1)]);
		// rand() % (i+1) isn't actually correct, because the generated number
		// is not uniformly distributed for most values of i. A correct implementation
		// will need to essentially reimplement C++11 std::uniform_int_distribution,
		// which is beyond the scope of this example.
	}
}




template<class RandomIt, class RandomFunc>
void random_shuffle(RandomIt first, RandomIt last, RandomFunc&& r)
{
	typename std::iterator_traits<RandomIt>::difference_type i, n;
	n = last - first;
	for (i = n - 1; i > 0; --i) {
		using std::swap;
		swap(first[i], first[r(i + 1)]);
	}
}




template<class RandomIt, class UniformRandomBitGenerator>
void shuffle(RandomIt first, RandomIt last,
	UniformRandomBitGenerator&& g)
{
	typedef typename std::iterator_traits<RandomIt>::difference_type diff_t;
	typedef std::uniform_int_distribution<diff_t> distr_t;
	typedef typename distr_t::param_type param_t;

	distr_t D;
	diff_t n = last - first;
	for (diff_t i = n - 1; i > 0; --i) {
		using std::swap;
		swap(first[i], first[D(g, param_t(0, i))]);
	}
}