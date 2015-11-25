#ifndef STRATEGY_H
#define STRATEGY_H

#include "scoretracker.h"

class Strategy
{
private:
    ScoreTracker *scorer;

protected:
    // All algorithms implementations will return grid coordinates (i,j) in the form of (i*9 + j)
    int minimax(int grid[9][9], int frameno, int turn, int depth, int validFrame[]);
    int alphaBeta(int grid[9][9]);
    int monteCarlo(int grid[9][9]);
    bool isFilled(int grid[9][9], int n);

public:
    Strategy();

    int aiMove(int grid[9][9], int frameno, int validFrame[9]);
};

#endif // STRATEGY_H
