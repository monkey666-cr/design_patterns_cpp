#include <iostream>

using namespace std;

class Berverage
{
public:
    virtual double charge() = 0;
};

class RedTea : public Berverage
{
public:
    double charge()
    {
        return 1;
    }
};

class GreenTea : public Berverage
{
public:
    double charge()
    {
        return 8;
    }
};

// 解决类爆炸问题
class HalfGreenHalfRed;