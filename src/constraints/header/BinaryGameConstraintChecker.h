//
// Created by Anna Siwik on 2017-04-15.
//

#ifndef SI_LAB_2_BINARYGAMECONSTRAINT_H
#define SI_LAB_2_BINARYGAMECONSTRAINT_H


#include <constraints/interface/IConstraintChecker.h>
#include "../interface/IRow.h"

class BinaryGameConstraintChecker : public IConstraintChecker
{
    std::vector<IRow*> rows;
    std::vector<IRow*> columns;

    public:
        BinaryGameConstraintChecker(IProblem*);
        ~BinaryGameConstraintChecker() override;

        const bool updateConstraints(const IVariable*) override;
        void undoConstraints(const IVariable*) override;

        void setProblem(IProblem*) override;
        const IProblem* getProblem() const override;

    const void putForwardConstraints(const IVariable *variable) override;

    const void undoForwardConstraints(const IVariable *variable) override;

private:
        bool checkConstraints(const IRow*, const IRow*) const;
        bool checkRepetitions(const IRow*, const IRow*) const;
        bool checkEqualValueSplit(const IRow*, const IRow*) const;

        void clearColumns();
        void clearRows();

        bool existsRow(const IRow*) const;
        bool existsColumn(const IRow*) const;

    void removeRow(IRow *pRow);

    void removeColumn(IRow *pRow);

    void limitDomainsByRepetitions(const IVariable*);

    void limitDomainsByEqualSplit(const IVariable*);

    const IValue *getValueWithMaxOccurrence(IRow *pRow);

    void removeValueFromDomainsInColumn(const IVariable *pVariable, const IValue *pValue);

    void removeValueFromDomainsInRow(const IVariable *pVariable, const IValue *pValue);

    void limitDomainsByExistingRow(const IVariable*);

    void limitDomainsByExistingColumn(const IVariable *pVariable);

    void limitDomainsInRowByExistingRows(const IVariable *pVariable);

    void limitDomainsInColumnByExistingColumns(const IVariable *pVariable);
};


#endif //SI_LAB_2_BINARYGAMECONSTRAINT_H
