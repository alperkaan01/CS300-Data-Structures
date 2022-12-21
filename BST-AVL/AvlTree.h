#ifndef _AVL_H
#define _AVL_H

template <class Comparable>
class AvlTree;

template <class Comparable>
class AvlNode
{
public:
	Comparable 	element;
	Comparable 	info;
	AvlNode   		*left;
	AvlNode   		*right;
	AvlTree<Comparable>   *innerTree;
	int        		height;

	AvlNode( const Comparable & theElement, 
		AvlNode *lt, AvlNode *rt, int h = 0, AvlTree<Comparable>   *it = NULL)
		: element( theElement ), left( lt ), right( rt ), height( h ), innerTree(it) {
	}

	friend class AvlTree<Comparable>;
};

template <class Comparable>
class Notebook;

template <class Comparable>
class AvlTree
{
public:

	friend class Notebook<Comparable>;

	explicit AvlTree( const Comparable & notFound );
	AvlTree( const AvlTree & rhs );
	~AvlTree();
	AvlTree(){
		root = nullptr;
		currentAVLNode = nullptr;
	};

	void setRoot(AvlNode<Comparable> * temp){
		this->root = temp;
	};

	int getDifference(AvlNode<Comparable> *) const;

	AvlNode<Comparable> * getRoot() const { return root; };
	AvlNode<Comparable> * getcurNode() const { return currentAVLNode; };
	AvlNode<Comparable> * findNode(const Comparable &) const;

	const Comparable & findMin() const;
	const Comparable & findMax() const;
	const Comparable & find( const Comparable & x) const;
	bool isEmpty( ) const;
	void printTree( ) const;

	void makeAVLEmpty( );
	void insertAVL( const Comparable & x );
	void removeAVL( const Comparable & x );

	const AvlTree & operator=( const AvlTree & rhs );
private:
	AvlNode<Comparable> *root;
	AvlNode<Comparable> *currentAVLNode;
	const Comparable ITEM_NOT_FOUND;

	const Comparable & elementAt( AvlNode<Comparable> *t ) const;

	void insertAVL( const Comparable & x, AvlNode<Comparable> * & t );
	void removeAVL(const Comparable & x, AvlNode<Comparable> * & t ) const;

	AvlNode<Comparable> * findMin( AvlNode<Comparable> *t ) const;
	AvlNode<Comparable> * findMax( AvlNode<Comparable> *t ) const;
	AvlNode<Comparable> * find( const Comparable & x, AvlNode<Comparable> *t ) 
		const;
	void makeAVLEmpty( AvlNode<Comparable> * & t ) const;
	void printTree( AvlNode<Comparable> *t ) const;
	AvlNode<Comparable> * clone( AvlNode<Comparable> *t ) const;

	// Avl manipulations
	int height( AvlNode<Comparable> *t ) const;
	int max( int lhs, int rhs ) const;
	void rotateWithLeftChild( AvlNode<Comparable> * & k2 ) const;
	void rotateWithRightChild( AvlNode<Comparable> * & k1 ) const;
	void doubleWithLeftChild( AvlNode<Comparable> * & k3 ) const;
	void doubleWithRightChild( AvlNode<Comparable> * &) const;
};

#include "AvlTree.cpp"

#endif
