//
// Created by Anna Siwik on 18.04.2017.
//

#ifndef SI_LAB_2_MOSTFILLEDCROSSINGVARIABLEGETTER_H
#define SI_LAB_2_MOSTFILLEDCROSSINGVARIABLEGETTER_H


#include <accessors/interface/IVariableGetter.h>

class MostFilledCrossingVariableGetter : public IVariableGetter
{
    public:
        MostFilledCrossingVariableGetter(const IProblem*);
        ~MostFilledCrossingVariableGetter() override;

        IVariable* getNext() override;

        void setProblem(const IProblem*) override;
        const IProblem* getProblem() const override;

    private:
        int countNullsOnCrossing(IVariable *pVariable);
};


#endif //SI_LAB_2_MOSTFILLEDCROSSINGVARIABLEGETTER_H
