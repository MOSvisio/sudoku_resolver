#include"User.h"
#include"Userdao.h"
#include"scoredao.h"
User::User(){
    this->id = 0;
    this->setName("");
    this->userScore.clear();
}

User::User(string nom){
    this->id = 0;
    this->setName(nom);
    this->userScore.clear();
}


User::User(int id, string name){
    this->id = id;
    this->setName(name);
    this->userScore.clear();
}

void User::setName(string name){
    this->name = name;
}

void User::setId(int id){
    this->id = id;
}

void User::addScore(Score newScore){
    if(newScore.getScore())
        this->userScore.push_back(newScore);
    else
        cerr << "the score is not valid" << endl;
}


void User::addThisUser(){
    UserDAO bdd = UserDAO(QString::fromStdString("/home/lucas/Documents/Development/C++/learn/sudoku_clean_projet/table.db"));
    bdd.addUser(*this);
}

bool userExistByName(string name){
    User tmp = User(name);
    UserDAO bdd = UserDAO(QString::fromStdString("/home/lucas/Documents/Development/C++/learn/sudoku_clean_projet/table.db"));

    if(bdd.existIn(tmp)){
        return true;
    } else {
        return false;
    }

}

void User::getUser(){
    UserDAO bdd = UserDAO(QString::fromStdString("/home/lucas/Documents/Development/C++/learn/sudoku_clean_projet/table.db"));
    cout << this->getName();
    string name = this->getName();
    if(bdd.existIn(*this)){
        User tmp = bdd.getByName(name);
        this->setId(tmp.getId());
    } else{
        this->addThisUser();
        bdd = UserDAO(QString::fromStdString("/home/lucas/Documents/Development/C++/learn/sudoku_clean_projet/table.db"));
        User tmp = bdd.getByName(name);
        this->setId(tmp.getId());
    }
}

void User::getUserScore(){
    ScoreDAO bdd = ScoreDAO(QString::fromStdString("/home/lucas/Documents/Development/C++/learn/sudoku_clean_projet/table.db"));
    this->userScore = bdd.getAllById(this->getId());
}
