//
// Created by Anna Siwik on 2017-04-07.
//

#ifndef SI_LAB_2_COLOR_H
#define SI_LAB_2_COLOR_H

#include "../interface/IValue.h"

class Color : public IValue
{
    int value;

    public:
        Color();

        int getValue() override;
        int setValue(int) override;
        int resetValue() override;
};

#endif //SI_LAB_2_COLOR_H
