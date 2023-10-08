#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Observer
{

public:
    virtual void update(string, string) = 0;

protected:
    Observer() {}
};

class Subject
{
public:
    virtual void registerObserver(Observer *) = 0;
    virtual void removeObserver(Observer *) = 0;
    virtual void notify() = 0;

protected:
    Subject() {}
};

class PC : public Observer
{

public:
    void update(string Temp, string Humi)
    {
        cout << "PC显示温度: " << Temp << ", 湿度: " << Humi << endl;
    }
};

class Mobile : public Observer
{

public:
    void update(string Temp, string Humi)
    {
        cout << "Mobile显示温度: " << Temp << ", 湿度: " << Humi << endl;
    }
};

class WeatherData : public Subject
{
public:
    WeatherData(string Temp, string Humi) : m_Temp(Temp), m_Humi(Humi)
    {
    }

    void registerObserver(Observer *po)
    {
        m_observers.push_back(po);
    }

    void removeObserver(Observer *po)
    {
        auto iter = find(m_observers.begin(), m_observers.end(), po);

        if (iter != m_observers.end())
        {
            m_observers.erase(iter);
        }
    }

    void notify()
    {
        for (vector<Observer *>::iterator iter = m_observers.begin(); iter != m_observers.end(); iter++)
        {
            (*iter)->update(m_Temp, m_Humi);
        }
    }

private:
    vector<Observer *> m_observers;
    string m_Temp; // 温度
    string m_Humi; // 湿度
};

int main(int argc, char const *argv[])
{
    Subject *pWeatherData = new WeatherData("25度", "50%");

    Observer *pPC = new PC;
    Observer *pMobile = new Mobile;

    pWeatherData->registerObserver(pPC);
    pWeatherData->registerObserver(pMobile);

    pWeatherData->notify();

    pWeatherData->removeObserver(pPC);
    pWeatherData->notify();

    pWeatherData->registerObserver(pPC);
    pWeatherData->notify();

    return 0;
}
