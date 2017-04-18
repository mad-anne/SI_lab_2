//
// Created by Anna Siwik on 2017-04-07.
//

#ifndef SI_LAB_2_NODE_H
#define SI_LAB_2_NODE_H

#include "../interface/IVariable.h"

class Node : public IVariable
{
    public:
        Node(int, int);
        ~Node();

        void setValue(IValue*) override;
        IValue* getValue() const override;
        void resetValue() override;

        const IDomain* getDomain() const override;
        void addDomain(const IDomain*) override;
        void addValueToDomain(IValue*) override;
        void removeValueFromDomain(const IValue*) override;

        const int getRow() const override;
        const int getColumn() const override;
};

#endif //SI_LAB_2_NODE_H
