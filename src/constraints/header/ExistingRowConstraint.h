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
        void putConstraintsOffVariable(const IVariable*, bool limitDomains) override;

    private:
        bool existsRow(const IVariable*) const;
        bool existsColumn(const IVariable*) const;
};


#endif //SI_LAB_2_EXISTINGROWCONSTRAINT_H
