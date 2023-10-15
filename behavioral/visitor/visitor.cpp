#include <iostream>
#include <string>

using namespace std;

// 访问者模式: 核心->双重分发

class Xiaomi;
class Huawei;
class OPPO;

class CellPhoneVisitor
{
public:
    virtual void visit(Xiaomi *p) = 0;
    virtual void visit(Huawei *p) = 0;
    virtual void visit(OPPO *p) = 0;
};

class CellPhone
{
public:
    virtual void dial() = 0;
    virtual void sendMsg() = 0;
    virtual void hang() = 0;
    virtual void recvMsg() = 0;
    virtual void accept(CellPhoneVisitor *p) = 0;

protected:
    CellPhone() {}
};

class Xiaomi : public CellPhone
{
public:
    void dial()
    {
        cout << "小米在拨号" << endl;
    }

    void sendMsg()
    {
        cout << "小米在发短信" << endl;
    }

    void hang()
    {
        cout << "小米在挂断电话" << endl;
    }

    void recvMsg()
    {
        cout << "在收短信" << endl;
    }

    void accept(CellPhoneVisitor *p)
    {
        p->visit(this);
    }
};

class Huawei : public CellPhone
{
public:
    void dial()
    {
        cout << "华为在拨号" << endl;
    }

    void sendMsg()
    {
        cout << "华为在发短信" << endl;
    }

    void hang()
    {
        cout << "华为在挂断电话" << endl;
    }

    void recvMsg()
    {
        cout << "在收短信" << endl;
    }

    void accept(CellPhoneVisitor *p)
    {
        p->visit(this);
    }
};

class OPPO : public CellPhone
{
public:
    void dial()
    {
        cout << "OPPO在拨号" << endl;
    }

    void sendMsg()
    {
        cout << "OPPO在发短信" << endl;
    }

    void hang()
    {
        cout << "OPPO在挂断电话" << endl;
    }

    void recvMsg()
    {
        cout << "在收短信" << endl;
    }

    void accept(CellPhoneVisitor *p)
    {
        p->visit(this);
    }
};

class SolarisConfigure : public CellPhoneVisitor
{
public:
    void visit(Xiaomi *p)
    {
        p->dial();
        p->hang();
        p->sendMsg();
        p->recvMsg();
    }

    void visit(Huawei *p)
    {
        p->dial();
        p->hang();
        p->sendMsg();
        p->recvMsg();
    }

    void visit(OPPO *p)
    {
        p->dial();
        p->hang();
        p->sendMsg();
        p->recvMsg();
    }
};

int main(int argc, char const *argv[])
{
    CellPhoneVisitor *pVisitor = new SolarisConfigure;

    Xiaomi *pXiaomi = new Xiaomi;
    Huawei *pHuawei = new Huawei;
    OPPO *pOppo = new OPPO;

    pXiaomi->accept(pVisitor);
    pHuawei->accept(pVisitor);
    pOppo->accept(pVisitor);

    return 0;
}
