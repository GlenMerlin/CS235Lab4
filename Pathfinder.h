#include "PathfinderInterface.h"
using namespace std;


class Pathfinder: protected PathfinderInterface {
protected:
  const int ROW_SIZE = 5;
  const int COL_SIZE = 5;
  const int BACKGROUND = 1;
  const int WALL = 0;
  const int TEMPORARY = 2; // Used to show this path has been explored
  const int PATH = 3;
  int maze_grid[5][5]; // To hold values
  vector<string> solution;
};