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
    fillDomainWithValues();
    generateEmptyGraph();
}

HarmoniousGraph::~HarmoniousGraph()
{
    removeGraph();
}

void HarmoniousGraph::fillDomainWithValues()
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

IVariable* HarmoniousGraph::getVariable(int row, int column) const
{
    return (row < width && row  >= 0) && (column < width && column >= 0)
           ? nodes[row][column]
           : nullptr;
}