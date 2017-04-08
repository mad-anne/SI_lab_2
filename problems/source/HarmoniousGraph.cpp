//
// Created by Anna Siwik on 2017-04-07.
//

#include <algorithm>
#include "../header/HarmoniousGraph.h"
#include "../../components/header/Node.h"
#include "../../components/header/Color.h"

HarmoniousGraph::HarmoniousGraph(int width) :
    IProblem(width),
    colors(2 * width + (width % 2 == 1 ? 1 : 0))
{
    generateEmptyGraph();
    generateDomain();
}

HarmoniousGraph::~HarmoniousGraph()
{
    removeGraph();
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
            nodes[row][col] = new Node();
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

const IVariable* HarmoniousGraph::getVariable(int row, int column)
{
    return (row < width) && (column < width)
           ? nodes[row][column]
           : nullptr;
}

const IVariable* HarmoniousGraph::setVariableValue(int row, int column, IValue* value)
{
    return nullptr;
}

bool HarmoniousGraph::isComplete() const
{
    for (int row = 0; row < width; ++row)
    {
        for (int col = 0; col < width; ++col)
        {
            if (nodes[row][col]->getValue()->getValue() == -1)
                return false;
        }
    }

    return true;
}

IVariable* HarmoniousGraph::getUnassignedVariable() const
{
    for (int row = 0; row < width; ++row)
    {
        for (int col = 0; col < width; ++col)
        {
            if (nodes[row][col]->getValue()->getValue() == -1)
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

