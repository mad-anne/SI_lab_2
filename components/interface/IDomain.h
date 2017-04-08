    //
// Created by Dom on 2017-04-08.
//

#ifndef SI_LAB_2_IDOMAIN_H
#define SI_LAB_2_IDOMAIN_H

#include <vector>
#include "IValue.h"

class IDomain
{
    protected:
        std::vector<IValue*> values;

    public:
<<<<<<< HEAD
        virtual ~IDomain() {}

=======
>>>>>>> 8e927268749581ebfa7dbdd3c68afe7a0c154d50
        virtual void addValue(IValue*) = 0;
        virtual const IValue* getValue(int) = 0;
        virtual const int getDomainSize() = 0;
};

#endif //SI_LAB_2_IDOMAIN_H
