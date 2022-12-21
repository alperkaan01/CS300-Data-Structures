#ifndef _NOTEBOOK_H
#define _NOTEBOOK_H

#include "BinarySearchTree.h"
#include "AvlTree.h"
#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;

template <class Type>
class Notebook {

public:

	//Constructor & destructor
	Notebook(){};
	Notebook(const string &);
	//~Notebook();

	bool isEmpty(const Type &) const;
	//Sections
	void printAVLSections() const;
	void printBSTSections() const;

	bool isFound(const Type &) const;

	void addSection(const Type &);
	void deleteSection(const Type &);

	//Items
	void displayItemsAVL(const Type &) const;
	void displayItemsBST(const Type &) const;

	bool isItemExist(const Type &, const Type &) const;
	bool isItemNotExist(const Type &, const Type &) const;
	Type getItemInfo(const Type &, const Type &) const;

	void addItem(const Type &, const Type &,const Type &);
	void setInfo(const Type &, const Type &, const Type &);
	void deleteItem(const Type &, const Type &);

private:
	BinarySearchTree<Type> BST;
	AvlTree<Type> AVL;
};

template <class Type>
Notebook<Type>::Notebook(const string & fileName){
	ifstream f(fileName);

	if(f.fail())
		cout << "File cannot be opened" << endl;
	else{
		string line, section, tit, inf;
		bool isSection = false;
		BinarySearchTree<Type> * itemTree = NULL;

		AvlTree<Type> * AvlItemTree = NULL;

		double avlTimer = 0, bstTimer = 0;
		bool isSectionChanged = false;


		while(getline(f, line)){
			if(line[0] == '-'){

				line = line.substr(1,line.length()-1);
				tit = line.substr(0, line.find('-'));
				inf = line.substr(line.find('-')+1,line.length()-1);

				//cout << tit << endl;

				auto start = std::chrono::high_resolution_clock::now();
				itemTree->insertBST(tit);
				auto end = std::chrono::high_resolution_clock::now();
				bstTimer = bstTimer + ((end-start).count() / 1000.0);

				itemTree->getCurrentRoot()->info = inf;

				auto st = std::chrono::high_resolution_clock::now();
				AvlItemTree->insertAVL(tit);
				auto en = std::chrono::high_resolution_clock::now();
				avlTimer = avlTimer + ((en-st).count() / 1000.0);

				AvlItemTree->getcurNode()->info = inf;

				if(isSection){
					BST.findNode(section)->innerTree = itemTree;
					AVL.findNode(section)->innerTree = AvlItemTree;
					isSection = false;
					isSectionChanged = true;
				}
			}else { //Section

				if(isSectionChanged){
					cout << "Section \"" << section << "\" has been inserted into the AVL notebook." << endl;
					cout << "[AVL] Elapsed time: " << avlTimer  << " microseconds" << endl;

					cout << "Section \"" << section << "\" has been inserted into the BST notebook." << endl;
					cout << "[BST] Elapsed time: " << bstTimer << " microseconds" << endl << endl;

					bstTimer = 0;
					avlTimer = 0;
				}

				section = line;

				auto start = std::chrono::high_resolution_clock::now();
				BST.insertBST(line);
				auto end = std::chrono::high_resolution_clock::now();
				bstTimer = bstTimer + ((end-start).count() / 1000.0);

				auto st = std::chrono::high_resolution_clock::now();
				AVL.insertAVL(line);
				auto en = std::chrono::high_resolution_clock::now();
				avlTimer = avlTimer + ((en-st).count() / 1000.0);

				itemTree = new BinarySearchTree<string>();
				AvlItemTree = new AvlTree<string>();
				isSection = true;
			}
		}

		cout << "Section \"" << section << "\" has been inserted into the AVL notebook." << endl;
		cout << "[AVL] Elapsed time: " << avlTimer  << " microseconds" << endl;

		cout << "Section \"" << section << "\" has been inserted into the BST notebook." << endl;
		cout << "[BST] Elapsed time: " << bstTimer << " microseconds" << endl;
		cout << endl;

	}
	f.close();
}

template <class Type>
void Notebook<Type>::printBSTSections() const{
	BST.printTree();
}

template <class Type>
void Notebook<Type>::printAVLSections() const{
	AVL.printTree();
}

template<class Type>
bool Notebook<Type>::isFound(const Type & section) const{
	if(AVL.findNode(section) == NULL)
		return false;
	return true;
}

template<class Type>
void Notebook<Type>::addSection(const Type & section){
	BST.insertBST(section);
	AVL.insertAVL(section);
}

template<class Type>
void Notebook<Type>::deleteSection(const Type & section){
	if(BST.findNode(section)->innerTree != NULL)
		BST.findNode(section)->innerTree->makeEmpty();
	BST.remove(section);

	//MAKE SAME THING WITH AVL
	if(AVL.findNode(section)->innerTree != NULL)
		AVL.findNode(section)->innerTree->makeAVLEmpty();
	AVL.removeAVL(section);
}

template<class Type>
void Notebook<Type>::displayItemsBST(const Type & title) const {
	if(!isEmpty(title))
		BST.findNode(title)->innerTree->printTree();
}

template<class Type>
void Notebook<Type>::displayItemsAVL(const Type & title) const {
	if(!isEmpty(title))
		AVL.findNode(title)->innerTree->printTree();
}

