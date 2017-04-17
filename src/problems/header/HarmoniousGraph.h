//
// Created by Anna Siwik on 2017-04-07.
//

#ifndef SI_LAB_2_HARMONIOUSGRAPH_H
#define SI_LAB_2_HARMONIOUSGRAPH_H

#include <memory>
#include "../interface/IProblem.h"

class HarmoniousGraph : public IProblem
{
    int colors;
    IVariable*** nodes;

    public:
        HarmoniousGraph(int width);
        ~HarmoniousGraph();

        IProblem* deepCopy() const;
        IVariable* getVariable(int row, int column) const override;
        void resetAllDomains();

    private:
        void generateEmptyGraph();
        void fillDomainWithValues();
        void removeGraph();
};

#endif //SI_LAB_2_HARMONIOUSGRAPH_H
