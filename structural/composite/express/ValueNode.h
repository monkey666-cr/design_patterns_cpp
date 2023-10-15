#pragma once

#include <Express.h>
#include <ExpressNode.h>

class ValueNode : public ExpressNode
{
public:
    friend class Express;
    ValueNode();
    ValueNode(int value) : m_value(value) {}
    ~ValueNode() {}

private:
    void print(ostream &os) const
    {
        os << m_value;
    }
    int eval() const
    {
        return m_value;
    }
    int m_value;
}