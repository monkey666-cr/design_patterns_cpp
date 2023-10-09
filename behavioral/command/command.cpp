#include <iostream>

using namespace std;

class Command
{
public:
    virtual void execute() = 0;
    virtual void undo() = 0;

protected:
    Command() {}
};

class NoCommand : public Command
{
public:
    void execute() {}
    void undo() {}
};

class Light
{
public:
    void on()
    {
        cout << "灯亮了" << endl;
    }

    void off()
    {
        cout << "灯灭了" << endl;
    }
};

class LightOnCommand : public Command
{
public:
    LightOnCommand(Light *pLight)
    {
        m_pLight = pLight;
    }

    void execute()
    {
        m_pLight->on();
    }

    void undo()
    {
        m_pLight->off();
    }

private:
    Light *m_pLight;
};

class LightOffCommand : public Command
{
public:
    LightOffCommand(Light *pLight)
    {
        m_pLight = pLight;
    }

    void execute()
    {
        m_pLight->off();
    }

    void undo()
    {
        m_pLight->on();
    }

private:
    Light *m_pLight;
};

class Stereo
{

public:
    void on()
    {
        cout << "打开音响" << endl;
    }

    void off()
    {
        cout << "关闭音响" << endl;
    }

    void setCd()
    {
        cout << "放入CD" << endl;
    }

    void setDvd()
    {
        cout << "放入DVD" << endl;
    }

    void setRadio()
    {
        cout << "放入Radio" << endl;
    }

    void setVolume(int volumeSize)
    {
        VolumeSize = volumeSize;
        cout << "调整音量为: " << VolumeSize << endl;
    }

public:
    int VolumeSize = 10;
};

class StereoOnWithCDCommand : public Command
{
public:
    StereoOnWithCDCommand(Stereo *pStereo)
    {
        m_pStereo = pStereo;
    }

    void execute()
    {
        m_pStereo->on();
        m_pStereo->setCd();
        m_pStereo->setVolume(11);
    }

    void undo()
    {
        m_pStereo->off();
    }

private:
    Stereo *m_pStereo;
};

class StereoOffWithCDCommand : public Command
{
public:
    StereoOffWithCDCommand(Stereo *pStereo)
    {
        m_pStereo = pStereo;
    }

    void execute()
    {
        m_pStereo->off();
    }

    void undo()
    {
        m_pStereo->on();
        m_pStereo->setCd();
        m_pStereo->setVolume(m_pStereo->VolumeSize);
    }

private:
    Stereo *m_pStereo;
};

class SimpleRemoteControl
{
public:
    void buttonWasPressed()
    {
        m_pCommand->execute();
    }

    void setCommand(Command *pCommand)
    {
        m_pCommand = pCommand;
    }

private:
    Command *m_pCommand;
};

class RemoteControl
{
public:
    RemoteControl()
    {
        Command *pNoCommand = new NoCommand;
        for (int i{0}; i < 7; i++)
        {
            m_onCommands[i] = pNoCommand;
            m_offCommands[i] = pNoCommand;
        }
        m_undoCommand = pNoCommand;
    }

    void setCommand(int slot, Command *pOnCommand, Command *pOffCommand)
    {
        m_onCommands[slot] = pOnCommand;
        m_offCommands[slot] = pOffCommand;
    }

    void onButtonWasPushed(int slot)
    {
        m_onCommands[slot]->execute();
        m_undoCommand = m_onCommands[slot];
    }

    void offButtonWasPushed(int slot)
    {
        m_offCommands[slot]->execute();
        m_undoCommand = m_offCommands[slot];
    }

    void undoButtonWasPushed()
    {
        m_undoCommand->undo();
    }

private:
    Command *m_onCommands[7];
    Command *m_offCommands[7];
    Command *m_undoCommand;
};

int main(int argc, char const *argv[])
{
    // SimpleRemoteControl *remote = new SimpleRemoteControl;

    // Light *pLight = new Light;
    // LightOnCommand *pLightOnCommand = new LightOnCommand(pLight);

    // remote->setCommand(pLightOnCommand);
    // remote->buttonWasPressed();

    RemoteControl *remote = new RemoteControl;

    Light *pLivingRootLight = new Light;
    LightOnCommand *pLightOnCommand = new LightOnCommand(pLivingRootLight);
    LightOffCommand *pLightOffCommand = new LightOffCommand(pLivingRootLight);

    Stereo *pStereo = new Stereo;
    StereoOnWithCDCommand *pStereoOnWithCommand = new StereoOnWithCDCommand(pStereo);
    StereoOffWithCDCommand *pStereoOffWithCommand = new StereoOffWithCDCommand(pStereo);

    remote->setCommand(0, pLightOnCommand, pLightOffCommand);
    remote->setCommand(1, pStereoOnWithCommand, pStereoOffWithCommand);

    // remote->onButtonWasPushed(0);
    remote->onButtonWasPushed(1);

    // remote->offButtonWasPushed(0);
    // remote->offButtonWasPushed(1);

    remote->undoButtonWasPushed();

    return 0;
}
