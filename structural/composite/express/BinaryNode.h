#pragma once

#include "Express.h"
#include "ExpressNode.h"

class BinaryNode : public ExpressNode
{
public:
    friend class Express;
    BinaryNode();
    BinaryNode(char, class Express, class Express);
    ~BinaryNode();

private:
    void print(ostream &) const;
    int eval() const;
    class Express left;
    class Express right;
};