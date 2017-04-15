//
// Created by Anna Siwik on 2017-04-15.
//

#ifndef SI_LAB_2_BINARYGAMECONSTRAINT_H
#define SI_LAB_2_BINARYGAMECONSTRAINT_H


#include <constraints/interface/IConstraint.h>
#include "../interface/IRow.h"

class BinaryGameConstraint : public IConstraint
{
    std::vector<IRow*> rows;
    std::vector<IRow*> columns;

    public:
        BinaryGameConstraint(IProblem*);
        ~BinaryGameConstraint() override;

        const bool updateConstraints(const IVariable*) override;
        void undoConstraints(const IVariable*) override;

        void setProblem(IProblem*) override;
        const IProblem* getProblem() const override;

    private:
        bool checkConstraints(const IRow*, const IRow*) const;
        bool checkRepetitions(const IRow*, const IRow*) const;
        bool checkEqualValueSplit(const IRow*, const IRow*) const;

        void clearColumns();
        void clearRows();

        bool existsRow(const IRow*) const;
        bool existsColumn(const IRow*) const;
};


#endif //SI_LAB_2_BINARYGAMECONSTRAINT_H
