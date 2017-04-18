//
// Created by Anna Siwik on 2017-04-15.
//

#ifndef SI_LAB_2_ROW_H
#define SI_LAB_2_ROW_H


#include <constraints/interface/IRow.h>
#include <problems/interface/IProblem.h>
#include <components/interface/IVariable.h>

class Row : public IRow
{
    int rowNumber;

    public:
        Row(const IProblem*, const IVariable*);
        ~Row() override;

        const int getRowNumber() const;

private:
        void readRow(const IProblem*);
};


#endif //SI_LAB_2_ROW_H
