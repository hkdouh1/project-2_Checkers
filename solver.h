#ifndef SOLVER_H
#define SOLVER_H

#include <vector>

class Solver 
{
public:
   
    Solver(const std::vector<std::vector<char>>& input_board);

    int getMaxJumps();

private:
    std::vector<std::vector<char>> board;

    void printBoard(const std::vector<std::vector<char>>& board) const;

    bool isValidJump(int x, int y, int dx, int dy, const std::vector<std::vector<char>>& board) const;

    std::vector<std::vector<char>> simulateJump(int x, int y, int mx, int my, const std::vector<std::vector<char>>& board) const;

    // Recursive function to find max jumps for a single piece and track the jump sequence
    int findMaxJumpsForPiece(int x, int y, std::vector<std::vector<char>> current_board, std::vector<std::pair<int, int>>& jump_sequence) const;
};

#endif // SOLVER_H