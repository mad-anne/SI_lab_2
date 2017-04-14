//
// Created by Anna Siwik on 2017-04-07.
//

#include "../header/HarmoniousGraph.h"
#include "../../components/header/Node.h"
#include "../../components/header/Color.h"

HarmoniousGraph::HarmoniousGraph(int width) :
    IProblem(width),
    colors(2 * width + (width % 2 == 1 ? 1 : 0))
{
    generateDomain();
    generateEmptyGraph();
}

HarmoniousGraph::~HarmoniousGraph()
{
    removeGraph();
}

IProblem* HarmoniousGraph::deepCopy() const
{
    IProblem* copy = new HarmoniousGraph(width);
    const IDomain* domain = copy->getDomain();

    for (int row = 0; row < width; ++row)
    {
        for (int col = 0; col < width; ++col)
        {
            int index = nodes[row][col]->getValue()->getValue();
            const IValue* value = domain->getValue(index);
            copy->setVariableValue(row, col, value);
        }
    }

    return copy;
}

void HarmoniousGraph::generateDomain()
{
    for (int i = 0; i < colors; ++i)
        domain->addValue(new Color(i));
}

void HarmoniousGraph::generateEmptyGraph()
{
    nodes = new IVariable**[width];

    for (int row = 0; row < width; ++row)
        nodes[row] = new IVariable*[width];

    for (int row = 0; row < width; ++row)
    {
        for (int col = 0; col < width; ++col)
        {
            nodes[row][col] = new Node(row, col);
            nodes[row][col]->addDomain(domain);
        }
    }
}

void HarmoniousGraph::removeGraph()
{
    for (int row = 0; row < width; ++row)
    {
        for (int col = 0; col < width; ++col)
            delete nodes[row][col];
    }

    for (int row = 0; row < width; ++row)
        delete [] nodes[row];

    delete [] nodes;
}

const IVariable* HarmoniousGraph::getVariable(int row, int column) const
{
    return (row < width) && (column < width)
           ? nodes[row][column]
           : nullptr;
}

const IVariable* HarmoniousGraph::setVariableValue(int row, int column, const IValue* value)
{
    nodes[row][column]->setValue(value);
    return nodes[row][column];
}

bool HarmoniousGraph::isComplete() const
{
    for (int row = 0; row < width; ++row)
    {
        for (int col = 0; col < width; ++col)
        {
            if (nodes[row][col]->getValue() == nullptr)
                return false;
        }
    }

    return true;
}

bool HarmoniousGraph::checkConstraints() const
{
    return true;
}

IVariable* HarmoniousGraph::getUnassignedVariable() const
{
    for (int row = 0; row < width; ++row)
    {
        for (int col = 0; col < width; ++col)
        {
            if (nodes[row][col]->getValue() == nullptr)
                return nodes[row][col];
        }
    }

    return nullptr;
}

const IValue* HarmoniousGraph::setVariableValue(const IVariable* variable, const IValue* value)
{
    for (int row = 0; row < width; ++row)
    {
        for (int col = 0; col < width; ++col)
        {
            if (nodes[row][col] == variable)
                nodes[row][col]->setValue(value);
        }
    }
}

