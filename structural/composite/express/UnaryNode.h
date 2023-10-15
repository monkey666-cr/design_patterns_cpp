#pragma once
#include "Express.h"
#include "ExpressNode.h"

class UnaryNode : public ExpressNode
{
public:
private:
    void print(ostream &os) const;
    int eval() const;
    char opend;
    class Express left;
};