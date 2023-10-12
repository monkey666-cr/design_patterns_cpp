#include <string>
#include <iostream>

using namespace std;

class OriginalWord;

class Memento
{
public:
    Memento(string strWord) : m_strWord(strWord) {}

private:
    friend class OriginalWord;

    string getWords()
    {
        return m_strWord;
    }

    string m_strWord;
};

class OriginalWord
{
public:
    OriginalWord(string myWord) : m_strWord(myWord) {}

    // 存档
    Memento *saveWords()
    {
        return new Memento(m_strWord);
    }

    // 恢复存档
    void recycleWords(Memento *pMemento)
    {
        m_strWord = pMemento->getWords();
        cout << "存档恢复成功" << endl;
    }

    void showWords()
    {
        cout << m_strWord << endl;
    }

private:
    string m_strWord;
};

// 用来设置快照, 获得快照
class Caretake
{
public:
    void setMemento(Memento *pMemento)
    {
        m_pMemento = pMemento;
    }

    Memento *getMemento()
    {
        return m_pMemento;
    }

private:
    Memento *m_pMemento;
};

int main(int argc, char const *argv[])
{
    // 第一个消息
    OriginalWord *pWordFst = new OriginalWord("跟着老陈学开发");

    pWordFst->showWords();

    Caretake *pCT = new Caretake;
    // 保存当前的快照
    pCT->setMemento(pWordFst->saveWords());
    cout << "保存了当前Fst的快照" << endl;

    OriginalWord *pWordSec = new OriginalWord("升职加薪");

    cout << "第二个Msg" << endl;
    pWordSec->showWords();

    OriginalWord *pWordThd = new OriginalWord("放假了");
    cout << "第三个Msg" << endl;
    pWordThd->showWords();

    cout << "我们在多看看xxx" << endl;

    // 当需要回溯到某一个状态的时候我们需要访问Caretake
    // pWordFst->recycleWords(pCT->getMemento());
    // pWordFst->showWords();
    pWordSec->recycleWords(pCT->getMemento());
    pWordSec->showWords();

    return 0;
}
