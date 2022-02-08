#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include "PathfinderInterface.h"

using namespace std;


const int ROW_SIZE = 5;
const int COL_SIZE = 5;
const int DEPTH_SIZE = 5;
class Pathfinder: public PathfinderInterface {
  protected:
    
    const int BACKGROUND = 1;
    const int WALL = 0;
    const int TEMPORARY = 2; // Used to show this path has been explored
    const int PATH = 3;
    int maze_grid[ROW_SIZE][COL_SIZE][DEPTH_SIZE]; // To hold values
    int maze_backup[ROW_SIZE][COL_SIZE][DEPTH_SIZE];
    int new_maze[ROW_SIZE][COL_SIZE][DEPTH_SIZE];
    vector<string> solution;
  public:
    Pathfinder() {
      srand (time(0));
    for (int depth = 0; depth < DEPTH_SIZE; depth++)
		{
			for (int row = 0; row < ROW_SIZE; row++)
			{
				for (int col = 0; col < COL_SIZE; col++)
				{
					
					maze_grid[row][col][depth] = 1;

				}
			}
		}	
    }
    ~Pathfinder() {

    }
    string toString() const;
    void createRandomMaze();
    bool importMaze(string file_name);
    bool find_maze_path(int grid[ROW_SIZE][COL_SIZE][DEPTH_SIZE], int r, int c, int d);
    vector<string> solveMaze();
};