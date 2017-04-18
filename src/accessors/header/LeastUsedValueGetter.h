//
// Created by Anna Siwik on 18.04.2017.
//

#ifndef SI_LAB_2_LEASTUSEDVALUEGETTER_H
#define SI_LAB_2_LEASTUSEDVALUEGETTER_H


#include <accessors/interface/IValueGetter.h>
#include <problems/interface/IProblem.h>

class LeastUsedValueGetter : public IValueGetter
{
    std::vector<const IValue*> used;
    const IDomain* domain;

    public:
        LeastUsedValueGetter(const IVariable*);
        ~LeastUsedValueGetter() override;

        IValue* getNext() override;

        void setVariable(const IVariable*) override;
        const IVariable* getVariable() const override;

        IValueGetter* instantiate(const IVariable*) const override;

        void setProblem(const IProblem*) override;

    private:
        bool hasBeenUsed(IValue *pValue);
};


#endif //SI_LAB_2_LEASTUSEDVALUEGETTER_H
