//
// Created by Anna Siwik on 2017-04-15.
//

#ifndef SI_LAB_2_BINARYGAMECONSTRAINT_H
#define SI_LAB_2_BINARYGAMECONSTRAINT_H


#include <constraints/interface/IConstraintChecker.h>
#include "../interface/IRow.h"

class BinaryGameConstraintChecker : public IConstraintChecker
{
    IConstraint* pairConstraint;
    IConstraint* existingRowConstraint;
    IConstraint* equalSplitConstraint;

    public:
        BinaryGameConstraintChecker(IProblem*);
        ~BinaryGameConstraintChecker() override;

        bool isCorrectAssignment(const IVariable*) const override;

        const void putConstraintsOn(const IVariable*, bool limitDomains) override;
        const void putConstraintsOff(const IVariable*, bool limitDomains) override;
};


#endif //SI_LAB_2_BINARYGAMECONSTRAINT_H
