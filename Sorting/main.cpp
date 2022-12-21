#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>
#include "strutils.h"

//NOTE: I get the k = 100 for timing but it sometimes give 0 division exception, for small sample sizes you can play with k, also for shuffle you need to wait a bit !!! 

using namespace std;

//INSERTION SORT ALGORITHM FROM SLIDESET OF SORTING LECTURE
template <class Comparable>
void insertionSort (vector <Comparable> & a)
{
	int j;
	// loop over the passes
	for (unsigned int p = 1;  p < a.size(); p++)
	{
		Comparable tmp = a[p];
		// loop over the elements
		for (j = p; j > 0 &&  tmp < a[j - 1]; j--)
			a[j] = a[j -1];
		a[j] = tmp;
	}
}



//HEAP SORT ALGORITHM FROM SLIDESET OF SORTING LECTURE

inline int leftChild( int i )
{
	return 2*i+1;
}

template <class Comparable>
void heapsort(vector<Comparable> & a)
{
	// buildHeap
	for (int i = a.size()/2; i >=0; i--)
		percDown(a, i, a.size());

	// sort
	for (int j = a.size()-1; j >0; j--)
	{
		swap(a[0], a[j]);    // swap max to the last pos.
		percDown(a, 0, j); // re-form the heap
	}
}

template <class Comparable>  // for deleteMax
// a is the array, i is the position to percolate down from
// n is the logical size of the array
void percDown( vector<Comparable> & a, int i, int n )
{
	int child;
	Comparable tmp;

	for (tmp=a[i] ; leftChild(i) < n; i = child )
	{
		child = leftChild(i);
		if ( child != n-1 && a[ child  ] < a[ child+1 ] )
			child++;
		if ( a[child ] > tmp )
			a[i] = a[ child ];
		else
			break;
	} 
	a[ i ] = tmp;
}



//MERGE SORT ALGORITHM FROM SLIDESET OF SORTING LECTURE
/**
* Mergesort algorithm (driver).
*/
template <class Comparable>
void mergeSort( vector<Comparable> & a )
{
	vector<Comparable> tmpArray( a.size( ) );

	mergeSort( a, tmpArray, 0, a.size( ) - 1 );
}

/**
* Internal method that makes recursive calls.
* a is an array of Comparable items.
* tmpArray is an array to place the merged result.
* left is the left-most index of the subarray.
* right is the right-most index of the subarray.
*/
template <class Comparable>
void mergeSort( vector<Comparable> & a,
			   vector<Comparable> & tmpArray, int left, int right )
{
	if ( left < right )
	{
		int center = ( left + right ) / 2;
		mergeSort( a, tmpArray, left, center );
		mergeSort( a, tmpArray, center + 1, right );
		merge( a, tmpArray, left, center + 1, right );
	}
}

/**
* Internal method that merges two sorted halves of a subarray.
* a is an array of Comparable items.
* tmpArray is an array to place the merged result.
* leftPos is the left-most index of the subarray.
* rightPos is the index of the start of the second half.
* rightEnd is the right-most index of the subarray.
*/
template <class Comparable>
void merge(  vector<Comparable> & a, 
		   vector<Comparable> & tmpArray,
		   int leftPos, int rightPos, int rightEnd )
{
	int leftEnd = rightPos - 1;
	int tmpPos = leftPos;
	int numElements = rightEnd - leftPos + 1;
	// Main loop
	while ( leftPos <= leftEnd && rightPos <= rightEnd )
		if ( a[ leftPos ] <= a[ rightPos ] )
			tmpArray[ tmpPos++ ] = a[ leftPos++ ];
		else
			tmpArray[ tmpPos++ ] = a[ rightPos++ ];

	while ( leftPos <= leftEnd )    // Copy rest of first half
		tmpArray[ tmpPos++ ] = a[ leftPos++ ];

	while ( rightPos <= rightEnd )  // Copy rest of right half
		tmpArray[ tmpPos++ ] = a[ rightPos++ ];

	// Copy tmpArray back
	for ( int i = 0; i < numElements; i++, rightEnd-- )
		a[ rightEnd ] = tmpArray[ rightEnd ];
}


//QUICK SORT ALGORITHM FROM SLIDESET OF SORTING LECTURE

/**
* Return median of left, center, and right.
* Order these and hide the pivot.
*/
template <class Comparable>
const Comparable & median3(  vector<Comparable> & a,
						   int left, int right )
{
	int center = ( left + right ) / 2;
	if ( a[ center ] < a[ left ] )
		swap( a[ left ], a[ center ] );
	if ( a[ right ] < a[ left ] )
		swap( a[ left ], a[ right ] );
	if ( a[ right ] < a[ center ] )
		swap( a[ center ], a[ right ] );

	// Place pivot at position right - 1
	swap( a[ center ], a[ right - 1 ] );
	return a[ right - 1 ];
}

/**
* Quicksort algorithm (driver).
*/
template <class Comparable>
void quicksort( vector<Comparable> & a )
{
	quicksort( a, 0, a.size( ) - 1 );
}

