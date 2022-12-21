#include <iostream>
#include <string>
using namespace std;

/**
* Construct the tree.
*/
template <class Comparable>
BinarySearchTree<Comparable>::
	BinarySearchTree(const Comparable & notFound ) :
	ITEM_NOT_FOUND( notFound ), root( NULL )
{
}

/**
* Internal method to get element field in node t.
* Return the element field or ITEM_NOT_FOUND if t is NULL.
*/
template <class Comparable>
const Comparable & BinarySearchTree<Comparable>::
	elementAt( BinaryNode<Comparable> *t ) const
{
	return t == NULL ? ITEM_NOT_FOUND : t->element;
}

/**
* Find item x in the tree.
* Return the matching item or ITEM_NOT_FOUND if not found.
*/
template <class Comparable>
const Comparable & BinarySearchTree<Comparable>::
	find( Comparable x )
{
	return elementAt( find( x, root ) );
}

template <class Comparable>
BinaryNode<Comparable> *
	BinarySearchTree<Comparable>::
	findNode( Comparable x )
{
	return find( x, root );
}

/**
* Internal method to find an item in a subtree.
* x is item to search for.
* t is the node that roots the tree.
* Return node containing the matched item.
*/
template <class Comparable>
BinaryNode<Comparable> *
	BinarySearchTree<Comparable>::
	find( Comparable  x, BinaryNode<Comparable> * t )
{
	BinaryNode<Comparable> * temp = t;
	while(temp != NULL && temp->element != x){
		if(x > temp->element)
			temp = temp->right;
		else if(x < temp->element)
			temp = temp->left;
	}
	if(temp == NULL)
		return NULL;
	else
		return temp;
}

/**
* Find the smallest item in the tree.
* Return smallest item or ITEM_NOT_FOUND if empty.
*/
template <class Comparable>
const Comparable & BinarySearchTree<Comparable>::findMin( )
{
	return elementAt( findMin( root ) );
}

/**
* Internal method to find the smallest item in a subtree t.
* Return node containing the smallest item.
*/
template <class Comparable>
BinaryNode<Comparable> *
	BinarySearchTree<Comparable>::findMin( BinaryNode<Comparable> *t ) 
{
	if(t == nullptr)
		return nullptr;
	else{
		while(t->left != NULL)
			t = t->left;
		return t;
	}
}

/**
* Internal method to find the largest item in a subtree t.
* Return node containing the largest item.
*/
template <class Comparable>
BinaryNode<Comparable> *
	BinarySearchTree<Comparable>::findMax( BinaryNode<Comparable> *t )
{
	if( t != NULL )
		while( t->right != NULL )
			t = t->right;
	return t;
}

/**
* Find the smallest item in the tree.
* Return smallest item or ITEM_NOT_FOUND if empty.
*/
template <class Comparable>
const Comparable & BinarySearchTree<Comparable>::findMax()
{
	return elementAt(findMax(root));
}

/**
* Insert x into the tree; duplicates are ignored.
*/
template <class Comparable>
void BinarySearchTree<Comparable>::insertBST( Comparable x)
{
	insertBST( x, root );
}

/**
* Internal method to insert into a subtree.
* x is the item to insert.
* t is the node that roots the tree.
* Set the new root.
*/
template <class Comparable>
void BinarySearchTree<Comparable>::
	insertBST( Comparable x, BinaryNode<Comparable> * & t )
{
	//if( t == NULL ){ //  create a new node at the right place
	//	t = new BinaryNode<Comparable>( x, NULL, NULL );
	//	currentRoot = t;
	//}
	//else if( x < t->element )
	//	insertBST( x, t->left );  // insert at the left or 
	//else if( t->element < x )
	//	insertBST( x, t->right );  // right subtree
	//else
	//	;  // Duplicate; do nothing

	BinaryNode<Comparable> *temp = t;
	BinaryNode<Comparable> *prevTemp = NULL;
	while(temp != NULL){
		prevTemp = temp;
		if(x > temp->element){
			temp = temp->right;
		}
		else if(x < temp->element){
			temp = temp->left;
		}
		else
			return;
	}
	if(t == NULL){
		t = new BinaryNode<Comparable>( x, NULL, NULL );
	}
	else{
		if(prevTemp->element > x){
			prevTemp->left = new BinaryNode<Comparable>( x, NULL, NULL );
		}
		else if(prevTemp->element < x) {
			prevTemp->right = new BinaryNode<Comparable>( x, NULL, NULL );
		}
	}
}

/**
* Remove x from the tree. Nothing is done if x is not found.
*/
template <class Comparable>
void BinarySearchTree<Comparable>::remove
	( Comparable x )
{
	remove( x, root );
}

