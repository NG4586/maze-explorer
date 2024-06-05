// Nathaniel Graves
#include "maze-printer.h"

void getKeys(int* keys, int row, int col) // quadrants
{
  keys[0] = (row << 16) + col;
  keys[1] = (row << 16) + (col - 1);
  keys[2] = ((row + 1) << 16) + (col - 1);
  keys[3] = ((row + 1) << 16) + col;
}

void printMaze(map<int, map<int, int> > maze, int rows, int cols)
{
  map<int, map<int, int> >::iterator i;
  int counter = 0;
  int keys[4];
  int r = 0;
  int c = 1;
  cout << "┏";
  while (c < cols)
    {
      getKeys(keys, 0, c);
      if (maze[keys[1]].count(2))
        {
          cout << "━━";
        }
      else
        {
          cout << "━┳";
        }
      c ++;
    }
  cout << "━┓" << endl;
  while (r < rows - 1)
    {
      getKeys(keys, r, 1);
      if (maze[keys[1]].count(1))
        {
          cout << "┃";
        }
      else
        {
          cout << "┣";
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
                          cout << "  ";
                        }
                      else
                        {
                          cout << " ━";
                        }
                    }
                  else
                    {
                      if (maze[keys[0]].count(1))
                        {
                          cout << " ╻";
                        }
                      else
                        {
                          cout << " ┏";
                        }
                    }
                }
              else
                {
                  if (maze[keys[2]].count(2))
                    {
                      if (maze[keys[0]].count(1))
                        {
                          cout << " ╹";
                        }
                      else
                        {
                          cout << " ┗";
                        }
                    }
                  else
                    {
                      if (maze[keys[0]].count(1))
                        {
                          cout << " ┃";
                        }
                      else
                        {
                          cout << " ┣";
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
                          cout << "━ ";
                        }
                      else
                        {
                          cout << "━━";
                        }
                    }
                  else
                    {
                      if (maze[keys[0]].count(1))
                        {
                          cout << "━┓";
                        }
                      else
                        {
                          cout << "━┳";
                        }
                    }
                }
              else
                {
                  if (maze[keys[2]].count(2))
                    {
                      if (maze[keys[0]].count(1))
                        {
                          cout << "━┛";
                        }
                      else
                        {
                          cout << "━┻";
                        }
                    }
                  else
                    {
                      if (maze[keys[0]].count(1))
                        {
                          cout << "━┫";
                        }
                      else
                        {
                          cout << "━╋";
                        }
                    }
                }
            }
          c ++;
        }
      if (maze[keys[0]].count(1))
        {
          cout << " ┃";
        }
      else
        {
          cout << "━┫";
        }
      cout << endl;
      r ++;
    }
  c = 1;
  cout << "┗";
  while (c < cols)
    {
      getKeys(keys, rows - 2, c);
      if (maze[keys[2]].count(2))
        {
          cout << "━━";
        }
      else
        {
          cout << "━┻";
        }
      c ++;
    }
  cout << "━┛" << endl;
}
