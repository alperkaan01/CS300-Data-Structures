#include <iostream>
#include "Maze.h"
#include "Stack.h"
#include "randgen.h"
#include <fstream>
#include "strutils.h"

Maze::Maze(const int & i , const int & row, const int & col):id(i+1), rows(row), cols(col) {
	size = row * col;
	Matrix = new cell*[rows];

	for(int k = 0 ; k < rows ; k++)
		Matrix[k] = new cell[cols];
	for(int i = 0 ; i < rows ; i++){
		for(int k = 0 ; k < cols ; k++)
		{
			Matrix[i][k].x = k;
			Matrix[i][k].y = rows - i - 1;
		}	
	}
	mazeGenerator();
}

ostream & operator <<(ostream & os, const Maze & maze){
	ostringstream ostr;

	int rows = maze.rows;
	int cols = maze.cols;

	ostr << rows << " " << cols << endl;

	for(int i = rows-1 ; i >= 0 ; i--){
		for(int j = 0 ; j < cols ;j++){
			ostr << "x=" << maze.Matrix[i][j].x << " " << "y=" << maze.Matrix[i][j].y << " " << "l=" << maze.Matrix[i][j].l << " " << "r=" << maze.Matrix[i][j].r << " " << "u=" << maze.Matrix[i][j].u << " " << "d=" << maze.Matrix[i][j].d << endl;
		}	
	}

	os << ostr.str();
	return os;
}

Maze::~Maze(){
	for(int i = 0; i < rows ; i++){
		delete [] Matrix[i];
		Matrix[i] = nullptr;
	}
	delete [] Matrix;
	Matrix = nullptr;
}

int Maze::randomWallSelector(const int & x, const int & y) const
{
	RandGen random;
	if((x < cols-1) && (y < rows-1) && (x > 0) && (y > 0)){
		return random.RandInt(4);
	}else
	{
		if((x == 0 || x == cols -1) && (y == 0 || y == rows-1))
			if(x == 0 && y == 0) return random.RandInt(1, 2);
			else if(x == cols-1 && y == 0) return random.RandInt(0, 1);
			else if(x == 0 && y == rows-1) return random.RandInt(2, 3);
			else{
				int arr[2] = {0 , 3}; 
				return arr[random.RandInt(0,1)];
			}
		else{
			if(x==0) return random.RandInt(1,3);
			else if(x == cols-1){
				int arr[3] = {0, 1, 3}; return arr[random.RandInt(0,2)];
			}
			else if(y == 0) return random.RandInt(0,2);
			else{ int arr[3] = {0, 2, 3}; return arr[random.RandInt(0,2)];}
		}
	}
}

void Maze::deleteMatrix(){
	for(int i = 0; i < rows ; i++){
		delete [] Matrix[i];
		Matrix[i] = nullptr;
	}
	delete [] Matrix;
	Matrix = nullptr;
}

const Maze & Maze::operator=(const Maze & rhs) {

	if(this != &rhs){
		//this->deleteMatrix();
		rows = rhs.rows;
		cols = rhs.cols;
		size = rows * cols;
		id = rhs.id;
		Matrix = new cell*[rows];

		for(int k = 0 ; k < rows ; k++)
			Matrix[k] = new cell[cols];
		for(int i = 0 ; i < rows ; i++){
			for(int k = 0 ; k < cols ; k++)
			{
				Matrix[i][k] = rhs.Matrix[i][k];
			}	
		}

	}
	return *this;
}

