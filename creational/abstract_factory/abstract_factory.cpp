
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

class AbstractFactory
{
public:
    virtual FrameApi *createFrameApi() = 0;
    virtual LayoutApi *createLayoutApi() = 0;

protected:
    AbstractFactory() {}
};

class Schema1 : public AbstractFactory
{
    FrameApi *createFrameApi()
    {
        return new ComputerFrame(1024);
    }

    LayoutApi *createLayoutApi()
    {
        return new HighLayout(1024);
    }
};

class Schema2 : public AbstractFactory
{
    FrameApi *createFrameApi()
    {
        return new MobileFrame(800);
    }

    LayoutApi *createLayoutApi()
    {
        return new LowLayout(800);
    }
};

class AdvancedGuiEngineer
{
private:
    FrameApi *pFrame;
    LayoutApi *pLayout;

public:
    void prepareMaterials(AbstractFactory *pSchema)
    {
        this->pFrame = pSchema->createFrameApi();
        this->pLayout = pSchema->createLayoutApi();

        pFrame->draw();
        pLayout->installFrame();
    }
};

int main(int argc, char const *argv[])
{
    AdvancedGuiEngineer *pEng = new AdvancedGuiEngineer();
    pEng->prepareMaterials(new Schema2());

    return 0;
}
