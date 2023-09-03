#include <iostream>
#include <string>
#include <vector>

class ExportHeaderModel
{
public:
    ExportHeaderModel(std::string strDepId, std::string strExportDate)
        : m_strDepId(strDepId), m_strExportDate(strExportDate) {}

    std::string getDepId()
    {
        return m_strDepId;
    }

    std::string getExportDate()
    {
        return m_strExportDate;
    }

private:
    std::string m_strDepId;
    std::string m_strExportDate;
};

class ExportDataModel
{
public:
    ExportDataModel(std::string strTransId, double Quantity) : m_strTransId(strTransId), m_Quantity(Quantity) {}

    std::string getTransId()
    {
        return m_strTransId;
    }

    double getQuantity()
    {
        return m_Quantity;
    }

private:
    std::string m_strTransId;
    double m_Quantity;
};

class ExportFooterModel
{
public:
    ExportFooterModel(std::string exportUser) : m_exportUser(exportUser) {}

    std::string getExportUser()
    {
        return m_exportUser;
    }

private:
    std::string m_exportUser;
};

class ExportToTextHelper
{
public:
    void doExport(ExportHeaderModel &ehm, std::vector<ExportDataModel *> &edmCollection, ExportFooterModel &efm);
};

void ExportToTextHelper::doExport(ExportHeaderModel &ehm, std::vector<ExportDataModel *> &edmCollection, ExportFooterModel &efm)
{
    // 第一步: 字符串拼接
    std::string strTemp = "";

    // 第二步: 写文件头
    strTemp += ehm.getDepId() + ", " + ehm.getExportDate() + "\n";

    // 第三步: 写文件数据
    for (std::vector<ExportDataModel *>::iterator iter = edmCollection.begin(); iter != edmCollection.end(); iter++)
    {
        strTemp += (*iter)->getTransId() + ": " + std::to_string((*iter)->getQuantity()) + "\n";
    }

    // 第四步: 写文件尾部
    strTemp += efm.getExportUser() + "\n";

    std::cout << strTemp << std::endl;
}

class ExportToXmlHelper
{
public:
    void doExport(ExportHeaderModel &ehm, std::vector<ExportDataModel *> &edmCollection, ExportFooterModel &efm);
};

void ExportToXmlHelper::doExport(ExportHeaderModel &ehm, std::vector<ExportDataModel *> &edmCollection, ExportFooterModel &efm)
{
    std::string strTemp = "";

    strTemp.append("<?xml version='1.0' encoding='utf-8'>\n");
    strTemp.append("<Receipt>\n");
    strTemp.append("    <Header>\n");
    strTemp.append("        <DepId>");
    strTemp.append(ehm.getDepId() + "</DepId>\n");
    strTemp.append("        <ExportDate>" + ehm.getExportDate() + "</ExportDate>");
    strTemp.append("    </Header>");
    strTemp.append("    <Data>\n");
    for (auto &data : edmCollection)
    {
        strTemp.append("        <TransId>\n");
        strTemp.append("        " + data->getTransId() + "</TransId>");
        strTemp.append("        <Quantity>\n");
        strTemp.append("        " + std::to_string(data->getQuantity()) + "</Quantity>");
    }
    strTemp.append("    </Data>\n");
    strTemp.append("    <Footer>");
    strTemp.append(efm.getExportUser());
    strTemp.append("    </Footer>");

    std::cout << strTemp << std::endl;
}

int main(int argc, char const *argv[])
{
    ExportHeaderModel *pEhm = new ExportHeaderModel("深圳支行", "9月3号");
    ExportDataModel *pEdm = new ExportDataModel("1", 100000.00f);
    ExportDataModel *pEdm2 = new ExportDataModel("2", 200000.00f);
    std::vector<ExportDataModel *> data;
    data.push_back(pEdm);
    data.push_back(pEdm2);

    ExportFooterModel *pEfm = new ExportFooterModel("cr");

    // ExportToTextHelper helper;
    ExportToXmlHelper helper;

    helper.doExport(*pEhm, data, *pEfm);

    return 0;
}
