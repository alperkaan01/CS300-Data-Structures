#ifndef _BST
#define _BST


template <class Comparable>
class BinarySearchTree;

template <class Comparable>
class BinaryNode
{
public:
	Comparable element;
	BinaryNode  *left;
	BinaryNode  *right;

	BinaryNode( const Comparable & theElement, 
		BinaryNode *lt, BinaryNode *rt, BinarySearchTree<Comparable>  *nxtT = NULL )
		: element( theElement ), left( lt ), right( rt ){
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
	};
	BinarySearchTree(const BinarySearchTree &);
	~BinarySearchTree();

	BinaryNode<Comparable> * findNode( Comparable );

	BinaryNode<Comparable> * getRoot() const{
		return root;
	}

	const Comparable & findMin();
	const Comparable & findMax();
	const Comparable & find( Comparable );
	bool isEmpty() const;
	void printTree();

	void makeEmpty( );
	void insertBST( Comparable );
	void remove( Comparable );

	const BinarySearchTree & operator=( const BinarySearchTree &);
private:
	BinaryNode<Comparable> *root;
	const Comparable ITEM_NOT_FOUND;

	const Comparable & elementAt( BinaryNode<Comparable> *) const;

	void insertBST( Comparable, BinaryNode<Comparable> * &);
	void remove( Comparable , BinaryNode<Comparable> * &);
	BinaryNode<Comparable> * findMin( BinaryNode<Comparable> *);
	BinaryNode<Comparable> * findMax( BinaryNode<Comparable> *);
	BinaryNode<Comparable> * find( Comparable, 
		BinaryNode<Comparable> *);
	void makeEmpty( BinaryNode<Comparable> * &) const;
	void printTree( BinaryNode<Comparable> *);
	BinaryNode<Comparable> * clone( BinaryNode<Comparable> *) const;
};

#include "BinarySearchTree.cpp"

#endif
