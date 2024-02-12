#pragma once
#include <vector>
#include "trenchCoat.h"


class AbstractShoppingBasket {
protected:

    std::vector<trenchCoat> data;

public:

    virtual void write() = 0;

    virtual void open() = 0;

    virtual void setData(std::vector<trenchCoat> dataToSet) = 0;        // puteam sa facem implementarea la setData aici pt ca e la fel si pt CSV si pt HTML

    virtual ~AbstractShoppingBasket() = default;
};