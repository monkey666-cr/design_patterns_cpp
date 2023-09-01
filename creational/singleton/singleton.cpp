#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <functional>
#include <chrono>
#include <map>

class Singleton;
static std::map<std::string, Singleton *> instanceMap = std::map<std::string, Singleton *>();

class Singleton
{
private:
    Singleton()
    {
        std::cout << "构造一个Singleton对象" << std::endl;
    };

public:
    inline static Singleton *findInstance(const std::string &key)
    {
        Singleton *instance = nullptr;
        if (instanceMap.find(key) != instanceMap.end())
        {
            instance = instanceMap.find(key)->second;
        }
        return instance;
    }

    static Singleton *getInstance(std::string key = "")
    {
        if (key == "")
        {
            key = DEFAULT_KEY;
        }

        // double check
        Singleton *instance = findInstance(key);
        if (instance != nullptr)
        {
            return instance;
        }
        else
        {
            std::unique_lock<std::mutex> lock(mtx);
            // 再次查找
            instance = findInstance(key);
            if (instance != nullptr)
            {
                return instance;
            }
            instance = new Singleton;
            instanceMap[key] = instance;
        }

        return instance;
    };

private:
    static Singleton *m_singer;
    static std::mutex mtx;
    static std::string DEFAULT_KEY;
};

Singleton *Singleton::m_singer = nullptr;
std::mutex Singleton::mtx = std::mutex();
std::string Singleton::DEFAULT_KEY = "DEFAULT_KEY";

void do_something()
{
    Singleton *p = Singleton::getInstance();

    std::cout << p << std::endl;
}

int main(int argc, char const *argv[])
{

    std::vector<std::thread> threads;

    // 创建10个线程创建对象
    for (int i = 0; i < 10; i++)
    {
        threads.emplace_back(std::thread(do_something));
    }

    for (auto &thread : threads)
    {
        thread.join();
    }

    Singleton *p1 = Singleton::getInstance("ONE");

    std::cout << p1 << std::endl;

    Singleton *p2 = Singleton::getInstance("ONE");

    std::cout << p2 << std::endl;

    Singleton *p3 = Singleton::getInstance();

    std::cout << p3 << std::endl;

    return 0;
}
