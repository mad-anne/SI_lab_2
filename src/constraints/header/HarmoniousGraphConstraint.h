//
// Created by Anna Siwik on 2017-04-13.
//

#ifndef SI_LAB_2_HARMONIOUSGRAPHCONSTRAINT_H
#define SI_LAB_2_HARMONIOUSGRAPHCONSTRAINT_H

#include <constraints/interface/IConstraint.h>

class HarmoniousGraphConstraint : public IConstraint
{
    public:
        HarmoniousGraphConstraint(IProblem*);
        ~HarmoniousGraphConstraint();

        const bool checkConstraints() const override;
        void setProblem(IProblem *problem) override;
};

#endif //SI_LAB_2_HARMONIOUSGRAPHCONSTRAINT_H
