//
// Created by Anna Siwik on 2017-04-07.
//

#include "../header/HarmoniousGraph.h"
#include "../../components/header/Node.h"

HarmoniousGraph::HarmoniousGraph(int width) :
    IProblem(width),
    colors(2 * width)
{
    generateEmptyGraph();
}

HarmoniousGraph::~HarmoniousGraph()
{
    removeGraph();
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
