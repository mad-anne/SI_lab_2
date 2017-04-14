//
// Created by Anna Siwik on 2017-04-07.
//

#ifndef SI_LAB_2_IVARIABLE_H
#define SI_LAB_2_IVARIABLE_H

#include "IValue.h"
#include "IDomain.h"
#include "../header/Domain.h"

class IVariable
{
    protected:
        int row;
        int col;
        const IValue* value;
        IDomain* domain;

    public:
        IVariable(int row, int col)
                : row(row),
                  col(col),
                  value(nullptr),
                  domain(new Domain())

        {}
        virtual ~IVariable()
        {
            delete domain;
        }

        virtual void setValue(const IValue*) = 0;
        virtual const IValue* getValue() const = 0;
        virtual void resetValue() = 0;

        virtual const IDomain* getDomain() const = 0;
        virtual void addDomain(const IDomain*) = 0;
        virtual void addValueToDomain(const IValue*) = 0;
        virtual void removeValueFromDomain(const IValue*) = 0;

        virtual const int getRow() const = 0;
        virtual const int getColumn() const = 0;
};

#endif //SI_LAB_2_IVARIABLE_H
