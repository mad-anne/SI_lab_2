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
<<<<<<< HEAD
        ~Node();

        const IValue* getValue() const override;
        const IDomain* getDomain() const override;
=======

        const IValue* getValue() override;
        const IDomain* getDomain() override;
>>>>>>> 8e927268749581ebfa7dbdd3c68afe7a0c154d50
};

#endif //SI_LAB_2_NODE_H
