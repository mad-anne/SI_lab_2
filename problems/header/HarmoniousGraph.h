//
// Created by Anna Siwik on 2017-04-07.
//

#ifndef SI_LAB_2_HARMONIOUSGRAPH_H
#define SI_LAB_2_HARMONIOUSGRAPH_H

#include <memory>
#include "../interface/IProblem.h"

class HarmoniousGraph : public IProblem
{
<<<<<<< HEAD
    int colors;
    IVariable*** nodes;
=======
    int width;
    int colors;
    IVariable** nodes;
>>>>>>> 8e927268749581ebfa7dbdd3c68afe7a0c154d50

    public:
        HarmoniousGraph(int width);
        ~HarmoniousGraph();

        const IVariable* getVariable(int row, int column) override;
        const IVariable* setVariableValue(int row, int column, IValue* value) override;

<<<<<<< HEAD
    private:
=======
private:
>>>>>>> 8e927268749581ebfa7dbdd3c68afe7a0c154d50
        void generateEmptyGraph();
        void removeGraph();
};

#endif //SI_LAB_2_HARMONIOUSGRAPH_H
