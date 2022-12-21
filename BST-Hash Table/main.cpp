#include <iostream>
#include <string>
#include <vector>
#include "structs.cpp"
#include <fstream>
#include <sstream>
#include "strutils.h"
#include "Hash.h"
#include "BinarySearchTree.h"

using namespace std;

void getFileNames(vector<string> & fileList, unsigned short int  numDoc, ifstream & file){
	string fileName;
	for(unsigned int i = 0 ; i < numDoc ; i++){
		cout << "Enter " << i+1 << ". file name: ";
		cin >> fileName;
		fileList.push_back(fileName);
	}
}

int main(){
	unsigned short int numDoc;
	string fileName;
	int uniqueWordCount = 0;
	cout << "Enter number of input files: ";
	cin >> numDoc;
	ifstream file;
	vector<string> documentList;
	getFileNames(documentList, numDoc, file);

	BinarySearchTree<WordItem> uniqueWordTree;
	WordItem notFound( "not found");
	HashTable<WordItem> uniqueWordTable(notFound);

	for(unsigned int i = 0; i < documentList.size() ;i++){
		fileName = documentList[i];
		file.open(fileName.c_str());
		if(!file.fail()){
			string word;
			while(file >> word){
				//cout << word << endl;
				ToLower(word);
				string emptyString = "";
				WordItem item;
				for(unsigned short int i = 0; i < word.length(); i++){
					if(isalpha(word[i])){
						emptyString += word[i];
						if(!isalpha(word[i+1])){
							//cout << emptyString << endl; DEBUG
							item.word = emptyString;
							//Make the operations - add BST and Hash
							//BST
							if(uniqueWordTree.findNode(item) == NULL){
								uniqueWordCount++;
								DocumentItem docItem(fileName, 1);
								item.itemList.push_back(docItem);
								uniqueWordTree.insertBST(item);
							}else{
								for(unsigned short int i = 0 ; i < uniqueWordTree.findNode(item)->element.itemList.size(); i++){
									if(uniqueWordTree.findNode(item)->element.itemList[i].documentName == fileName)
										uniqueWordTree.findNode(item)->element.itemList[i].count++;
								}
							}
							
							//Hash
							uniqueWordTable.insert(item);

						}
					}else{
						emptyString = "";
					}
				}
			}

		}

		//uniqueWordTree.printTree();
		file.close();
	}

	cout << uniqueWordCount << endl;

	string line;
	cout << "Enter queried words in one line: ";
	cin.get();
	getline(cin,line);
	int totalCount = 0;
	for(unsigned short int j = 0 ; j < documentList.size(); j++){
		vector<DocumentItem> existingItems;
		vector<string> queryList;
		//cout << documentList[j] << endl;
		istringstream sstream(line);
		string word;
		int wordCount = 0;
		while(sstream >> word){
			//cout << word << endl;
			ToLower(word);
			string emptyString = "";
			WordItem item;

			//BST QUERY
		/*	for(unsigned short int i = 0; i < word.length(); i++){
				if(isalpha(word[i])){
					emptyString += word[i];
					if(!isalpha(word[i+1])){
						item.word = word;
						queryList.push_back(word);
						if(uniqueTreeList[j].findNode(item) != NULL){
							for(unsigned short int k = 0 ; k < uniqueTreeList[j].findNode(item)->element.itemList.size() ; k++){
								if(uniqueTreeList[j].findNode(item)->element.itemList[k].documentName == documentList[j]){
									existingItems.push_back(uniqueTreeList[j].findNode(item)->element.itemList[k]);
								}
							}
						}
					}
				}else{
					emptyString = "";
				}
			}*/


			//HASH QUERY


			wordCount++;
		}
		sstream.get();
		sstream.clear();
		/*string empStr = "";
		if(wordCount == existingItems.size()){
			empStr += ("in Document " + documentList[j]);
			for(unsigned short int i= 0 ; i < queryList.size() ;i++){
				empStr += (", " + queryList[i] + " found " + itoa(existingItems[i].count) + " times");
			}
			empStr += ".";
			totalCount++;
		}
		cout << empStr << endl;*/
	}

	if(totalCount == 0){
		cout <<	"No document contains the given query" << endl;
		cout <<	"No document contains the given query" << endl;
	}
	return 0;
}
//cout << "in Document " << d.txt << ", " << a << " found 4 times, " << the << " found 12 times, " << to << " found 4 times, " << as << " found 1 times." << endl;
//uniqueWordTree.findNode(item)->element.itemList.size()
