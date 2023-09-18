#include <sstream>
#include <iostream>

using namespace std;

template <class T>
string MyConvertToStr(T obj)
{
    stringstream ss;
    ss << obj;
    return ss.str();
}

class Beverage
{
public:
    virtual string getDescription() = 0;
    virtual double cost() = 0;

protected:
    string m_Description;
};

class CondimentDecorate : public Beverage
{
public:
    virtual string getDescription() = 0;

protected:
    CondimentDecorate() {}
};

class Soy : public CondimentDecorate
{
public:
    Soy(Beverage *pBeverage) : m_pBeverage(pBeverage) {}

    string getDescription()
    {
        return m_pBeverage->getDescription() + "加了酱油";
    }

    double cost()
    {
        return 0.1 + m_pBeverage->cost();
    }

private:
    // 持有被装饰的对象
    Beverage *m_pBeverage;
};

class Milk : public CondimentDecorate
{
public:
    Milk(Beverage *pBeverage) : m_pBeverage(pBeverage) {}

    string getDescription()
    {
        return m_pBeverage->getDescription() + "加了牛奶";
    }

    double cost()
    {
        return 5 + m_pBeverage->cost();
    }

private:
    Beverage *m_pBeverage;
};

class Lattee : public Beverage
{
public:
    Lattee()
    {
        m_Description = "拿铁";
    }

    string getDescription()
    {
        return m_Description;
    }

    double cost()
    {
        return 14;
    }
};

class Mocha : public Beverage
{
public:
    Mocha()
    {
        m_Description = "摩卡";
    }

    string getDescription()
    {
        return m_Description;
    }

    double cost()
    {
        return 20;
    }
};

int main(int argc, char const *argv[])
{
    Beverage *pBeverage0 = new Lattee();
    cout << pBeverage0->getDescription() << endl;

    Beverage *pBeverage1 = new Mocha();
    pBeverage1 = new Soy(pBeverage1);
    pBeverage1 = new Milk(pBeverage1);
    cout << pBeverage1->getDescription() << ", 售价" << pBeverage1->cost() << endl;

    return 0;
}
