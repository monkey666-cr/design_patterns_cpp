
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

class Builder
{
public:
    virtual void builderHeader(ExportHeaderModel &ehm) = 0;
    virtual void builderBody(std::vector<ExportDataModel *> &edmCollection) = 0;
    virtual void builderFoot(ExportFooterModel &efm) = 0;
    virtual std::string getResult() = 0;

protected:
    Builder() {}
};

class TxtBuilder : public Builder
{
public:
    void builderHeader(ExportHeaderModel &ehm)
    {
        m_strResult += ehm.getDepId() + ", " + ehm.getExportDate() + "\n";
    }

    void builderBody(std::vector<ExportDataModel *> &edmCollection)
    {
        for (std::vector<ExportDataModel *>::iterator iter = edmCollection.begin(); iter != edmCollection.end(); iter++)
        {
            m_strResult += (*iter)->getTransId() + ": " + std::to_string((*iter)->getQuantity()) + "\n";
        }
    }

    void builderFoot(ExportFooterModel &efm)
    {
        m_strResult += efm.getExportUser() + "\n";
    }

    std::string getResult()
    {
        return m_strResult;
    }

private:
    std::string m_strResult;
};

class Director
{
public:
    Director(Builder *pBuilder) : m_pBuilder(pBuilder) {}

    void construct(ExportHeaderModel &ehm, std::vector<ExportDataModel *> &edmCollection, ExportFooterModel &efm)
    {
        m_pBuilder->builderHeader(ehm);
        m_pBuilder->builderBody(edmCollection);
        m_pBuilder->builderFoot(efm);
    }

private:
    Builder *m_pBuilder;
};

int main(int argc, char const *argv[])
{
    ExportHeaderModel *pEhm = new ExportHeaderModel("深圳支行", "9月3号");
    ExportDataModel *pEdm = new ExportDataModel("1", 100000.00f);
    ExportDataModel *pEdm2 = new ExportDataModel("2", 200000.00f);
    std::vector<ExportDataModel *> data;
    data.push_back(pEdm);
    data.push_back(pEdm2);

    ExportFooterModel *pEfm = new ExportFooterModel("cr");

    Builder *pBuilder = new TxtBuilder();
    Director *pDirector = new Director(pBuilder);
    pDirector->construct(*pEhm, data, *pEfm);

    std::cout << pBuilder->getResult() << std::endl;

    return 0;
}
