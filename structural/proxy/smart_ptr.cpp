/**
 * 模拟智能指针
 */
#include <iostream>

using namespace std;

template <class T>
class Auto_ptr;

template <class T>
class Ref_Ptr
{
    friend class Auto_ptr<T>;

private:
    T *m_pTtr;
    size_t m_RefCount;

    Ref_Ptr(T *ptr);
    ~Ref_Ptr();
};

template <class T>
Ref_Ptr<T>::Ref_Ptr(T *ptr) : m_pTtr(ptr), m_RefCount(1)
{
    cout << "Ref_Ptr()构造函数调用\n";
}

template <class T>
Ref_Ptr<T>::~Ref_Ptr()
{
    if (m_pTtr)
    {
        cout << "~Ref_Ptr()析构函数调用\n";
        delete m_pTtr;
        m_pTtr = nullptr;
    }

    m_pTtr = nullptr;
}

template <class T>
class Auto_ptr
{
public:
    Auto_ptr();
    Auto_ptr(T *p);
    ~Auto_ptr();

    // 重载运算符
    Auto_ptr<T> &operator=(Auto_ptr &other);
    T &operator*();
    T *operator->();

    // 拷贝构造函数
    Auto_ptr(Auto_ptr<T> &other);

private:
    Ref_Ptr<T> *m_pRef;
};

template <class T>
Auto_ptr<T>::Auto_ptr()
{
    m_pRef = nullptr;
}

template <class T>
Auto_ptr<T>::Auto_ptr(T *p)
{
    m_pRef = new Ref_Ptr(p);
    cout << "构造函数被调用" << endl;
}

template <class T>
Auto_ptr<T>::Auto_ptr(Auto_ptr<T> &other)
{
    m_pRef = other->m_pRef;
    ++(m_pRef->m_RefCount);
    cout << "拷贝构造函数被调用" << endl;
}

template <class T>
Auto_ptr<T> &Auto_ptr<T>::operator=(Auto_ptr &other)
{
    // 右操作加一
    ++(other.m_pRef->m_RefCount);
    if (m_pRef)
    {
        if (--(m_pRef->m_RefCount) == 0)
        {
            delete m_pRef;
        }
    }
    m_pRef = other.m_pRef;
    printf("operator被调用, 当前引用计数: %d\n", (int)(m_pRef->m_RefCount));

    return *this;
}

template <class T>
T &Auto_ptr<T>::operator*()
{
    return *(m_pRef->m_pTtr);
}

template <class T>
T *Auto_ptr<T>::operator->()
{
    return m_pRef->m_pTtr;
}

template <class T>
Auto_ptr<T>::~Auto_ptr()
{
    cout << "析构函数被调用\n";
    if (--(m_pRef->m_RefCount) == 0)
    {
        cout << "删除\n";
        delete m_pRef;
        m_pRef = nullptr;
    }
}

int main(int argc, char const *argv[])
{
    Auto_ptr<int> *pPtr = nullptr;
    {
        Auto_ptr<int> g_ptr;
        {
            Auto_ptr<int> ptr1(new int(4));
            g_ptr = ptr1;
        }

        Auto_ptr<int> ptr2 = Auto_ptr<int>(new int(3));
        g_ptr = ptr2;
        Auto_ptr<int> *pPtr = &ptr2;
    }

    return 0;
}
