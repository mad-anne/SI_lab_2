//
// Created by Anna Siwik on 2017-04-14.
//

#ifndef SI_LAB_2_IVARIABLEGETTER_H
#define SI_LAB_2_IVARIABLEGETTER_H

#include <problems/interface/IProblem.h>

class IVariableGetter
{
    protected:
        const IProblem* problem;

    private:
        IVariableGetter() {};

    public:
        IVariableGetter(const IProblem* problem)
                : problem(problem)
        {}
        virtual ~IVariableGetter() = default;

        virtual const IVariable* getNext() = 0;
    
        virtual void setProblem(const IProblem* problem) = 0;
        virtual const IProblem* getProblem() = 0;
};

#endif //SI_LAB_2_IVARIABLEGETTER_H
