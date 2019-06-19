#include "Score.h"
#include "scoredao.h"

Score::Score(){
    this->setStart(QTime::currentTime());
    this->setBoard("none");
    this->setNbStep(0);
    this->setScore(0);
    this->setUse(false);
    this->sDate = QDate::currentDate().toString().toStdString();
    this->calculDuration();
}

Score::Score(string b){
    this->setStart(QTime::currentTime());
    this->setBoard(b);
    this->setNbStep(0);
    this->setScore(0);
    this->setUse(false);
    this->sDate = QDate::currentDate().toString().toStdString();
    this->calculDuration();
}

Score::Score(int score, string sDate, string board, QTime pTime, bool use, int nbstep, int idUser){
    this->setBoard(board);
    this->setNbStep(nbstep);
    this->score = score;
    this->setUse(use);
    this->sDate = sDate;
    this->setDuration(pTime);
    this->setUser(idUser);
}

void Score::setUser(int id){
    this->idUser = id;
}

void Score::setNbStep(int nb){
    this->nbStep = nb;
}

void Score::setBoard(string b){
    this->associateBoard=b;
}

void Score::setScore(int score){
    this->score += score;
}

void Score::setUse(bool use){
    this->useSolver = use;
}

void Score::calculDuration(){
    QTime end = QTime::currentTime();
    this->setEnd(end);

    int timeInSec = end.secsTo(this->listStartEndDurationTime[0]) * -1;
    int hour = timeInSec / 60 / 60;
    int minute = (timeInSec - hour*60*60)/60;
    int second = (timeInSec - hour*60*60 - minute*60);

    QTime duration;
    duration.setHMS(hour,minute,second);

   this->setDuration(duration);
}

void Score::setStart(QTime start){
    this->listStartEndDurationTime[0] = start;
}

void Score::setEnd(QTime end){
    this->listStartEndDurationTime[1] = end;
}

void Score::setDuration(QTime duration){
    this->listStartEndDurationTime[2] = duration;
}

void Score::addThisScore(){
    ScoreDAO bdd = ScoreDAO(QString::fromStdString("/home/lucas/Documents/Development/C++/learn/sudoku_clean_projet/table.db"));
    bdd.addScore(*this);
}
