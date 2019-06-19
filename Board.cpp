#include "Board.h"

Board::Board()
{}

/*
    this is the constructor for Board
    he read the .txt file who contain a board 
    he get all the value and put on the possibleValue of each case the values from 1 to 9
*/
Board::Board(char * &a)
{
    ifstream flux(a);
    if(flux){
        int i(0), j(0);
        vector<int> tmpV(0);
        string line, tmp;
        while(getline(flux, line)){ // read all the file, line per line
            tmp = "";
            // erase the space between values
            for(i=0; i<(int)line.size(); i++){
                if(line[i] != ' '){
                    tmp += line[i];
                }
            }
            line = tmp;
            // find the playables values for each case
            for(i=0; i<(int)line.size(); ++i){
                if(line[i] - 48 != 0){
                    tmpV.push_back(line[i] - 48);
                    this->playableBox[j][i].addValue(tmpV);
                }
                else{
                    for(int k = 0; k<9; ++k){
                        tmpV.push_back(k+1);
                    }
                    this->playableBox[j][i].addValue(tmpV);
                }
                tmpV.clear();
            }
            j++;
        }
    }
}

Board::~Board()
{
    //dtor
}


/*
    check out if the board is valid and can be use by the program
    A programm is valid only if there is only one time the same value in a Row, a column or a region
    Call the countValue programm who check for each region, if there is only one same number
*/
bool Board::isValid() const
{
    for(int i=0; i<9; ++i){
        for(int j=0; j<9; ++j)
        {
            if(!(countValue(this->verifH(j)) && countValue(this->verifV(i)) && countValue(this->verifT(i,j)) && this->playableBox[i][j].getDefValue() <= 9 && this->playableBox[i][j].getDefValue() >= 0))
            {
                return false;
            }

        }
    }
    return true;
}

/*
    check out if the board is solved
    the board is solved only when all the box are full, and the board is valid
*/
bool Board::isSolved() const
{
    if(this->isValid()){
        for(int i=0; i<9; ++i){
            for(int j=0; j<9; ++j)
            {
                if(this->playableBox[i][j].getDefValue() == 0)
                {
                    return false;
                }

            }
        }
        return true;
    } 
    else 
    {
        return false;
    }
}

bool operator==(Board const& a, Board const& b)
{
    return a.isEqual(b);
}

bool operator!=(Board const& a, Board const& b)
{
    return !(a==b);
}

ostream &operator<<(ostream &flux, Board const& b)
{
    b.print(flux);
    return flux;
}

void Board::print(ostream &flux) const
{

    for(int i=0; i<9; ++i){
        for(int j=0; j<9; ++j){
            cout << "[";
            for(int k =0; k<(int)this->playableBox[i][j].getValues().size(); ++k){
                cout << this->playableBox[i][j].getValues()[k];
            }
            cout << "] ";
        }
        cout  << endl;
    }

    for(int i=0; i<9; ++i){
        flux << endl;
        for(int j=0; j<9 ; ++j){
            flux << this->playableBox[i][j].getDefValue() << " ";
        }
    }
}

bool Board::isEqual(Board const& b) const
{
    for(int i = 0; i<9; ++i){
        for(int j=0; j<9; ++j){
            if(playableBox[i][j].getDefValue() != b.playableBox[i][j].getDefValue()){
                return false;
            }
            if(playableBox[i][j].getValues() != b.playableBox[i][j].getValues()){
                return false;
            }
        }
    }
    return true;
}


/*
    call all the verif functions
    look all the possible value for each boxes, and remove the values in the possibleValues of a box who are already put
*/
void Board::boardVerification(){
    for(int i=0; i<9; ++i){
        for(int j=0; j<9; ++j){
            this->playableBox[i][j].removeValue(this->verifV(i));
            this->playableBox[i][j].removeValue(this->verifH(j));
            this->playableBox[i][j].removeValue(this->verifT(i,j));
        }
    }
}

/*
    return a vector of integer
    return all the vertical impossibles value
    this function return a vector with all the value that appear in a column 
*/
vector<int> Board::verifV(int const& i) const 
{
    vector<int> tmp(0);
    for(int j=0; j<9; ++j){
        if(this->playableBox[i][j].getDefValue() != 0){
            tmp.push_back(this->playableBox[i][j].getDefValue());
        }
    }
    return tmp;
}

/*
    return a vector of integer
    return all the Horizontal impossibles value
    this function return a vector with all the value that appear in a row
*/
vector<int> Board::verifH(int const& j) const 
{
    vector<int> tmp(0);
    for(int i=0; i<9; ++i){
        if(this->playableBox[i][j].getDefValue() != 0){
            tmp.push_back(this->playableBox[i][j].getDefValue());
        }
    }
    return tmp;
}

