//
// Created by Anna Siwik on 2017-04-17.
//

#include <constraints/header/Row.h>
#include <constraints/header/Column.h>
#include "constraints/header/EqualSplitConstraint.h"

EqualSplitConstraint::EqualSplitConstraint(IProblem* problem) :
        IConstraint(problem)
{}

EqualSplitConstraint::~EqualSplitConstraint()
{}

const bool EqualSplitConstraint::checkVariable(const IVariable* variable) const
{
    if (variable == nullptr || variable->getValue() == nullptr)
        return true;

    return checkEqualSplit(variable);
}

const bool EqualSplitConstraint::checkAllAndPutConstraints(bool limitDomains)
{
    return 0; //TODO - przenieść do checkerów
}

void EqualSplitConstraint::putConstraintsOnVariable(const IVariable* variable, bool limitDomains)
{
    if (variable == nullptr || variable->getValue() == nullptr)
        return;

    if (limitDomains)
        limitDomainsOnVariable(variable);
}

const bool EqualSplitConstraint::checkEqualSplit(const IVariable* variable) const
{
    Row r(problem, variable);
    Column c(problem, variable);

    const IValue* zero = problem->getDomain()->getValue(0);
    const IValue* one = problem->getDomain()->getValue(1);

    int maxValue = problem->getWidth() / 2;

    return r.countValue(zero) <= maxValue &&  r.countValue(one) <= maxValue
           && c.countValue(zero) <= maxValue &&  c.countValue(one) <= maxValue;
}

void EqualSplitConstraint::limitDomainsOnVariable(const IVariable* variable)
{
    limitDomainsInRow(variable);
    limitDomainsInColumn(variable);
}

void EqualSplitConstraint::limitDomainsInRow(const IVariable* variable)
{
    Row r(problem, variable);

    const IValue* zero = problem->getDomain()->getValue(0);
    const IValue* one = problem->getDomain()->getValue(1);

    int maxValue = problem->getWidth() / 2;

    if (r.countValue(zero) == maxValue)
        limitDomainsInRowByValue(variable, zero);

    if (r.countValue(one) == maxValue)
        limitDomainsInRowByValue(variable, one);
}

void EqualSplitConstraint::limitDomainsInColumn(const IVariable* variable)
{
    Column c(problem, variable);

    const IValue* zero = problem->getDomain()->getValue(0);
    const IValue* one = problem->getDomain()->getValue(1);

    int maxValue = problem->getWidth() / 2;

    if (c.countValue(zero) == maxValue)
        limitDomainsInColumnByValue(variable, zero);

    if (c.countValue(one) == maxValue)
        limitDomainsInColumnByValue(variable, one);
}

void EqualSplitConstraint::limitDomainsInRowByValue(const IVariable* variable, const IValue* value)
{
    const int rowNumber = variable->getRow();

    int width = problem->getWidth();
    for (int col = 0; col < width; ++col)
    {
        IVariable* tempVar = problem->getVariable(rowNumber, col);

        if (tempVar->getValue() == nullptr)
            tempVar->removeValueFromDomain(value);
    }
}

void EqualSplitConstraint::limitDomainsInColumnByValue(const IVariable* variable, const IValue* value)
{
    const int colNumber = variable->getColumn();

    int width = problem->getWidth();
    for (int row = 0; row < width; ++row)
    {
        IVariable* tempVar = problem->getVariable(row, colNumber);

        if (tempVar->getValue() == nullptr)
            tempVar->removeValueFromDomain(value);
    }
}

bool EqualSplitConstraint::canAddValueToDomain(const IVariable *checked, const IValue *, const IVariable *reversed) {
    return false; // TODO czy ktoras z wartosci moze byc zaburzona  (bo ilosc w kol/wier jest juz max i to te val dodajemu); jesli nie ta wie/kol to true
}

void EqualSplitConstraint::putConstraintsOffVariable(const IVariable *)
{
    return;
}
