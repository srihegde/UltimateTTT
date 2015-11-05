#ifndef STRATEGY_H
#define STRATEGY_H


class Strategy
{
public:
    Strategy();

    // All algorithms implementations will return grid coordinates (i,j) in the form of (i*9 + j)
    int minimax(int grid[9][9]);
    int alphaBeta(int grid[9][9]);
    int monteCarlo(int grid[9][9]);

};

#endif // STRATEGY_H
