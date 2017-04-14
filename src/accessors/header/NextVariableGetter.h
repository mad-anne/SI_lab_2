//
// Created by Anna Siwik on 2017-04-14.
//

#ifndef SI_LAB_2_NEXTVARIABLEGETTER_H
#define SI_LAB_2_NEXTVARIABLEGETTER_H

#include <accessors/interface/IVariableGetter.h>

class NextVariableGetter : public IVariableGetter
{
    public:
        NextVariableGetter(const IProblem *problem);
        ~NextVariableGetter();

        const IVariable* getNext() override;

        void setProblem(const IProblem* problem) override;
        const IProblem *getProblem() override;

    private:
        const IVariable* findUnassignedVariable();
};

#endif //SI_LAB_2_NEXTVARIABLEGETTER_H
