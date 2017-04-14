//
// Created by Anna Siwik on 2017-04-14.
//

#ifndef SI_LAB_2_NEXTVALUEGETTER_H
#define SI_LAB_2_NEXTVALUEGETTER_H


#include <accessors/interface/IValueGetter.h>

class NextValueGetter : public IValueGetter
{
    int currentIndex;
    const IDomain* domain;

    public:
        NextValueGetter(const IVariable*);
        ~NextValueGetter();

        const IValue* getNext() override;

        void setVariable(const IVariable*) override;
        const IVariable* getVariable() const override;
};


#endif //SI_LAB_2_NEXTVALUEGETTER_H
