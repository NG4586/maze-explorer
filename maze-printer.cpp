// Nathaniel Graves
#include "maze-printer.h"

void getKeys(int* keys, int row, int col) // quadrants
{
  keys[0] = (row << 16) + col;
  keys[1] = (row << 16) + (col - 1);
  keys[2] = ((row + 1) << 16) + (col - 1);
  keys[3] = ((row + 1) << 16) + col;
}

vector<string> writeMaze(map<int, map<int, int> > maze, int rows, int cols)
{
  int counter = 0;
  int keys[4];
  int r = 0;
  int c = 1;
  string nextLine = "┌";
  vector<string> result;
  while (c < cols)
    {
      getKeys(keys, 0, c);
      if (maze[keys[1]].count(2))
        {
          nextLine += "──";
        }
      else
        {
          nextLine += "─┬";
        }
      c ++;
    }
  nextLine += "─┐";
  result.push_back(nextLine);
  while (r < rows - 1)
    {
      getKeys(keys, r, 1);
      if (maze[keys[1]].count(1))
        {
          nextLine = "│";
        }
      else
        {
          nextLine = "├";
        }
      c = 1;
      while (c < cols)
        {
          getKeys(keys, r, c);
          if (maze[keys[1]].count(1))
            {
              if (maze[keys[1]].count(2))
                {
                  if (maze[keys[2]].count(2))
                    {
                      if (maze[keys[0]].count(1))
                        {
                          nextLine += "  ";
                        }
                      else
                        {
                          nextLine += " ─";
                        }
                    }
                  else
                    {
                      if (maze[keys[0]].count(1))
                        {
                          nextLine += " ╷";
                        }
                      else
                        {
                          nextLine += " ┌";
                        }
                    }
                }
              else
                {
                  if (maze[keys[2]].count(2))
                    {
                      if (maze[keys[0]].count(1))
                        {
                          nextLine += " ╵";
                        }
                      else
                        {
                          nextLine += " └";
                        }
                    }
                  else
                    {
                      if (maze[keys[0]].count(1))
                        {
                          nextLine += " │";
                        }
                      else
                        {
                          nextLine += " ├";
                        }
                    }
                }
            }
          else
            {
              if (maze[keys[1]].count(2))
                {
                  if (maze[keys[2]].count(2))
                    {
                      if (maze[keys[0]].count(1))
                        {
                          nextLine += "─ ";
                        }
                      else
                        {
                          nextLine += "──";
                        }
                    }
                  else
                    {
                      if (maze[keys[0]].count(1))
                        {
                          nextLine += "─┐";
                        }
                      else
                        {
                          nextLine += "─┬";
                        }
                    }
                }
              else
                {
                  if (maze[keys[2]].count(2))
                    {
                      if (maze[keys[0]].count(1))
                        {
                          nextLine += "─┘";
                        }
                      else
                        {
                          nextLine += "─┴";
                        }
                    }
                  else
                    {
                      if (maze[keys[0]].count(1))
                        {
                          nextLine += "─┤";
                        }
                      else
                        {
                          nextLine += "─┼";
                        }
                    }
                }
            }
          c ++;
        }
      if (maze[keys[0]].count(1))
        {
          nextLine += " │";
        }
      else
        {
          nextLine += "─┤";
        }
      result.push_back(nextLine);
      r ++;
    }
  c = 1;
  nextLine = "└";
  while (c < cols)
    {
      getKeys(keys, rows - 2, c);
      if (maze[keys[2]].count(2))
        {
          nextLine += "──";
        }
      else
        {
          nextLine += "─┴";
        }
      c ++;
    }
  nextLine += "─┘";
  result.push_back(nextLine);
  return result;
}

void printMaze(vector<string> maze, int* player, int* dest)
{
  cout << " ";
  for (int c = 0; c < player[1]; c ++)
    {
      cout << "  ";
    }
  cout << " ┆" << endl;
  for (int r = 0; r < maze.size(); r ++)
    {
      if (r == player[0])
        {
          cout << "╲";
        }
      else if (r - 1 == player[0])
        {
          cout << "╱";
        }
      else
        {
          cout << " ";
        }
      cout << maze[r];
      if (r == dest[0])
        {
          cout << "╱";
        }
      else if (r - 1 == dest[0])
        {
          cout << "╲";
        }
      cout << endl;
    }
  cout << " ";
  for (int c = 0; c < dest[1]; c ++)
    {
      cout << "  ";
    }
  cout << " ┆" << endl;
}
