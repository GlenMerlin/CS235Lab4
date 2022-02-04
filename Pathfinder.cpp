#include <fstream>
#include "Pathfinder.h"
#include <string>
#include <sstream>

using namespace std;

bool Pathfinder::importMaze(string file_name)
{
    cout << "importMaze from " << file_name << endl;
    ifstream file(file_name.c_str());
    if (file.is_open())
    {
        string line;
        int row_count = 0;
        for (int row = 0; row < ROW_SIZE; row++)
        {
            getline(file, line);
            stringstream ss(line);
            for (int col = 0; col < COL_SIZE; col++)
            {
                int value;
                ss >> value;
                cout << "[" << row << "][" << col << "]=" << value << endl;
                maze_grid[row][col] = value;
            }
        }
    }
    return (true);
};
