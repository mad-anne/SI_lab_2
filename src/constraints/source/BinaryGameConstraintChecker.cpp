//
// Created by Anna Siwik on 2017-04-15.
//

#include <constraints/header/Row.h>
#include <constraints/header/Column.h>
#include <constraints/header/PairConstraint.h>
#include <constraints/header/EqualSplitConstraint.h>
#include <constraints/header/ExistingRowConstraint.h>
#include <iostream>
#include "constraints/header/BinaryGameConstraintChecker.h"

BinaryGameConstraintChecker::BinaryGameConstraintChecker(IProblem* problem) :
    IConstraintChecker(problem),
    pairConstraint(new PairConstraint(problem)),
    equalSplitConstraint(new EqualSplitConstraint(problem)),
    existingRowConstraint(new ExistingRowConstraint(problem))
{}

BinaryGameConstraintChecker::~BinaryGameConstraintChecker()
{
    delete pairConstraint;
    delete equalSplitConstraint;
    delete existingRowConstraint;
}


bool BinaryGameConstraintChecker::isCorrectAssignment(const IVariable* variable) const
{
    if (variable == nullptr || variable->getValue() == nullptr)
        return true;

    return pairConstraint->checkVariable(variable)
           && equalSplitConstraint->checkVariable(variable)
           && existingRowConstraint->checkVariable(variable);
}

const void BinaryGameConstraintChecker::putConstraintsOn(const IVariable* variable, bool limitDomains)
{
    pairConstraint->putConstraintsOnVariable(variable, limitDomains);
    equalSplitConstraint->putConstraintsOnVariable(variable, limitDomains);
    existingRowConstraint->putConstraintsOnVariable(variable, limitDomains);
}

const void BinaryGameConstraintChecker::putConstraintsOff(const IVariable* variable, bool limitDomains)
{
    pairConstraint->putConstraintsOffVariable(variable);
    equalSplitConstraint->putConstraintsOffVariable(variable);
    existingRowConstraint->putConstraintsOffVariable(variable);

    if (! limitDomains)
        return;

    const IValue* zero = problem->getDomain()->getValue(0);
    const IValue* one = problem->getDomain()->getValue(1);

    int width = problem->getWidth();
    for (int row = 0; row < width; ++row)
    {
        for (int col = 0; col < width; ++col)
        {
            IVariable* tempVar = problem->getVariable(row, col);

            if (variable->getRow() == 1 && variable->getColumn() == 1 && variable->getValue() == 0
                && tempVar->getRow() == 1 && tempVar->getColumn() == 2)
                std::cout << "GOT YA" << std::endl;

            if (tempVar->getValue() == nullptr)
            {
                if (! tempVar->getDomain()->hasValue(zero))
                {
                    if (pairConstraint->canAddValueToDomain(tempVar, zero, variable)
                        && equalSplitConstraint->canAddValueToDomain(tempVar, zero, variable)
                        && existingRowConstraint->canAddValueToDomain(tempVar, zero, variable))
                    {
                        tempVar->addValueToDomain(zero);
                    }
                }

                if (! tempVar->getDomain()->hasValue(one))
                {
                    if (pairConstraint->canAddValueToDomain(tempVar, one, variable)
                        && equalSplitConstraint->canAddValueToDomain(tempVar, one, variable)
                        && existingRowConstraint->canAddValueToDomain(tempVar, one, variable))
                    {
                        tempVar->addValueToDomain(one);
                    }
                }
            }
        }
    }
}