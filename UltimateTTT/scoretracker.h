#ifndef SCORETRACKER_H
#define SCORETRACKER_H


class ScoreTracker
{
private:
    int scoreP1, scoreP2;
    bool validateScore(int frame[]);

public:
    ScoreTracker();
    int updateScoreP1(int frame[]);
    int updateScoreP2(int frame[]);
    int checkWin(int frame[]);
    int getScoreP1();
    int getScoreP2();
    void refresh();
};

#endif // SCORETRACKER_H