bool Maze::isUnVisitedNotExist(const int & x, const int & y) const 
{
	int currRow = rows-1-y;
	if((x < cols-1) && (y < rows-1) && (x > 0) && (y > 0)){
		return((Matrix[currRow][x+1].isVisited)&&
			(Matrix[currRow][x-1].isVisited)&&
			(Matrix[currRow+1][x].isVisited)&&
			(Matrix[currRow-1][x].isVisited));
	}else
	{
		if((x == 0 || x == cols -1) && (y == 0 || y == rows-1))
			if(x == 0 && y == 0) return (Matrix[currRow-1][x].isVisited && Matrix[currRow][x+1].isVisited);
			else if(x == cols-1 && y == 0) return (Matrix[currRow][x-1].isVisited && Matrix[currRow-1][x].isVisited);
			else if(x == 0 && y == rows-1) return (Matrix[currRow+1][x].isVisited && Matrix[currRow][x+1].isVisited);
			else return (Matrix[currRow+1][x].isVisited && Matrix[currRow][x-1].isVisited);
		else{
			if(x==0) return (Matrix[currRow-1][x].isVisited && Matrix[currRow+1][x].isVisited && Matrix[currRow][x+1].isVisited);
			else if(x == cols-1){
				return (Matrix[currRow-1][x].isVisited && Matrix[currRow+1][x].isVisited && Matrix[currRow][x-1].isVisited);
			}
			else if(y == 0) return (Matrix[currRow-1][x].isVisited && Matrix[currRow][x-1].isVisited && Matrix[currRow][x+1].isVisited);
			else return ((Matrix[currRow][x-1].isVisited && Matrix[currRow+1][x].isVisited && Matrix[currRow][x+1].isVisited));
		}
	}
}

bool Maze::breakWalls( int &x, int &y) const{
	int currRow = rows-1-y;
	int randWall = randomWallSelector(x, y);
	if(randWall == 0){
		if(!Matrix[currRow][x-1].isVisited){
			Matrix[currRow][x].l = 0;
			Matrix[currRow][x-1].r = 0;
			Matrix[currRow][x].isVisited = true;
			Matrix[currRow][x-1].isVisited = true;
			x--;
			return true;
		}
	}else if(randWall == 1){
		if(!Matrix[currRow-1][x].isVisited){
			Matrix[currRow][x].u = 0;
			Matrix[currRow-1][x].d = 0;
			Matrix[currRow][x].isVisited = true;
			Matrix[currRow-1][x].isVisited = true;
			y++;
			return true;
		}
	}else if(randWall == 2){
		if(!Matrix[currRow][x+1].isVisited){
			Matrix[currRow][x].r = 0;
			Matrix[currRow][x+1].l = 0;
			Matrix[currRow][x].isVisited = true;
			Matrix[currRow][x+1].isVisited = true;
			x++;
			return true;
		}
	}else{
		if(!Matrix[currRow+1][x].isVisited){
			Matrix[currRow][x].d =0;
			Matrix[currRow+1][x].u =0;
			Matrix[currRow][x].isVisited = true;
			Matrix[currRow+1][x].isVisited = true;
			y--;
			return true;
		}
	}
	return false;
}

void Maze::mazeGenerator(){

	int counterForVisit = 1, x, y ;
	Matrix[rows - 1][0].isVisited = true;
	commonStack.push( Matrix[rows - 1][0]);
	cell tempCell;
	while(counterForVisit != size){
		tempCell = commonStack.top();
		x = tempCell.x;
		y = tempCell.y;
		if(!isUnVisitedNotExist(x, y)){
			while(!breakWalls(x, y)){}
			commonStack.push(Matrix[rows-1-y][x]);
			counterForVisit++;
		}else{
			commonStack.pop();
		}
	}
	oFileGenerator();
	commonStack.makeEmpty();
	FillVec();
}

void Maze::PathFinder( int &initX, int &initY, const int &exitX, const int &exitY) {

	commonStack.push(Matrix[rows -1 -initY][initX]);
	cell temp;

	while(!((initX == exitX) && (initY == exitY))){
		temp = commonStack.top();
		initX = temp.x;
		initY = temp.y;
		if(isAWayExist(Matrix[rows -1 -initY][initX])){
			PathIncrement(initX, initY);
			commonStack.push(Matrix[rows -1 -initY][initX]);
		}else{
			commonStack.pop();
		}
	}
}

