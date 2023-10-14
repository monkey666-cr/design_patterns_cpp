#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>

using namespace std;

// 抽象的表达式对象以及Context对象
// 用于保存计算的中间结果以及当前执行的操作符
class Context
{
public:
    int m_value;
    char m_operator;
    Context() : m_value(0), m_operator('\0') {}
};

// 表示所有表达式的抽象接口
class IExpression
{
public:
    virtual void Eval(Context *p) = 0;
};

// 拆分表达式的元素
class Operator : public IExpression
{
public:
    Operator(char op)
    {
        this->m_op = op;
    }

    void Eval(Context *pContext)
    {
        pContext->m_operator = m_op;
    }

private:
    char m_op;
};

// 拆分操作数
class Operand : public IExpression
{
public:
    Operand(int num)
    {
        this->m_num = num;
    }

    void Eval(Context *pContext)
    {
        switch (pContext->m_operator)
        {
        case '\0':
            pContext->m_value = m_num;
            break;
        case '+':
            pContext->m_value += m_num;
            break;
        case '-':
            pContext->m_value -= m_num;
            break;
        default:
            break;
        }
    }

private:
    int m_num;
};

class Calculator
{
public:
    int Calc(string expression)
    {
        Context *pContext = new Context;
        vector<IExpression *> tree;
        for (int i{0}; i < expression.size(); i++)
        {
            if ((expression[i] == '+') || (expression[i] == '-'))
            {
                tree.push_back(new Operator(expression[i]));
                printf("第%d次压入的符号是=%c\n", i, expression[i]);
            }
            else
            {
                tree.push_back(new Operand((int)(expression[i] - 48)));
                printf("第%d次压入的数字是=%d\n", i, ((int)expression[i]) - 48);
            }
        }

        for (vector<IExpression *>::iterator iter = tree.begin(); iter != tree.end(); iter++)
        {
            (*iter)->Eval(pContext);
            printf("value=%d, oper=%c\n", pContext->m_value, pContext->m_operator);
        }
        return pContext->m_value;
    }
};

int main(int argc, char const *argv[])
{
    Calculator *pc = new Calculator;
    int res = pc->Calc("1+4-2");
    cout << "1+4-2=" << res << endl;
    return 0;
}
