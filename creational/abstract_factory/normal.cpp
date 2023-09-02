#include <iostream>

class FrameApi
{
public:
    virtual void draw() = 0;

protected:
    FrameApi() {}
};

class LayoutApi
{
public:
    virtual void installFrame() = 0;

protected:
    LayoutApi() {}
};

class ComputerFrame : public FrameApi
{
private:
    int m_pins;

public:
    ComputerFrame(int pins) : m_pins(pins) {}

    void draw()
    {
        std::cout << "现在是pc机的Frame, 我适用的分辨率是" << m_pins << std::endl;
    }
};

class MobileFrame : public FrameApi
{
private:
    int m_pins;

public:
    MobileFrame(int pins) : m_pins(pins) {}

    void draw()
    {
        std::cout << "现在是手机的Frame, 我适用的分辨率是" << m_pins << std::endl;
    }
};

class HighLayout : public LayoutApi
{
public:
    HighLayout(int FrameAdapterPins) : m_FrameAdapterPins(FrameAdapterPins) {}

    void installFrame()
    {
        std::cout << "现在是在PC环境下, 我们使用的高分辨率布局" << m_FrameAdapterPins << std::endl;
    }

private:
    int m_FrameAdapterPins;
};

class LowLayout : public LayoutApi
{
public:
    LowLayout(int FrameAdapterPins) : m_FrameAdapterPins(FrameAdapterPins) {}

    void installFrame()
    {
        std::cout << "现在是在Mobile环境下, 我们使用的低分辨率布局" << m_FrameAdapterPins << std::endl;
    }

private:
    int m_FrameAdapterPins;
};

class FrameFactory
{
public:
    static FrameApi *createFrame(int type)
    {
        FrameApi *pFrame = nullptr;

        switch (type)
        {
        case 1:
            pFrame = new ComputerFrame(1024);
            break;
        case 2:
            pFrame = new MobileFrame(800);
            break;
        default:
            break;
        }

        return pFrame;
    }
};

class LayoutFactory
{

public:
    static LayoutApi *createLayout(int type)
    {
        LayoutApi *pLayout;

        switch (type)
        {
        case 1:
            pLayout = new HighLayout(1024);
            break;
        case 2:
            pLayout = new LowLayout(800);
            break;

        default:
            break;
        }

        return pLayout;
    }
};

class GUIEngineer
{
public:
    void prepareDraw(int FrameType, int LayoutType)
    {
        this->pFrame = FrameFactory::createFrame(FrameType);
        this->pLayout = LayoutFactory::createLayout(LayoutType);
        pFrame->draw();
        pLayout->installFrame();
    }

private:
    FrameApi *pFrame;
    LayoutApi *pLayout;
};

int main(int argc, char const *argv[])
{
    GUIEngineer *pEng = new GUIEngineer();

    pEng->prepareDraw(2, 2);

    return 0;
}
