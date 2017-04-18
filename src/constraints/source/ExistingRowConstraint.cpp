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

    if (row->isCompleted())
    {
        rows.push_back(row);
        limitDomainsInRows(row);
    }
    else
        delete row;

    if (col->isCompleted())
    {
        columns.push_back(col);
        limitDomainsInColumns(col);
    }
    else
        delete col;
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

bool ExistingRowConstraint::canAddValueToDomain(const IVariable *checked, const IValue *, const IVariable *reversed) {
    return false; // TODO sprawdzenie czy dodanie wartosci wplwa na to ze bedzie mogla powstac taka sama kolmna/wiersz jak jest
}

void ExistingRowConstraint::putConstraintsOffVariable(const IVariable *)
{
    return; // TODO - sprawdzenie czy istnieje juz taka kolumna/wiersz jesli var uzupelnialo i usuniecie jej
}

void ExistingRowConstraint::limitDomainsInRows(IRow* row)
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

void ExistingRowConstraint::limitDomainsInColumns(IRow* col)
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
