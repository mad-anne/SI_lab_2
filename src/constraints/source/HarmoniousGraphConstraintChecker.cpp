//
// Created by Anna Siwik on 2017-04-13.
//

#include <problems/interface/IProblem.h>
#include <constraints/header/HarmoniousGraphConstraintChecker.h>
#include <constraints/header/ConnectionConstraint.h>
#include <constraints/header/NeighbourConstraint.h>
#include <iostream>

HarmoniousGraphConstraintChecker::HarmoniousGraphConstraintChecker(IProblem* problem)
        : IConstraintChecker(problem),
          connectionConstraint(new ConnectionConstraint(problem)),
          neighbourConstraint(new NeighbourConstraint(problem))
{}

HarmoniousGraphConstraintChecker::~HarmoniousGraphConstraintChecker()
{
    delete connectionConstraint;
    delete neighbourConstraint;
}

bool HarmoniousGraphConstraintChecker::isCorrectAssignment(const IVariable* variable) const
{
    if (variable == nullptr || variable->getValue() == nullptr)
        return true;

    return neighbourConstraint->checkVariable(variable) && connectionConstraint->checkVariable(variable);
}

const void HarmoniousGraphConstraintChecker::putConstraintsOn(const IVariable* variable, bool limitDomains)
{
    connectionConstraint->putConstraintsOnVariable(variable, limitDomains);
    neighbourConstraint->putConstraintsOnVariable(variable, limitDomains);
}

const void HarmoniousGraphConstraintChecker::putConstraintsOff(const IVariable* variable, bool limitDomains)
{
    if (variable == nullptr || variable->getValue() == nullptr)
        return;

    connectionConstraint->putConstraintsOffVariable(variable);
    neighbourConstraint->putConstraintsOffVariable(variable);

    std::vector<const IValue*> valuesToCheck;
    valuesToCheck.push_back(variable->getValue());

    const IValue* valLeft = ((ConnectionConstraint*) connectionConstraint)->getLeftValueInConnection(variable);
    const IValue* valUp = ((ConnectionConstraint*) connectionConstraint)->getUpValueInConnection(variable);
    const IValue* valRight = ((ConnectionConstraint*) connectionConstraint)->getRightValueInConnection(variable);
    const IValue* valDown = ((ConnectionConstraint*) connectionConstraint)->getDownValueInConnection(variable);

    if (valLeft != nullptr)
        valuesToCheck.push_back(valLeft);
    if (valUp != nullptr)
        valuesToCheck.push_back(valUp);
    if (valRight != nullptr)
        valuesToCheck.push_back(valRight);
    if (valDown != nullptr)
        valuesToCheck.push_back(valDown);

    int width = problem->getWidth();
    for (int i = 0; i < valuesToCheck.size(); ++i)
    {
        const IValue* checkedValue = valuesToCheck.at(i);

        for (int row = 0; row < width; ++row)
        {
            for (int col = 0; col < width; ++col)
            {
                IVariable *tempVar = problem->getVariable(row, col);
                if (tempVar->getValue() == nullptr && tempVar != variable)
                {
                    if (connectionConstraint->canAddValueToDomain(tempVar, checkedValue, variable)
                        && neighbourConstraint->canAddValueToDomain(tempVar, checkedValue, variable))
                        tempVar->addValueToDomain(checkedValue);
                }
            }
        }
    }
}
