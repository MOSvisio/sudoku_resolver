#ifndef SCORE_H
#define SCORE_H

#include "Board.h"

#include <string>
#include <QDateTime>
#include <QTime>
#include <iostream>

using namespace std;

class Score
{
    public:
        Score();
        Score(string b);
        Score(int score, string sDate, string board, QTime pTime, bool use, int nbstep, int idUser);

        void setScore(int score);
        void setUse(bool use);
        void setBoard(string b);
        void setNbStep(int nb);
        void setStart(QTime start);
        void setEnd(QTime end);
        void setDuration(QTime duration);
        void setUser(int id);

        int getNbStep() const {return this->nbStep;}
        string getBoard() const{return this->associateBoard;}
        QTime getTime() const{return this->listStartEndDurationTime[2];}

        int getScore() const {return this->score;}
        string getDate() const {return this->sDate;}
        bool getUse() const{return this->useSolver;}
        int getUserId() const{return this->idUser;}


        void addThisScore();
        void calculDuration();

    private:
        int score; 
        string sDate;
        string associateBoard;
        QTime listStartEndDurationTime[3];
        bool useSolver;
        int nbStep;
        int idUser;        
};

#endif // USER_H
