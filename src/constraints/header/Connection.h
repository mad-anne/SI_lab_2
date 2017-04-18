//
// Created by Anna Siwik on 2017-04-13.
//

#ifndef SI_LAB_2_CONNECTION_H
#define SI_LAB_2_CONNECTION_H


#include <components/interface/IValue.h>

class Connection
{
    IValue* first;
    IValue* second;

    public:
        Connection(IValue*, IValue*);
        Connection(const Connection&);
        ~Connection();

        IValue* getFirstValue() const;
        IValue* getSecondValue() const;

        bool operator==(const Connection& con);
};

#endif //SI_LAB_2_CONNECTION_H
