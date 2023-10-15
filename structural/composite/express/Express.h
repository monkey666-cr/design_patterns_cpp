#pragma once

#include <iostream>
#include "ExpressNode.h"

using namespace std;

class Express
{
public:
    Express(int);
    Express(char, const Express);
    Express(char, const Express, const Express);
    Express(const Express &);
    Express &operator=(const Express &);
    friend ostream &operator<<(ostream &os, const Express express)
    {
        os << *(express.p);
        return os;
    }
    int eval() const;

private:
    class ExpressNode *p;
};