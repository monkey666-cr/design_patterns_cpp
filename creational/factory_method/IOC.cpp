#include <string>
#include <map>
#include <memory>
#include <functional>
#include <iostream>

template <class T>
class IocContainer
{
public:
    IocContainer(){};
    ~IocContainer(){};

    // 注册需要创建对象的构造函数, 通过一个唯一的标识, 以便以后查找
    template <class Drived>
    void RegisterType(std::string key)
    {
        std::function<T *()> function = []
        { return new Drived(); };
        RegisterType(key, function);
    };

    // 根据唯一的标识去查找对应的构造函数
    T *Resolve(std::string key)
    {
        if (m_createMap.find(key) == m_createMap.end())
        {
            return nullptr;
        }
        std::function<T *()> function = m_createMap[key];

        return function();
    }

    std::shared_ptr<T> ResolveShared(std::string key)
    {
        T *ptr = Resolve(key);
        return std::shared_ptr<T>(ptr);
    }

private:
    void RegisterType(std::string key, std::function<T *()> creator)
    {
        if (m_createMap.find(key) != m_createMap.end())
        {
            throw std::invalid_argument("已经存在这个key");
        }
        m_createMap.emplace(key, creator);
    }

private:
    std::map<std::string, std::function<T *()>> m_createMap;
};

struct ICar
{
    virtual ~ICar() {}
    virtual void test() const = 0;
};

struct Bus : ICar
{
    Bus() {}
    void test() const { std::cout << "BUS" << std::endl; };
};

struct Track : ICar
{
    Track() {}
    void test() const { std::cout << "Track" << std::endl; };
};

int main(int argc, char const *argv[])
{
    IocContainer<ICar> carIOC;
    carIOC.RegisterType<Bus>("bus");
    carIOC.RegisterType<Track>("track");

    std::shared_ptr<ICar> bus = carIOC.ResolveShared("bus");
    bus->test();

    std::shared_ptr<ICar> track = carIOC.ResolveShared("track");
    track->test();

    return 0;
}
