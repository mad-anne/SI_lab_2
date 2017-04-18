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
        ~Domain();

        void addValue(IValue* value) override;
        void removeValue(const IValue*) override;
        IValue* getValue(int) const override;
        const unsigned long int getSize() const override;

    private:
        bool hasValue(const IValue*) const;
};

#endif //SI_LAB_2_DOMAIN_H
