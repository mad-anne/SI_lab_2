//
// Created by Anna Siwik on 2017-04-15.
//

#include <components/header/Number.h>
#include "constraints/header/Column.h"

Column::Column(const IProblem* problem, const IVariable* variable) :
    IRow(problem->getWidth()),
    colNumber(variable->getColumn())
{
    readColumn(problem);
}

const int Column::getColNumber() const
{
    return colNumber;
}

void Column::readColumn(const IProblem* problem)
{
    for (int row = 0; row < width; ++row)
        values.push_back(problem->getVariable(row, colNumber)->getValue());
}
