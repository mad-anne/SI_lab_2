//
// Created by Anna Siwik on 2017-04-08.
//

#ifndef SI_LAB_2_BACKTRACKING_H
#define SI_LAB_2_BACKTRACKING_H

#include "../interface/IConstraintSatisfactionProblem.h"
#include "../../constraints/interface/IConstraint.h"
#include "../../accessors/interface/IVariableGetter.h"

class Backtracking : public IConstraintSatisfactionProblem
{
    public:
        Backtracking();
        virtual ~Backtracking();

        virtual const ISolution* getFirstSolution(IProblemFactory*) override;
        virtual int getNumberOfSolutions(IProblemFactory*) override;
        virtual std::vector<ISolution*>* getAllSolutions(IProblemFactory*) override;

    private:
        void recursive();
        void setAttributes(IProblemFactory*);
};

#endif //SI_LAB_2_BACKTRACKING_H
