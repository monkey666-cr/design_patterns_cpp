#include <memory>
#include <iostream>

class ThreePhaseOutlet
{
public:
    void doThreePhasePlug()
    {
        std::cout << "三相插头接入" << std::endl;
    }
};

class TwoPhaseOutlet
{
public:
    virtual void doPlug() = 0;
};

// 类适配器
class OutletConverter : public TwoPhaseOutlet, public ThreePhaseOutlet
{
public:
    void doPlug()
    {
        doConvertor();
        doThreePhasePlug();
    }

    void doConvertor()
    {
        std::cout << "正在将三相插头转为两相插头" << std::endl;
    }
};

// 对象适配器
class OutletObjConvertor : public TwoPhaseOutlet
{

public:
    OutletObjConvertor(ThreePhaseOutlet *pOutlet) : m_pOutlet(pOutlet) {}

    void doPlug()
    {
        doConvert();

        m_pOutlet->doThreePhasePlug();
    }

private:
    ThreePhaseOutlet *m_pOutlet;

    void doConvert()
    {
        std::cout << "正在将三相插头转为两相插头" << std::endl;
    }
};

int main(int argc, char const *argv[])
{
    TwoPhaseOutlet *pOutlet = new OutletConverter();

    pOutlet->doPlug();

    OutletObjConvertor *pOutletObj = new OutletObjConvertor(new ThreePhaseOutlet());

    pOutletObj->doPlug();

    return 0;
}
