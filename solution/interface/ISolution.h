//
// Created by Dom on 2017-04-08.
//

#ifndef SI_LAB_2_ISOLUTION_H
#define SI_LAB_2_ISOLUTION_H

<<<<<<< HEAD
#include "../../problems/interface/IProblem.h"

class ISolution
{
    protected:
        IProblem* solution;

    public:
        virtual ~ISolution() { if (solution != nullptr) delete solution; }

        virtual void printHarmoniousGraph() = 0;
        virtual void printBinaryGame() = 0;
        virtual void setSolution(IProblem*) = 0;
=======
class ISolution
{

>>>>>>> 8e927268749581ebfa7dbdd3c68afe7a0c154d50
};

#endif //SI_LAB_2_ISOLUTION_H
