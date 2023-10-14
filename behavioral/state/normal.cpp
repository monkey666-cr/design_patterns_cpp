#include <map>
#include <string>
#include <iostream>

using namespace std;

class DownloadManager
{
public:
    void Down(string user, string DownItem)
    {
        int oldDownCount = 0;
        if (m_mapDownCount.count(user) > 0)
        {
            oldDownCount = m_mapDownCount[user];
        }
        else
        {
            m_mapDownCount[user] = 0;
        }

        oldDownCount++;
        m_mapDownCount[user] = oldDownCount;

        // 判断行为
        if (oldDownCount == 1)
        {
            m_mapDown[user] = DownItem;
            cout << "正常下载" << endl;
        }
        else if (oldDownCount > 1 && oldDownCount < 3)
        {
            cout << "请您不要重复下载" << endl;
        }
        else if (oldDownCount >= 3 && oldDownCount < 5)
        {
            cout << "您有恶意下载的嫌疑, 即将取消您的下载资格" << endl;
        }
        else if (oldDownCount >= 5)
        {
            // 进入黑名单
            cout << "您已经进入黑名单, 禁止登录" << endl;
        }
    }

private:
    map<string, string> m_mapDown;   // 用户名, 用户下载的资源
    map<string, int> m_mapDownCount; // 用户名, 下载次数
};

int main(int argc, char const *argv[])
{
    DownloadManager *pDM = new DownloadManager;

    for (int i{0}; i < 5; i++)
    {
        pDM->Down("chenrun", "设计模式完全手册源代码");
    }

    return 0;
}
