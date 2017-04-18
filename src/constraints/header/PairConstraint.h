//
// Created by Anna Siwik  on 2017-04-17.
//

#ifndef SI_LAB_2_PAIRCONSTRAINT_H
#define SI_LAB_2_PAIRCONSTRAINT_H


#include <constraints/interface/IConstraint.h>

class PairConstraint : public IConstraint
{
    public:
        PairConstraint(IProblem *problem);
        ~PairConstraint() override;

        const bool checkVariable(const IVariable*) const override;
        const bool checkAllAndPutConstraints(bool limitDomains) override;

        void putConstraintsOnVariable(IVariable*, bool limitDomains) override;
        void putConstraintsOffVariable(IVariable*) override;

        bool canAddValueToDomain(const IVariable* checked, IValue*, const IVariable* reversed) override;

    private:
        const bool checkValueRepetitions(const IVariable*) const;

        const bool checkValuesInRow(const IVariable*) const;
        bool checkValuesInColumn(const IVariable*) const;

        void limitDomainsOnVariable(const IVariable*);
        void limitDomainsInRow(const IVariable*);
        void limitDomainsInColumn(const IVariable*);

    bool canAddValueToRow(const IVariable *pVariable, const IValue *pValue, const IVariable *pIVariable);

    bool canAddValueToColumn(const IVariable *pVariable, const IValue *pValue, const IVariable *pIVariable);
};


#endif //SI_LAB_2_PAIRCONSTRAINT_H
