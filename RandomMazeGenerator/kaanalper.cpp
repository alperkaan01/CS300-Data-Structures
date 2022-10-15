#include <iostream>
#include <string>
#include "Maze.h"
#include <vector>
#include "Stack.h"

using namespace std;


int main()
{
	int number_of_mazes, rows, cols;

	cout << "Enter the number of mazes: ";
	cin >> number_of_mazes;

	cout << "Enter the number of rows and columns (M and N): ";
	cin >> rows >> cols;

	Maze * arr = new Maze[number_of_mazes];

	Maze maze;
	for(int i = 0 ; i < number_of_mazes ; i++){
		Maze localMaze(i, rows, cols);
		maze = localMaze;
		arr[i] = maze;
	} 

	cout << "All mazes are generated." << endl << endl;

	int mazeId, initX, initY, exitX, exitY;
	if(number_of_mazes > 1){
		cout << "Enter a maze ID between 1 to " << number_of_mazes << " inclusive to find a path: ";
		cin >> mazeId;

		maze = arr[mazeId-1];
	}else {
		maze = arr[0];
	}

	cout << "Enter x and y coordinates of the entry points (x,y) or (column,row): ";
	cin >> initX >> initY;
	cout << "Enter x and y coordinates of the exit points (x,y) or (column,row): ";
	cin >> exitX >> exitY;

	int firstX(initX), firstY(initY);

	maze.PathFinder(initX,initY,exitX,exitY);
	maze.PathFileGenerator(firstX,firstY,exitX,exitY);
	delete [] arr;
	return 0;
}