void Maze::FillVec() const {

	for(int i = 0 ; i < rows; i++)
	{
		for(int k = 0; k < cols ; k++){
			if(Matrix[i][k].l == 0) Matrix[i][k].vec.push_back(0);
			if(Matrix[i][k].d == 0) Matrix[i][k].vec.push_back(3);
			if(Matrix[i][k].u == 0) Matrix[i][k].vec.push_back(1);
			if(Matrix[i][k].r == 0) Matrix[i][k].vec.push_back(2);
		}
	}
}

int Maze::randPathSelector(const vector<int> & vec) const {
	RandGen random;
	return vec[random.RandInt(vec.size())];
}

int indxFinder(const vector<int> & vec, const int& target) {
	for(unsigned int i = 0 ; i < vec.size() ; i++)
	{
		if(vec[i] == target) return i;
	}
	return -1; //cannot find a element
}

void removeElement(vector<int> & a, int pos){
	//This function is taken from CS201 slides
	// post: original a[pos] removed, size decreased
	int lastIndex = a.size()-1;
	a[pos] = a[lastIndex];
	a.pop_back();
}

void Maze::PathIncrement(int &x , int& y) const {
	int currRow = rows-1-y;
	int temp = randPathSelector(Matrix[currRow][x].vec);
	if(temp == 0){ //temp = l
		removeElement(Matrix[currRow][x].vec, indxFinder(Matrix[currRow][x].vec, temp));
		removeElement(Matrix[currRow][x-1].vec, indxFinder(Matrix[currRow][x-1].vec, 2));
		Matrix[currRow][x].l = 1;
		Matrix[currRow][x-1].r = 1;
		x--;
	}else if(temp == 1){ //temp = u
		removeElement(Matrix[currRow][x].vec, indxFinder(Matrix[currRow][x].vec, temp));
		removeElement(Matrix[currRow-1][x].vec, indxFinder(Matrix[currRow-1][x].vec, 3));
		Matrix[currRow][x].u = 1;
		Matrix[currRow-1][x].d = 1;
		y++;
	}else if(temp == 2) { //temp = r
		removeElement(Matrix[currRow][x].vec, indxFinder(Matrix[currRow][x].vec, temp));
		removeElement(Matrix[currRow][x+1].vec, indxFinder(Matrix[currRow][x+1].vec, 0));
		Matrix[currRow][x].r = 1;
		Matrix[currRow][x+1].l = 1;
		x++;
	}else{ //temp = d
		removeElement(Matrix[currRow][x].vec, indxFinder(Matrix[currRow][x].vec, temp));
		removeElement(Matrix[currRow+1][x].vec, indxFinder(Matrix[currRow+1][x].vec, 1));
		Matrix[currRow][x].d = 1;
		Matrix[currRow+1][x].u = 1;
		y--;
	}
}

bool Maze::isAWayExist(const cell & cell) const {
	if(cell.l == 1 && cell.r == 1 && cell.u == 1 && cell.d == 1) return false;
	return true;
}


void Maze::oFileGenerator() {
	ofstream output;
	string i = tostring(id);

	output.open("maze_" + i + ".txt");
	output << *this;
	output.close();
}

void Maze::PathFileGenerator(const int &initX, const int &initY, const int &exitX, const int &exitY){
	ofstream output;
	Stack<cell> temp;
	cell tempCell;
	string i = tostring(id), x = tostring(initX), y = tostring(initY), ex = tostring(exitX), ey = tostring(exitY);

	while(!commonStack.isEmpty()){
		tempCell = commonStack.topAndPop();
		temp.push(tempCell);
	}
	output.open("maze_" + i + "_path_" + x + "_" + y + "_" + ex + "_" + ey + ".txt");
	while(!temp.isEmpty())
	{
		tempCell = temp.topAndPop();
		output << tempCell.x << " " << tempCell.y << endl;
	}
	output.close();

}
