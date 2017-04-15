//
// Created by Anna Siwik on 2017-04-14.
//

#include <problems/interface/IProblem.h>
#include <accessors/header/NextVariableGetter.h>

NextVariableGetter::NextVariableGetter(const IProblem* problem)
        : IVariableGetter(problem)
{}

NextVariableGetter::~NextVariableGetter()
{}

IVariable* NextVariableGetter::getNext()
{
    return findUnassignedVariable();
}

void NextVariableGetter::setProblem(const IProblem* problem)
{
    this->problem = problem;
}

const IProblem* NextVariableGetter::getProblem() const
{
    return problem;
}

IVariable* NextVariableGetter::findUnassignedVariable()
{
    IVariable* unassignedVar = nullptr;
    int width = problem->getWidth();

    for (int row = 0; unassignedVar == nullptr && row < width; ++row)
    {
        for (int col = 0; unassignedVar == nullptr && col < width; ++col)
        {
            if (problem->getVariable(row, col)->getValue() == nullptr)
                unassignedVar = problem->getVariable(row, col);
        }
    }

    return unassignedVar;
}