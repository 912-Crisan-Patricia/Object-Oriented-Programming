#pragma once
#include "AbstractBasket.h"
#include <string>

class CSVShoppingBasket : public AbstractShoppingBasket {
private:

    string fileName;

public:

    CSVShoppingBasket();

    void write() override;

    void open() override;

    void setData(std::vector<trenchCoat> dataToSet) override;

    ~CSVShoppingBasket() override;
};
