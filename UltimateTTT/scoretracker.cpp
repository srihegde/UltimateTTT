#include "scoretracker.h"

bool ScoreTracker::validateScore(int frame[])
{
    // Check Horizontals
    for (int i = 0; i < 9; i+=3)
        if(frame[i] == frame[i+1] && frame[i] == frame[i+2] && frame[i])
            return true;

    // Check Verticals
    for (int i = 0; i < 3; i++)
        if(frame[i] == frame[i+3] && frame[i] == frame[i+6] && frame[i])
            return true;

    // Check Diagonals
    if(frame[0] == frame[4] && frame[0] == frame[8] && frame[0])
        return true;
    else if(frame[2] == frame[4] && frame[2] == frame[6] && frame[2])
        return true;

    return false;
}

ScoreTracker::ScoreTracker()
{
    scoreP1 = 0;
    scoreP2 = 0;
}

int ScoreTracker::updateScoreP1(int frame[])
{
    if(validateScore(frame))
    {
        scoreP1++;
        return 1;
    }
    return 0;
}

int ScoreTracker::updateScoreP2(int frame[])
{
    if(validateScore(frame))
    {
        scoreP2++;
        return 1;
    }
    return 0;
}

int ScoreTracker::checkWin(int frame[])
{
    // Check Horizontals
    for (int i = 0; i < 9; i+=3)
        if(frame[i] == frame[i+1] && frame[i] == frame[i+2])
        {
            if(frame[i] == 1) return 1;
            else if(frame[i] == 2) return 2;
        }


    // Check Verticals
    for (int i = 0; i < 3; i++)
        if(frame[i] == frame[i+3] && frame[i] == frame[i+6])
        {
            if(frame[i] == 1) return 1;
            else if(frame[i] == 2) return 2;
        }

    // Check Diagonals
    if(frame[0] == frame[4] && frame[0] == frame[8])
    {
        if(frame[0] == 1) return 1;
        else if(frame[0] == 2) return 2;
    }
    else if(frame[2] == frame[4] && frame[2] == frame[6])
    {
        if(frame[2] == 1) return 1;
        else if(frame[2] == 2) return 2;
    }

    return 0;
}

int ScoreTracker::getScoreP1()
{
    return scoreP1;
}

int ScoreTracker::getScoreP2()
{
    return scoreP2;
}

void ScoreTracker::refresh()
{
    scoreP1 = 0;
    scoreP2 = 0;
}