/*
    return a vector of integer
    return all the impossible value from a region
    this function return a vector with all the value that appear in a region 
*/
vector<int> Board::verifT(int const& i, int const& j) const 
{
    int valI(0), valJ(0);
    vector<int> tmp(0);
    if(i <=2 && i>=0){
        valI = 0;
    }
    else if(i<=5 && i>=3){
        valI = 3;
    }
    else if(i<=8 && i>=6){
        valI = 6;
    }

    if(j <=2 && j>=0){
        valJ = 0;
    }
    else if(j<=5 && j>=3){
        valJ = 3;
    }
    else if(j<=8 && j>=6){
        valJ = 6;
    }
    int iMax = valI+2;
    int jMax = valJ+2;
    for(int i=valI; i<=iMax; ++i){
        for(int j = valJ;j<=jMax;++j){
            if(this->playableBox[i][j].getDefValue() != 0){
                tmp.push_back(this->playableBox[i][j].getDefValue());
            }
        }
    }
    return tmp;
}

/*
    return a list of integer
    with the two values of a box with only 2 value
    will be use for the randomDraw function
*/
int *Board::findBoxWithTwoValue(){
    static int coord[2];
    for(int i(0); i<9; ++i){
        for(int j(0); j<9; ++j){
            if(this->playableBox[i][j].getValues().size() == 2 && this->playableBox[i][j].getWasTested() == false){
                coord[0] = i;
                coord[1] = j;
                this->playableBox[i][j].setWasTested(true);
                return coord;
            }
        }
    }
    coord[0] = -1;
    coord[1] = -1;
    return coord;
}

/*
    not definitive will be delete
    if the board can't be solved by the other strategie we try the 2 value of a box
*/
void Board::randomDraw(){
    Board base = *this;
    int i(0);
    int* tmp = base.findBoxWithTwoValue();
    Board retour = base;
    if(!(tmp[0] == -1 && tmp[1] == -1)){
        vector<int> possibleValue = base.playableBox[tmp[0]][tmp[1]].getValues();
        while((!base.isSolved()) && i<2){
            base = retour;
            base.playableBox[tmp[0]][tmp[1]].setDefValue(possibleValue[i]);
            base.boardVerification();
            Board test;
            do{
                test = base;
                base.step();
                //cout << base << endl;
            }while(test != base && !this->isBlocked());
            i++;
        }
        if(base.isSolved()){
            *this = base;
        }
    }
}

/*
    take a unit and watch the frequencie of a number, if a number appear only one time in a region, we can put this number in the definitive value of the right box
*/
int Board::uniqueNumberStrategie(){

    vector<int> temp(0), once(0);
    this->boardVerification();
    for(int i(0); i<9; ++i){
        // get all the vertical values already assign 
        temp.clear();
        //this->boardVerification();
        for(int j=0; j<9; ++j){
            for(int k=0; k<(int)this->playableBox[i][j].getValues().size(); ++k){
                temp.push_back(this->playableBox[i][j].getValues()[k]);
            }
        }
        // get the number that appear only one time
        once = appearOnceInList(temp);

        for(int j=0; j<9; ++j){
            for(int k=0; k<(int)once.size(); ++k){
                if(this->playableBox[i][j].existIn(once[k])){
                    this->playableBox[i][j].setDefValue(once[k]);
                    once.erase(once.begin() + k);
                    this->boardVerification();
                    return 1;
                }
            }
        }
    }
    this->boardVerification();
    for(int j(0); j<9; ++j){
        temp.clear();
        //this->boardVerification();
        for(int i=0; i<9; ++i){
            for(int k=0; k<(int)this->playableBox[i][j].getValues().size(); ++k){
                temp.push_back(this->playableBox[i][j].getValues()[k]);
            }
        }
        // get the number that appear only one time
        once = appearOnceInList(temp);

        // we set the value in the box were it belong
        for(int i=0; i<9; ++i){
            for(int k=0; k<(int)once.size(); ++k){
                if(this->playableBox[i][j].existIn(once[k])){
                    this->playableBox[i][j].setDefValue(once[k]);
                    once.erase(once.begin() + k);
                    this->boardVerification();
                    return 1;
                }
            }
        }
    }
    this->boardVerification();
    for(int l(0); l<9; l+=3){
        for(int m(0); m<9; m+=3){
            temp.clear();
            for(int i=l; i<=l+2; ++i){
                for(int j = m;j<=m+2;++j){
                    for(int k=0; k<(int)this->playableBox[i][j].getValues().size(); ++k){
                        temp.push_back(this->playableBox[i][j].getValues()[k]);
                    }
                }
            }

            once = appearOnceInList(temp);

            for(int i=l; i<=l+2; ++i){
                for(int j = m;j<=m+2;++j){
                    for(int k=0; k<(int)once.size(); ++k){
                        if(this->playableBox[i][j].existIn(once[k])){
                            this->playableBox[i][j].setDefValue(once[k]);
                            once.erase(once.begin() + k);
                            this->boardVerification();
                            return 1;
                        }
                    }
                }
            }
        }
    }
    this->uniqueNumberInBox();
    return 0;
}

