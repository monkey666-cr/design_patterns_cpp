#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>

using namespace std;

template <typename T>
string convertToString(T value)
{
    stringstream ss;
    ss << setiosflags(ios::fixed) << setprecision(2) << value;
    return ss.str();
}

class Handle
{
public:
    void setSuccessor(Handle *pSuccessor)
    {
        this->m_pHandle = pSuccessor;
    }

    virtual string handleFeeRequest(double fee) = 0;

protected:
    Handle *m_pHandle;
};

class PrjManager : public Handle
{
public:
    string handleFeeRequest(double fee)
    {
        string strTemp = "";
        if (fee < 500)
        {
            strTemp = "项目经理同意" + convertToString(fee) + "金额";
        }
        else
        {
            if (this->m_pHandle != nullptr)
            {
                return m_pHandle->handleFeeRequest(fee);
            }
        }
        return strTemp;
    }
};

class DepManager : public Handle
{
public:
    string handleFeeRequest(double fee)
    {
        string strTemp = "";
        if (fee >= 500 && fee < 1000)
        {
            strTemp = "部门经理同意" + convertToString(fee) + "金额";
        }
        else
        {
            if (this->m_pHandle != nullptr)
            {
                return m_pHandle->handleFeeRequest(fee);
            }
        }
        return strTemp;
    }
};

class CEOManager : public Handle
{
public:
    virtual string handleFeeRequest(double fee)
    {
        string strTemp = "";
        if (fee >= 1000)
        {
            strTemp = "CEO经理同意" + convertToString(fee) + "金额";
        }
        else
        {
            if (this->m_pHandle != nullptr)
            {
                return m_pHandle->handleFeeRequest(fee);
            }
        }
        return strTemp;
    }
};

int main(int argc, char const *argv[])
{
    Handle *pHandle1 = new PrjManager;
    Handle *pHandle2 = new DepManager;
    Handle *pHandle3 = new CEOManager;

    pHandle1->setSuccessor(pHandle2);
    pHandle2->setSuccessor(pHandle3);

    cout << pHandle1->handleFeeRequest(100) << endl;
    cout << pHandle1->handleFeeRequest(600) << endl;
    cout << pHandle1->handleFeeRequest(1000) << endl;

    return 0;
}
