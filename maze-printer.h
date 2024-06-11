// Nathaniel Graves
#include <iostream>
#include <vector>
#include <string>
#include <map>
using std::vector;
using std::string;
using std::map;
using std::cout;
using std::endl;

void getKeys(int* keys, int row, int col);

vector<string> writeMaze(map<int, map<int, int> > maze, int rows, int cols);

void printMaze(vector<string> maze, int* player, int* dest);
