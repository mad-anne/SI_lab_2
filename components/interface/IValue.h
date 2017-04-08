//
// Created by Anna Siwik on 2017-04-07.
//

#ifndef SI_LAB_2_IVALUE_H
#define SI_LAB_2_IVALUE_H

class IValue
{
<<<<<<< HEAD
    protected:
        int value;

    public:
        virtual ~IValue() {}

        virtual const int getValue() const = 0;
        virtual const int setValue(int) = 0;
        virtual const int resetValue() = 0;
=======
    int value;

    public:
        virtual int getValue() = 0;
        virtual int setValue(int) = 0;
        virtual int resetValue() = 0;
>>>>>>> 8e927268749581ebfa7dbdd3c68afe7a0c154d50
};

#endif //SI_LAB_2_IVALUE_H