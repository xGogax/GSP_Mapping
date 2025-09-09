#include <iostream>

#include "Skelet/BusStop.h"
#include "Skelet/Network.h"

using namespace std;

int main() {
    ifstream file("data/_lines.txt");

    if (!file.is_open()) {
        cerr << "Greska: fajl se ne moze otvoriti!" << endl;
        return 1;
    }

    string line;
    Network t;
    while (getline(file, line)) {
        t.addLine(line);
    }

    file.close();

    t.removeLine("7");
    cout << "--------------------------------" << endl;
    BusStop::printMap();
    cout << "--------------------------------" << endl;
    t.printBusStops("6");


    //TODO izmenu podataka o liniji
    //TODO dodati opciju filtriranja
    //TODO funkcionalnosti linije
    //TODO dodati L i C moduo generatora (Generator -> (L, C))
    
    return 0;
}