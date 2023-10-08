#include <iostream>

using namespace std;

class Duck
{
public:
    virtual void Quack() = 0;
    virtual void Display() = 0;

protected:
private:
};

class DonaladDuck : public Duck
{
public:
    void Quack()
    {
        cout << "我是唐老鸭" << endl;
    }

    void Display()
    {
        Quack();
    }

    void fly(int params)
    {
        cout << "我是唐老鸭，虽然自身不会分，但是我可以坐飞机，坐气球飞" << endl;
    }
};

// 子类与父类不像
class RuberDuck : public Duck
{
public:
    void Quack()
    {
    }

    void Display()
    {
        Quack();
    }
};

class WigeonDuck : public Duck
{

    void Quack()
    {
        cout << "我是小野鸭" << endl;
    }

    void Display()
    {
        Quack();
    }

    void fly()
    {
        cout << "我在天空" << endl;
    }
};