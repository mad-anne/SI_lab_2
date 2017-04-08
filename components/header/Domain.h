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
<<<<<<< HEAD
        ~Domain();

        void addValue(IValue* value) override;
        const IValue* getValue(int) override;
        const int getDomainSize() override;
=======

    void addValue(IValue* value) override;
    const IValue* getValue(int) override;
    const int getDomainSize() override;
>>>>>>> 8e927268749581ebfa7dbdd3c68afe7a0c154d50
};

#endif //SI_LAB_2_DOMAIN_H
