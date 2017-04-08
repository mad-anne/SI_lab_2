//
// Created by Anna Siwik on 2017-04-07.
//

#ifndef SI_LAB_2_IVALUE_H
#define SI_LAB_2_IVALUE_H

class IValue
{
    protected:
        int value;

    public:
        virtual ~IValue() {}

        virtual int getValue() = 0;
        virtual int setValue(int) = 0;
        virtual int resetValue() = 0;
};

#endif //SI_LAB_2_IVALUE_H