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

<<<<<<< HEAD
    public:
        std::unique_ptr<ISolution> solveProblem(IProblem* problem) override;
=======
    private:
        void solveProblem(IProblem* problem) override;
>>>>>>> 8e927268749581ebfa7dbdd3c68afe7a0c154d50
};

#endif //SI_LAB_2_BACKTRACKING_H
