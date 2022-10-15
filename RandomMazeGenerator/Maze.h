#ifndef _MAZE_H
#define _MAZE_H
#include "Stack.h"
#include <vector>
#include <sstream>
#include <fstream>

struct cell{
	int x, y;
	int l, r, d, u;
	bool isVisited;

	vector<int> vec;

	cell::cell():l(1),r(1),u(1),d(1),isVisited(false){x = 0 ; y = 0;};
};

class Maze{

public:
	
	//constructor
	Maze(){};
	Maze(const int &, const int &, const int &);
	//destructor
	~Maze();

	//Mutator
	void mazeGenerator();
	void oFileGenerator(); //generate output file
	void PathFileGenerator(const int& ,const int& , const int&, const int&);
	void PathFinder( int& , int& , const int&, const int&);

	//Accessors
	int randomWallSelector(const int &, const int &) const;
	bool isUnVisitedNotExist(const int &, const int &) const; // for all push operation this function look neighboring cells and decide whether an unvisited cell exist
	bool breakWalls( int &, int &) const;
	void FillVec() const;

	void deleteMatrix();

	int randPathSelector(const vector<int> &) const;
	void PathIncrement(int &, int &) const;
	bool isAWayExist(const cell &) const;

	const Maze & operator = (const Maze &);
	friend ostream & operator << (ostream &, const Maze &);

private:
	int id, rows, cols;
	int size;
	cell ** Matrix;
	Stack<cell> commonStack;
};

#endif
