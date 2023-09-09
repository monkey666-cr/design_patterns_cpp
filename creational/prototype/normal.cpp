/*
** 普通模式
** 场景: 有一家制造业MRP系统里有一个工件包的概念，制造型企业对于工件包中的每一个工件每天都有一个核查的要求。
** 每当工件超过200项的时候，就需要将这个工件包拆成两份，如果还是超过200，继续拆分，直到单个数量不超过200。
** 原因是后续阶段，该企业的生产部门对于工件的设计和进行人工处理，每个人每天处理的工件的上限是200个。起始，这个企业
** 遇到的工件基本类型有国内企业和海外企业，我们把这个工件包需求定义成两种类型
** HomeOrder 和 AboradOrder3
*/

#include <iostream>
#include <string>

class OrderApi
{
public:
    virtual int getOrderProductNum() = 0;
    virtual void serOrderProductNum(int num) = 0;
    virtual std::string getOrderConetnt() = 0;

protected:
    OrderApi() {}
};

class HomeOrder : public OrderApi
{
public:
    int getOrderProductNum()
    {
        return m_orderProductNum;
    }

    void serOrderProductNum(int num)
    {
        m_orderProductNum = num;
    }

    std::string getOrderConetnt()
    {
        return "本次订单的客户是" + m_strCustomerName + "订单的数量是" + std::to_string(m_orderProductNum) + "订单的ID是: " + std::to_string(m_strProductId);
    }

    void setCustomerName(std::string strCustomerName)
    {
        m_strCustomerName = strCustomerName;
    }

    std::string getCustomerName()
    {
        return m_strCustomerName;
    }

    void setProductId(int strProductId)
    {
        m_strProductId = strProductId;
    }

    int getProductId()
    {
        return m_strProductId;
    }

private:
    std::string m_strCustomerName;
    int m_strProductId;
    int m_orderProductNum;
};

class OrderBusiness
{
private:
    /* data */
public:
    OrderBusiness(/* args */);
    ~OrderBusiness();

    void saveOrder(OrderApi *pOrder);
};

OrderBusiness::OrderBusiness(/* args */)
{
}

OrderBusiness::~OrderBusiness()
{
}

void OrderBusiness::saveOrder(OrderApi *pOrder)
{
    while (pOrder->getOrderProductNum() > 200)
    {
        OrderApi *pNewOrder = nullptr;
        if (dynamic_cast<HomeOrder *>(pOrder) != nullptr)
        {
            // 创建一个新的对象, 去暂存我们的目标
            HomeOrder *p2 = new HomeOrder();
            HomeOrder *p1 = static_cast<HomeOrder *>(pOrder);
            p2->setCustomerName(p1->getCustomerName());
            p2->setProductId(p1->getProductId());
            p2->serOrderProductNum(200);

            pNewOrder = p2;
        }

        pOrder->serOrderProductNum(pOrder->getOrderProductNum() - 200);
        std::cout << "新订单是" << pNewOrder->getOrderConetnt() << std::endl;
    }

    std::cout << "最终订单是" << pOrder->getOrderConetnt() << std::endl;
}

int main(int argc, char const *argv[])
{

    HomeOrder *pHome = new HomeOrder();
    pHome->setCustomerName("test01");
    pHome->setProductId(111);
    pHome->serOrderProductNum(512);

    OrderBusiness *pOb = new OrderBusiness();
    pOb->saveOrder(pHome);

    delete pOb;
    delete pHome;

    return 0;
}
