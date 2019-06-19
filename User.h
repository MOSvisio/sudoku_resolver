#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>
#include <vector>
#include "Score.h"

using namespace std;

class User
{
    public:
        User();
        User(string nom);
        User(int id, string name);

        void setName(string name);
        void setId(int id);

        int getId()const {return this->id;}
        string getName()const {return this->name;}
        vector<Score> getScore(){return this->userScore;}
        void addScore(Score newScore);

        void addThisUser();
        void getUser();
        void getUserScore();

    private:
        int id; 
        string name;
        vector<Score> userScore;


};

bool userExistByName(string name);
#endif // USER_H
