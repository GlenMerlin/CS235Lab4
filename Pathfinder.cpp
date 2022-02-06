#include "Pathfinder.h"

using namespace std;

bool Pathfinder::importMaze(string file_name)
{
	cout << "importMaze from " << file_name << endl;
	ifstream checkfile(file_name.c_str());
	string checklines;
	int line_count = 0;
	while (getline(checkfile, checklines)){
		line_count++;
	}
	if (line_count != 29){
		return false;
	}
	cout << line_count << endl;
	ifstream file(file_name.c_str());
	if (file.is_open())
	{
		string line;
		int row_count = 0;
		
		
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
				row_count++;
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
						// cout << "["<<row<<"]["<<col<<"]["<<depth<<"]="<<value<<endl;
						maze_grid[row][col][depth] = value;	
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
				ss << maze_grid[row][col][depth] << " ";
			}
			ss << endl;
		}
		ss << endl;
	}
	return ss.str();
}

vector<string> Pathfinder::solveMaze()
{
	find_maze_path(maze_grid, 0, 0, 0);
	for (auto s : solution)
	{
		// cout << s << endl;
	}
	return solution;
}

void Pathfinder::createRandomMaze()
{
}

bool Pathfinder::find_maze_path(int grid[ROW_SIZE][COL_SIZE][DEPTH_SIZE], int r, int c, int d)
{
	// cout << "find_maze_path [" << r << "][" << c << "][" << d << "]" << endl;
	// cout << this->toString();
	if (r < 0 || c < 0 || d < 0 || r >= ROW_SIZE || c >= COL_SIZE || d >= DEPTH_SIZE)
		return false; // Cell is out of bounds.
	else if (grid[r][c][d] != BACKGROUND)
		return false; // Cell is on barrier or dead end.
	else if (r == ROW_SIZE - 1 && c == COL_SIZE - 1 && d == DEPTH_SIZE - 1)
	{
		grid[r][c][d] = PATH; // Cell is on path
		solution.push_back("(" + to_string(r) + "," + to_string(c) + "," + to_string(d) + ")");
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
			solution.push_back("(" + to_string(r) + "," + to_string(c) + "," + to_string(d) + ")");
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