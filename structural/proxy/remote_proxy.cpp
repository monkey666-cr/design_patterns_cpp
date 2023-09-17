#include <iostream>
#include <string>

class AbstractServer
{
public:
    virtual void Request() = 0;

protected:
    AbstractServer() {}
};

class RealServer : public AbstractServer
{
public:
    void Request()
    {
        std::cout << "服务器启动" << std::endl;
    }
};

class ProxyServer : public AbstractServer
{
public:
    ProxyServer(std::string name, std::string pwd) : m_username(name), m_pwd(pwd)
    {
        m_pServer = new RealServer();
    }
    ~ProxyServer()
    {
        delete m_pServer;
    }

    void Request()
    {
        if (m_username == "chenrun" && m_pwd == "123456")
        {
            std::cout << "启动成功\n";
            m_pServer->Request();
        }
        else
        {
            std::cout << "启动失败, 用户名密码错误\n";
        }
    }

private:
    std::string m_username;
    std::string m_pwd;

    AbstractServer *m_pServer;
};

int main(int argc, char const *argv[])
{
    AbstractServer *pServer = new ProxyServer("chenrun", "1234561");

    pServer->Request();

    return 0;
}