/**
* Internal method to remove from a subtree.
* x is the item to remove.
* t is the node that roots the tree.
* Set the new root.
*/
template <class Comparable>
void BinarySearchTree<Comparable>::
	remove( Comparable x, BinaryNode<Comparable> * & t ) 
{
	if( t == NULL )
		return;   // Item not found; do nothing
	if( x < t->element )
		remove( x, t->left );
	else if( t->element < x )
		remove( x, t->right );
	else if( t->left != NULL && t->right != NULL ) // Two children
	{
		t->innerTree = findMin( t->right )->innerTree;
		t->element = findMin( t->right )->element;
		remove( t->element, t->right );
	}
	else // one or no children
	{
		BinaryNode<Comparable> *oldNode = t;
		t = ( t->left != NULL ) ? t->left : t->right;
		delete oldNode;
	}

	//BinaryNode<Comparable> *temp = t;
	//BinaryNode<Comparable> *prev = temp;
	//while(temp != nullptr && temp->element != x){
	//	prev = temp;
	//	if( x < temp->element )
	//		temp = temp->left;
	//	else if( temp->element < x )
	//		temp = temp->right;
	//}
	//if(temp == nullptr)
	//	return;
	//else{
	//	if(temp->left != NULL && temp->right != NULL){ // Two children
	//		BinaryNode<Comparable> * currentTemp = temp;
	//		BinaryNode<Comparable> *prevTemp = temp;
	//		Comparable tempElement = findMin( temp->right )->element;
	//		while(temp != NULL && temp->element != tempElement){
	//			prevTemp = temp;
	//			if(temp->element < tempElement)
	//				temp = temp->right;
	//			else
	//				temp = temp->left;
	//		}
	//		currentTemp->element = tempElement;
	//		if(temp->right != NULL){
	//			if(prevTemp->right == temp)
	//				prevTemp->right = temp->right;
	//			else
	//				prevTemp->left = temp->right;
	//		}else{
	//			if(prevTemp->right == temp)
	//				prevTemp->right = NULL;
	//			else
	//				prevTemp->left = nullptr;
	//		}
	//		delete temp;
	//	}else{ // one or no children
	//		if(temp->left == NULL && temp->right == NULL){
	//			if(prev->left == temp){
	//				prev->left = nullptr;
	//			}else if(prev->right == temp){
	//				prev->right = NULL;
	//			}
	//		}else if(temp->left != NULL && temp->right == NULL){
	//			if(temp == t){
	//				t = t->left;
	//			}else{
	//				if(prev->left == temp){
	//					prev->left = temp->left;
	//				}else if(prev->right == temp){
	//					prev->right = temp->left;
	//				}
	//			}
	//		}else{
	//			if(temp == t){
	//				t = t->right;
	//			}
	//			else{
	//			if(prev->left == temp){
	//				prev->left = temp->right;
	//			}else if(prev->right == temp){
	//				prev->right = temp->right;
	//			}
	//			}
	//		}
	//		if(temp == t && (temp->right == NULL && temp->left == NULL)){
	//			t = NULL;
	//			delete temp;
	//		}else
	//			delete temp;
	//	}
	//}
}            

/**
* Make the tree logically empty.
*/
template <class Comparable>
void BinarySearchTree<Comparable>::makeEmpty( )
{
	makeEmpty( root );
}

/**
* Internal method to make subtree empty.
*/
template <class Comparable>
void BinarySearchTree<Comparable>::
	makeEmpty( BinaryNode<Comparable> * & t ) const
{
	if( t != NULL )
	{
		makeEmpty( t->left );
		makeEmpty( t->right );
		delete t;
	}
	t = NULL;
}

/**
* Print the tree contents in sorted order.
*/
template <class Comparable>
void BinarySearchTree<Comparable>::printTree( )
{
	if( isEmpty( ) )
		cout << "" << endl;
	else
		printTree( root );
}

template <class Comparable>
bool BinarySearchTree<Comparable>::isEmpty( ) const {
	if(root == NULL)
		return true;
	return false;
}

/**
* Destructor for the tree.
*/
template <class Comparable>
BinarySearchTree<Comparable>::~BinarySearchTree( )
{
	makeEmpty();
}

/**
* Copy constructor.
*/
template <class Comparable>
BinarySearchTree<Comparable>::
	BinarySearchTree( const BinarySearchTree<Comparable> & rhs ) :
	root( NULL ), ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND )
{ 
	*this = rhs;
}

/**
* Internal method to print a subtree rooted at t in sorted order.
*/
template <class Comparable>
void BinarySearchTree<Comparable>::
	printTree( BinaryNode<Comparable> * t )
{
	if ( t != NULL )
	{
		printTree( t->left );
		cout << t->element << endl;
		printTree( t->right );
	}
}

/**
* Internal method to clone subtree.
*/
template <class Comparable>
BinaryNode<Comparable> *
	BinarySearchTree<Comparable>::
	clone( BinaryNode<Comparable> * t ) const
{
	if ( t == NULL )
		return NULL;
	else
		return new BinaryNode<Comparable> 
		( t->element, 
		clone( t->left ), 
		clone( t->right ) );
}

template <class Comparable>
const BinarySearchTree<Comparable> & BinarySearchTree<Comparable>::operator=( const BinarySearchTree &rhs){
	
	if(this != &rhs)
		root = clone(rhs.root);
	return *this;
}
