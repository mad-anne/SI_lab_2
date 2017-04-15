//
// Created by Anna Siwik on 2017-04-14.
//

#ifndef SI_LAB_2_NEXTVARIABLEGETTER_H
#define SI_LAB_2_NEXTVARIABLEGETTER_H

#include <accessors/interface/IVariableGetter.h>

class NextVariableGetter : public IVariableGetter
{
    public:
        NextVariableGetter(const IProblem*);
        ~NextVariableGetter();

        IVariable* getNext() override;

        void setProblem(const IProblem*) override;
        const IProblem* getProblem() const override;

    private:
        IVariable* findUnassignedVariable();
};

#endif //SI_LAB_2_NEXTVARIABLEGETTER_H
