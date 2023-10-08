#include <iostream>

using namespace std;

class QuackBehavior
{
public:
    virtual void quack() = 0;

protected:
    QuackBehavior() {}
};

class ZhiZhiQuack : public QuackBehavior
{
public:
    void quack()
    {
        cout << "吱吱" << endl;
    }
};

class PersonQuack : public QuackBehavior
{
public:
    void quack()
    {
        cout << "我是唐老鸭" << endl;
    }
};

class WigeonQuack : public QuackBehavior
{
public:
    void quack()
    {
        cout << "丑小鸭" << endl;
    }
};

class FlyBehavior
{
public:
    virtual void fly() = 0;

protected:
    FlyBehavior() {}
};

class FlyWithRocket : public FlyBehavior
{
public:
    void fly()
    {
        cout << "坐着火箭飞" << endl;
    }
};

class FlyWithWings : public FlyBehavior
{
public:
    void fly()
    {
        cout << "我有翅膀可以自己飞" << endl;
    }
};

class FlyWithNoWay : public FlyBehavior
{
public:
    void fly()
    {
        cout << "我根本不会飞" << endl;
    }
};

class Duck
{
public:
    virtual void Display() = 0;

    void setFlyBehavior(FlyBehavior *fb)
    {
        m_pFly = fb;
    }

    void setQuackBehavior(QuackBehavior *qb)
    {
        m_pQuack = qb;
    }

    virtual void perfomrFly()
    {
        m_pFly->fly();
    }

    virtual void performQuack()
    {
        m_pQuack->quack();
    }

protected:
    QuackBehavior *m_pQuack;
    FlyBehavior *m_pFly;

private:
};

class DonaladDuck : public Duck
{
public:
    DonaladDuck()
    {
        m_pFly = new FlyWithRocket;
        m_pQuack = new PersonQuack;
    }

    void Display()
    {
        perfomrFly();
        performQuack();
    }
};

class RuberDuck : public Duck
{
public:
    RuberDuck()
    {
        m_pFly = new FlyWithNoWay;
        m_pQuack = new ZhiZhiQuack;
    }

    void Display()
    {
        perfomrFly();
        performQuack();
    }
};

class WigeonDuck : public Duck
{
public:
    WigeonDuck()
    {
        m_pFly = new FlyWithWings;
        m_pQuack = new WigeonQuack;
    }

    void Display()
    {
        perfomrFly();
        performQuack();
    }
};

int main(int argc, char const *argv[])
{
    Duck *pDuck = new RuberDuck;

    pDuck->Display();

    return 0;
}
