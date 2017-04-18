//
// Created by Anna Siwik on 2017-04-14.
//


#include <components/interface/IVariable.h>

#ifndef SI_LAB_2_IVALUEGETTER_H
#define SI_LAB_2_IVALUEGETTER_H

class IValueGetter
{
    protected:
        const IVariable* variable;

    private:
        IValueGetter() {}

    public:
        IValueGetter(const IVariable* variable)
                : variable(variable)
        {}

        virtual ~IValueGetter() = default;

        virtual IValueGetter* instantiate(const IVariable*) const = 0;

        virtual IValue* getNext() = 0;

        virtual void setVariable(const IVariable*) = 0;
        virtual const IVariable* getVariable() const = 0;

};

#endif //SI_LAB_2_IVALUEGETTER_H

