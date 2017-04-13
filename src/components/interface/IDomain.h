//
// Created by Anna Siwik on 2017-04-08.
//

#ifndef SI_LAB_2_IDOMAIN_H
#define SI_LAB_2_IDOMAIN_H

#include <vector>
#include "IValue.h"

class IDomain
{
    protected:
        std::vector<const IValue*> values;

    public:
        IDomain() {}
        IDomain(const IDomain* domain)
        {
            for (int i = 0; i < domain->getDomainSize(); ++i)
                this->values.push_back(domain->getValue(i)->deepCopy());
        }

        virtual ~IDomain() = default;

        virtual void addValue(const IValue*) = 0;
        virtual const IValue* getValue(int) const = 0;
        virtual const unsigned long int getDomainSize() const = 0;
};

#endif //SI_LAB_2_IDOMAIN_H
