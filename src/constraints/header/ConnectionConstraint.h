//
// Created by Dom on 2017-04-17.
//

#ifndef SI_LAB_2_CONNECTIONCONSTRAINT_H
#define SI_LAB_2_CONNECTIONCONSTRAINT_H


#include <constraints/interface/IConstraint.h>

class ConnectionConstraint : public IConstraint
{
    public:
        ConnectionConstraint(IProblem *problem);
        ~ConnectionConstraint() override;

        const bool checkVariable(IVariable *variable) const override;
        const bool checkAll() const override;

        void putConstraintsOnVariable(IVariable *variable, bool limitDomains) override;
        void putConstraintsOnAll() override;

    private:
        const bool existsConnection(IValue*, IValue*) const;
        const bool addConnection(Connection*);
};


#endif //SI_LAB_2_CONNECTIONCONSTRAINT_H
