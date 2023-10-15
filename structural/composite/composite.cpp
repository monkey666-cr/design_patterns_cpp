#include <list>
#include <string>
#include <iostream>

using namespace std;

class IFile
{
public:
    virtual void display() = 0;
    virtual int add(IFile *iFile) = 0;
    virtual int remove(IFile *IFile) = 0;
    virtual list<IFile *> *getChild() = 0;
};

class File : public IFile
{
public:
    File(string name) : m_name(name) {}

    virtual void display()
    {
        cout << m_name << endl;
    }

    virtual int add(IFile *iFile)
    {
        return -1;
    }

    virtual int remove(IFile *iFile)
    {
        return -1;
    }

    virtual list<IFile *> *getChild()
    {
        return nullptr;
    }

private:
    string m_name;
};

class Dir : public IFile
{
public:
    Dir(string name) : m_name(name)
    {
        m_list = new list<IFile *>;
    }
    ~Dir()
    {
        delete m_list;
    }

    virtual void display()
    {
        cout << m_name << endl;
    }

    virtual int add(IFile *iFile)
    {
        m_list->push_back(iFile);
        return 0;
    }

    virtual int remove(IFile *iFile)
    {
        m_list->remove(iFile);
    }

    virtual list<IFile *> *getChild()
    {
        return m_list;
    }

private:
    string m_name;
    list<IFile *> *m_list;
};

void showTree(IFile *root, int level)
{
    if (root == nullptr)
    {
        return;
    }

    int i = 0;
    for (i = 0; i < level; i++)
    {
        printf("\t");
    }

    root->display();
    list<IFile *> *list1 = root->getChild();
    if (list1 != nullptr)
    {
        for (list<IFile *>::iterator iter = list1->begin(); iter != list1->end(); iter++)
        {
            if ((*iter)->getChild() == nullptr)
            {
                for (i = 0; i < level; i++)
                {
                    printf("\t");
                }
                (*iter)->display();
            }
            else
            {
                showTree(*iter, level + 1);
            }
        }
    }
};

int main(int argc, char const *argv[])
{
    Dir *root = new Dir("C://");
    Dir *dir1 = new Dir("Program Files");
    Dir *dir2 = new Dir("windows");

    File *file1 = new File("a.txt");
    File *file2 = new File("b.txt");
    File *file3 = new File("c.txt");
    File *file4 = new File("d.txt");

    root->add(dir1);
    root->add(file1);
    dir1->add(file2);
    dir1->add(dir2);

    list<IFile *> *list1 = root->getChild();
    showTree(root, 0);

    return 0;
}
