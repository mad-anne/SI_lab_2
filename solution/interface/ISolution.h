//
// Created by Dom on 2017-04-08.
//

#ifndef SI_LAB_2_ISOLUTION_H
#define SI_LAB_2_ISOLUTION_H

#include "../../problems/interface/IProblem.h"

class ISolution
{
    protected:
        IProblem* solution;

    public:
        virtual ~ISolution() { if (solution != nullptr) delete solution; }

        virtual void printHarmoniousGraph() = 0;
        virtual void printBinaryGame() = 0;
};

#endif //SI_LAB_2_ISOLUTION_H
