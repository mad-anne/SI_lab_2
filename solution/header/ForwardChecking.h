//
// Created by Dom on 2017-04-08.
//

#ifndef SI_LAB_2_FORWARDCHECKING_H
#define SI_LAB_2_FORWARDCHECKING_H

#include "../interface/IConstraintSatisfactionProblem.h"

class ForwardChecking : public IConstraintSatisfactionProblem
{
    public:
        ForwardChecking();
        ~ForwardChecking();

    private:
        void solveProblem(IProblem* problem) override;
};


#endif //SI_LAB_2_FORWARDCHECKING_H
