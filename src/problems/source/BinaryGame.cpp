//
// Created by Anna Siwik on 2017-04-15.
//

#include <components/header/Number.h>
#include <components/header/Node.h>
#include "problems/header/BinaryGame.h"

BinaryGame::BinaryGame(int width, int filledFields) :
    IProblem(width),
    filledFields(filledFields)
{
    fillDomainWithValues();
    generateEmptyGrid();
}

BinaryGame::~BinaryGame()
{
    removeGrid();
}

IVariable* BinaryGame::getVariable(int row, int column) const
{
    return (row < width) && (column < width)
           ? nodes[row][column]
           : nullptr;
}

void BinaryGame::generateEmptyGrid()
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

void BinaryGame::removeGrid()
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

void BinaryGame::fillDomainWithValues()
{
    domain->addValue(new Number(0));
    domain->addValue(new Number(1));
}