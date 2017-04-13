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
        IValue() :
            value(-1)
        { }

        IValue(int value) :
            value(value)
        { }
        virtual ~IValue() {}

        virtual IValue* deepCopy() const = 0;
        virtual const int getValue() const = 0;
        virtual const int setValue(int) = 0;
        virtual const int resetValue() = 0;
};

#endif //SI_LAB_2_IVALUE_H