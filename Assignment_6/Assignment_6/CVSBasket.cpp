#include "CSVBasket.h"
#include "trenchCoat.h"
#include "customExceptions.h"
#include <iostream>
#include <fstream>
#include <utility>
#include <string>
#include <windows.h>
#include <shellapi.h>


CSVShoppingBasket::CSVShoppingBasket() {
    this->fileName = R"(C:\Users\Patri-PC\Desktop\MATERII UBB\1\II semester\Object Oriented Programming\Assignment_6\Assignment_6\basket.csv)";
}

void CSVShoppingBasket::write() {
    std::ofstream out(this->fileName);
    if (!out.is_open())
        throw RepositoryException("Could not open the file!");
    for (auto currentCoat : this->data)
        out << currentCoat.getCSVRepresentation() << "\n";

    out.close();
    this->data.clear();
}

void CSVShoppingBasket::open() {
    std::ifstream in(this->fileName);

    if (!in.is_open())
        throw RepositoryException("Could not open the file!");

    ShellExecute(nullptr, nullptr, R"(C:\Users\Patri-PC\Desktop\MATERII UBB\1\II semester\Object Oriented Programming\Assignment_6\Assignment_6\basket.csv)", nullptr, nullptr, SW_SHOWNORMAL);

    //    string topic;
    //    topic = "notepad \"" + this->fileName + "\"";
    //    system(topic.c_str());

    in.close();
}

void CSVShoppingBasket::setData(std::vector<trenchCoat> dataToSet) {
    this->data = std::move(dataToSet);
}

CSVShoppingBasket::~CSVShoppingBasket() = default;