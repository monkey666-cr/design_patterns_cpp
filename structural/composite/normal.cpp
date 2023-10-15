#include <list>
#include <string>
#include <iostream>

using namespace std;

class Leaf
{
public:
    Leaf(string name) : m_name(name) {}

    void showStruct(string preStr)
    {
        cout << "preStr"
             << "-" << m_name << endl;
    }

private:
    string m_name;
};

class Composite
{
public:
    Composite(string name) : m_name(name) {}

    void addComposite(Composite *pCom)
    {
        childComposite.push_back(pCom);
    }

    void addLeaf(Leaf *pLeaf)
    {
        childLeaf.push_back(pLeaf);
    }

    void showStruct(string preStr)
    {
        cout << preStr
             << "+" << m_name << endl;
        preStr += "";

        for (list<Leaf *>::iterator iter = childLeaf.begin(); iter != childLeaf.end(); iter++)
        {
            (*iter)->showStruct(preStr);
        }
        // 输出当前对象
        for (list<Composite *>::iterator iter = childComposite.begin(); iter != childComposite.end(); iter++)
        {
            (*iter)->showStruct(preStr);
        }
    }

private:
    string m_name;

    list<Leaf *> childLeaf;
    list<Composite *> childComposite;
};

int main(int argc, char const *argv[])
{
    Composite *pRoot = new Composite("C://");

    Composite *pC1 = new Composite("Program Files");
    Composite *pC2 = new Composite("Windows");

    // 定义文件节点
    Leaf *pLeaf1 = new Leaf("a.txt");
    Leaf *pLeaf2 = new Leaf("b.txt");

    Leaf *pLeaf3 = new Leaf("1.c");
    Leaf *pLeaf4 = new Leaf("2.c");

    pRoot->addComposite(pC1);
    pRoot->addComposite(pC2);

    pC1->addLeaf(pLeaf1);
    pC1->addLeaf(pLeaf2);
    pC2->addLeaf(pLeaf3);
    pC2->addLeaf(pLeaf4);

    pRoot->showStruct("");

    return 0;
}
