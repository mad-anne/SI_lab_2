//
// Created by Anna Siwik on 2017-04-17.
//

#ifndef SI_LAB_2_EQUALSPLITCONSTRAINT_H
#define SI_LAB_2_EQUALSPLITCONSTRAINT_H


#include <constraints/interface/IConstraint.h>

class EqualSplitConstraint : public IConstraint
{
    public:
        EqualSplitConstraint(IProblem *problem);
        ~EqualSplitConstraint() override;

        const bool checkVariable(const IVariable*) const override;
        const bool checkAllAndPutConstraints(bool limitDomains) override;

        void putConstraintsOnVariable(IVariable*, bool limitDomains) override;
        void putConstraintsOffVariable(IVariable*) override;

        bool canAddValueToDomain(const IVariable* checked, IValue*, const IVariable* reversed) override;

    private:
        const bool checkEqualSplit(const IVariable*) const;

        void limitDomainsOnVariable(const IVariable*);

        void limitDomainsInRow(const IVariable *variable);
        void limitDomainsInColumn(const IVariable *variable);

        void limitDomainsInRowByValue(const IVariable *pVariable, const IValue *pValue);
        void limitDomainsInColumnByValue(const IVariable *pVariable, const IValue *pValue);

    bool canAddValueToRow(const IVariable *pVariable, const IValue *pValue, const IVariable *pIVariable);

    bool canAddValueToColumn(const IVariable *pVariable, const IValue *pValue, const IVariable *pIVariable);
};


#endif //SI_LAB_2_EQUALSPLITCONSTRAINT_H
