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
        void printVariableGetters() const;
        void printValueGetters() const;

        void printGreeting() const;
        void printFarewell() const;

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
        IVariableGetter* getVariableGetter() const;
        IValueGetter* getValueGetter() const;

        void performHarmoniousGraphColoring(int method, int type) const;
        void performBinaryGameSolving(int method, int type) const;
};


#endif //SI_LAB_2_MENU_H
