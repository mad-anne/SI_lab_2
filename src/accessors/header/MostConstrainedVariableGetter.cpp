//
// Created by Anna Siwik on 18.04.2017.
//

#include <set>
#include "MostConstrainedVariableGetter.h"

MostConstrainedVariableGetter::MostConstrainedVariableGetter(IProblem* problem) :
    IVariableGetter(problem)
{}

MostConstrainedVariableGetter::~MostConstrainedVariableGetter()
{}

IVariable* MostConstrainedVariableGetter::getNext()
{
    unsigned long int smallestDomain = problem->getDomain()->getSize() + 1;
    int maxConnectedConstraints = 0;
    IVariable* mostConstrained = nullptr;
    IVariable* tempVar = nullptr;

    int width = problem->getWidth();
    for (int row = 0; row < width; ++row)
    {
        for (int col = 0; col < width; ++col)
        {
            tempVar = problem->getVariable(row, col);

            if (tempVar->getValue() == nullptr)
            {
                if (mostConstrained == nullptr || tempVar->getDomain()->getSize() < smallestDomain
                    || getNumberOfNeighboursConstraints(tempVar) > maxConnectedConstraints)
                {
                    mostConstrained = tempVar;
                    smallestDomain = tempVar->getDomain()->getSize();
                    maxConnectedConstraints = getNumberOfNeighboursConstraints(tempVar);
                }
            }
        }
    }

    return mostConstrained;
}

void MostConstrainedVariableGetter::setProblem(const IProblem* problem)
{
    this->problem = problem;
}

const IProblem *MostConstrainedVariableGetter::getProblem() const
{
    return problem;
}

int MostConstrainedVariableGetter::getNumberOfNeighboursConstraints(IVariable* variable)
{
    int numberOfConstraints = 0;
    std::set<const IValue*> neighbours;

    IVariable* varLeft = problem->getVariable(variable->getRow(), variable->getColumn() - 1);
    IVariable* varUp = problem->getVariable(variable->getRow() - 1, variable->getColumn());
    IVariable* varRight = problem->getVariable(variable->getRow(), variable->getColumn() + 1);
    IVariable* varDown = problem->getVariable(variable->getRow() + 1, variable->getColumn());

    if (varLeft != nullptr && varLeft->getValue() != nullptr)
        neighbours.insert(varLeft->getValue());

    if (varUp != nullptr && varUp->getValue() != nullptr)
        neighbours.insert(varUp->getValue());

    if (varRight != nullptr && varRight->getValue() != nullptr)
        neighbours.insert(varRight->getValue());

    if (varDown != nullptr && varDown->getValue() != nullptr)
        neighbours.insert(varDown->getValue());

    std::set<const IValue*>::const_iterator it;
    for (it = neighbours.begin(); it != neighbours.end(); ++it)
        numberOfConstraints += (*it)->getNumberOfConnectedConstraints();

    return numberOfConstraints;
}
