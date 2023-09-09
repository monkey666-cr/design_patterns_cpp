#include <iostream>
#include <string>

class OrderApi
{
public:
    virtual int getOrderProductNum() = 0;
    virtual void serOrderProductNum(int num) = 0;
    virtual std::string getOrderConetnt() = 0;
    virtual OrderApi *cloneOrder() = 0;

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

    HomeOrder *cloneOrder();

private:
    std::string m_strCustomerName;
    int m_strProductId;
    int m_orderProductNum;
};

HomeOrder *HomeOrder::cloneOrder()
{
    HomeOrder *pHomeOrder = new HomeOrder();
    pHomeOrder->setCustomerName(m_strCustomerName);
    pHomeOrder->setProductId(m_strProductId);
    pHomeOrder->serOrderProductNum(m_orderProductNum);

    return pHomeOrder;
}

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
        OrderApi *pNewOrder = pOrder->cloneOrder();

        pNewOrder->serOrderProductNum(200);

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
