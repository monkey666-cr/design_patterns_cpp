#include <string>
#include <iostream>

#include "DynOBJ.h"

using namespace std;

class Api
{
public:
    virtual void test(string s) = 0;

protected:
    Api() {}
};

class ImplOne : public Api
{
public:
    void test(string s)
    {
        cout << "现在是One在执行" << s << endl;
    }
};

class ImplTwo : public Api
{
public:
    void test(string s)
    {
        cout << "现在是Two在执行" << s << endl;
    }
};

REG_CLASS(ImplOne);
REG_CLASS(ImplTwo);

class Factory
{
public:
    static Api *createApi(const string name)
    {
        Api *pApi = nullptr;

        pApi = static_cast<Api *>(CObjectFactory::createObject(name));

        return pApi;
    }
};

int main(int argc, char const *argv[])
{
    Api *pApi = Factory::createApi("ImplTwo");

    pApi->test("RegClass");

    return 0;
}
