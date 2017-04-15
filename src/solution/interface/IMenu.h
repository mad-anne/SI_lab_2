//
// Created by Anna Siwik on 2017-04-15.
//

#ifndef SI_LAB_2_IMENU_H
#define SI_LAB_2_IMENU_H

class IMenu
{
    public:
        virtual ~IMenu() = default;

        virtual void start() = 0;
};

#endif //SI_LAB_2_IMENU_H
