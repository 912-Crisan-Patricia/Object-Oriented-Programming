#include "HTMLBasket.h"
#include "trenchCoat.h"
#include "customExceptions.h"
#include <iostream>
#include <fstream>
#include <utility>
#include <string>
#include <windows.h>
#include <shellapi.h>


HTMLShoppingBasket::HTMLShoppingBasket() {
    this->fileName = R"(C:\Users\Patri-PC\Desktop\MATERII UBB\1\II semester\Object Oriented Programming\Assignment_6\Assignment_6\basket.html)";
}

void HTMLShoppingBasket::write() {
    std::ofstream out(this->fileName);
    if (!out.is_open())
        throw RepositoryException("Could not open the file!");
    out << "<!DOCTYPE html>\n";
    out << "<html>\n";
    out << "<head>\n";
    out << "\t<title>Shopping basket</title>\n";
    out << "</head>\n";
    out << "<body>\n";
    out << "<table border=\"1\">\n";
    out << "\t<tr>\n";
    out << "\t\t<td><b>Size</b></td>\n";
    out << "\t\t<td><b>Color</b></td>\n";
    out << "\t\t<td><b>Price</b></td>\n";
    out << "\t\t<td><b>Quantity</b></td>\n";
    out << "\t\t<td><b>Photograph</b></td>\n";
    out << "\t</tr>\n";
    for (auto currentCoat : this->data)
        out << currentCoat.getHTMLRepresentation() << "\n";
    out << "</table>\n";
    out << "</body>\n";
    out << "</html>";

    out.close();
    this->data.clear();
}

void HTMLShoppingBasket::open() {
    std::ifstream in(this->fileName);

    if (!in.is_open())
        throw RepositoryException("Could not open the file!");

    ShellExecute(nullptr, nullptr, R"(C:\Users\Patri-PC\Desktop\MATERII UBB\1\II semester\Object Oriented Programming\Assignment_6\Assignment_6\basket.html)", nullptr, nullptr, SW_SHOWNORMAL);

    in.close();
}

void HTMLShoppingBasket::setData(std::vector<trenchCoat> dataToSet) {
    this->data = std::move(dataToSet);
}

HTMLShoppingBasket::~HTMLShoppingBasket() = default;