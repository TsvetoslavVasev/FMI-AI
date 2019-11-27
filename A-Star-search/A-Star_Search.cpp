//
//  main.cpp
//  A-Start_FMI_AI
//
//  Created by TsvetoslavVasev on 22.10.19.
//  Copyright © 2019 TsvetoslavVasev. All rights reserved.



#include<iostream>
#include<vector>
#include<queue>
#include<math.h>

struct Node
{
    std::vector<int> state;
    int g_cost, h_cost, f_cost;
    Node* parent;

    Node()
    {
        this->g_cost = 0;
        this->h_cost = 0;
        this->f_cost = 0;
        this->parent = nullptr;
    }
};

// comparator for the priority queue
struct comp
{
    bool operator()(const Node* lhs, const Node* rhs) const
    {
        return lhs->f_cost > rhs->f_cost;
    }
};

int numberOfElements = 9;
std::vector<int> goalState;
std::vector<Node*> alreadyExplored;
std::priority_queue<Node*, std::vector<Node*>, comp> toBeExplored;

void printBoard(Node* n)
{
    int dim = sqrt(numberOfElements);
    int k = 0;
    for(int i = 0; i < dim; i++)
    {
        for(int j = 0; j < dim; ++j)
            std::cout << n->state[k++] << " ";
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// print solution
void reconstructPathFromRoot(Node* n)
{
    Node* temp = n;
    std::vector<Node*> totalpath;    // list containing all the nodes in the path from the root to the goal
    while(temp != nullptr)
    {
        totalpath.push_back(temp);
        temp = temp->parent;
    }

    int size = totalpath.size();
    std::cout << "Required Moves: " << size-1 << std::endl;

    //show the moves one by one
    for(int i = size-1; i >= 0; i--)
        printBoard(totalpath[i]);
}

// calculate heuristic
int calculate_manhatan(Node* n)
{
    int count = 0;
    for(int i = 0; i < numberOfElements; i++)
    {
            int stateX, stateY, x, y;

            stateX = n->state[i] % 3;
            stateY = n->state[i] / 3;

            x = i % 3;
            y = i / 3;

            count += abs(stateX - x) + abs(stateY - y);
    }
    return count;
}

// build successor node
Node* createSuccessor(Node* state, int pos1, int pos2)
{
    Node* new_state = new Node();
    new_state->state = state->state;
    
    std::swap(new_state->state[pos1], new_state->state[pos2]);
    
    new_state->h_cost = calculate_manhatan(new_state);
    new_state->g_cost = state->g_cost+1;
    new_state->f_cost = new_state->h_cost + new_state->g_cost;
    new_state->parent = state;

    return new_state;
}

// generate successors
std::vector<Node*> getSuccessor(Node* n)
{
    int pos, row, col, dim;
    for(int i = 0; i < numberOfElements; i++)
    {
        if(n->state[i] == 0)
        {
            pos = i;
            break;
        }
    }
    dim = sqrt(numberOfElements);
    row = pos / dim;
    col = pos % dim;

    std::vector<Node*> successors;
    
    // left
    if(col != 0)
        successors.push_back(createSuccessor(n, pos, pos-1));
    // right
    if(col != dim-1)
        successors.push_back(createSuccessor(n, pos, pos+1));
    // up
    if(row != 0)
        successors.push_back(createSuccessor(n, pos, pos-dim));
    // down
    if(row != dim-1)
        successors.push_back(createSuccessor(n, pos, pos+dim));

    return successors;
}

bool isGoal(Node* n)
{
    return (n->h_cost == 0) ? true : false;
}

bool checkAlreadyExplored(Node* n)
{
    int size = alreadyExplored.size(), j;
    for(int i = 0; i < size; i++)
    {
        for(j = 0; j < numberOfElements; ++j)
        {
            if(n->state[j] != alreadyExplored[i]->state[j])
                break;
        }
        if(j == numberOfElements)
            return true;
    }
    return false;
}

void A_starSearch(Node* n)
{
    n->h_cost = calculate_manhatan(n);
    n->f_cost = n->h_cost;
    n->parent = nullptr;
    toBeExplored.push(n);

    bool flag;
    int speculative_g_cost, size, k;
    Node *current;
    Node *temp;
    std::vector<Node*> currentSuccessors;
    std::priority_queue<Node*, std::vector<Node*>, comp> pq;

    while(!toBeExplored.empty())
    {
        current = toBeExplored.top();
        toBeExplored.pop();
        alreadyExplored.push_back(current);

        if(isGoal(current))
        {
            reconstructPathFromRoot(current);
            return;
        }

        currentSuccessors.clear();
        currentSuccessors = getSuccessor(current);

        size = currentSuccessors.size();
        for(int i = 0; i < size; i++)
        {
            if(checkAlreadyExplored(currentSuccessors[i]))
                continue;
            speculative_g_cost = current->g_cost+1;

            while(!pq.empty())
                pq.pop();
            while(!toBeExplored.empty())
            {
                temp = toBeExplored.top();
                toBeExplored.pop();

                flag = 0;
                for(k = 0; k < numberOfElements; ++k)
                    if(currentSuccessors[i]->state[k] != temp->state[k])
                        break;
                if(k == numberOfElements)
                    flag = 1;


                if(flag && speculative_g_cost < temp->g_cost)
                {
                    temp->parent = current;
                    temp->g_cost = speculative_g_cost;
                    temp->f_cost = temp->g_cost + temp->h_cost;
                }
                pq.push(temp);
            }
            if(!flag)
                pq.push(currentSuccessors[i]);
            toBeExplored = pq;
        }
    }

    return;
}

int main()
{
    // 2 4 3 7 1 5 0 8 6
    // 2 3 1 5 8 7 4 6 0
    
    int x;
    Node* node = new Node();

    // input initial state
    for(int i = 0; i < numberOfElements; i++)
    {
        std::cin >> x;
        node->state.push_back(x);
    }

    for(int i = 0; i < 9; i++)
    {
        goalState.push_back(i);
    }
    
    A_starSearch(node);
}
