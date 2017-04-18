//
// Created by Anna Siwik on 2017-04-17.
//

#ifndef SI_LAB_2_EXISTINGROWCONSTRAINT_H
#define SI_LAB_2_EXISTINGROWCONSTRAINT_H


#include <constraints/interface/IConstraint.h>
#include <constraints/interface/IRow.h>

class ExistingRowConstraint : public IConstraint
{
    std::vector<IRow*> rows;
    std::vector<IRow*> columns;

    public:
        ExistingRowConstraint(IProblem *problem);
        ~ExistingRowConstraint() override;

        const bool checkVariable(const IVariable *variable) const override;
        const bool checkAllAndPutConstraints(bool limitDomains) override;

        void putConstraintsOnVariable(const IVariable*, bool limitDomains) override;
        void putConstraintsOffVariable(const IVariable*) override;

        bool canAddValueToDomain(const IVariable* checked, const IValue*, const IVariable* reversed);

    private:
        bool existsRow(const IVariable*) const;
        bool existsColumn(const IVariable*) const;

    void limitDomainsInRows(IRow *pRow);

    void limitDomainsInRow(int r, IRow *pRow);
    void limitDomainsInColumn(int colNumber, IRow*);

    void limitDomainsInColumns(IRow *pRow);
};


#endif //SI_LAB_2_EXISTINGROWCONSTRAINT_H