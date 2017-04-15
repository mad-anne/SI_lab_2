//
// Created by Anna Siwik on 2017-04-15.
//

#ifndef SI_LAB_2_HARMONIOUSGRAPHFACTORY_H
#define SI_LAB_2_HARMONIOUSGRAPHFACTORY_H


#include <factories/interface/IProblemFactory.h>

class HarmoniousGraphFactory : public IProblemFactory
{
    public:
        HarmoniousGraphFactory(int width);
        ~HarmoniousGraphFactory() override;

        IProblem* getProblem() const override;
        IConstraint* getConstraint() const override;
        IVariableGetter* getVariableGetter() const override;
        IValueGetter* getValueGetter() const override;

    private:
        void clearProblem();
        void clearConstraint();
        void clearVariableGetter();
        void clearValueGetter();
};


#endif //SI_LAB_2_HARMONIOUSGRAPHFACTORY_H
