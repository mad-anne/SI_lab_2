//
// Created by Anna Siwik on 2017-04-13.
//

#ifndef SI_LAB_2_ICONNECTION_H
#define SI_LAB_2_ICONNECTION_H

#include <components/interface/IValue.h>

class IConnection
{
    protected:
        const IValue* first;
        const IValue* second;

    public:
        IConnection()
                : first(nullptr),
                  second(nullptr)
        {}
        IConnection(const IValue* first, const IValue* second)
            : first(first),
              second(second)
        {}
        virtual ~IConnection() = default;

        virtual const IValue* getFirstValue() const = 0;
        virtual const IValue* getSecondValue() const = 0;
};

#endif //SI_LAB_2_ICONNECTION_H