/**
* Standard swap
*/
template <class Comparable>
inline void swap( Comparable & obj1, 
				 Comparable & obj2 )
{
	Comparable tmp = obj1;
	obj1 = obj2;
	obj2 = tmp;
}


/**
* Internal quicksort method that makes recursive calls.
* Uses median-of-three partitioning and a cutoff of 10.
* a is an array of Comparable items.
* left is the left-most index of the subarray.
* right is the right-most index of the subarray.
*/
template <class Comparable>
void quicksort( vector<Comparable> & a, 
			   int left, int right )
{
	if ( left + 10 <= right )
	{
		Comparable pivot = median3( a, left, right );
		// Begin partitioning
		int i = left, j = right - 1;
		for ( ; ; )
		{
			while ( a[ ++i ] < pivot ) { }

			while ( pivot < a[ --j ] ) { }

			if ( i < j )
				swap( a[ i ], a[ j ] );
			else
				break;
		}
		swap( a[ i ], a[ right - 1 ] );   // Restore pivot

		quicksort( a, left, i - 1 );       // Sort small elements
		quicksort( a, i + 1, right );    // Sort large elements
	}
	else  // Do an insertion sort on the subarray
		insertionSort( a, left, right );
}

/**
* Internal insertion sort routine for subarrays
* that is used by quicksort.
* a is an array of Comparable items.
* left is the left-most index of the subarray.
* right is the right-most index of the subarray.
*/
template <class Comparable>
void insertionSort( vector<Comparable> & a, int left, int right )
{
	for ( int p = left + 1; p <= right; p++ )
	{
		Comparable tmp = a[ p ];
		int j;

		for ( j = p; j > left && tmp < a[ j - 1 ]; j-- )
			a[ j ] = a[ j - 1 ];
		a[ j ] = tmp;
	}
}



void printVector(vector<string> &);


vector<string> bsearch(const vector<string>&, const string&);

vector<string> seqSearch(const vector<string>&, const string&);



int main(){

	string fileName, queryWord;
	ifstream fStream;

	cout << "Please enter the contact file name: " << endl;
	cin >> fileName;

	cout << "Please enter the word to be queried: " << endl;
	cin.get();
	getline(cin , queryWord);

	cout << "Sorting the vector copies" << endl;
	cout << "======================================" << endl;

	fStream.open(fileName.c_str());

	if(fStream.fail()){
		cout << "Fail to open file." << endl;
	}else{
		vector <string> insertVector;
		vector <string> quickVector;
		vector <string> mergeVector;
		vector <string> heapVector;
		vector <string> unsorted;

		string line;

		while(getline(fStream, line)){


			insertVector.push_back(line);
			quickVector.push_back(line);
			mergeVector.push_back(line);
			heapVector.push_back(line);
			unsorted.push_back(line);

		}


		//printVector(insertVector); //DEBUG
		//cout << endl << endl;

		unsigned short int k = 20;

		/*int minTimeAlgorithm = INT_MAX;*/

		auto insertStart = std::chrono::high_resolution_clock::now();
		for(int i = 0; i < k; i++){
			insertVector = unsorted;
			insertionSort(insertVector);
		}
		auto insertTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - insertStart);

		/*if(double(insertTime.count() / k) < (double)minTimeAlgorithm){
			minTimeAlgorithm = insertTime.count() / k;
		}*/

		auto QuickStart = std::chrono::high_resolution_clock::now();
		for(int i = 0; i < k; i++){
			quickVector = unsorted;
			quicksort(quickVector);
		}
		auto QuickTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - QuickStart);

		/*if(double(QuickTime.count() / k) < (double)minTimeAlgorithm){
			minTimeAlgorithm = QuickTime.count() / k;
		}*/

		auto HeapStart = std::chrono::high_resolution_clock::now();
		for(int i = 0; i < k; i++){
			heapVector = unsorted;
			heapsort(heapVector);
		}
		auto HeapTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - HeapStart);

		/*if(double(HeapTime.count() / k) < (double)minTimeAlgorithm){
			minTimeAlgorithm = HeapTime.count() / k;
		}*/

		auto MergeStart = std::chrono::high_resolution_clock::now();
		for(int i = 0; i < k; i++){
			mergeVector = unsorted;
			mergeSort(mergeVector);
		}
		auto MergeTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - MergeStart);

		/*if(double(MergeTime.count() / k) < (double)minTimeAlgorithm){
			minTimeAlgorithm = MergeTime.count() / k;
		}*/



		//printVector(insertVector); //DEBUG
		//cout << endl << endl;

		cout << "Quick Sort Time: " << QuickTime.count() / k << " Nanoseconds" << endl;
		cout << "Insertion Sort Time: " << insertTime.count() / k << " Nanoseconds" << endl;
		cout << "Merge Sort Time: " << MergeTime.count() / k << " Nanoseconds" << endl;
		cout << "Heap Sort Time: " << HeapTime.count() / k << " Nanoseconds" << endl;
		cout << endl;



		cout << "Searching for " << queryWord << endl;
		cout <<	"======================================" << endl;

		auto bStart = std::chrono::high_resolution_clock::now();
		for(int i = 0; i < k; i++){
			bsearch(quickVector, queryWord);
		}
		auto bTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - bStart);

		vector<string> binaryResult = bsearch(quickVector, queryWord);
		if(binaryResult.size() > 0) {
			printVector(binaryResult);
		}
		else{
			ToUpper(queryWord);
			cout << queryWord << " does NOT exist in the dataset" << endl;
		}

		cout << "Binary Search Time: " << bTime.count() / k << " Nanoseconds" << endl << endl;

		
		cout << "Search results for Sequential Search:" << endl;

		auto sStart = std::chrono::high_resolution_clock::now();
		for(int i = 0; i < k; i++){
			seqSearch(quickVector, queryWord);
		}
		auto sTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - sStart);

		vector<string> squentialResult = seqSearch(quickVector, queryWord);
		if(squentialResult.size() > 0) {
			printVector(squentialResult);
		}
		else{
			ToUpper(queryWord);
			cout << queryWord << " does NOT exist in the dataset" << endl;
		}

		cout << "Sequential Search Time: " << sTime.count() / k << " Nanoseconds" << endl << endl;


		//Speed Ups

		cout << "SpeedUp between Search Algorithms" << endl;
		cout <<	"======================================" << endl;

		cout << "(Sequential Search/ Binary Search) SpeedUp = " << (sTime.count() / k) / (bTime.count() / k) << endl;


		cout << "SpeedUp between Sorting Algorithms" << endl;
		cout <<	"======================================" << endl;

		cout << "(Insertion Sort/ Quick Sort) SpeedUp = " << double(insertTime.count() / k) / (QuickTime.count() / k) << endl;
		cout << "(Merge Sort / Quick Sort) SpeedUp = " << double(MergeTime.count() / k) / (QuickTime.count() / k) << endl;
		cout << "(Heap Sort / Quick Sort) SpeedUp = " << double(HeapTime.count() / k) / (QuickTime.count() / k) << endl;
	}

	fStream.close();
	return 0;
}

