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

class FeeRequest
{
public:
    string requestToPrjManager(double fee)
    {
        string strTemp = "";
        if (fee < 500)
        {
            strTemp = prjHandle(fee);
        }
        else if (fee < 1000)
        {
            strTemp = depHandle(fee);
        }
        else if (fee >= 100)
        {
            strTemp = CEOHandle(fee);
        }
        return strTemp;
    }

private:
    string prjHandle(double fee)
    {
        if (fee >= 0 && fee < 500)
        {
            return "项目经理同意" + convertToString(fee) + "金额";
        }
        else
        {
            return "项目经理不同意" + convertToString(fee) + "金额";
        }
    }

    string depHandle(double fee)
    {
        if (fee >= 500 && fee < 1000)
        {
            return "部门经理同意" + convertToString(fee) + "金额";
        }
        else
        {
            return "部门经理不同意" + convertToString(fee) + "金额";
        }
    }

    string CEOHandle(double fee)
    {
        if (fee >= 1000)
        {
            return "CEO同意" + convertToString(fee) + "金额";
        }
        else
        {
            return "CEO不同意" + convertToString(fee) + "金额";
        }
    }
};

int main(int argc, char const *argv[])
{
    FeeRequest *pRequest = new FeeRequest;

    cout << pRequest->requestToPrjManager(300) << endl;
    cout << pRequest->requestToPrjManager(500) << endl;
    cout << pRequest->requestToPrjManager(1200) << endl;

    return 0;
}
