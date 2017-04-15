//
// Created by Anna Siwik on 2017-04-15.
//

#ifndef SI_LAB_2_NUMBER_H
#define SI_LAB_2_NUMBER_H

#include <components/interface/IValue.h>

class Number : public IValue
{
    public:
        Number();
        Number(int);
        ~Number();

        IValue* deepCopy() const override;
        const int getValue() const override;
};


#endif //SI_LAB_2_NUMBER_H
