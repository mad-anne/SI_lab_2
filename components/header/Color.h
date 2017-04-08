//
// Created by Anna Siwik on 2017-04-07.
//

#ifndef SI_LAB_2_COLOR_H
#define SI_LAB_2_COLOR_H

#include "../interface/IValue.h"

class Color : public IValue
{
<<<<<<< HEAD
    public:
        Color();
        ~Color();

        const int getValue() const override;
        const int setValue(int) override;
        const int resetValue() override;
=======
    int value;

    public:
        Color();

        int getValue() override;
        int setValue(int) override;
        int resetValue() override;
>>>>>>> 8e927268749581ebfa7dbdd3c68afe7a0c154d50
};

#endif //SI_LAB_2_COLOR_H
