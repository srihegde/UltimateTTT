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
    frameNum = -1;
    memset(grid, 0, sizeof(grid));
    memset(validFrame, 0, sizeof(validFrame));
    strategy = new Strategy();
    scorer = new ScoreTracker();

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

    printf("Scores:\nP1: %d  P2: %d\n", scorer->getScoreP1(), scorer->getScoreP2());
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

bool MainWindow::isFilled(int n)
{
    for (int i = 0; i < 9; ++i) {
        if(grid[n][i] != 1 && grid[n][i] != 2)
            return false;
    }
    return true;
}

void MainWindow::fillBoxes(int n)
{
    int flag = 0, status=-1;

    if(isFilled(frameNum))
        frameNum = -1;

    if(boxes[n/9][n%9]->text() != "O" && boxes[n/9][n%9]->text() != "X" && (frameNum == -1 || (n/9) == frameNum))
    {
        if(turn)
        {
            boxes[n/9][n%9]->setText("X");
            grid[n/9][n%9] = 2;
            if(!validFrame[n/9])
                status = scorer->updateScoreP1(grid[n/9]);
            if(status == 1)
                validFrame[n/9] = 1;
        }
        else
        {
            boxes[n/9][n%9]->setText("O");
            grid[n/9][n%9] = 1;
            if(!validFrame[n/9])
                status = scorer->updateScoreP2(grid[n/9]);
            if(status == 1)
                validFrame[n/9] = 2;
        }

        turn = (turn + 1)%2;
        frameNum = n%9;

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

    for (int i = 0; i < 9; ++i)
        if(!isFilled(i))
        {
            flag = 1;
            break;
        }

    int win = scorer->checkWin(validFrame);
    if(win == 1)
    {
        flag = 1;
        printf("Player 1 Won the game !!!\n");
        printf("Scores:\nP1: %d  P2: %d\n", scorer->getScoreP1(), scorer->getScoreP2());
        on_actionNew_Game_triggered();
    }
    else if(win == 2)
    {
        flag = 1;
        printf("Player 2 Won the game !!!\n");
        printf("Scores:\nP1: %d  P2: %d\n", scorer->getScoreP1(), scorer->getScoreP2());
        on_actionNew_Game_triggered();
    }

    if(!flag)
    {
        printf("Game Drawn...\n");
        printf("Scores:\nP1: %d  P2: %d\n", scorer->getScoreP1(), scorer->getScoreP2());
        on_actionNew_Game_triggered();
    }
}

void MainWindow::on_actionNew_Game_triggered()
{
    turn = 0;
    frameNum = -1;
    scorer->refresh();
    memset(grid, 0, sizeof(grid));

    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 9; ++j)
            boxes[i][j]->setText("");
}
