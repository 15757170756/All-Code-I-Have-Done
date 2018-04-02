/*
��д�Ƽ�ϵͳ�Ĵ�ɢ����,�����ǰ��÷ִӸߵ���������������飬
���鳤��1-100�����10ƪ��ɢ����Ƽ����½��Ҫ�����£�

3.1����������ٺ���3����Ŀ
3.2��ͬ��Ŀ�����²�������
3.3���������ʱ����������Ҫ�����ȱ�֤�н��
3.4��������Ҫ���£��÷ֱ����������

*/

/*
�ҵ��뷨�ǣ���Ȼ�÷��Ѿ��Ӹߵ��������ˣ������������δ�
��һƪ����push��resultVec����Ϊ��ͬ��Ŀ�����²������ڣ�
������жϣ�����ͬʱҪ������ٺ���3����Ŀ�����ҵ���������
��Щ��̬�ģ�Ҫ���ȱ�֤�н�����������ȡ�Ļ������ĸ������Ϳ���������

*/
struct ArticleNode
{
	unsigned int article_id; // ���±�ʶ
	unsigned int category_id; // ��Ŀ��ʶ
	float score; // ���µ÷�
};
int MixArticle(vector<ArticleNode> & nodeVec, vector<ArticleNode> & resultVec)
{

}




struct ArticleNode
{
	unsigned int article_id; // ���±�ʶ
	unsigned int category_id; // ��Ŀ��ʶ
	float score; // ���µ÷�
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