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

        const IValue* getValue() override;
        const IDomain* getDomain() override;
};

#endif //SI_LAB_2_NODE_H
