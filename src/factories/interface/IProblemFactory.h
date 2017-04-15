//
// Created by Dom on 2017-04-15.
//

#ifndef SI_LAB_2_IPROBLEMFACTORY_H
#define SI_LAB_2_IPROBLEMFACTORY_H

#include <problems/interface/IProblem.h>
#include <constraints/interface/IConstraint.h>
#include <accessors/interface/IValueGetter.h>
#include <accessors/interface/IVariableGetter.h>

class IProblemFactory
{
    protected:
        IProblem* problem;
        IConstraint* constraint;
        IVariableGetter* varGetter;
        IValueGetter* valGetter;

    public:

        virtual ~IProblemFactory() = default;

        virtual IProblem* getProblem() const = 0;
        virtual IConstraint* getConstraint() const = 0;
        virtual IVariableGetter* getVariableGetter() const = 0;
        virtual IValueGetter* getValueGetter() const = 0;
};

#endif //SI_LAB_2_IPROBLEMFACTORY_H
