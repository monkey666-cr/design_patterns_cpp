
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

// 切分成log
// 故障名, 故障时间, 故障描述
// map<int, vector<string>>: int 故障序号
std::map<int, std::vector<std::string>> Cache;

class BugManager
{
public:
    virtual void getBugs() = 0;
};

class RealBugModel : public BugManager
{
public:
    void getBugs()
    {
        std::ifstream fin("./故障列表.txt");
        if (!fin)
        {
            std::cerr << "文件打开错误" << std::endl;
            return;
        }
        std::string line;
        int i = 0;
        while (getline(fin, line))
        {
            Cache[i] = getCache(line);
            i++;
        }

        fin.close();
    }

private:
    std::vector<std::string> getCache(std::string words)
    {
        std::vector<std::string> results;

        std::istringstream ss(words);

        while (!ss.eof())
        {
            std::string word;
            std::getline(ss, word, '|');
            results.push_back(word);
        }

        return results;
    }
};

class ProxyBugModel : public BugManager
{
public:
    ProxyBugModel() : m_reload(false) {}

    void getBugs()
    {
        if (m_reload)
        {
            std::cout << "从缓存中获取的\n";
            showBugs();
        }
        else
        {
            std::cout << "从真实的类中获取\n";
            (new RealBugModel())->getBugs();
            showBugs();
            m_reload = true;
        }
    }

private:
    void showBugs()
    {
        for (int i = 0; i < Cache.size(); i++)
        {
            std::cout << "第" << i << "行是";
            for (auto iter = Cache[i].begin(); iter != Cache[i].end(); iter++)
            {
                std::cout << (*iter) << " ";
            }
            std::cout << std::endl;
        }
    }

private:
    bool m_reload;
};

int main(int argc, char const *argv[])
{
    ProxyBugModel *p = new ProxyBugModel();

    for (int i = 0; i < 5; i++)
    {
        p->getBugs();
    }

    return 0;
}
