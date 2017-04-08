//
// Created by Dom on 2017-04-08.
//

#ifndef SI_LAB_2_BACKTRACKING_H
#define SI_LAB_2_BACKTRACKING_H

#include "../interface/IConstraintSatisfactionProblem.h"

class Backtracking : public IConstraintSatisfactionProblem
{
    public:
        Backtracking();
        ~Backtracking();

    public:
        std::unique_ptr<ISolution> solveProblem(IProblem* problem) override;
};

#endif //SI_LAB_2_BACKTRACKING_H
