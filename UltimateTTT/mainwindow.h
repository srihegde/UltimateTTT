#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QFrame>
#include <QGridLayout>
#include <QSignalMapper>
#include "strategy.h"
#include "scoretracker.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    QPushButton *boxes[9][9];
    QFrame *frames[9];
    int grid[9][9];
    int validFrame[9];
    int frameNum;     // turn to decide 'X' or 'O' and frameNum for appropriate frame to consider in a turn.
    Strategy *strategy;
    ScoreTracker *scorer;

protected:
    void initFrames();
    void initBoxes();
    bool isFilled(int n);

public slots:
    void fillBoxes(int n);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void printGrid();
private slots:
    void on_actionNew_Game_triggered();
};

#endif // MAINWINDOW_H
