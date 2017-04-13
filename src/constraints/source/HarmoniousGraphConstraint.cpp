//
// Created by Anna Siwik on 2017-04-13.
//

#include <problems/interface/IProblem.h>
#include <constraints/header/HarmoniousGraphConstraint.h>

HarmoniousGraphConstraint::HarmoniousGraphConstraint(IProblem* problem)
        : IConstraint(problem)
{}

HarmoniousGraphConstraint::~HarmoniousGraphConstraint()
{}

const bool HarmoniousGraphConstraint::checkConstraints() const
{
    return 0;
}

void HarmoniousGraphConstraint::setProblem(IProblem* problem)
{
    this->problem = problem;
}
