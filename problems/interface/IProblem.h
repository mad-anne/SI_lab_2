//
// Created by Anna Siwik on 2017-04-07.
//

#ifndef SI_LAB_2_IGRAPH_H
#define SI_LAB_2_IGRAPH_H

#include "../../components/interface/IVariable.h"

class IProblem
{
    protected:
        int width;

    public:
        IProblem(int width)
        {
            this->width = width;
        }

        virtual ~IProblem() {}

        virtual const IVariable* getVariable(int row, int column) = 0;
        virtual const IVariable* setVariableValue(int row, int column, IValue* value) = 0;

        virtual const int getWidth()
        {
            return width;
        }
};

#endif //SI_LAB_2_IGRAPH_H
