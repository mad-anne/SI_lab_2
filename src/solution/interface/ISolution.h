//
// Created by Anna Siwik on 2017-04-08.
//

#ifndef SI_LAB_2_ISOLUTION_H
#define SI_LAB_2_ISOLUTION_H

#include <stdlib.h>
#include "../../problems/interface/IProblem.h"

class ISolution
{
    protected:
        int** solution;
        int width;

    public:
        ISolution(int width) : width(width) {}
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

        virtual int getWidth() const
        {
            return width;
        }

        virtual int getValue(int row, int col) const
        {
            return (row >= 0 && row <= width && col >= 0 && col <= width)
                   ? solution[row][col]
                   : -1;
        }

        virtual int setValue(int row, int col, int value)
        {
            if (row >= 0 && row <= width && col >= 0 && col <= width)
                solution[row][col] = value;
        }

        virtual resetRandomValues(int emptyFields)
        {
            while (emptyFields > 0)
            {
                int randRow = rand() % width;
                int randCol = rand() % width;

                if (solution[randRow][randCol] != -1)
                {
                    setValue(randRow, randCol, -1);
                    --emptyFields;
                }
            }
        }
};

#endif //SI_LAB_2_ISOLUTION_H
