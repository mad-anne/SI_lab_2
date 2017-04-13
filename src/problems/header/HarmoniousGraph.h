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

        const IVariable* getVariable(int row, int column) override;
        const IVariable* setVariableValue(int row, int column, IValue* value) override;
        const IValue* setVariableValue(const IVariable*, const IValue*) override;
        bool checkConstraints() const override;

        bool isComplete() const override;
        IVariable* getUnassignedVariable() const override;

private:
        void generateEmptyGraph();
        void generateDomain();
        void removeGraph();
};

#endif //SI_LAB_2_HARMONIOUSGRAPH_H
