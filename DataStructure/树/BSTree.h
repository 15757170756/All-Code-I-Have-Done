/*************************************************************************
> File Name: BTREE.h
> Author: licf
> Mail: licf.xdu@gmail.com
************************************************************************/

#ifndef BSTREE_H_
#define BSTREE_H_

template<typename type>
class BSTree 
{
private:
	class BSTNode
	{
	public:
		BSTNode *left;
		BSTNode *right;
		type data;
		BSTNode() :left(nullptr), right(nullptr) {}
	};

	typedef BSTNode *BSTNodePtr;
	BSTNodePtr root;

public:
	BSTree() :root(nullptr) {}
	~BSTree() { deleteNode(root); }
	bool isEmpty() const { return root == nullptr; }
	bool find(const type &a_data) const;
	void insert(const type &a_data) { insertAux(root, a_data); }
	void remove(const type &a_data);
	void inorder(ostream &out) const { inorderAux(out.root); }
	void graph(ostream &out) const { graphAux(out, 0, root); }

protected:
	void deleteNode(BSTNodePtr a_node);
	void insertAux(BSTNodePtr &a_subRoot, const type &a_data);
	void inorderAux(ostream &out, BSTNodePtr a_subRoot) const;
	void graphAux(ostream &out, int a_indent, BSTNodePtr a_subRoot) const;
	void find2(const type &a_data, bool &found, BSTNodePtr &a_locPtr, BSTNodePtr &a_parent) const;
};

#endif