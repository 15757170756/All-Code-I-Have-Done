/*
编写推荐系统的打散策略,输入是按得分从高到低排序的文章数组，
数组长度1-100，输出10篇打散后的推荐文章结果要求如下：

3.1结果文章至少含有3个类目
3.2相同类目的文章不能相邻
3.3当结果不足时，忽略以上要求，优先保证有结果
3.4满足上述要求下，得分保持相对有序

*/

/*
我的想法是：既然得分已经从高到低排序了，那这样就依次从
第一篇文章push近resultVec，因为相同类目的文章不能相邻，
这个好判断，但是同时要兼顾至少含有3各类目，而且第三个条件
有些变态的，要优先保证有结果。如果依次取的话，第四个条件就可以满足了

*/
struct ArticleNode
{
	unsigned int article_id; // 文章标识
	unsigned int category_id; // 类目标识
	float score; // 文章得分
};
int MixArticle(vector<ArticleNode> & nodeVec, vector<ArticleNode> & resultVec)
{

}




struct ArticleNode
{
	unsigned int article_id; // 文章标识
	unsigned int category_id; // 类目标识
	float score; // 文章得分
	ArticleNode(unsigned int article_id = 0,
		unsigned int category_id = 0,
		float score = 0.0) :
		article_id(article_id),
		category_id(category_id),
		score(score) {}
};

bool cmpBycategory_id(const ArticleNode & Article1,
	const ArticleNode & Article2)
{
	return Article1.category_id < Article2.category_id;
}

bool cmpByscore(const ArticleNode & Article1,
	const ArticleNode & Article2)
{
	return Article1.score > Article2.score;
}

int MixArticle(vector<ArticleNode> & nodeVec,
	vector<ArticleNode> & resultVec)
{
	unsigned int category_id0 = nodeVec[0].category_id;
	int lastIndex;
	vector<int> category;
	resultVec.emplace_back(nodeVec[0]);
	category.emplace_back(category_id0);
	for (int i = 1; i < nodeVec.size(); ++i) {
		lastIndex = i;
		ArticleNode tempArticle = nodeVec[i];
		if (tempArticle.category_id != category_id0) {
			resultVec.emplace_back(tempArticle);
			int totalCategory = 0;
			for (int j = 0; j < category.size(); ++j) {
				if (tempArticle.category_id != category[j]) {
					++totalCategory;
				}
			}
			if (totalCategory == category.size())
				category.emplace_back(tempArticle.category_id);

			category_id0 = tempArticle.category_id;
		}
		if (resultVec.size() >= 10)
			break;
	}
	if (resultVec.size() < 10) {
		for (int i = 0; i < nodeVec.size(); ++i) {
			resultVec.emplace_back(nodeVec[i]);
			if (resultVec.size() >= 10)
				break;
		}
	}
	else {
		if (category.size() >= 3)
			return 0;
		else {
			resultVec.pop_back();
			for (int i = 0; i < nodeVec.size(); ++i) {
				ArticleNode tempAtricle = nodeVec[i];
				if (tempAtricle.category_id !=
					resultVec[resultVec.size() - 1].category_id) {
					for (int j = 0; j < category.size(); ++j) {
						if (tempAtricle.category_id != category[j]) {
							resultVec.emplace_back(tempAtricle);
							return 0;
						}
					}
				}
			}
		}
	}
	return 0;
}

void testMixArticle()
{
	vector<ArticleNode> nodeVec, resultVec;
	nodeVec.reserve(100);
	for (int i = 0; i < 100; ++i) {
		nodeVec.emplace_back(rand() % 10, rand() % 3, rand());
	}
	sort(nodeVec.begin(), nodeVec.end(), cmpByscore);
	MixArticle(nodeVec, resultVec);
	for (int i = 0; i < resultVec.size(); ++i) {
		ArticleNode tempArticle = resultVec[i];
		cout << tempArticle.article_id << ' ' <<
			tempArticle.category_id << ' ' <<
			tempArticle.score << ' ' << endl;
	}

}