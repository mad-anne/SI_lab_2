//
// Created by Anna Siwik on 2017-04-15.
//

#ifndef SI_LAB_2_BINARYGAMEFACTORY_H
#define SI_LAB_2_BINARYGAMEFACTORY_H


#include <factories/interface/IProblemFactory.h>
#include <solution/interface/ISolution.h>

class BinaryGameFactory : public IProblemFactory
{
    public:
        BinaryGameFactory(int width, int emptyFields, IVariableGetter*, IValueGetter*);
        ~BinaryGameFactory() override;

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


#endif //SI_LAB_2_BINARYGAMEFACTORY_H
