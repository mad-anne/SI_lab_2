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
            : width(width),
              domain(new MainDomain())
        {}

        virtual ~IProblem()
        {
            delete domain;
        }

        virtual IProblem* deepCopy() const = 0;

        virtual IVariable* getVariable(int row, int column) const = 0;

        virtual const int getWidth() const
        {
            return width;
        }

        virtual const IDomain* getDomain() const
        {
            return domain;
        }

        virtual void resetAllDomains() = 0;
        virtual void resetAllVariables() = 0;

        virtual bool isCompleted() const = 0;
};

#endif //SI_LAB_2_IGRAPH_H
