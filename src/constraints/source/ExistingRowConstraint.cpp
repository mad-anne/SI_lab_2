//
// Created by Anna Siwik on 2017-04-17.
//

#include <constraints/header/Row.h>
#include <constraints/header/Column.h>
#include "constraints/header/ExistingRowConstraint.h"

ExistingRowConstraint::ExistingRowConstraint(IProblem *problem) :
        IConstraint(problem)
{}

ExistingRowConstraint::~ExistingRowConstraint()
{}

const bool ExistingRowConstraint::checkVariable(const IVariable* variable) const
{
    if (variable == nullptr || variable->getValue() == nullptr)
        return true;

    return (! existsRow(variable)) && (! existsColumn(variable));
}

const bool ExistingRowConstraint::checkAllAndPutConstraints(bool limitDomains)
{
    return 0; // TODO
}

void ExistingRowConstraint::putConstraintsOnVariable(const IVariable* variable, bool limitDomains)
{
    IRow* row = new Row(problem, variable);
    IRow* col = new Column(problem, variable);

    if (limitDomains)
    {
        limitDomainsInRows(row);
        limitDomainsInColumns(col);
    }

    if (row->isCompleted())
        rows.push_back(row);
    else
        delete row;

    if (col->isCompleted())
        columns.push_back(col);
    else
        delete col;
}

bool ExistingRowConstraint::canAddValueToDomain(const IVariable* checked, const IValue* value, const IVariable* reversed)
{
    return canAddValueToRow(checked, value, reversed)
           && canAddValueToColumn(checked, value, reversed);
}

bool ExistingRowConstraint::existsRow(const IVariable* variable) const
{
    IRow* row = new Row(problem, variable);
    bool exists = false;

    std::vector<IRow*>::const_iterator it = rows.begin();

    while (!exists && it != rows.end())
    {
        if ( *(*it) == *row)
            exists = true;

        ++it;
    }

    delete row;

    return exists;
}

void ExistingRowConstraint::putConstraintsOffVariable(const IVariable* variable)
{
    IRow* row = new Row(problem, variable);
    IRow* col = new Column(problem, variable);

    removeFromRows(row);
    removeFromColumns(col);

    delete row;
    delete col;
}

bool ExistingRowConstraint::existsColumn(const IVariable* variable) const
{
    IRow* col = new Column(problem, variable);
    bool exists = false;

    std::vector<IRow*>::const_iterator it = columns.begin();

    while (!exists && it != columns.end())
    {
        if ( *(*it) == *col)
            exists = true;

        ++it;
    }

    delete col;

    return exists;
}

void ExistingRowConstraint::limitDomainsInRows(IRow* row)
{
    if (row->isCompleted())
    {
        int width = problem->getWidth();
        for (int r = 0; r < width; ++r)
        {
            IRow* tempRow = new Row(problem, problem->getVariable(r, 0));

            int numberOfNulls = tempRow->countValue(nullptr);
            if (numberOfNulls <= 2 && numberOfNulls > 0 && row->compareWithAllowingNulls(tempRow))
                limitDomainsInRow(r, row);

            delete tempRow;
        }
    }
    else
    {
        if (row->countValue(nullptr) <= 2)
        {
            int rowNumber = ((Row*) row)->getRowNumber();
            for (int i = 0; i < rows.size(); ++i)
            {
                if (rows[i]->compareWithAllowingNulls(row))
                    limitDomainsInRow(rowNumber, rows[i]);
            }
        }
    }
}

void ExistingRowConstraint::limitDomainsInColumns(IRow* col)
{
    if (col->isCompleted())
    {
        int width = problem->getWidth();
        for (int c = 0; c < width; ++c)
        {
            IRow* tempCol = new Column(problem, problem->getVariable(0, c));

            int numberOfNulls = tempCol->countValue(nullptr);
            if (numberOfNulls <= 2 && numberOfNulls > 0 && col->compareWithAllowingNulls(tempCol))
                limitDomainsInColumn(c, col);

            delete tempCol;
        }
    }
    else
    {
        if (col->countValue(nullptr) <= 2)
        {
            int colNumber = ((Column*) col)->getColNumber();
            for (int i = 0; i < columns.size(); ++i)
            {
                if (columns[i]->compareWithAllowingNulls(col))
                    limitDomainsInColumn(colNumber, columns[i]);
            }
        }
    }

}

void ExistingRowConstraint::limitDomainsInRow(int rowNumber, IRow* row)
{
    int width = problem->getWidth();
    for (int col = 0; col < width; ++col)
    {
        IVariable* variable = problem->getVariable(rowNumber, col);

        if (variable->getValue() == nullptr)
            variable->removeValueFromDomain(row->getValue(col));
    }
}

void ExistingRowConstraint::limitDomainsInColumn(int colNumber, IRow* column)
{
    int width = problem->getWidth();
    for (int row = 0; row < width; ++row)
    {
        IVariable* variable = problem->getVariable(row, colNumber);

        if (variable->getValue() == nullptr)
            variable->removeValueFromDomain(column->getValue(row));
    }
}

void ExistingRowConstraint::removeFromRows(IRow* row)
{
    std::vector<IRow*>::const_iterator it = rows.begin();
    bool found = false;
    while (! found && it != rows.end())
    {
        if ( *(*it) == *row)
        {
            found = true;
            delete *it;
            it = rows.erase(it);
        }
        else
            ++it;
    }
}

void ExistingRowConstraint::removeFromColumns(IRow* col)
{
    if (! col->isCompleted())
        return;

    std::vector<IRow*>::const_iterator it = columns.begin();
    bool found = false;
    while (! found && it != columns.end())
    {
        if ( *(*it) == *col)
        {
            found = true;
            delete *it;
            it = columns.erase(it);
        }
        else
            ++it;
    }
}

bool ExistingRowConstraint::canAddValueToRow(const IVariable* checked, const IValue* value, const IVariable* reversed)
{
    IRow* row = new Row(problem, checked);
    bool canAdd = true;

    if (! row->isCompleted() && row->countValue(nullptr) <= 2)
    {
        for (int i = 0; canAdd && i < rows.size(); ++i)
        {
            if (rows[i]->compareWithAllowingNulls(row) && rows[i]->getValue(checked->getColumn()) == value)
                canAdd = false;
        }
    }

    delete row;

    return canAdd;
}

bool ExistingRowConstraint::canAddValueToColumn(const IVariable* checked, const IValue* value, const IVariable* reversed)
{
    IRow* col = new Column(problem, checked);
    bool canAdd = true;

    if (! col->isCompleted() && col->countValue(nullptr) <= 2)
    {
        for (int i = 0; canAdd && i < columns.size(); ++i)
        {
            if (columns[i]->compareWithAllowingNulls(col) && columns[i]->getValue(checked->getRow()) == value)
                canAdd = false;
        }
    }

    delete col;

    return canAdd;
}
