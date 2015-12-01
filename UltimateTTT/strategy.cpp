#include "strategy.h"
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

vector< pair<int, int> > rootPosition;

Strategy::Strategy()
{
    scorer = new ScoreTracker();
}

int Strategy::aiMove(int grid[9][9], int frameno, int validFrame[])
{
    int maxs = -10000, index;

    // Solve by Minimax
    minimax(grid, frameno, 1, 0, validFrame);

    // Solve by Minimax with Alpha Beta Pruning
//    alphaBeta(grid, frameno, 1, 0);

    // Solve by Monte Carlo Tree Search
//    monteCarlo(grid, frameno, 1, 0);

    for (int i = 0; i < rootPosition.size(); ++i) {
        if(maxs < rootPosition[i].first)
        {
            maxs = rootPosition[i].first;
            index = i;
        }
    }

    return (9*frameno + rootPosition[index].second);
}

bool Strategy::isFilled(int grid[9][9], int n)
{
    for (int i = 0; i < 9; ++i) {
        if(grid[n][i] != 1 && grid[n][i] != 2)
            return false;
    }
    return true;
}

int Strategy::minimax(int grid[9][9], int frameno, int turn, int depth, int validFrame[9])
{
    int win = scorer->checkWin(validFrame);
    if(win == 2) return 1;
    else if(win == 1) return -1;
    else
    {
        int flag = 0;
        for (int i = 0; i < 9; ++i)
            if(!isFilled(grid, i))
                flag = 1;
        if(!flag)
            return 0;
    }

    vector<int> scores;
    int status;

    if (frameno != -1)
    {
        for (int i = 0; i < 9; ++i) {
            if(!grid[frameno][i])
            {
                if(turn)
                {
                    grid[frameno][i] = 1;

                    if(!validFrame[frameno])
                        status = scorer->updateScoreP1(grid[frameno]);
                    if(status == 1)
                        validFrame[frameno] = 1;
                    if(isFilled(grid, frameno) && !validFrame[frameno])
                        validFrame[frameno] = -1;

                    // Check validity of frameno here.
                    int tmpScore;
                    if(isFilled(grid, i))
                         tmpScore= minimax(grid, -1, 0, depth+1, validFrame);
                    else
                        tmpScore= minimax(grid, i, 0, depth+1, validFrame);

                    scores.push_back(tmpScore);

                    if(!depth)
                    {
                        pair<int, int> tmp(tmpScore, i);
                        rootPosition.push_back(tmp);
                    }
                }
                else if(!turn)
                {
                    grid[frameno][i] = 2;

                    if(!validFrame[frameno])
                        status = scorer->updateScoreP2(grid[frameno]);
                    if(status == 1)
                        validFrame[frameno] = 2;
                    if(isFilled(grid, frameno) && !validFrame[frameno])
                        validFrame[frameno] = -1;

                    // Check validity of frameno here.
                    int tmpScore;
                    if(isFilled(grid, i))
                         tmpScore= minimax(grid, -1, 1, depth+1, validFrame);
                    else
                        tmpScore= minimax(grid, i, 1, depth+1, validFrame);

                    scores.push_back(tmpScore);
                }
                grid[frameno][i] = 0;
            }
        }
    }

    else
    {
        for (int j = 0; j < 9; ++j) {
            for (int i = 0; i < 9; ++i) {
                if(!grid[j][i])
                {
                    if(turn)
                    {
                        grid[j][i] = 1;

                        if(!validFrame[j])
                            status = scorer->updateScoreP1(grid[j]);
                        if(status == 1)
                            validFrame[j] = 1;
                        if(isFilled(grid, j) && !validFrame[j])
                            validFrame[j] = -1;

                        // Check validity of frameno here.
                        int tmpScore;
                        if(isFilled(grid, i))
                             tmpScore= minimax(grid, -1, 0, depth+1, validFrame);
                        else
                            tmpScore= minimax(grid, i, 0, depth+1, validFrame);

                        scores.push_back(tmpScore);

                        if(!depth)
                        {
                            pair<int, int> tmp(tmpScore, i);
                            rootPosition.push_back(tmp);
                        }
                    }
                    else if(!turn)
                    {
                        grid[j][i] = 2;

                        if(!validFrame[j])
                            status = scorer->updateScoreP2(grid[j]);
                        if(status == 1)
                            validFrame[j] = 2;
                        if(isFilled(grid, j) && !validFrame[j])
                            validFrame[j] = -1;

                        // Check validity of frameno here.
                        int tmpScore;
                        if(isFilled(grid, i))
                             tmpScore= minimax(grid, -1, 1, depth+1, validFrame);
                        else
                            tmpScore= minimax(grid, i, 1, depth+1, validFrame);

                        scores.push_back(tmpScore);
                    }
                    grid[j][i] = 0;
                }
            }
        }
    }

    if(turn)
        return *max_element(scores.begin(), scores.end());
    else
        return *min_element(scores.begin(), scores.end());
}

int Strategy::alphaBeta(int grid[9][9])
{
    return 0;
}

int Strategy::monteCarlo(int grid[9][9])
{
    return 0;
}


