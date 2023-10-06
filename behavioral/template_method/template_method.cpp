#include <iostream>

using namespace std;

class MakeOrder
{
public:
    virtual void startOrder() = 0;
    virtual void replyStart() = 0;
    virtual void finishOrder() = 0;
    virtual void replyFinish() = 0;

    // 模板方法
    void make()
    {
        startOrder();
        replyStart();
        finishOrder();
        replyFinish();
    }

protected:
    MakeOrder() {}
};

class Fanuc : public MakeOrder
{
public:
    void startOrder()
    {
        cout << "Fanuc 开始接受订单" << endl;
    }

    void replyStart()
    {
        cout << "Fanuc 做好预备, 请将后继订单进入排队" << endl;
    }

    void finishOrder()
    {
        cout << "本次订单已经完成, 请推进下一个订单进入生产" << endl;
    }

    void replyFinish()
    {
        cout << "Fanuc订单信号已经送达, 即将推进下个订单进入生产" << endl;
    }
};

class Sims : public MakeOrder
{
public:
    void startOrder()
    {
        cout << "Sims 开始接受订单" << endl;
    }

    void replyStart()
    {
        cout << "Sims 做好预备, 请将后继订单进入排队" << endl;
    }

    void finishOrder()
    {
        cout << "本次订单已经完成, 请推进下一个订单进入生产" << endl;
    }

    void replyFinish()
    {
        cout << "Sims订单信号已经送达, 即将推进下个订单进入生产" << endl;
    }
};

int main(int argc, char const *argv[])
{
    MakeOrder *pMakeOrder = new Fanuc;
    pMakeOrder->make();

    delete pMakeOrder;

    pMakeOrder = new Sims;
    pMakeOrder->make();

    delete pMakeOrder;

    return 0;
}
