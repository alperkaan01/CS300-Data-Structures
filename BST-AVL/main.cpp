#include <iostream>
#include <string>
#include "Notebook.h"
#include <chrono> //I used some of the high resolution clocks on notebook objects because some of the commands consist of more than one member function of AVL and BST
#pragma comment(linker, "/STACK:5000000")
#pragma comment(linker, "/HEAP:5000000")
using namespace std;

void menu1();

template <class obj>
void menu2(const obj& sectionTitle ){
	cout << "Selected section -> " << sectionTitle << '\n' <<
		"Please enter an input between [1 - 7]: " << '\n' << 
		"1- Display the items [AVL]" << '\n' <<
		"2- Display the items [BST]" << '\n' <<
		"3- Display the information of a item" << '\n' <<
		"4- Add new item" << '\n' << 
		"5- Update the information of a item" << '\n' <<
		"6- Delete an item" << '\n' <<
		"7- Return to main menu" << '\n';
}

// Test program
int main()
{
	char char1, char2;
	string title = "CourseWorks", newSection, dSection;
	bool isMenu1 = false;
	cout << "Welcome to the Notebook!" << endl << endl;
	//Create the general framework of the program flow - Than implement functions

	string fileName = "data.txt";
	Notebook<string> noteBook(fileName);

	do{
		if(!isMenu1){
			menu1();
			isMenu1 = true;
		}
		cout << "Input: ";
		cin >> char1;

		if(char1 == '1'){
			//Display the sections [AVL]
			cout << "*****" << endl;
			noteBook.printAVLSections();
			cout << "*****" << endl;
		}else if(char1 == '2'){
			//Display the sections [BST] 
			cout << "*****" << endl;
			noteBook.printBSTSections();
			cout << "*****" << endl;
		}else if(char1 == '3'){
			//Select a section
			cout << "Enter the title of the section: ";
			cin >> title;
			if(noteBook.isFound(title)){
				menu2(title);
				do{
					cout << "Input: ";
					cin >> char2;

					if(char2 == '1'){
						// Display the items [AVL]
						cout << "*****" << endl;
						noteBook.displayItemsAVL(title);
						cout << "*****" << endl;
					}else if(char2 == '2'){
						//Display the items [BST]
						cout << "*****" << endl;
						noteBook.displayItemsBST(title);
						cout << "*****" << endl;
					}else if(char2 == '3'){
						//Display the information of a item
							string itemTitle;
							cout << "Enter the title of the item: ";
							cin.get();
							getline(cin, itemTitle);
							if(!noteBook.isEmpty(title)){
								if(noteBook.isItemExist(title, itemTitle)){
									cout << noteBook.getItemInfo(title, itemTitle) << endl;
								}else{
									cout << "Invalid title." << endl;
								}
							}
							else
								cout << "Invalid title." << endl;

					}else if(char2 == '4'){
						//Add new item
						string addI;
						cout << "Enter a title for the item: ";
						cin.get();
						getline(cin, addI);
						if(!noteBook.isEmpty(title)){
							if(noteBook.isItemNotExist(title, addI)){
								cout << "Item \"" << addI << "\" already exists in the \"" << title << "\"." << endl;
							}else{
								string description;
								cout <<	"Enter a description for the item: ";
								getline(cin, description);
								noteBook.addItem(title, addI, description);
								cout << "The new item \"" << addI << "\" has been inserted." << endl;
							}
						}else{
								string description;
								cout <<	"Enter a description for the item: ";
								getline(cin, description);
								noteBook.addItem(title, addI, description);
								cout << "The new item \"" << addI << "\" has been inserted." << endl;
							}
					}else if(char2 == '5'){
						//Update the information of an item
							string iTitle;
							cout << "Enter the title of the item: ";
							cin.get();
							getline(cin,iTitle);
							if(!noteBook.isEmpty(title)){
								if(noteBook.isItemExist(title, iTitle)){
									string newinfo;
									cout << "Enter the new information: ";
									getline(cin,newinfo);
									noteBook.setInfo(title, iTitle, newinfo);
									cout << "The content " << title << " has been updated." << endl;
								}else 
									cout << "Item \"" << iTitle << "\" does not exist in the \""<< title << "\"." << endl;
							}else{
								cout << "Item \"" << iTitle << "\" does not exist in the \""<< title << "\"." << endl;
							}
					}else if(char2 == '6'){
						//Delete an item
						string dItem;
						cout << "Enter the title of the item: ";
						cin.get();
						getline(cin, dItem);
						if(!noteBook.isEmpty(title)){
							if(noteBook.isItemNotExist(title, dItem)){
								noteBook.deleteItem(title, dItem);
								cout << "The item \"" << dItem << "\" has been deleted." << endl;
							}else
								cout << "Item \"" << dItem << "\" does not exist in the \""<< title << "\"." << endl;
						}else{
							cout << "Item \"" << dItem << "\" does not exist in the \""<< title << "\"." << endl;
						}
					}
				}while(char2 != '7');
				isMenu1 = false;
			}else{
				cout << "Invalid title!" << endl;
			}
		}else if(char1 == '4'){
			//Add new section
			cout << "Enter a title for the section: ";
			cin >> newSection;
			if(noteBook.isFound(newSection)){
				cout << "Section \"" << newSection << "\" already exists." << endl;
			}else{
				noteBook.addSection(newSection);
				cout << "The new section \"" << newSection << "\" has been inserted." << endl;
			}
		}else if(char1 == '5'){
			//Delete a section
			cout << "Enter the title of the section: ";
			cin >> dSection;
			if(noteBook.isFound(dSection)){
				noteBook.deleteSection(dSection);
				cout << "The section has been deleted." << endl;
			}else{
				cout << "Section \"" << dSection << "\" does not exist." << endl;
			}
		}

	}while(char1 != '6');


	return 0;   

}

void menu1(){
	cout << "MENU" << endl <<
		"Please enter an input between [1 - 6]: " << endl << 
		"1- Display the sections [AVL]" << endl <<
		"2- Display the sections [BST]" << endl <<
		"3- Select a section" << endl <<
		"4- Add new section" << endl << 
		"5- Delete a section" << endl <<
		"6- Exit" << endl;
}
