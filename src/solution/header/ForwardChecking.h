//
// Created by Anna Siwik on 2017-04-08.
//

#ifndef SI_LAB_2_FORWARDCHECKING_H
#define SI_LAB_2_FORWARDCHECKING_H

#include "../interface/IConstraintSatisfactionProblem.h"

class ForwardChecking : public IConstraintSatisfactionProblem
{
    public:
        ForwardChecking();
        ~ForwardChecking();

        virtual const ISolution* getFirstSolution(IProblemFactory*) override;
        virtual long long int getNumberOfSolutions(IProblemFactory*) override;
        virtual std::vector<ISolution*>* getAllSolutions(IProblemFactory*) override;

    private:
        ISolution* recursive();
        void recursiveFindNumberOfAll();
        void setAttributes(IProblemFactory*);
};


#endif //SI_LAB_2_FORWARDCHECKING_H
