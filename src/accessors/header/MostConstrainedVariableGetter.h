//
// Created by Anna Siwik on 18.04.2017.
//

#ifndef SI_LAB_2_MOSTCONSTRAINTEDVARIABLEGETTER_H
#define SI_LAB_2_MOSTCONSTRAINTEDVARIABLEGETTER_H


#include <accessors/interface/IVariableGetter.h>

class MostConstrainedVariableGetter : public IVariableGetter
{
    public:
        MostConstrainedVariableGetter(IProblem*);
        ~MostConstrainedVariableGetter();

        IVariable* getNext() override;

        void setProblem(const IProblem*) override;
        const IProblem* getProblem() const override;

        int getNumberOfNeighboursConstraints(IVariable *pVariable);
};


#endif //SI_LAB_2_MOSTCONSTRAINTEDVARIABLEGETTER_H
