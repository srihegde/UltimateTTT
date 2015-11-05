#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QFrame>
#include <QGridLayout>
#include <QSignalMapper>
#include "strategy.h"

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
    int turn;
    Strategy *strategy;

protected:
    void initFrames();
    void initBoxes();

public slots:
    void fillBoxes(int n);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void printGrid();
};

#endif // MAINWINDOW_H
