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
    if (variable == nullptr)
        return;

    limitDomainsByRepetitions(variable);
    limitDomainsByEqualSplit(variable);
    limitDomainsByExistingRow(variable);
    limitDomainsByExistingColumn(variable); // TODO: sprawdzenie, czy są zapisane jakieś kolumny i powtarzają się wartości (a może nie trzeba? bo forward checking)

    IRow* row = new Row(problem, variable);
    IRow* col = new Column(problem, variable);

    row->isCompleted() ? rows.push_back(row) : delete row;
    col->isCompleted() ? columns.push_back(col) : delete col;
}

const void BinaryGameConstraint::undoForwardConstraints(const IVariable* variable)
{
    //TODO
}

void BinaryGameConstraint::limitDomainsByRepetitions(const IVariable* variable)
{
    const IValue* value = variable->getValue();

    if (value == nullptr)
        return;

    IVariable* varLeft = problem->getVariable(variable->getRow(), variable->getColumn() - 1);
    IVariable* varRight = problem->getVariable(variable->getRow(), variable->getColumn() + 1);
    IVariable* varUp = problem->getVariable(variable->getRow() - 1, variable->getColumn());
    IVariable* varDown = problem->getVariable(variable->getRow() + 1, variable->getColumn());

    if (varLeft != nullptr && varLeft->getValue() == value && varRight != nullptr)
        varRight->removeValueFromDomain(value);

    if (varRight != nullptr && varRight->getValue() == value && varLeft != nullptr)
        varRight->removeValueFromDomain(value);

    if (varUp != nullptr && varUp->getValue() == value && varDown != nullptr)
        varUp->removeValueFromDomain(value);

    if (varDown != nullptr && varDown->getValue() == value && varUp != nullptr)
        varDown->removeValueFromDomain(value);
}

void BinaryGameConstraint::limitDomainsByEqualSplit(const IVariable* variable)
{
    IRow* row = new Row(problem, variable);
    IRow* col = new Column(problem, variable);

    removeValueFromDomainsInColumn(variable, getValueWithMaxOccurrence(col));
    removeValueFromDomainsInRow(variable, getValueWithMaxOccurrence(row));

    delete row;
    delete col;
}

const IValue* BinaryGameConstraint::getValueWithMaxOccurrence(IRow* row)
{
    const IValue* zero = problem->getDomain()->getValue(0);
    const IValue* one = problem->getDomain()->getValue(1);

    int maxValue = problem->getWidth() / 2;

    if (row->countValue(zero) == maxValue)
        return zero;

    if (row->countValue(one) == maxValue)
        return one;

    return nullptr;
}

void BinaryGameConstraint::removeValueFromDomainsInColumn(const IVariable* variable, const IValue* value)
{
    if (value == nullptr)
        return;

    int col = variable->getColumn();
    int width = problem->getWidth();

    for (int row = 0; row < width; ++row)
    {
        IVariable* tempVariable = problem->getVariable(row, col);

        if (tempVariable->getValue() == nullptr)
            tempVariable->removeValueFromDomain(value);
    }
}

void BinaryGameConstraint::removeValueFromDomainsInRow(const IVariable* variable, const IValue* value)
{
    if (value == nullptr)
        return;

    int row = variable->getRow();
    int width = problem->getWidth();

    for (int col = 0; col < width; ++col)
    {
        IVariable* tempVariable = problem->getVariable(row, col);

        if (tempVariable->getValue() == nullptr)
            tempVariable->removeValueFromDomain(value);
    }
}

void BinaryGameConstraint::limitDomainsByExistingRow(const IVariable* variable)
{
    Row r(problem, variable);

    if (r.isCompleted())
    {
        int width = problem->getWidth();
        int varRow = variable->getRow();

        for (int row = 0; row < width; ++row)
        {
            if (row == varRow)
                continue;

            Row tempRow = Row(problem, problem->getVariable(row, 0));
            int numberOfNulls = tempRow.countValue(nullptr);

            if (numberOfNulls <= 2 && numberOfNulls != 0)
            {
                int col;
                for (col = 0; col < width; ++col)
                {
                    IVariable* tempVar = problem->getVariable(row, col);
                    IVariable* comparedVar = problem->getVariable(varRow, col);

                    if (tempVar->getValue() != comparedVar->getValue()
                        && tempVar->getValue() != nullptr)
                        break;
                }

                if (col == width)
                {
                    for (col = 0; col < width; ++col)
                    {
                        IVariable* tempVar = problem->getVariable(row, col);
                        IVariable* comparedVar = problem->getVariable(varRow, col);

                        if (tempVar->getValue() == nullptr)
                            tempVar->removeValueFromDomain(comparedVar->getValue());
                    }
                }
            }
        }
    }
}

void BinaryGameConstraint::limitDomainsByExistingColumn(const IVariable* variable)
{
    Column c(problem, variable);

    if (c.isCompleted())
    {
        int width = problem->getWidth();
        int varCol = variable->getColumn();

        for (int col = 0; col < width; ++col)
        {
            if (col == varCol)
                continue;

            Column tempCol(problem, problem->getVariable(0, col));
            int numberOfNulls = tempCol.countValue(nullptr);

            if (numberOfNulls <= 2 && numberOfNulls != 0)
            {
                int row;
                for (row = 0; row < width; ++row)
                {
                    IVariable* tempVar = problem->getVariable(row, col);
                    IVariable* comparedVar = problem->getVariable(row, varCol);

                    if (tempVar->getValue() != comparedVar->getValue()
                        && tempVar->getValue() != nullptr)
                        break;
                }

                if (col == width)
                {
                    for (row = 0; row < row; ++row)
                    {
                        IVariable* tempVar = problem->getVariable(row, col);
                        IVariable* comparedVar = problem->getVariable(row, varCol);

                        if (tempVar->getValue() == nullptr)
                            tempVar->removeValueFromDomain(comparedVar->getValue());
                    }
                }
            }
        }
    }
}

// TODO: limit number of each value and inverse
// TODO: limit neighbours to have the same value as last two
// TODO: limit the same column repetition