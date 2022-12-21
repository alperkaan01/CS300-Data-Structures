#ifndef _BST
#define _BST


template <class Comparable>
class BinarySearchTree;

template <class Comparable>
class BinaryNode
{
public:
	Comparable element;
	Comparable info;
	BinaryNode  *left;
	BinaryNode  *right;
	BinarySearchTree<Comparable>  *innerTree;

	BinaryNode( const Comparable & theElement, 
		BinaryNode *lt, BinaryNode *rt, BinarySearchTree<Comparable>  *nxtT = NULL )
		: element( theElement ), left( lt ), right( rt ), innerTree(nxtT){
	}

	friend class BinarySearchTree<Comparable>;
};


template <class Comparable>
class Notebook;

template <class Comparable>
class BinarySearchTree
{
public:

	friend class Notebook<Comparable>;

	explicit BinarySearchTree(const Comparable &);
	BinarySearchTree(){
		root = nullptr;
		currentRoot = root;
	};
	BinarySearchTree(const BinarySearchTree &);
	~BinarySearchTree();

	BinaryNode<Comparable> * findNode(const Comparable &) const;

	BinaryNode<Comparable> * getRoot() const{
		return root;
	}

	BinaryNode<Comparable> * getCurrentRoot() const{
		return currentRoot;
	}

	const Comparable & findMin() const;
	const Comparable & findMax() const;
	const Comparable & find( const Comparable &) const;
	bool isEmpty() const;
	void printTree() const;

	void makeEmpty( );
	void insertBST( const Comparable &);
	void remove( const Comparable &);

	const BinarySearchTree & operator=( const BinarySearchTree &);
private:
	BinaryNode<Comparable> *root;
	BinaryNode<Comparable> *currentRoot;
	const Comparable ITEM_NOT_FOUND;

	const Comparable & elementAt( BinaryNode<Comparable> *) const;

	void insertBST( const Comparable &, BinaryNode<Comparable> * &);
	void remove( const Comparable &, BinaryNode<Comparable> * &) const;
	BinaryNode<Comparable> * findMin( BinaryNode<Comparable> *) const;
	BinaryNode<Comparable> * findMax( BinaryNode<Comparable> *) const;
	BinaryNode<Comparable> * find( const Comparable &, 
		BinaryNode<Comparable> *) const;
	void makeEmpty( BinaryNode<Comparable> * &) const;
	void printTree( BinaryNode<Comparable> *) const;
	BinaryNode<Comparable> * clone( BinaryNode<Comparable> *) const;
};

#include "BinarySearchTree.cpp"

#endif