template<class Type>
bool Notebook<Type>::isItemExist(const Type & section, const Type & item) const{
	
	auto start = std::chrono::high_resolution_clock::now();
	BST.findNode(section)->innerTree->findNode(item);
	auto end = std::chrono::high_resolution_clock::now();

	auto st = std::chrono::high_resolution_clock::now();
	AVL.findNode(section)->innerTree->findNode(item);
	auto en = std::chrono::high_resolution_clock::now();

	if(isEmpty(section)){
		return false;
	}

	if(AVL.findNode(section)->innerTree->findNode(item) == NULL){
		cout << "[AVL] Elapsed time: " << ((en-st).count() / 1000.0)  << " microseconds" << endl;
		cout << "[BST] Elapsed time: " << ((end-start).count() / 1000.0) << " microseconds" << endl;
		return false;
	}

	return true;
}

template<class Type>
Type Notebook<Type>::getItemInfo(const Type &section, const Type &item) const {
	
	

	auto start = std::chrono::high_resolution_clock::now();
	BST.findNode(section)->innerTree->findNode(item)->info;
	auto end = std::chrono::high_resolution_clock::now();

	auto st = std::chrono::high_resolution_clock::now();
	Type temp = AVL.findNode(section)->innerTree->findNode(item)->info;
	auto en = std::chrono::high_resolution_clock::now();
	cout << "[AVL] Elapsed time: " << ((en-st).count() / 1000.0)  << " microseconds" << endl;
	cout << "[BST] Elapsed time: " << ((end-start).count() / 1000.0) << " microseconds" << endl;
	return temp;

}

template<class Type>
void Notebook<Type>::addItem(const Type &section, const Type &item, const Type & description){

	double bstTimer = 0, avlTimer = 0;

	if(BST.findNode(section)->innerTree == NULL){
		auto start = std::chrono::high_resolution_clock::now();
		BinarySearchTree<Type> * itemTree = new BinarySearchTree<Type>();
		itemTree->insertBST(item);
		BST.findNode(section)->innerTree = itemTree;
		auto end = std::chrono::high_resolution_clock::now();
		bstTimer += ((end-start).count() / 1000.0);
	}else
	{
		auto start = std::chrono::high_resolution_clock::now();
		BST.findNode(section)->innerTree->insertBST(item);
		auto end = std::chrono::high_resolution_clock::now();
		bstTimer += ((end-start).count() / 1000.0);
	}

	if(AVL.findNode(section)->innerTree == NULL){
		auto st = std::chrono::high_resolution_clock::now();
		AvlTree<Type> * AvlItemTree = new AvlTree<Type>();
		AvlItemTree->insertAVL(item);
		AVL.findNode(section)->innerTree = AvlItemTree;
		auto en = std::chrono::high_resolution_clock::now();
		avlTimer = avlTimer + ((en-st).count() / 1000.0);
	}else
	{
		auto st = std::chrono::high_resolution_clock::now();
		AVL.findNode(section)->innerTree->insertAVL(item);
		auto en = std::chrono::high_resolution_clock::now();
		avlTimer = avlTimer + ((en-st).count() / 1000.0);
	}

	auto start = std::chrono::high_resolution_clock::now();	
	BST.findNode(section)->innerTree->findNode(item)->info = description;
	auto end = std::chrono::high_resolution_clock::now();
	bstTimer += ((end-start).count() / 1000.0);
	auto st = std::chrono::high_resolution_clock::now();
	AVL.findNode(section)->innerTree->findNode(item)->info = description;
	auto en = std::chrono::high_resolution_clock::now();
	avlTimer = avlTimer + ((en-st).count() / 1000.0);

	cout << "[AVL] Elapsed time: " << avlTimer  << " microseconds" << endl;
	cout << "[BST] Elapsed time: " << bstTimer << " microseconds" << endl;
}

template<class Type>
void Notebook<Type>::setInfo(const Type &section, const Type &item, const Type & description){
	auto start = std::chrono::high_resolution_clock::now();	
	BST.findNode(section)->innerTree->findNode(item)->info = description;
	auto end = std::chrono::high_resolution_clock::now();
	auto st = std::chrono::high_resolution_clock::now();
	AVL.findNode(section)->innerTree->findNode(item)->info = description;
	auto en = std::chrono::high_resolution_clock::now();
	cout << "[AVL] Elapsed time: " << ((en-st).count() / 1000.0)  << " microseconds" << endl;
	cout << "[BST] Elapsed time: " << ((end-start).count() / 1000.0) << " microseconds" << endl;
}

template<class Type>
void Notebook<Type>::deleteItem(const Type &section, const Type &item){
	auto start = std::chrono::high_resolution_clock::now();	
	BST.findNode(section)->innerTree->remove(item);
	auto end = std::chrono::high_resolution_clock::now();
	//delete AVL too AVL.findNode(section)->innerTree->remove(item)
	auto st = std::chrono::high_resolution_clock::now();
	AVL.findNode(section)->innerTree->removeAVL(item);
	auto en = std::chrono::high_resolution_clock::now();
	cout << "[AVL] Elapsed time: " << ((en-st).count() / 1000.0)  << " microseconds" << endl;
	cout << "[BST] Elapsed time: " << ((end-start).count() / 1000.0) << " microseconds" << endl;
}

template<class Type>
bool Notebook<Type>::isEmpty(const Type &section) const{
	if(AVL.findNode(section)->innerTree == NULL)
		return true;
	return false;
}


template<class Type>
bool Notebook<Type>::isItemNotExist(const Type & section, const Type & item) const{

	BST.findNode(section)->innerTree->findNode(item);

	AVL.findNode(section)->innerTree->findNode(item);

	if(isEmpty(section)){
		return false;
	}

	if(AVL.findNode(section)->innerTree->findNode(item) == NULL){
		return false;
	}
	return true;
}

#endif
