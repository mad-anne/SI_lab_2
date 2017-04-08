//
// Created by Anna Siwik on 2017-04-07.
//

<<<<<<< HEAD
#include <iostream>
=======
>>>>>>> 8e927268749581ebfa7dbdd3c68afe7a0c154d50
#include "../header/Color.h"

Color::Color()
{
    value = -1;
}

<<<<<<< HEAD
Color::~Color()
{ }

const int Color::getValue() const
=======
int Color::getValue()
>>>>>>> 8e927268749581ebfa7dbdd3c68afe7a0c154d50
{
    return value;
}

<<<<<<< HEAD
const int Color::setValue(int value)
=======
int Color::setValue(int value)
>>>>>>> 8e927268749581ebfa7dbdd3c68afe7a0c154d50
{
    return this->value = value;
}

<<<<<<< HEAD
const int Color::resetValue()
=======
int Color::resetValue()
>>>>>>> 8e927268749581ebfa7dbdd3c68afe7a0c154d50
{
    return this->value = -1;
}
