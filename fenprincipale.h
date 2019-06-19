#ifndef FENPRINCIPALE_H
#define FENPRINCIPALE_H

#include<QtWidgets>
#include "Board.h"
#include "User.h"
#include "Score.h"
#include <unistd.h>
#include <QThread>
#include <QtGui>
#include <stdlib.h>
#include <iostream>

class myThread : public QThread
{
    Q_OBJECT

    public:
    explicit myThread(QObject *parent = 0) : QThread(parent){
        setParent(0);
        moveToThread(this);
    }
    void setBoard(Board b){this->thBoard = b;}

    protected: 
    void run();

    signals:
    void updateBoard(Board b);
    void thIsStopped();

    private:
    Board thBoard;
    vector<QLineEdit*> list;
};

class FenPrincipale : public QMainWindow
{

    Q_OBJECT
public:
    FenPrincipale();
    ~FenPrincipale();

    void userCreation();
    void screenBoard(Board &b);

public slots:
    void updateBoard(Board b);
    void thIsStopped();
    void openBoard();
    void verificationBoard();
    void resolveBoard();
    void getPreviousBoard();
    void getNextBoard();
    void reset();

private:
    myThread *th;

    //layout
    QGridLayout *boardLayout;
    QVBoxLayout *btnLayout;
    QHBoxLayout *allLayout;
    QVBoxLayout *gridAndBtn;
    QHBoxLayout *btnBackNext;

    //button
    QPushButton *btn_openFile;
    QPushButton *btn_validate;
    QPushButton *btn_quit;
    QPushButton *btn_correct;
    QPushButton *btn_cancel;
    QPushButton *btn_forward;
    QPushButton *btn_backward;

    //list
    vector<QLineEdit*> listWid;
    vector<Board> listBoardResolve;

    Board Grid;
    Score actualScore;
    User player;
};

#endif // FENPRINCIPALE_H
