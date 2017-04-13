//
// Created by Anna Siwik on 2017-04-07.
//

#ifndef SI_LAB_2_NODE_H
#define SI_LAB_2_NODE_H

#include "../interface/IVariable.h"

class Node : public IVariable
{
    public:
        Node();
        ~Node();

        const IValue* getValue() const override;
        const IDomain* getDomain() const override;
        const IValue* setValue(const IValue*) override;
};

#endif //SI_LAB_2_NODE_H
