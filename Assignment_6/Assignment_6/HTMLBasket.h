#pragma once
#include "AbstractBasket.h"
#include <string>


class HTMLShoppingBasket : public AbstractShoppingBasket {
private:

    string fileName;

public:

    HTMLShoppingBasket();

    void write() override;

    void open() override;

    void setData(std::vector<trenchCoat> dataToSet) override;

    ~HTMLShoppingBasket() override;
};