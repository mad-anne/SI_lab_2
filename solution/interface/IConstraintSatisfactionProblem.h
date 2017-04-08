//
// Created by Anna Siwik on 2017-04-07.
//

#ifndef SI_LAB_2_ICONSTRAINTSATISFACTIONPROBLEM_H
#define SI_LAB_2_ICONSTRAINTSATISFACTIONPROBLEM_H

#include <vector>
<<<<<<< HEAD
#include <memory>
=======
>>>>>>> 8e927268749581ebfa7dbdd3c68afe7a0c154d50
#include "ISolution.h"
#include "../../problems/interface/IProblem.h"

class IConstraintSatisfactionProblem
{
    protected:
        IProblem* problem;
<<<<<<< HEAD

    public:
        virtual ~IConstraintSatisfactionProblem() {}

        virtual std::unique_ptr<ISolution> solveProblem(IProblem*) = 0;
=======

    public:
        virtual void solveProblem(IProblem*) = 0;
>>>>>>> 8e927268749581ebfa7dbdd3c68afe7a0c154d50
};

#endif //SI_LAB_2_ICONSTRAINTSATISFACTIONPROBLEM_H