/*
    if in a unit 2 boxs have the same two number we can delete this two number in all the others boxs
*/
void Board::exclusivePairStrategie(){
    vector<int> tmp(0), dble(0);
    
    //this->boardVerification();
    for(int i=0; i<9; i+=3){
        for(int j=0 ; j<9; j+=3){
            tmp.clear();
            for(int l=i; l<=i+2; ++l){
                for(int m=j;m<=j+2;++m){
                    if(this->playableBox[l][m].getValues().size() == 2){
                        for(int k=0; k<(int)this->playableBox[l][m].getValues().size(); ++k){
                            tmp.push_back(this->playableBox[l][m].getValues()[k]);
                        }
                    }
                }
            }
            dble.clear();

            // we get the values that appear two time 
            for(int k=0; k<(int)tmp.size(); k+=2){
                for(int l=k+2; l<(int)tmp.size(); l+=2){
                    if(tmp[k] == tmp[l] && tmp[k+1] == tmp[l+1]){
                        dble.push_back(tmp[k]);
                        dble.push_back(tmp[k+1]);
                    }
                }
            }

            //if there is only one case of double value
            if(dble.size() == 2){
                for(int l=i; l<=i+2; ++l){
                    for(int m=j;m<=j+2;++m){
                        if(this->playableBox[l][m].getValues().size() > 2){
                            this->playableBox[l][m].removeValue(dble);
                            this->uniqueNumberInBox();
                        }
                    }
                }
            }
        }
    }
    this->uniqueNumberInBox();
}

/*
    when there is only one possible value in a box, this number will be the definitive one
*/
int Board::uniqueNumberInBox(){
    
    for(int i(0); i<9; ++i){
        for(int j(0); j<9; ++j){
            if(this->playableBox[i][j].removeSingle() == true){
                this->boardVerification();
                return 1;
            }
        }
    }
    this->boardVerification();
    return 0;
}

/*

    remove the duplicate value that appear in the vector put in parameter
*/
void removeDouble(vector<int> &list){
    for(int i(0); i<(int)list.size(); ++i){
        for(int j(0); j<(int)list.size(); ++j){
            if(list[i] == list[j] && i!=j){
                list.erase(list.begin() + j);
            }
        }
    }
}

/*
    remove the value of the vector toModified that appear in the vector toDel
*/
void removeValueInVector(vector<int> &toModified, vector<int> const& toDel){
    for(int i=0; i<(int)toDel.size(); ++i){
        for(int j=0; j<(int)toModified.size(); ++j){
            if(toDel[i] == toModified[j]){
                toModified.erase(toModified.begin() + j);
            }
        }
    }  
}

/*
    Check if the vector contain two time the same value
*/
bool countValue(vector<int> list)
{
    int count(0);
    for(int i=0; i<(int)list.size(); ++i){
        count = 0;
        for(int j=0+i; j<(int)list.size(); ++j){
            if(list[i] == list[j]){
                count++;
            }
            if(count > 1){
                return false;
            }
        }
    }
    return true;
}

/*
    each step checkout if he can directly put the right numbers, if not he find he number that appear once in a group, else he choose one value int the duplicates
*/
void Board::step()
{
    Board tmp = *this; 
    int count(0);
    count += this->uniqueNumberStrategie();
    if(count == 0){
        count += this->uniqueNumberInBox();
    }
    if(count == 0){
        this->exclusivePairStrategie();
    }

    if(tmp == *this && !this->isSolved()){
        this->randomDraw();
    }
}

/*
    Return a vector who contain the number that appear only one time in the vector in parameter
*/
vector<int> appearOnceInList(vector<int> const& list){
    int count(0);
    vector<int> tmp(0);
    for(int i=0; i<(int)list.size(); ++i){
        count = 0;
        for(int j=0; j<(int)list.size(); ++j){
            if(list[i] == list[j]){
                count++;
            }
        }
        if(count == 1){
            tmp.push_back(list[i]);
        }
    }
    return tmp;
}

bool Board::isBlocked(){
    for(int i(0); i<9; ++i){
        for(int j(0); j<9; ++j){
            if(this->playableBox[i][j].getDefValue() == 0 && this->playableBox[i][j].getValues().size() == 0){
                return true;
            }
        }
    }
    return false;
}
