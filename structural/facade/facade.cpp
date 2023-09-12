#include <iostream>

class Carmera
{
public:
    void trunOn()
    {
        std::cout << "相机启动" << std::endl;
    }

    void trunOff()
    {
        std::cout << "相机关闭" << std::endl;
    }
};

class Light
{
public:
    void turnOn()
    {
        std::cout << "照明灯开启" << std::endl;
    }

    void turnOff()
    {
        std::cout << "照明等关闭" << std::endl;
    }
};

class Sensor
{
public:
    void active()
    {
        std::cout << "传感器启动" << std::endl;
    }

    void deactivate()
    {
        std::cout << "传感器关闭" << std::endl;
    }
};

class Alarm
{
public:
    void activate()
    {
        std::cout << "报警启动" << std::endl;
    }

    void deactivate()
    {
        std::cout << "报警关闭" << std::endl;
    }
};

class SecurityFacade
{
private:
    Carmera *m_pCarmera;
    Light *m_pLight;
    Sensor *m_pSensor;
    Alarm *m_pAlarm;

public:
    SecurityFacade()
    {
        m_pCarmera = new Carmera();
        m_pLight = new Light();
        m_pSensor = new Sensor();
        m_pAlarm = new Alarm();
    }

    void activate()
    {
        m_pCarmera->trunOn();
        m_pLight->turnOn();
        m_pSensor->active();
        m_pAlarm->activate();
    }

    void deactivate()
    {
        m_pCarmera->trunOff();
        m_pLight->turnOff();
        m_pSensor->deactivate();
        m_pAlarm->deactivate();
    }
};

int main(int argc, char const *argv[])
{
    SecurityFacade *pSecurityFacade = new SecurityFacade();

    std::cout << "启动系统" << std::endl;
    pSecurityFacade->activate();

    std::cout << "关闭系统" << std::endl;
    pSecurityFacade->deactivate();

    return 0;
}
