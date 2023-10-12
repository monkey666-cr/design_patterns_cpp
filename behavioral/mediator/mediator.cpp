#include <string>
#include <iostream>

using namespace std;

class Colleague;

class Mediator
{
public:
    // 对象在自身改变的情况下，通知Mediator进行变更
    // 让我们Mediator这个总线，负责相应的对象的交互
    virtual void changed(Colleague *pColleague) = 0;

protected:
    Mediator() {}
};

class Colleague
{
public:
    Colleague() {}
    Colleague(Mediator *pMediator) : m_pMediator(pMediator) {}

    Mediator *getMediator()
    {
        return m_pMediator;
    }

private:
    Mediator *m_pMediator;
};

class SoundCard : public Colleague
{
public:
    SoundCard(Mediator *pMediator) : Colleague(pMediator) {}

    void soundData(string data)
    {
        cout << "声卡在工作" << data << endl;
    }
};

class VideoCard : public Colleague
{
public:
    VideoCard(Mediator *pMediator) : Colleague(pMediator) {}

    void videoData(string data)
    {
        cout << "显卡在工作" << data << endl;
    }
};

class Display : public Colleague
{
public:
    Display(Mediator *pMediator) : Colleague(pMediator) {}

    void displayData(string data)
    {
        cout << "显示器正在工作" << data << endl;
    }
};

class CPU : public Colleague
{
public:
    CPU(Mediator *pMediator) : Colleague(pMediator) {}

    void executeData(string data[])
    {
        m_strVideoData = data[0];
        m_strSoundData = data[1];
        m_strDisplayData = data[2];

        this->getMediator()->changed(this);
    }

    string getVideoData()
    {
        return m_strVideoData;
    }

    string getSoundData()
    {
        return m_strSoundData;
    }

    string getDisplayData()
    {
        return m_strDisplayData;
    }

private:
    string m_strVideoData;
    string m_strSoundData;
    string m_strDisplayData;
};

class MotherBoard : public Mediator
{
public:
    void setCPU(CPU *pCpu)
    {
        m_pCPU = pCpu;
    }

    void setVideoCard(VideoCard *pVC)
    {
        m_pVideoCard = pVC;
    }

    void setSoundCard(SoundCard *pSC)
    {
        m_pSoundCard = pSC;
    }

    void setDisplay(Display *pDisplay)
    {
        m_pDisplay = pDisplay;
    }

    void changed(Colleague *pColleague)
    {
        if (pColleague == m_pCPU)
        {
            this->openCPU((CPU *)pColleague);
        }
    }

private:
    void openCPU(CPU *pCPU)
    {
        string strVideoData = pCPU->getVideoData();
        string strSoundData = pCPU->getSoundData();
        string strDisplayData = pCPU->getDisplayData();

        m_pSoundCard->soundData(strSoundData);
        m_pVideoCard->videoData(strVideoData);
        m_pDisplay->displayData(strDisplayData);
    }

private:
    CPU *m_pCPU;
    VideoCard *m_pVideoCard;
    SoundCard *m_pSoundCard;
    Display *m_pDisplay;
};

int main(int argc, char const *argv[])
{
    MotherBoard *pMediator = new MotherBoard;

    CPU *pCPU = new CPU(pMediator);
    VideoCard *pVC = new VideoCard(pMediator);
    SoundCard *pSC = new SoundCard(pMediator);
    Display *pDisplay = new Display(pMediator);

    pMediator->setCPU(pCPU);
    pMediator->setSoundCard(pSC);
    pMediator->setVideoCard(pVC);
    pMediator->setDisplay(pDisplay);

    string arr[] = {"跟着老陈学开发", "升职加薪就找他", "Hello World"};

    pCPU->executeData(arr);

    return 0;
}
