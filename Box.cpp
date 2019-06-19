#include "Box.h"

Box::Box(){
    this->possibleValue = vector<int> (0);
    this->wasTested = false;
}

Box::~Box()
{
    //dtor
}

/*
    Add the value from the parameter vector to the possibleVector vector
*/
void Box::addValue(vector<int> &a)
{
    this->possibleValue = a;
    if(this->possibleValue.size() == 1){
        this->definitiveValue = this->possibleValue[0];
        this->possibleValue.clear();
    } else {
        this->definitiveValue = 0;
    }
}

/*
    remove the value that appear in the list vector from the possibleVector
*/
void Box::removeValue(vector<int> const& list)
{
    for(int i=0; i<(int)list.size(); ++i){
        for(int j=0; j<(int)this->possibleValue.size(); ++j){
            if(list[i] == this->possibleValue[j]){
                this->possibleValue.erase(this->possibleValue.begin() + j);
            }
        }
    }   
}

/*
    if the possibleValue vector contain only one value, 
    clear the vector and put this value as the definitive one
    return a boolean
*/
bool Box::removeSingle(){
    if(this->possibleValue.size() == 1 && this->definitiveValue == 0){
        this->definitiveValue = this->possibleValue[0];
        this->possibleValue.clear();
        return true;
    }
    return false;
}

void Box::setDefValue(int const& a){
    if(this->definitiveValue == 0){
        this->definitiveValue = a;
        this->possibleValue.clear();
    }
}

/*
    check if a value appear in the possibleValue vector
    return a boolean
*/
bool Box::existIn(int const& number) const{
    for(int i=0; i<(int)this->possibleValue.size(); ++i){
        if(this->possibleValue[i] == number){
            return true;
        }
    }
    return false;
}

