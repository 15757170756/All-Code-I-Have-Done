#include<cstring>
#include<iostream>
#include<conio.h>
using namespace std;
namespace trie
{
	template<class T, size_t CHILD_MAX>
	/*
	ParameterT:Typeofreserveddata.
	ParameterCHILD_MAX:Sizeofarryofpointerstochildnode.
	*/
	struct nod
	{
		T reserved;
		nod<T, CHILD_MAX>* child[CHILD_MAX];
		nod()
		{
			memset(this, 0, sizeof(*this));
		}
		~nod()
		{
			for (unsigned i = 0; i<CHILD_MAX; i++)
				delete child[i];
		}
		void Traversal(char* str, unsigned index)
		{
			unsigned i;
			for (i = 0; i<index; i++)
				cout << str[i];
			cout << '\t' << reserved << endl;
			for (i = 0; i<CHILD_MAX; i++)
			{
				if (child[i])
				{
					str[index] = i;
					child[i]->Traversal(str, index + 1);
				}
			}
			return;
		}
	};

	template<class T, size_t CHILD_MAX = 127>
	/*
	ParameterT:Typeofreserveddata.
	ParameterCHILD_MAX:Sizeofarryofpointerstochildnode.
	*/
	class trie
	{
	private:
		nod<T, CHILD_MAX> root;
	public:
		nod<T, CHILD_MAX>* AddStr(char* str);
		nod<T, CHILD_MAX>* FindStr(char* str);
		bool DeleteStr(char* str);
		void Traversal()
		{
			char str[100];
			root.Traversal(str, 0);
		}
	};

	template<class T, size_t CHILD_MAX>
	nod<T, CHILD_MAX>* trie<T, CHILD_MAX>::AddStr(char* str)
	{
		nod<T, CHILD_MAX>* now = &root;
		do
		{
			if (now->child[*str] == NULL)
				now->child[*str] = new nod<T, CHILD_MAX>;
			now = now->child[*str];
		} while (*(++str) != '\0');
		return now;
	}

	template<class T, size_t CHILD_MAX>
	nod<T, CHILD_MAX>* trie<T, CHILD_MAX>::FindStr(char*str)
	{
		nod<T, CHILD_MAX>*now = &root;
		do
		{
			if (now->child[*str] == NULL)
				return NULL;
			now = now->child[*str];
		} while (*(++str) != '\0');
		return now;
	}

	template<class T, size_t CHILD_MAX>
	bool trie<T, CHILD_MAX>::DeleteStr(char*str)
	{
		nod<T, CHILD_MAX>** nods = new nod<T, CHILD_MAX>*[strlen(str)];
		int snods = 1;
		nod<T, CHILD_MAX>* now = &root;
		nods[0] = &root;
		do
		{
			if (now->child[*str] == NULL)
				return false;
			nods[snods++] = now = now->child[*str];
		} while (*(++str) != '\0');
		snods--;
		while (snods>0)
		{
			for (unsigned i = 0; i<CHILD_MAX; i++)
				if (nods[snods]->child[i] != NULL)
					return true;
			delete nods[snods];
			nods[--snods]->child[*(--str)] = NULL;
		}
		return true;
	}
}
int main()
{
	//Test Program
	trie::trie<int> tree;
	while (1)
	{
		cout << "1 for addastring" << endl;
		cout << "2 for findastring" << endl;
		cout << "3 for deleteastring" << endl;
		cout << "4 for traversal" << endl;
		cout << "5 for exit" << endl;
		char str[100];
		switch (getch())
		{
		case'1':
			cin.getline(str, 100);
			cout << "This sting has existed for " << tree.AddStr(str)->reserved++ << " times." << endl;
			break;
		case'2':
			cin.getline(str, 100);
			trie::nod<int, 127>*find;
			find = tree.FindStr(str);
			if (!find)
				cout << "No found." << endl;
			else
				cout << "This sting has existed for " << find->reserved << " times." << endl;
			break;
		case'3':
			cin.getline(str, 100);
			cout << "The action is " << (tree.DeleteStr(str) ? "Successful." : "Unsuccessful.") << endl;
			break;
		case'4':
			tree.Traversal();
			break;
		case'5':
			return 0;
		}
	}
	return 0;
}

