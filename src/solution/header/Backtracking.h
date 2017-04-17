//
// Created by Anna Siwik on 2017-04-08.
//

#ifndef SI_LAB_2_BACKTRACKING_H
#define SI_LAB_2_BACKTRACKING_H

#include "../interface/IConstraintSatisfactionProblem.h"
#include "constraints/interface/IConstraintChecker.h"
#include "../../accessors/interface/IVariableGetter.h"

class Backtracking : public IConstraintSatisfactionProblem
{
    public:
        Backtracking();
        virtual ~Backtracking();

        virtual const ISolution* getFirstSolution(IProblemFactory*) override;
        virtual long long int getNumberOfSolutions(IProblemFactory*) override;
        virtual std::vector<ISolution*>* getAllSolutions(IProblemFactory*) override;

    private:
        ISolution* recursive();
        void recursiveFindAll();
        void recursiveFindNumberOfAll();
        void setAttributes(IProblemFactory*);
};

#endif //SI_LAB_2_BACKTRACKING_H
