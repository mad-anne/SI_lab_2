//
// Created by Anna Siwik on 2017-04-08.
//

#ifndef SI_LAB_2_SOLUTION_H
#define SI_LAB_2_SOLUTION_H

#include "../interface/ISolution.h"

class Solution : public ISolution
{
    public:
        Solution(IProblem*);
        ~Solution();

        void print() const override;

    private:
        void readProblem(IProblem*);
};

#endif //SI_LAB_2_SOLUTION_H
