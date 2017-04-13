//
// Created by Anna Siwik on 2017-04-13.
//

#include <problems/interface/IProblem.h>
#include <constraints/header/HarmoniousGraphConstraint.h>

HarmoniousGraphConstraint::HarmoniousGraphConstraint(IProblem* problem)
        : IConstraint(problem)
{}

HarmoniousGraphConstraint::~HarmoniousGraphConstraint()
{
    for (int i = 0; i < connections.size(); ++i)
        delete connections[i];

    connections.clear();
}

const bool HarmoniousGraphConstraint::checkConstraints()
{
    bool isCorrect = true;
    int width = problem->getWidth();

    for (int i = 0; isCorrect && i < width; ++i)
    {
        for (int j = 0; isCorrect && j < width; ++j)
        {
            if (! checkNeighbours(i, j) || ! checkConnection(i, j))
                isCorrect = false;
        }
    }

    return isCorrect;
}

const bool HarmoniousGraphConstraint::checkConstraints(int row, int col)
{
    return checkConstraints();
}

void HarmoniousGraphConstraint::setProblem(IProblem* problem)
{
    this->problem = problem;
}

const bool HarmoniousGraphConstraint::checkNeighbours(int row, int col) const
{
    int width = problem->getWidth();
    const IValue* valueObj = problem->getVariable(row, col)->getValue();

    if (valueObj == nullptr)
        return true;

    const int value = valueObj->getValue();

    const IValue* valueLeft = nullptr;
    const IValue* valueRight = nullptr;
    const IValue* valueUp = nullptr;
    const IValue* valueDown = nullptr;

    if (col > 0)
        valueLeft = problem->getVariable(row, col - 1)->getValue();

    if (col < width - 1)
        valueRight = problem->getVariable(row, col + 1)->getValue();

    if (row > 0)
        valueUp = problem->getVariable(row - 1, col)->getValue();

    if (row < width - 1)
        valueDown = problem->getVariable(row + 1, col)->getValue();

    return  (valueLeft != nullptr ? valueLeft->getValue() != value : true)
            && (valueRight != nullptr ? valueRight->getValue() != value : true)
            && (valueUp != nullptr ? valueUp->getValue() != value : true)
            && (valueDown != nullptr ? valueDown->getValue() != value : true);
}

const bool HarmoniousGraphConstraint::checkConnection(int row, int col)
{
    int width = problem->getWidth();
    const IValue* value = problem->getVariable(row, col)->getValue();

    if (value == nullptr)
        return true;

    bool correctConnection = false;

    const IValue* valueLeft = nullptr;
    const IValue* valueRight = nullptr;
    const IValue* valueUp = nullptr;
    const IValue* valueDown = nullptr;

    if (col > 0)
        valueLeft = problem->getVariable(row, col - 1)->getValue();

    if (col < width - 1)
        valueRight = problem->getVariable(row, col + 1)->getValue();

    if (row > 0)
        valueUp = problem->getVariable(row - 1, col)->getValue();

    if (row < width - 1)
        valueDown = problem->getVariable(row + 1, col)->getValue();

    if (! existsConnection(value, valueLeft)
        && ! existsConnection(value, valueRight)
        && ! existsConnection(value, valueUp)
        && ! existsConnection(value, valueDown))
    {
        correctConnection = true;

        if (valueLeft != nullptr)
            connections.push_back(new Connection(value, valueLeft));

        if (valueRight != nullptr)
            connections.push_back(new Connection(value, valueRight));

        if (valueUp != nullptr)
            connections.push_back(new Connection(value, valueUp));

        if (valueDown != nullptr)
            connections.push_back(new Connection(value, valueDown));
    }

    return correctConnection;
}

const bool HarmoniousGraphConstraint::existsConnection(const IValue* value, const IValue* neighbour) const
{
    if (value == nullptr || neighbour == nullptr)
        return false;

    bool exists = false;

    for (unsigned long int i = 0; ! exists && i < connections.size(); ++i)
    {
        const IValue* first = connections[i]->getFirstValue();
        const IValue* second = connections[i]->getSecondValue();

        if (value == first && neighbour == second)
            exists = true;
    }

    return exists;
}