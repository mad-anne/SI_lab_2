//
// Created by Anna Siwik on 2017-04-07.
//

#ifndef SI_LAB_2_NODE_H
#define SI_LAB_2_NODE_H

#include "../interface/IVariable.h"

class Node : public IVariable
{
    int row;
    int col;

    public:
        Node(int, int);
        ~Node();

        const IValue* getValue() const override;
        const IDomain* getDomain() const override;
        void setValue(const IValue*) override;
        void addValueToDomain(const IValue*) override;
        void resetValue() override;
        void addDomain(const IDomain*) override;

        const int getRow() const override;
        const int getColumn() const override;
};

#endif //SI_LAB_2_NODE_H
