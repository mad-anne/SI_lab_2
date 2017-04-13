//
// Created by Anna Siwik on 2017-04-07.
//

#ifndef SI_LAB_2_COLOR_H
#define SI_LAB_2_COLOR_H

#include "../interface/IValue.h"

class Color : public IValue
{
    public:
        Color();
        Color(int);
        ~Color();

        IValue* deepCopy() const override;
        const int getValue() const override;
        const int setValue(int) override;
        const int resetValue() override;
};

#endif //SI_LAB_2_COLOR_H
