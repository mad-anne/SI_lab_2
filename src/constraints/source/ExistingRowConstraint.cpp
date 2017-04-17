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
        rows.push_back(row);
    else
        delete row;

    if (col->isCompleted())
        columns.push_back(row);
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
    return false;
}

void ExistingRowConstraint::putConstraintsOffVariable(const IVariable *)
{
    return; // TODO
}
