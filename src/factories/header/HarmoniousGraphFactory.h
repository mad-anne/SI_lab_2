//
// Created by Anna Siwik on 2017-04-15.
//

#ifndef SI_LAB_2_HARMONIOUSGRAPHFACTORY_H
#define SI_LAB_2_HARMONIOUSGRAPHFACTORY_H


#include <factories/interface/IProblemFactory.h>
#include <solution/interface/ISolution.h>

class HarmoniousGraphFactory : public IProblemFactory
{
    public:
        HarmoniousGraphFactory(int width, IVariableGetter*, IValueGetter*);
        ~HarmoniousGraphFactory() override;

        IProblem* getProblem() const override;
        IConstraintChecker* getConstraint() const override;
        IVariableGetter* getVariableGetter() const override;
        IValueGetter* getValueGetter() const override;

        void readPartialSolution(const ISolution*, bool limitDomains) override;

    private:
        void clearProblem();
        void clearConstraint();
        void clearVariableGetter();
        void clearValueGetter();
};


#endif //SI_LAB_2_HARMONIOUSGRAPHFACTORY_H
