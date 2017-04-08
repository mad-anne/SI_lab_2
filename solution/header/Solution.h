//
// Created by Anna Siwik on 2017-04-08.
//

#ifndef SI_LAB_2_SOLUTION_H
#define SI_LAB_2_SOLUTION_H

#include "../interface/ISolution.h"

class Solution : public ISolution
{
    public:
        Solution();
        Solution(IProblem*);
        ~Solution();

        void printHarmoniousGraph() override;
        void printBinaryGame() override;
        void setSolution(IProblem* problem) override;
};

#endif //SI_LAB_2_SOLUTION_H
