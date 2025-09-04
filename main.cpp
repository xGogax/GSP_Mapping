#include <iostream>

#include "Skelet/BusStop.h"
#include "Skelet/Network.h"

using namespace std;

int main() {
    Network t;
    t.addLine("6!Tasmajdan /park/!Ustanicka!");
    t.addLine("7!Ustanicka!Blok 45!");

    cout << "#############################################################" << endl;

    BusStop::printMap();

    char x = getchar();
    return 0;
}