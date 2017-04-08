//
// Created by Anna Siwik on 2017-04-08.
//

#ifndef SI_LAB_2_DOMAIN_H
#define SI_LAB_2_DOMAIN_H

#include "../interface/IDomain.h"

class Domain : public IDomain
{
    public:
        Domain();

    void addValue(IValue* value) override;
    const IValue* getValue(int) override;
    const int getDomainSize() override;
};

#endif //SI_LAB_2_DOMAIN_H
