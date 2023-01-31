#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm> 
#include <set>  
#include <unordered_set>
using namespace std;

struct cell
{
    int x;
    int y;
    char value = ' ';
    float g = 0;
    float h = 0;
    float f = 0;
    bool visited = false;
    bool justExplored = false;
    vector<cell> path;
};

vector<cell> openList;
vector<cell> closeList;
vector<vector<cell>> maze;
vector<cell> blockedCells;

bool Done = false;
int mazeSize;
int Blocked;
cell startNode;
cell goalNode;

bool checkIfBlocked(int x, int y)
{
    for (int i = 0; i < blockedCells.size(); i++)
    {
        if (x == blockedCells[i].x)
        {
            if (y == blockedCells[i].y)
                return true;
        }
    }
    return false;
}

bool checkCellMatch(cell n1, cell n2)
{
    if (n1.x == n2.x)
    {
        if (n1.y == n2.y)
            return true;
    }
    else return false;
}

void CalculateH()
{
    for (int i = 0; i < maze.size(); i++)
    {
        for (int j = 0; j < maze[i].size(); j++)
        {
            if (maze[i][j].value != '*')
            {
                maze[i][j].h = abs(i - goalNode.x) + abs(j - goalNode.y);
                //maze[i][j].h = sqrt(pow((maze[i][j].x - goalNode.x), 2) + pow((maze[i][j].y - goalNode.y), 2));
            }
        }
    }
}

bool compareByF(cell &N1, cell &N2)
{
    return N1.f < N2.f;
}

bool compareX(cell& N1, cell& N2)
{
    return (N1.x < N2.x );
}

bool compareY(cell& N1, cell& N2)
{
    return (N1.y < N2.y);
}