void printVector(vector <string> & item){
	for (unsigned int i = 0 ; i < item.size()  ; i++){
		cout << item[i] << endl;
	}
}

vector<string> bsearch(const vector<string>& list, const string& key){
	// pre: list.size() == # elements in list
	// post: returns index of key in list, -1 if key not found
	int low = 0;                   // leftmost possible entry
	int high = list.size()-1;      // rightmost possible entry
	int mid;     // middle of current range

	string name, surname, phone, city;
	string lowerkey = LowerString(key);

	vector<string> result;

	while (low <= high){

		mid = (low + high)/2;

		string line = LowerString(list[mid]);

		istringstream sstream(line);
		sstream >> name >> surname >> phone >> city;

		if(lowerkey.find(" ") != string::npos){
			
			string empStr = name + " " + surname;
			

			if (empStr == lowerkey){       // found key, exit search
				//return mid;
				result.push_back(list[mid]);
				return result;
			}
			else if (empStr < lowerkey){   // key in upper half
				low = mid + 1;
			}
			else{                        // key in lower half
				high = mid - 1;
			}
		}else {
			int length = lowerkey.length();
			if (name.substr(0, length) == lowerkey){       // found key, exit search
				//return mid;
				int i = mid;
				string lowerBool = LowerString(list[i].substr(0, list[i].find(' ')).substr(0, length));
				while((i>0 && lowerkey == lowerBool)){
					i = i-1;
					lowerBool = LowerString(list[i].substr(0, list[i].find(' ')).substr(0, length));
				}
				
				//cout << list[i].substr(0, list[i].find(' ')).substr(0, length) << endl;

				if(i != 0)
					i++;

				lowerBool = LowerString(list[i].substr(0, list[i].find(' ')).substr(0, length));

				for( unsigned int k = i ; (k < list.size() && lowerkey == lowerBool) ; ){
					result.push_back(list[k]);
					k++;
					if(k < list.size())
						lowerBool = LowerString(list[k].substr(0, list[k].find(' ')).substr(0, length));
				}

				return result;
			}
			else if (name.substr(0, length) < lowerkey){   // key in upper half
				low = mid + 1;
			}
			else{                        // key in lower half
				high = mid - 1;
			}
		}

	}
	//return -1;      // not in list
	return result;
} 

vector<string> seqSearch(const vector<string>& vec, const string& key){

	string name, surname, phone, city, lowerkey;

	lowerkey = LowerString(key);

	vector <string> result; 

	for(unsigned int i = 0 ; i < vec.size() ; i++){

		string lower = LowerString(vec[i]);

		istringstream sstream(lower);

		sstream >> name >> surname >> phone >> city;

		//cout << name << " " << surname << endl; 

		if(lowerkey.find(" ") != string::npos){

			//there is both name and surname exist

			string empStr = name + " " + surname;

			if(empStr == lowerkey){
				result.push_back(vec[i]);
			}

		}else {

			//there is just a name exist

			int length = lowerkey.length();

			if(name.substr(0, length) == lowerkey){
				result.push_back(vec[i]);
			}
		}
	}

	return result;
}
