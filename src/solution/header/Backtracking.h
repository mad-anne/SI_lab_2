//
// Created by Anna on 2017-04-08.
//

#ifndef SI_LAB_2_BACKTRACKING_H
#define SI_LAB_2_BACKTRACKING_H

#include "../interface/IConstraintSatisfactionProblem.h"

class Backtracking : public IConstraintSatisfactionProblem
{
    public:
        Backtracking();
        ~Backtracking();

        std::vector<ISolution*>* solveProblem(IProblem*) override;

    private:
        std::vector<ISolution*>* recursive(IProblem*);
};

#endif //SI_LAB_2_BACKTRACKING_H