int main()
{
    

    cout << "Input size of the Maze N (NxN): ";
    cin >> mazeSize;

    cout << "Input X value of start node: ";
    cin >> startNode.x;
    cout << "Input Y value of start node: ";
    cin >> startNode.y;
    

    closeList.push_back(startNode);

    cout << "Input X value of goal node: ";
    cin >> goalNode.x;
    cout << "Input Y value of goal node: ";
    cin >> goalNode.y;

    cout << "Input the number of blocked cells: ";
    cin >> Blocked;

    for (int i = 0; i < Blocked; i++)
    {
        cell temp;
        cout << "Please input X value of blocked cell no." << i << " : ";
        cin >> temp.x;
        cout << "Please input Y value of blocked cell no." << i << " : ";
        cin >> temp.y;
        blockedCells.push_back(temp);
    }

    maze.resize(mazeSize);
    for (int i = 0; i < mazeSize; i++)
    {
        for (int j = 0; j < mazeSize; j++)
        {
            cell temp;
            temp.x = i;
            temp.y = j;
            if (checkIfBlocked(i, j))
            {
                temp.value = '*';
            }
            maze[i].push_back(temp);
        }
    }
    cell currentCell = startNode;
    maze[startNode.x][startNode.y].f = maze[startNode.x][startNode.y].h;
    maze[startNode.x][startNode.y].visited = true;
    CalculateH();
    int count = 0;
    while (Done == false || count <= mazeSize*mazeSize)
    {
        //cout << count;
        if (checkCellMatch(currentCell, goalNode))
        {
            Done = true;
            
            break;
        }
        else
        {
            for (int i = 0; i < mazeSize; i++)
            {
                for (int j = 0; j < mazeSize; j++)
                {
                    if (maze[i][j].justExplored == true)
                    {
                        maze[i][j].justExplored = false;
                    }
                    
                }
            }

            

            
            //since we can only move up, down, left, or right
            if (currentCell.x + 1 < mazeSize )
            {
                if (maze[currentCell.x + 1][currentCell.y].value != '*' && maze[currentCell.x + 1][currentCell.y].visited == false)
                {
                    maze[currentCell.x + 1][currentCell.y].g = maze[currentCell.x][currentCell.y].g + 1;
                    maze[currentCell.x + 1][currentCell.y].f = maze[currentCell.x + 1][currentCell.y].g + maze[currentCell.x + 1][currentCell.y].h;
                    
                    maze[currentCell.x + 1][currentCell.y].visited = true;
                    maze[currentCell.x + 1][currentCell.y].justExplored = true;
                    openList.push_back(maze[currentCell.x + 1][currentCell.y]);
                }
            }
            if (currentCell.y + 1 < mazeSize)
            {
                if (maze[currentCell.x][currentCell.y + 1].value != '*' && maze[currentCell.x][currentCell.y + 1].visited == false)
                {
                    maze[currentCell.x][currentCell.y + 1].g = maze[currentCell.x][currentCell.y].g + 1;
                    maze[currentCell.x][currentCell.y + 1].f = maze[currentCell.x][currentCell.y + 1].g + maze[currentCell.x][currentCell.y + 1].h;
                    
                    maze[currentCell.x][currentCell.y + 1].visited = true;
                    maze[currentCell.x][currentCell.y + 1].justExplored = true;
                    openList.push_back(maze[currentCell.x][currentCell.y + 1]);
                }
            }
            if (currentCell.x - 1 > -1)
            {
                if (maze[currentCell.x - 1][currentCell.y].value != '*' && maze[currentCell.x - 1][currentCell.y].visited == false)
                {
                    maze[currentCell.x - 1][currentCell.y].g = maze[currentCell.x][currentCell.y].g + 1;
                    maze[currentCell.x - 1][currentCell.y].f = maze[currentCell.x - 1][currentCell.y].g + maze[currentCell.x - 1][currentCell.y].h;
                    
                    maze[currentCell.x - 1][currentCell.y].visited = true;
                    maze[currentCell.x - 1][currentCell.y].justExplored = true;
                    openList.push_back(maze[currentCell.x - 1][currentCell.y]);
                }
            }
            if (currentCell.y - 1 > -1)
            {
                if (maze[currentCell.x][currentCell.y - 1].value != '*' && maze[currentCell.x][currentCell.y - 1].visited == false)
                {
                    maze[currentCell.x][currentCell.y - 1].g = maze[currentCell.x][currentCell.y].g + 1;
                    maze[currentCell.x][currentCell.y - 1].f = maze[currentCell.x][currentCell.y - 1].g + maze[currentCell.x][currentCell.y - 1].h;
                    
                    maze[currentCell.x][currentCell.y - 1].visited = true;
                    maze[currentCell.x][currentCell.y - 1].justExplored = true;
                    openList.push_back(maze[currentCell.x][currentCell.y - 1]);
                }
            }
           
            sort(openList.begin(), openList.end(), compareByF); //sorting based on F value
            cell oldCell = currentCell;
            
            bool check = false;
            for (int i = 0; i < openList.size(); i++)
            {
                if (openList[i].justExplored)
                {
                    maze[openList[i].x][openList[i].y].path.push_back(maze[oldCell.x][oldCell.y]);
                    for (int j = 0; j < maze[oldCell.x][oldCell.y].path.size(); j++)
                    {
                        maze[openList[i].x][openList[i].y].path.push_back(maze[oldCell.x][oldCell.y].path[j]);
                    }
                }
            }

            if (currentCell.f == openList[0].f)
            {
                for (int i = 0; i < openList.size(); i++)
                {
                    if (openList[i].justExplored)
                    {
                        currentCell = openList[i];
                        closeList.push_back(maze[openList[i].x][openList[i].y]);
                        openList.erase(openList.begin() + i);
                        check = true;
                        continue;
                    }
                }
                
            }
            if (check)
            {
                continue;
            }

            

            closeList.push_back(maze[openList[0].x][openList[0].y]);
            currentCell = maze[openList[0].x][openList[0].y];
           
            if (maze[currentCell.x][currentCell.y].justExplored)
            {
                maze[currentCell.x][currentCell.y].path.push_back(maze[oldCell.x][oldCell.y]);
                for (int i = 0; i < maze[oldCell.x][oldCell.y].path.size(); i++)
                {
                    maze[currentCell.x][currentCell.y].path.push_back(maze[oldCell.x][oldCell.y].path[i]);
                }
            }
            
            openList.erase(openList.begin());
            
            

        }
        count++;
    }

    for (int i = 0; i < mazeSize; i++)
    {
        for (int j = 0; j < mazeSize; j++)
        {

            sort(maze[i][j].path.begin(), maze[i][j].path.end(), compareX);
            sort(maze[i][j].path.begin(), maze[i][j].path.end(), compareY);
            maze[i][j].path.erase(unique(maze[i][j].path.begin(), maze[i][j].path.end(), checkCellMatch), maze[i][j].path.end());
            //remove(maze[i][j].path);

        }
    }
   
    
    cout << endl << "Final path is:" << endl;
    for (int i = 0; i < maze[currentCell.x][currentCell.y].path.size(); i++)
    {
        cout << "(" << maze[currentCell.x][currentCell.y].path[i].x << " , " << maze[currentCell.x][currentCell.y].path[i].y << ") -> ";
    }
    cout << "(" << currentCell.x << " , " << currentCell.y << ")";
}

