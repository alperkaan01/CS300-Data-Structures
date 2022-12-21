#ifndef _HASH_H
#define _HASH_H

#include "BinarySearchTree.h"
#include <vector>
#include <iostream>
#include <string>
using namespace std;

const int LOADFACTOR = 0.6;

struct DocumentItem {
	string documentName;
	int count;

	DocumentItem(){};
	DocumentItem::DocumentItem(const string & str, const int & i): documentName(str), count(i){}

	bool operator > (const DocumentItem & item){
		return (documentName > item.documentName);
	};
	bool operator < (const DocumentItem & item){
		return (documentName < item.documentName);
	};
};

struct WordItem {
	string word;
	// List of DocumentItem’s.
	vector<DocumentItem> itemList;
	WordItem(){};
	WordItem::WordItem(const string & str): word(str){}

	bool WordItem::operator > (const WordItem & item){
		return (this->word > item.word);
	};
	bool WordItem::operator < (const WordItem & item){
		return (this->word < item.word);
	};
	bool WordItem::operator!=(const WordItem & item){
		return !(item.word == word);
	}
	bool WordItem::operator==(const WordItem & item){
		return (item.word == word);
	}

	friend ostream & operator <<(ostream &, const WordItem &);
};

ostream & operator <<(ostream &os, const WordItem &item){
	ostringstream ostr;
	ostr << item.word;
	os << ostr.str();
	return os;
};

template <class HashedObj>
class HashTable
{
public:
	explicit HashTable( const HashedObj & notFound, int size = 53 );
	HashTable( const HashTable & rhs )
		: ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND ),
		arr( rhs.arr ), currentSize( rhs.currentSize ) { }
	HashTable(){};

	double LoadFactor() const { return (currentSize / arr.size())}
	int getTableSize () const {return arr.size()}

	int hash( HashedObj , int);

	const HashedObj & find( const HashedObj & x ) const;

	void makeEmpty( );
	void insert( HashedObj x );
	void remove( const HashedObj & x );

	const HashTable & operator=( const HashTable & rhs );

	enum EntryType { ACTIVE, EMPTY, DELETED };

private:
	struct HashEntry
	{
		HashedObj element;
		EntryType info;

		HashEntry( const HashedObj & e = HashedObj( ), 
			EntryType i = EMPTY )
			: element( e ), info( i ) { }
	};

	vector<HashEntry> arr;
	unsigned int currentSize; // make this int at the end
	const HashedObj ITEM_NOT_FOUND;

	bool isActive( int currentPos ) const;
	int findPos( HashedObj x );
	void rehash( );

	//int nextPrime( HashedObj );

	/**
	* Internal method to test if a positive number is prime.
	* Not an efficient algorithm.
	*/
	//bool isPrime( HashedObj );

};



template <class obj>
int hashString (const obj & key, int tableSize)
{ 
	int hashVal = 0;

	for (unsigned int i = 0; i < key.length();i++) 
		hashVal = 37 * hashVal + key[ i ];

	hashVal = hashVal % tableSize;

	if (hashVal < 0) 
		hashVal = hashVal + tableSize;

	return(hashVal);
}

template <class HashedObj>
int HashTable<HashedObj>::hash( HashedObj x, int tableSize)
{
	return hashString(x.word, tableSize);
}


template <class HashedObj>
void HashTable<HashedObj>::makeEmpty()
{
	currentSize = 0;
}

int isPrime( int n )
{
	if ( n == 2 || n == 3 )
		return true;

	if ( n == 1 || n % 2 == 0 )
		return false;

	for ( int i = 3; i * i <= n; i += 2 )
		if ( n % i == 0 )
			return false;

	return true;
}


int nextPrime( int n )
{
	if ( n % 2 == 0 )
		n++;

	for ( ; ! isPrime( n ); n += 2 )
		;

	return n;
}

/**
* Construct the hash table.
*/
template <class HashedObj>
HashTable<HashedObj>::HashTable( const HashedObj & notFound, 
								int size = 53 )
								: ITEM_NOT_FOUND( notFound ), arr(nextPrime(size))
{
	makeEmpty( );
}

/**
* Method that performs quadratic probing resolution.
* Return the position where the search for x terminates.
*/
template <class HashedObj>
int HashTable<HashedObj>::findPos( HashedObj x )
{
	int collisionNum = 0;
	unsigned int currentPos = hash( x, arr.size( ) );

	while ( arr[ currentPos ].info != EMPTY && 
		arr[ currentPos ].element != x )
	{
		currentPos += int(pow(++collisionNum, 2)) ;  //add the difference
		if ( currentPos >= arr.size()){             // perform the mod
			currentPos = currentPos - arr.size();
		}// if necessary
	}
	return currentPos;
}


/**
* Return true if currentPos exists and is active.
*/
template <class HashedObj>
bool HashTable<HashedObj>::isActive( int currentPos ) const
{
	return arr[ currentPos ].info == ACTIVE;
}

/**
* Remove item x from the hash table.
*  x has to be in the table
*/
template <class HashedObj>
void HashTable<HashedObj>::remove( const HashedObj & x )
{
	int currentPos = findPos( x );
	if ( isActive( currentPos ) )
		arr[ currentPos ].info = DELETED;
}

/**
* Find item x in the hash table.
* Return the matching item, or ITEM_NOT_FOUND, if not found.
*/
template <class HashedObj>
const HashedObj & HashTable<HashedObj>::find( const HashedObj & x ) 
	const
{
	int currentPos = findPos( x );
	if (isActive( currentPos )) 
		return arr[ currentPos ].element; 

	return ITEM_NOT_FOUND;
}

/**
* Insert item x into the hash table. If the item is
* already present, then do nothing.
*/
template <class HashedObj>
void HashTable<HashedObj>::insert( HashedObj x )
{
	// Insert x as active
	int currentPos = findPos( x );
	if ( isActive( currentPos ) )
		return;
	arr[ currentPos ] = HashEntry( x, ACTIVE );

	// enlarge the hash table if necessary 
	if ( ++currentSize >= arr.size( ) * LOADFACTOR ){
		double lF = double(currentSize) / arr.size();
		rehash( );
		cout << "rehashed..." << endl;
		cout << loadFactor << endl;
	}
}

/**
* Expand the hash table.
*/
template <class HashedObj>
void HashTable<HashedObj>::rehash( )
{
	vector<HashEntry> oldArray = arr;

	// Create new double-sized, empty table
	arr.resize( nextPrime( 2 * oldArray.size( ) ) );
	for ( unsigned int j = 0; j < arr.size( ); j++ )
		arr[ j ].info = EMPTY;

	// Copy table over
	currentSize = 0;
	for ( unsigned int i = 0; i < oldArray.size( ); i++ )
		if ( oldArray[ i ].info == ACTIVE )
			insert( oldArray[ i ].element );
}

#endif
