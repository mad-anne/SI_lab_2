//
// Created by Anna Siwik on 2017-04-07.
//

#ifndef SI_LAB_2_IGRAPH_H
#define SI_LAB_2_IGRAPH_H

#include "../../components/interface/IVariable.h"
#include "../../components/header/MainDomain.h"

class IProblem
{
    protected:
        int width;
        IDomain* domain;

    public:
        IProblem(int width)
        {
            this->width = width;
            domain = new MainDomain();
        }

        virtual ~IProblem()
        {
            delete domain;
        }

        virtual IProblem* deepCopy() const = 0;
        virtual bool isComplete() const = 0;
        virtual IVariable* getUnassignedVariable() const = 0;
        virtual bool checkConstraints() const = 0;

        virtual const IVariable* getVariable(int row, int column) const = 0;
        virtual const IVariable* setVariableValue(int row, int column, const IValue* value) = 0;
        virtual const IValue* setVariableValue(const IVariable*, const IValue*) = 0;

        virtual const int getWidth() const
        {
            return width;
        }

        virtual const IDomain* getDomain()
        {
            return domain;
        }
};

#endif //SI_LAB_2_IGRAPH_H
