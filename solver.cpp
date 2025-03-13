#include "Solver.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

Solver::Solver(const vector<vector<char>>& input_board) 
{
    if (input_board.size() != 8 || input_board[0].size() != 8) 
    {
        cerr << "Error: Board must be 8x8." << endl;
        return;
    }
    for (const auto& row : input_board) 
    {
        for (char cell : row) {
            if (cell != 'B' && cell != 'W' && cell != ' ') 
            {
                cerr << "Error: Invalid character on board." << endl;
                return;
            }
        }
    }
    board = input_board;
}

void Solver::printBoard(const vector<vector<char>>& board) const 
{
    cout << "   0 1 2 3 4 5 6 7" << endl;
    for (int i = 0; i < 8; ++i) 
    {
        cout << i << " ";

        for (int j = 0; j < 8; ++j) 
        {
            cout << (board[i][j] == ' ' ? '.' : board[i][j]) << " ";
        }
        cout << endl;
    }
}



int Solver::getMaxJumps() 
{
    cout << "Initial board:" << endl;
    printBoard(board);

    int global_max_jumps = 0;

    pair<int, int> best_piece_position = { -1, -1 };

    vector<pair<int, int>> best_jump_sequence;

    for (int i = 0; i < 8; ++i) 
    {
        for (int j = 0; j < 8; ++j) 
        {
            if (board[i][j] == 'W') 
            {
                vector<pair<int, int>> jump_sequence;

                int max_jumps = findMaxJumpsForPiece(i, j, board, jump_sequence);

                cout << "Piece at (" << i << ", " << j << ") can make " << max_jumps << " jumps: ";

                if (!jump_sequence.empty()) 
                {
                    for (size_t k = 0; k < jump_sequence.size(); ++k)
                    {
                        cout << "(" << jump_sequence[k].first << ", " << jump_sequence[k].second << ")";

                        if (k != jump_sequence.size() - 1) cout << " -> ";
                    }
                }
                else 
                {
                    cout << "No jumps";
                }
                cout << endl;

                if (max_jumps > global_max_jumps) 
                {
                    global_max_jumps = max_jumps;
                    best_piece_position = { i, j };
                    best_jump_sequence = jump_sequence;
                }
            }
        }
    }


    if (best_piece_position.first != -1 && best_piece_position.second != -1) 
    {
        cout << "Best move: Piece at (" << best_piece_position.first << ", " << best_piece_position.second << ") ";
        cout << "with jump sequence: ";

        for (size_t k = 0; k < best_jump_sequence.size(); ++k) 
        {
            cout << "(" << best_jump_sequence[k].first << ", " << best_jump_sequence[k].second << ")";

            if (k != best_jump_sequence.size() - 1) cout << " -> ";
        }
        cout << endl;
    }
    else 
    {
        cout << "No valid moves for any white checker.\n" << endl;
    }

    return global_max_jumps;
}


bool Solver::isValidJump(int x, int y, int dx, int dy, const vector<vector<char>>& board) const 
{
    int nx = x + dx, ny = y + dy;
    int mx = x + 2 * dx, my = y + 2 * dy;


    if (mx < 0 || mx >= 8 || my < 0 || my >= 8) return false;
    if (board[nx][ny] != 'B') return false;
    if (board[mx][my] != ' ') return false;

    return true;
}


vector<vector<char>> Solver::simulateJump(int x, int y, int mx, int my, const vector<vector<char>>& board) const
{
    vector<vector<char>> new_board = board;
    new_board[x][y] = ' ';
    new_board[(x + mx) / 2][(y + my) / 2] = ' ';
    new_board[mx][my] = 'W';

    return new_board;
}


int Solver::findMaxJumpsForPiece(int x, int y, vector<vector<char>> current_board, vector<pair<int, int>>& jump_sequence) const 
{
    int max_jumps = 0;

    vector<pair<int, int>> local_jump_sequence;


    vector<pair<int, int>> directions = { {-1, -1}, {-1, 1}, {1, -1}, {1, 1} };


    for (const auto& dir : directions) 
    {
        int dx = dir.first, dy = dir.second;

        if (isValidJump(x, y, dx, dy, current_board)) 
        {
            int mx = x + 2 * dx, my = y + 2 * dy;
            auto new_board = simulateJump(x, y, mx, my, current_board);

            vector<pair<int, int>> new_jump_sequence = jump_sequence;
            new_jump_sequence.push_back({ mx, my });

            int jumps = 1 + findMaxJumpsForPiece(mx, my, new_board, new_jump_sequence);

            if (jumps > max_jumps) {
                max_jumps = jumps;
                local_jump_sequence = new_jump_sequence;
            }
        }
    }

    jump_sequence = local_jump_sequence; // Update the jump sequence for this piece
    return max_jumps;
}