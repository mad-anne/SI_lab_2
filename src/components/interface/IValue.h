//
// Created by Anna Siwik on 2017-04-07.
//

#ifndef SI_LAB_2_IVALUE_H
#define SI_LAB_2_IVALUE_H

class IValue
{
    protected:
        int value;
        int connectedConstraints;
        int assignments;

    public:
        IValue(int value) :
            value(value),
            connectedConstraints(0),
            assignments(0)
        { }

        virtual ~IValue() {}

        virtual IValue* deepCopy() const = 0;
        virtual const int getValue() const = 0;

        virtual int getNumberOfConnectedConstraints() const
        {
            return connectedConstraints;
        }

        virtual int incrementConnectedConstraints()
        {
            return ++connectedConstraints;
        }

        virtual int decrementConnectedConstraints()
        {
            return --connectedConstraints;
        }

        virtual int getNumberOfAssignments() const
        {
            return assignments;
        }

        virtual int incrementAssignments()
        {
            return ++assignments;
        }

        virtual int decrementAssignments()
        {
            return --assignments;
        }
};

#endif //SI_LAB_2_IVALUE_H