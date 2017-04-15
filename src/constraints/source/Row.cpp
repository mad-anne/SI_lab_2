//
// Created by Anna Siwik on 2017-04-15.
//

#include <components/header/Number.h>
#include "constraints/header/Row.h"

Row::Row(const IProblem* problem, const IVariable* variable) :
    IRow(problem->getWidth()),
    rowNumber(variable->getRow())
{
    readRow(problem);
}

const int Row::getRowNumber() const
{
    return rowNumber;
}

void Row::readRow(const IProblem* problem)
{
    for (int col = 0; col < width; ++col)
        values.push_back(problem->getVariable(rowNumber, col)->getValue());
}
