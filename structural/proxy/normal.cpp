#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

// 切分成log
// 故障名, 故障时间, 故障描述
// map<int, vector<string>>: int 故障序号
std::map<int, std::vector<std::string>> Logs;

std::vector<std::string> getBugs(std::string words)
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

bool getLogs()
{
    std::ifstream fin("./故障列表.txt", std::ios::in);
    if (!fin)
    {
        std::cerr << "文件打开失败" << std::endl;
        return false;
    }

    std::string line;
    int i = 0;
    while (std::getline(fin, line))
    {
        Logs[i] = getBugs(line);
        i++;
    }
    fin.close();

    return true;
}

int main(int argc, char const *argv[])
{
    getLogs();

    for (int i = 0; i < Logs.size(); i++)
    {
        std::cout << "第" << i << "行是";
        for (auto iter = Logs[i].begin(); iter != Logs[i].end(); iter++)
        {
            std::cout << (*iter) << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
