#ifndef BOX_H
#define BOX_H

#include <iostream>
#include <vector>

using namespace std;

class Box
{
    public:
        Box();
        virtual ~Box();

        void addValue(vector<int> &a);
        void setDefValue(int const& a);
        void removeValue(vector<int> const& list);
        bool removeSingle();

        vector<int> getValues() const{return this->possibleValue;};
        int getDefValue() const{return this->definitiveValue;};
        bool getWasTested() const{return this->wasTested;};
        void setWasTested(bool val){this->wasTested = val;};
        
        bool existIn(int const& number) const;

    private:
        vector<int> possibleValue;
        int definitiveValue;
        bool wasTested; 
};

#endif // BOX_H
