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
        IValue(int value) :
            value(value)
        { }

        virtual ~IValue() {}

        virtual IValue* deepCopy() const = 0;
        virtual const int getValue() const = 0;
};

#endif //SI_LAB_2_IVALUE_H