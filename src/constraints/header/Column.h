//
// Created by Anna Siwik on 2017-04-15.
//

#ifndef SI_LAB_2_COLUMN_H
#define SI_LAB_2_COLUMN_H


#include <constraints/interface/IRow.h>
#include <components/interface/IVariable.h>
#include <problems/interface/IProblem.h>

class Column : public IRow
{
    int colNumber;

    public:
        Column(const IProblem*, const IVariable*);
        ~Column() override = default;

        const int getColNumber() const;

    private:
        void readColumn(const IProblem*);
};


#endif //SI_LAB_2_COLUMN_H
