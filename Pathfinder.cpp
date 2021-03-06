#include "Pathfinder.h"
#include <bits/stdc++.h>

using namespace std;

bool Pathfinder::importMaze(string file_name)
{
	cout << "importMaze from " << file_name << endl;
	
	ifstream checkfile(file_name);
	string checklines;
	
	int line_count = 0;
	while (getline(checkfile, checklines)){
		line_count++;
	}

	if (line_count != 29){
		return false;
	}
	
	ifstream file(file_name);
	
	if (file.is_open())
	{
		string line;
		
		for (int depth = 0; depth < DEPTH_SIZE; depth++)
		{
			for (int row = 0; row < ROW_SIZE; row++)
			{
				
				getline(file, line);
				
				if (line.length()==0){
					getline(file, line);
				}
				
				stringstream ss(line);
				stringstream checkss(line);
				
				for (int col = 0; col < COL_SIZE; col++)
				{
					string check;
					checkss >> check;
					if (check.length() > 1){
						return false;
					}
					int value;
					ss >> value;
					
					if (value == 0 || value == 1)
					{
						maze_grid[row][col][depth] = value;
						maze_backup[row][col][depth] = value;
					}
					else {
						return false;
					}
				}
			}
		}

	}
	if (maze_grid[4][4][4] == 0 || maze_grid[0][0][0] == 0){
			return false;
	}
	
	return true;
}

string Pathfinder::toString() const
{
	stringstream ss;
	for (int depth = 0; depth < DEPTH_SIZE; depth++)
	{
		for (int row = 0; row < ROW_SIZE; row++)
		{
			for (int col = 0; col < COL_SIZE; col++)
			{
				if (col != 4){
					ss << maze_grid[row][col][depth] << " ";
				}
				else {
					ss << maze_grid[row][col][depth];
				}

			}
			ss << endl;
		}
		if (depth == DEPTH_SIZE -1){
			continue;
		}
		ss << endl;
	}
	return ss.str();
}

vector<string> Pathfinder::solveMaze()
{
	solution.clear();
	find_maze_path(maze_backup, 0, 0, 0);
	reverse(solution.begin(), solution.end());
	return solution;
}

bool Pathfinder::find_maze_path(int grid[ROW_SIZE][COL_SIZE][DEPTH_SIZE], int r, int c, int d)
{

	if (r < 0 || c < 0 || d < 0 || r > 4 || c > 4 || d > 4)
		return false; // Cell is out of bounds.
	
	else if (grid[r][c][d] != BACKGROUND)
		return false; // Cell is on barrier or dead end.

	// Exit if the exit is found	
	else if (r == 4 && c == 4 && d == 4)
	{
		grid[r][c][d] = PATH; // Cell is on path
		solution.push_back("(" + to_string(c) + ", " + to_string(r) + ", " + to_string(d) + ")");
		return true; // and is maze exit.
	}
	else
	{
		// Recursive case.
		// Attempt to find a path from each neighbor.
		// Tentatively mark cell as on path.
		grid[r][c][d] = PATH;
		if (find_maze_path(grid, r - 1, c, d)	 // Up
			|| find_maze_path(grid, r + 1, c, d) // Down
			|| find_maze_path(grid, r, c - 1, d) // Left
			|| find_maze_path(grid, r, c + 1, d) // Right
			|| find_maze_path(grid, r, c, d + 1) // Forward
			|| find_maze_path(grid, r, c, d - 1) // Back
		)
		{
			solution.push_back("(" + to_string(c) + ", " + to_string(r) + ", " + to_string(d) + ")");
			return true;
		}
		else
		{
			grid[r][c][d] = TEMPORARY; // Dead end.
			return false;
		}
	}
	return false;
}

void Pathfinder::createRandomMaze()
{
	int randomNum;
	cout << "creating a new maze" << endl << '1' << endl;
	for (int depth = 0; depth < DEPTH_SIZE; depth++)
	{
		for (int row = 0; row < ROW_SIZE; row++)
		{
			for (int col = 0; col < COL_SIZE; col++)
			{
				if (col == 0 && row == 0 && depth == 0 || col == 4 && row == 4 && depth == 4){
					maze_grid[row][col][depth] = 1;
					maze_backup[row][col][depth] = 1;
				}
				else{
					randomNum = rand() % 2;
					cout << randomNum << endl;
					maze_grid[row][col][depth] = randomNum;
					maze_backup[row][col][depth] = randomNum;
				}	
			}
		}
	}
}
