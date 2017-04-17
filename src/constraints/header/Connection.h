//
// Created by Anna Siwik on 2017-04-13.
//

#ifndef SI_LAB_2_CONNECTION_H
#define SI_LAB_2_CONNECTION_H


#include <components/interface/IValue.h>

class Connection
{
    const IValue* first;
    const IValue* second;

    public:
        Connection(const IValue*, const IValue*);
        Connection(const Connection&);
        ~Connection();

        const IValue* getFirstValue() const;
        const IValue* getSecondValue() const;

        bool operator==(const Connection& con);
};

#endif //SI_LAB_2_CONNECTION_H
