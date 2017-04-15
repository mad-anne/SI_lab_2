//
// Created by Anna Siwik on 2017-04-15.
//

#ifndef SI_LAB_2_BINARYGAME_H
#define SI_LAB_2_BINARYGAME_H


#include <problems/interface/IProblem.h>

class BinaryGame : public IProblem
{
    int filledFields;
    IVariable*** nodes;

    public:
        BinaryGame(int width, int filledFields);
        ~BinaryGame() override;

        IVariable* getVariable(int row, int column) const override;

    private:
        void generateEmptyGrid();
        void fillDomainWithValues();
        void removeGrid();
};


#endif //SI_LAB_2_BINARYGAME_H
