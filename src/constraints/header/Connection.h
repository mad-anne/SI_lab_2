//
// Created by Anna Siwik on 2017-04-13.
//

#ifndef SI_LAB_2_CONNECTION_H
#define SI_LAB_2_CONNECTION_H

#include <constraints/interface/IConnection.h>

class Connection : public IConnection
{
    public:
        Connection(const IValue*, const IValue*);
        ~Connection();

        const IValue* getFirstValue() const override;
        const IValue* getSecondValue() const override;
};

#endif //SI_LAB_2_CONNECTION_H
