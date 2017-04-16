//
// Created by Anna Siwik on 2017-04-15.
//

#include <constraints/header/Row.h>
#include <constraints/header/Column.h>
#include "constraints/header/BinaryGameConstraint.h"

BinaryGameConstraint::BinaryGameConstraint(IProblem* problem) :
    IConstraint(problem)
{}

BinaryGameConstraint::~BinaryGameConstraint()
{
    clearRows();
    clearColumns();
}

const bool BinaryGameConstraint::updateConstraints(const IVariable* variable)
{
    if (variable == nullptr)
        return true;

    IRow* row = new Row(problem, variable);
    IRow* col = new Column(problem, variable);

    if (checkConstraints(row, col))
    {
        if (row->isCompleted())
            rows.push_back(row);
        else
            delete row;

        if (col->isCompleted())
            columns.push_back(col);
        else
            delete col;

        return true;
    }

    delete row;
    delete col;

    return false;

}

void BinaryGameConstraint::undoConstraints(const IVariable* variable)
{
    IRow* row = new Row(problem, variable);
    IRow* col = new Column(problem, variable);

    removeRow(row);
    removeColumn(col);

    delete row;
    delete col;
}

bool BinaryGameConstraint::checkConstraints(const IRow* row, const IRow* col) const
{
    return checkRepetitions(row, col)
           && checkEqualValueSplit(row, col)
           && ! existsRow(row)
           && ! existsColumn(col);
}

void BinaryGameConstraint::setProblem(IProblem* problem)
{
    this->problem = problem;
}

const IProblem* BinaryGameConstraint::getProblem() const
{
    return problem;
}

bool BinaryGameConstraint::checkRepetitions(const IRow* row, const IRow* col) const
{
    return row->isCorrect()
           && col->isCorrect();
}

bool BinaryGameConstraint::checkEqualValueSplit(const IRow* row, const IRow* col) const
{
    const IValue* zero = problem->getDomain()->getValue(0);
    const IValue* one = problem->getDomain()->getValue(1);

    int maxValue = problem->getWidth() / 2;

    return row->countValue(zero) <= maxValue
           && row->countValue(one) <= maxValue
           && col->countValue(zero) <= maxValue
           && col->countValue(one) <= maxValue;
}

void BinaryGameConstraint::clearColumns()
{
    std::vector<IRow*>::const_iterator it = columns.begin();

    while (it != columns.end())
    {
        delete *it;
        it = columns.erase(it);
    }
}

void BinaryGameConstraint::clearRows()
{
    std::vector<IRow*>::const_iterator it = rows.begin();

    while (it != rows.end())
    {
        delete *it;
        it = rows.erase(it);
    }
}

bool BinaryGameConstraint::existsRow(const IRow* row) const
{
    std::vector<IRow*>::const_iterator it;

    for (it = rows.begin(); it != rows.end(); ++it)
        if (row->compareWith(*it))
            return true;

    return false;
}

bool BinaryGameConstraint::existsColumn(const IRow* col) const
{
    std::vector<IRow*>::const_iterator it;

    for (it = columns.begin(); it != columns.end(); ++it)
        if (col->compareWith(*it))
            return true;

    return false;
}

void BinaryGameConstraint::removeRow(IRow* row)
{
    std::vector<IRow*>::const_iterator it;

    for (it = rows.begin(); it != rows.end(); ++it)
    {
        if (row->compareWith(*it))
        {
            delete *it;
            it = rows.erase(it);
            return;
        }
    }
}

void BinaryGameConstraint::removeColumn(IRow* col)
{
    std::vector<IRow*>::const_iterator it;

    for (it = columns.begin(); it != columns.end(); ++it)
    {
        if (col->compareWith(*it))
        {
            delete *it;
            it = columns.erase(it);
            return;
        }
    }
}

const void BinaryGameConstraint::putForwardConstraints(const IVariable* variable)
{

}

const void BinaryGameConstraint::undoForwardConstraints(const IVariable* variable)
{

}

// TODO: limit number of each value and inverse
// TODO: limit neighbours to have the same value as last two
// TODO: limit the same column repetition