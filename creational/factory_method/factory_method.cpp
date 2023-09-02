#include <iostream>
#include <string>

class ExportFileApi
{
public:
    virtual bool exportData(std::string data) = 0;

protected:
    ExportFileApi(){};
};

// 具体化的子类
class ExportTxtFile : public ExportFileApi
{
public:
    bool exportData(std::string data)
    {
        std::cout << "正在导出数据" << data << "到csv文件" << std::endl;
        return true;
    }
};

class ExportDB : public ExportFileApi
{
public:
    bool exportData(std::string data)
    {
        std::cout << "正在导出数据" << data << "到数据库" << std::endl;
        return true;
    }
};

class ExportOperate
{
public:
    bool exportData(std::string data)
    {
        ExportFileApi *pApi = factoryMethod();

        return pApi->exportData(data);
    };

protected:
    virtual ExportFileApi *factoryMethod() = 0;
};

class ExportTextFileOperate : public ExportOperate
{
protected:
    ExportFileApi *factoryMethod()
    {
        return new ExportTxtFile;
    }
};

class ExportDBFileOperate : public ExportOperate
{
protected:
    ExportFileApi *factoryMethod()
    {
        return new ExportDB;
    }
};

int main(int argc, char const *argv[])
{
    ExportOperate *pOperate = new ExportTextFileOperate();
    pOperate->exportData("Haha");

    pOperate = new ExportDBFileOperate();
    pOperate->exportData("Haha");

    return 0;
}
