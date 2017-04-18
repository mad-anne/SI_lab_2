//
// Created by Anna Siwik on 18.04.2017.
//

#include <constraints/header/Row.h>
#include <constraints/header/Column.h>
#include "accessors/header/MostFilledCrossingVariableGetter.h"

MostFilledCrossingVariableGetter::MostFilledCrossingVariableGetter(const IProblem* problem) :
        IVariableGetter(problem)
{}

MostFilledCrossingVariableGetter::~MostFilledCrossingVariableGetter()
{}

IVariable* MostFilledCrossingVariableGetter::getNext()
{
    int tempNulls;
    int minNulls = problem->getWidth() + 1;
    IVariable* mostFilled = nullptr;
    IVariable* tempVar = nullptr;

    int width = problem->getWidth();
    for (int row = 0; row < width; ++row)
    {
        for (int col = 0; col < width; ++col)
        {
            tempVar = problem->getVariable(row, col);

            if (tempVar->getValue() == nullptr
                && (mostFilled == nullptr || (tempNulls = countNullsOnCrossing(tempVar)) < minNulls))
            {
                minNulls = tempNulls;
                mostFilled = tempVar;
            }
        }
    }

    return mostFilled;
}

void MostFilledCrossingVariableGetter::setProblem(const IProblem* problem)
{
    this->problem = problem;
}

const IProblem *MostFilledCrossingVariableGetter::getProblem() const
{
    return problem;
}

int MostFilledCrossingVariableGetter::countNullsOnCrossing(IVariable* variable)
{
    Row r(problem, variable);
    Column c(problem, variable);

    return r.countValue(nullptr) + c.countValue(nullptr)
           + (variable->getValue() == nullptr ? -1 : 0);
}
