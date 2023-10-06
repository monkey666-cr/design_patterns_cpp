#include <iostream>

using namespace std;

class IOS
{
public:
    IOS() {}
    virtual ~IOS() {}
    virtual void run() = 0;
};

class CWindows : public IOS
{
public:
    void run()
    {
        cout << "Windows 正在运行" << endl;
    }
};

class CLinux : public IOS
{
public:
    void run()
    {
        cout << "Linux 正在运行" << endl;
    }
};

class IComputer
{

public:
    virtual void Install(IOS *pIOS) = 0;
};

class CLenvo : public IComputer
{
public:
    void Install(IOS *pIOS)
    {
        cout << "联想电脑正在安装" << endl;
        pIOS->run();
    }
};

class CDell : public IComputer
{
public:
    void Install(IOS *pIOS)
    {
        cout << "戴尔电脑正在安装" << endl;
        pIOS->run();
    }
};

int main(int argc, char const *argv[])
{
    IOS *pWindows = new CWindows;
    IOS *pLinux = new CLinux;

    IComputer *pLenvo = new CLenvo;
    IComputer *pDell = new CDell;

    pLenvo->Install(pLinux);

    pDell->Install(pWindows);

    return 0;
}
