#include "Solver.h"
#include <iostream>
#include <vector>

using namespace std;

int main() 
{
    vector<vector<char>> board = 
    {
        {' ', 'B', ' ', 'B', ' ', 'B', ' ', 'B'},
        {'B', ' ', 'B', ' ', 'B', ' ', 'B', ' '},
        {' ', 'B', ' ', 'B', ' ', 'B', ' ', 'B'},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', 'W', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {'W', ' ', 'W', ' ', 'W', ' ', 'W', ' '}
    };

    cout << "Creating Solver object...\n" << endl;
    Solver solver(board);

    cout << "Analyzing board...\n" << endl;
    solver.getMaxJumps();

    return 0;
}