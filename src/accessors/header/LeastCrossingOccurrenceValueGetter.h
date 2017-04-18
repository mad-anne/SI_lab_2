//
// Created by Anna Siwik on 18.04.2017.
//

#ifndef SI_LAB_2_LEASTCROSSINGOCCURRENCEVALUEGETTER_H
#define SI_LAB_2_LEASTCROSSINGOCCURRENCEVALUEGETTER_H


#include <accessors/interface/IValueGetter.h>

class LeastCrossingOccurrenceValueGetter : public IValueGetter
{
    std::vector<const IValue*> used;
    const IDomain* domain;
    const IProblem* problem;

    public:
        LeastCrossingOccurrenceValueGetter(const IVariable*, const IProblem*);
        ~LeastCrossingOccurrenceValueGetter();

        IValueGetter* instantiate(const IVariable *variable) const override;

        IValue* getNext() override;

        void setVariable(const IVariable *variable) override;
        const IVariable* getVariable() const override;

    void setProblem(const IProblem *problem) override;

private:
        bool hasBeenUsed(IValue *pValue);
        int countValueOnCrossing(IValue* value);
};


#endif //SI_LAB_2_LEASTCROSSINGOCCURRENCEVALUEGETTER_H
