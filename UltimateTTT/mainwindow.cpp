#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cstdio>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initFrames();
    initBoxes();
    turn = 0;
    memset(grid, 0, sizeof(grid));
    strategy = new Strategy();

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            QSignalMapper *signalMapper = new QSignalMapper(this);
            connect(boxes[i][j], SIGNAL(clicked()),signalMapper, SLOT(map()));
            signalMapper -> setMapping(boxes[i][j], (i*9 + j)) ;
            connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(fillBoxes(int)));
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::printGrid()
{
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void MainWindow::initFrames()
{
    QGridLayout *glayout = new QGridLayout;
    for (int i = 0; i < 9; ++i)
    {
        frames[i] = new QFrame;
        glayout->addWidget(frames[i], i/3, i%3);
    }
    ui->centralWidget->setLayout(glayout);
}

void MainWindow::initBoxes()
{
    for (int i = 0; i < 9; ++i) {
        QGridLayout *glayout = new QGridLayout;

        for (int j = 0; j < 9; ++j) {
            boxes[i][j] = new QPushButton;
            glayout->addWidget(boxes[i][j], j/3, j%3);
        }

        frames[i]->setLayout(glayout);
    }
}

void MainWindow::fillBoxes(int n)
{
    if(turn)
    {
        boxes[n/9][n%9]->setText("X");
        grid[n/9][n%9] = 2;
    }
    else
    {
        boxes[n/9][n%9]->setText("O");
        grid[n/9][n%9] = 1;
    }

    turn = (turn + 1)%2;

    // Finding strategy

//    int result = strategy->minimax(grid);
//    int result = strategy->alphaBeta(grid);
//    int result = strategy->monteCarlo(grid);

//    if(turn)
//    {
//        boxes[result/9][result%9]->setText("X");
//        grid[result/9][result%9] = 2;
//    }
//    else
//    {
//        boxes[result/9][result%9]->setText("O");
//        grid[result/9][result%9] = 1;
//    }

//    turn = (turn + 1)%2;

    //For debugging purpose
    printGrid();
}
