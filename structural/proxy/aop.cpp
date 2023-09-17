/**
 * AOP: 面相切面编程, 一些于业务不相关的开发
 */

#include <memory>
#include <string>
#include <iostream>

using namespace std;

class IHello
{

public:
    IHello() {}
    ~IHello() {}

    virtual void Output(const string &s) {}
};

class Hello : public IHello
{
public:
    void Output(const string &s)
    {
        cout << s << endl;
    }
};

class HelloProxy : public IHello
{
public:
    HelloProxy(IHello *ptr) : m_pHello(ptr) {}

    ~HelloProxy()
    {
        delete m_pHello;
        m_pHello = nullptr;
    }

    void Output(const string &s)
    {
        cout << "执行之前\n";
        m_pHello->Output(s);
        cout << "执行之后\n";
    }

private:
    IHello *m_pHello;
};

int main(int argc, char const *argv[])
{
    unique_ptr<IHello> hello = make_unique<HelloProxy>(new Hello());

    hello->Output("chenrun");

    return 0;
}
