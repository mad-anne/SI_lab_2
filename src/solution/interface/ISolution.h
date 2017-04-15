//
// Created by Anna Siwik on 2017-04-08.
//

#ifndef SI_LAB_2_ISOLUTION_H
#define SI_LAB_2_ISOLUTION_H

#include "../../problems/interface/IProblem.h"

class ISolution
{
    protected:
        int** solution;
        int width;

    public:
        ISolution() {}
        virtual ~ISolution()
        {
            if (solution != nullptr && width > 0)
            {
                for (int row = 0; row < width; ++row)
                    delete[] solution[row];

                delete[] solution;
            }
        }

        virtual void print() const = 0;
};

#endif //SI_LAB_2_ISOLUTION_H
