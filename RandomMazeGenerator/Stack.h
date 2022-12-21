//This header file is taken from CS300 presentation slides
#ifndef STACK_H
#define STACK_H

template <class Object>
class Stack
{
public:
	Stack();
	Stack( const Stack & );
	~Stack();

	bool isEmpty() const;
	bool isFull() const;
	void makeEmpty( );

	void pop();
	void push( const Object & x );
	Object topAndPop( );
	const Object & top( ) const;

	const Stack & operator=( const Stack & );
private:
	struct ListNode
	{
		Object   element;
		ListNode *next;

		ListNode( const Object & theElement, ListNode * n = NULL )
			: element( theElement ), next( n ) { }
	};

	ListNode *topOfStack;  // list itself is the stack
};

#include "Stack.cpp"

#endif
