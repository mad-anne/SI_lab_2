//
// Created by Anna Siwik on 2017-04-13.
//

#include <components/header/MainDomain.h>

MainDomain::MainDomain()
{}

MainDomain::~MainDomain()
{
    clearValues();
}

void MainDomain::clearValues()
{
    for (int index = 0; index < values.size(); ++index)
        delete values[index];

    values.clear();
}