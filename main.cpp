#include <iostream>

#include "Filteri/Filter.h"
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

    // t.removeLine("7");
    // cout << "--------------------------------" << endl;
    // cout << "--------------------------------" << endl;
    // t.printBusStops("6");

    Filter f;
    // f.printLines();
    f.apply(1);
    f.apply(2);

    f.apply(4);

    f.apply(2);

    //TODO izmenu podataka o liniji
    //TODO funkcionalnosti linije
    //TODO dodati L i C moduo generatora (Generator -> (L, C))
    
    return 0;
}