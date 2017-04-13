//
// Created by Anna Siwik on 2017-04-13.
//

#ifndef SI_LAB_2_MAINDOMAIN_H
#define SI_LAB_2_MAINDOMAIN_H

#include "Domain.h"

class MainDomain : public Domain
{
    public:
        MainDomain();
        ~MainDomain();

    private:
        void clearValues();
};

#endif //SI_LAB_2_MAINDOMAIN_H
