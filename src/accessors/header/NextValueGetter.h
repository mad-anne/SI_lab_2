//
// Created by Anna Siwik on 2017-04-14.
//

#ifndef SI_LAB_2_NEXTVALUEGETTER_H
#define SI_LAB_2_NEXTVALUEGETTER_H


#include <accessors/interface/IValueGetter.h>

class NextValueGetter : public IValueGetter
{
    std::vector<const IValue*> used;
    const IDomain* domain;

    public:
        NextValueGetter(const IVariable*);
        ~NextValueGetter();

        IValue* getNext() override;

        void setVariable(const IVariable*) override;
        const IVariable* getVariable() const override;

    private:
        bool hasBeenUsed(const IValue *pValue);
};


#endif //SI_LAB_2_NEXTVALUEGETTER_H
