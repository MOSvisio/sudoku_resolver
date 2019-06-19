#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <fstream>

#include "Box.h"

using namespace std;

class Board
{
    public:

        Board();
        Board(char * &a);
        virtual ~Board();

        Box getBox(int const& i, int const& j) const {return playableBox[i][j];}
        void setDefinitiveValue(int const& i, int const& j, int const& val){this->playableBox[i][j].setDefValue(val);}

        vector<int> verifV(int const& i) const;
        vector<int> verifH(int const& j) const;
        vector<int> verifT(int const& i, int const& j) const;
     
        // All the strategies
        void boardVerification();
        int uniqueNumberStrategie();
        void exclusivePairStrategie();
        int uniqueNumberInBox();

        // last resort strategie for Diabolico sudoku
        void randomDraw();
        int* findBoxWithTwoValue(); // need a better algorithm, to find the case that can modified the biggest number of value

        bool isValid() const;
        bool isSolved() const;
        void step();
        bool isBlocked();

        bool isEqual(Board const& b) const;
        void print(ostream &flux) const;

    private:
        Box playableBox[9][9];

};

bool operator==(Board const& a, Board const& b);
bool operator!=(Board const& a, Board const& b);
ostream &operator<<(ostream &flux, Board const& b);

void removeDouble(vector<int> &list);
void removeValueInVector(vector<int> &toModified, vector<int> const& toDel);
bool countValue(vector<int> list);
vector<int> appearOnceInList(vector<int> const& list);

#endif // BOARD_H
