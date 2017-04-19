//
// Created by Anna Siwik on 2017-04-15.
//

#ifndef SI_LAB_2_MENU_H
#define SI_LAB_2_MENU_H

#include <solution/interface/IMenu.h>
#include <factories/interface/ICSPFactory.h>

class Menu : public IMenu
{
    std::shared_ptr<ICSPFactory> cspFactory;

    public:
        Menu();
        ~Menu() override = default;

        void start() override;

    private:
        void printMainOptions() const;
        void printSolvingOptions() const;
        void printResultTypeOptions() const;
        void printVariableGettersForHarmoniousGraph() const;
        void printValueGettersForHarmoniousGraph() const;
        void printVariableGettersForBinaryGame() const;
        void printValueGettersForBinaryGame() const;

        void printGreeting() const;
        void printFarewell() const;

        int getNumberFromRange(int min, int max) const;
        int getPositiveNumberInput() const;
        bool processChoice(int choice) const;

        void processHarmoniousGraphColoring() const;
        void processBinaryGameSolving() const;

        int getGraphSize() const;
        int getBinarySize() const;
        int getNumberOfFilledFields(int size) const;
        int getSizeFor(std::string whatFor) const;

        void printFirstTenSolutions(std::vector<ISolution*>* solutions) const;

        int getSolvingMethod() const;
        int getResultTypeOptions() const;

        IVariableGetter* getVariableGetterForHarmoniousGraph() const;
        IValueGetter* getValueGetterForHarmoniousGraph() const;
        IVariableGetter* getVariableGetterForBinaryGame() const;
        IValueGetter* getValueGetterForBinaryGame() const;

        void performHarmoniousGraphColoring(int method, int type) const;
        void performBinaryGameSolving(int method, int type) const;

        const ISolution* getSolutionFromPuzzles(int size, int filledFields) const;

        ISolution *getSolutionFromPuzzles_6_6() const;
        ISolution *getSolutionFromPuzzles_8_8() const;
        ISolution *getSolutionFromPuzzles_10_10() const;
        ISolution *getSolutionFromPuzzles_12_12() const;
        ISolution *getSolutionFromPuzzles_14_14() const;

    int binaryPuzzles_6_6[6][6] = {
        {1, 0, 1, 0, 1, 0},
        {0, 0, 1, 1, 0, 1},
        {0, 1, 0, 0, 1, 1},
        {1, 1, 0, 0, 1, 0},
        {1, 0, 1, 1, 0, 0},
        {0, 1, 0, 1, 0, 1}
    };

    int binaryPuzzles_8_8[8][8] = {
        {1, 1, 0, 0, 1, 0, 1, 0},
        {0, 1, 1, 0, 0, 1, 1, 0},
        {0, 0, 1, 1, 0, 1, 0, 1},
        {1, 0, 0, 1, 1, 0, 0, 1},
        {0, 1, 1, 0, 1, 0, 1, 0},
        {1, 0, 0, 1, 0, 1, 0, 1},
        {1, 0, 0, 1, 0, 1, 1, 0},
        {0, 1, 1, 0, 1, 0, 0, 1}
    };

    int binaryPuzzles_10_10[10][10] = {
        {0, 1, 0, 1, 0, 0, 1, 1, 0, 1},
        {0, 0, 1, 0, 1, 1, 0, 0, 1, 1},
        {1, 0, 1, 1, 0, 1, 0, 0, 1, 0},
        {1, 1, 0, 0, 1, 0, 1, 1, 0, 0},
        {0, 1, 0, 0, 1, 1, 0, 0, 1, 1},
        {1, 0, 1, 1, 0, 0, 1, 0, 0, 1},
        {1, 0, 1, 1, 0, 1, 0, 1, 0, 0},
        {0, 1, 0, 0, 1, 1, 0, 1, 1, 0},
        {0, 1, 0, 0, 1, 0, 1, 0, 1, 1},
        {1, 0, 1, 1, 0, 0, 1, 1, 0, 0}
    };

    int binaryPuzzles_12_12[12][12] = {
        {0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1},
        {0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0},
        {1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1},
        {1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1},
        {0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0},
        {1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0},
        {0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1},
        {1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0},
        {0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0},
        {1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1},
        {0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1},
        {1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0},
    };

     int binaryPuzzles_14_14[14][14] = {
         {0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1},
         {1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1},
         {1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0},
         {0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1},
         {0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1},
         {1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0},
         {0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 0},
         {0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1},
         {1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0},
         {0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1},
         {1, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0},
         {1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 1},
         {0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0},
         {1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0}
    };
};


#endif //SI_LAB_2_MENU_H
