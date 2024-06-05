// Nathaniel Graves
#include "maze-printer.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <ctime>
#include <list>
#include <set>
#include <map>
using std::advance;
using std::string;
using std::stoi;
using std::vector;
using std::list;
using std::set;
using std::map;
using std::cin;
using std::cout;
using std::endl;

const int DIRS = 4;
const unsigned int DIR_VALS[DIRS] = {0xffff0000, 0x00010000, // north, south
				     0x00000001, 0xffffffff}; // east, west

int walkTo(int location, vector<int> options)
{
  int step = options[rand() % options.size()];
  return location + DIR_VALS[step];
}

void addStep(vector<int>* path, set<int>* domain, int* dims)
{
  int distance = path -> size();
  int lastStep = path -> back();
  int testStep;
  vector<int> spaces;
  for (int n = 0; n < DIRS; n ++)
    {
      testStep = lastStep + DIR_VALS[n];
      // backtrack
      if (distance >= 2 && testStep == path -> at(distance - 2))
        {
          continue;
        }
      // nw bounds
      if ((testStep | 0x0000ffff) == -1 || (testStep | 0xffff0000) == -1)
        {
          continue;
        }
      // se bounds
      if ((testStep >> 16) == dims[0] || ((testStep << 16) >> 16) == dims[1])
        {
          continue;
        }
      spaces.push_back(n);
    }
  path -> push_back(walkTo(lastStep, spaces));
  int thisStep = path -> back();
  if (domain -> count(thisStep))
    {
      path -> pop_back();
      while (path -> back() != thisStep)
	{
	  domain -> erase(path -> back());
	  path -> pop_back();
	}
    }
  else
    {
      domain -> insert(thisStep);
    }
}

vector<int> addPath(int startAt, set<int>* endAt, int* dims)
{
  vector<int> newPath(1, startAt);
  set<int> pathPts;
  pathPts.insert(startAt);
  while (!endAt -> count(newPath.back()))
    {
      addStep(&newPath, &pathPts, dims);
    }
  for (int n = 0; n < newPath.size(); n ++)
    {
      endAt -> insert(newPath[n]);
    }
  return newPath;
}

map<int, map<int, int> > createMaze(int* dims)
{
  map<int, map<int, int> > newMaze;
  list<int> tiles;
  for (int row = 0; row < dims[0]; row ++)
    {
      for (int col = 0; col < dims[1]; col ++)
        {
          tiles.push_back((row << 16) + col);
        }
    }
  int unset = tiles.size();
  int nextTile;
  list<int>::iterator select;
  while (unset > 0)
    {
      select = tiles.begin();
      nextTile = rand() % unset;
      advance(select, nextTile);
      tiles.splice(tiles.end(), tiles, select);
      unset --;
    }
  set<int> mazePts;
  map<int, int> newNode;
  mazePts.insert(tiles.front());
  newMaze[tiles.front()] = newNode;
  tiles.pop_front();
  vector<int> nextPath;
  int stepType;
  while (!tiles.empty())
    {
      nextPath = addPath(tiles.front(), &mazePts, dims);
      newMaze[nextPath.front()] = newNode;
      for (int n = 1; n < nextPath.size(); n ++)
        {
          stepType = nextPath[n] - nextPath[n - 1];
          for (int d = 0; d < DIRS; d ++)
            {
              if (stepType == DIR_VALS[d])
                {
                  newMaze[nextPath[n - 1]][d] = nextPath[n];
                  if (n < nextPath.size() - 1)
                    {
                      newMaze[nextPath[n]] = newNode;
                    }
                  if (d % 2 == 0)
                    {
                      newMaze[nextPath[n]][d + 1] = nextPath[n - 1];
                    }
                  else
                    {
                      newMaze[nextPath[n]][d - 1] = nextPath[n - 1];
                    }
                  break;
                }
            }
        }
      while (!tiles.empty() && newMaze[tiles.front()].size() > 0)
        {
          tiles.pop_front();
        }
    }
  return newMaze;
}

int main(int argc, char** argv)
{
  srand(time(NULL));
  if (argc > 2)
    {
      int rows = stoi((string) argv[1]); // assuming valid inputs
      int cols = stoi((string) argv[2]);
      int inputs[2] = {rows, cols};
      map<int, map<int, int> > theMaze = createMaze(inputs);
      printMaze(theMaze, rows, cols);
    }
  return 0;
}
