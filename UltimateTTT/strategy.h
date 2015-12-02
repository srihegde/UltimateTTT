#ifndef STRATEGY_H
#define STRATEGY_H

#include "scoretracker.h"

class Strategy
{
private:
    ScoreTracker *scorer;
    double duration;

protected:
    // All algorithms implementations will return grid coordinates (i,j) in the form of (i*9 + j)
    int minimax(int grid[9][9], int frameno, int turn, int depth, int validFrame[]);
    int alphaBeta(int grid[9][9], int frameno, int turn, int depth, int validFrame[], int alpha, int beta);
    int monteCarlo(int grid[9][9]);
    bool isFilled(int grid[9][9], int n);
    int calcUtil(int grid[9][9], int frame, int turn);

public:
    Strategy();

    int aiMove(int grid[9][9], int frameno, int validFrame[9]);
    double getDuration();
};

#endif // STRATEGY_H
