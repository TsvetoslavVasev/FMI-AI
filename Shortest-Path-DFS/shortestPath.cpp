//
//  main.cpp
//  TASK-1_FMI_AI
//
//  Created by TsvetoslavVasev on 9.10.19.
//  Copyright © 2019 TsvetoslavVasev. All rights reserved.
//

#include <iostream>
#include <queue>
#include <stack>


struct Cell
{
    int row;
    int col;
    int dist;
    Cell* parent;
    
    Cell(int _row, int _col, int _dist, Cell* _parent)
    {
        this->row = _row;
        this->col = _col;
        this->dist = _dist;
        this->parent = _parent;
    }
    
};

const int matrix[6][6] = {
    {1,1,0,1,1,1},
    {1,2,0,0,1,1},
    {1,1,1,1,2,1},
    {1,1,1,1,1,1},
    {1,0,0,1,1,1},
    {1,1,1,1,1,1}
};
// teleport1 [1][1]
// teleport2 [2][4]

// source [0][0]
// goal [4][4]

int shortestPath()
{
    Cell* source = new Cell(0, 0, 0,nullptr);
    
    // To keep track of visited Cells.
    // Marking blocked cells as visited.
    bool visited[6][6];
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (matrix[i][j] == 0)
                visited[i][j] = true;
            else
                visited[i][j] = false;
        }
    }
    
    // applying BFS on matrix cells starting from source
    std::queue<Cell*> q;
    q.push(source);
    visited[source->row][source->col] = true;
    while (!q.empty())
    {
        Cell* currentCell = q.front();
        q.pop();
        
        // Destination found;
        if (currentCell->row == 4 && currentCell->col == 4)
        {
            
            // Using stack to print moves (indices of cells) from start to end
            Cell* crr = currentCell;
            std::stack<Cell*> stack;
            while(crr)
            {
                stack.push(crr);
                crr = crr->parent;
            }
            while(!stack.empty())
            {
                crr=stack.top();
                stack.pop();
                std::cout<<'['<<crr->row<<']'<<'['<<crr->col<<"] ";
            }
            std::cout<<'\n';
            return currentCell->dist;
        }
        
        // Check if currently on teleport cell
        if(currentCell->row == 1 && currentCell->col == 1)
        {
            Cell* toAdd = new Cell(2,4,currentCell->dist+1,currentCell);
            q.push(toAdd);
        }
        
        if(currentCell->row == 2 && currentCell->col == 4)
        {
            Cell* toAdd = new Cell(1,1,currentCell->dist+1,currentCell);
            q.push(toAdd);
        }
        
        // moving up
        if (currentCell->row - 1 >= 0 &&
            visited[currentCell->row - 1][currentCell->col] == false)
        {
            Cell* toAdd = new Cell(currentCell->row - 1, currentCell->col, currentCell->dist + 1,currentCell);
            q.push(toAdd);
            visited[currentCell->row - 1][currentCell->col] = true;
        }

        // moving down
        if (currentCell->row + 1 < 6 &&
            visited[currentCell->row + 1][currentCell->col] == false)
        {
            Cell* toAdd = new Cell(currentCell->row + 1, currentCell->col, currentCell->dist + 1,currentCell);
            q.push(toAdd);
            visited[currentCell->row + 1][currentCell->col] = true;
        }
        
        // moving left
        if (currentCell->col - 1 >= 0 &&
            visited[currentCell->row][currentCell->col - 1] == false)
        {
            Cell* toAdd = new Cell(currentCell->row , currentCell->col - 1, currentCell->dist + 1,currentCell);
            q.push(toAdd);
            visited[currentCell->row][currentCell->col - 1] = true;
        }
        
        // moving right
        if (currentCell->col + 1 < 6 &&
            visited[currentCell->row][currentCell->col + 1] == false)
        {
            Cell* toAdd = new Cell(currentCell->row, currentCell->col + 1, currentCell->dist + 1,currentCell);
            q.push(toAdd);
            visited[currentCell->row][currentCell->col + 1] = true;
        }
    }
    // case no path is found
    return -1;
}

int main()
{
    std::cout<<shortestPath()<<" steps is the shortest path\n";
    
}



