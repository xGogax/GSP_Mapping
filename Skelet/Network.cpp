#include "Network.h"

void Network::addBusStop(string busNum, string dir, string input) {
    for (auto &line:lines) {
        if (busNum == line.getBusNum()) {
            if (dir == "A") {
                line.getDirectionA().addBussStop(input);
                BusStop::addBusStop(input, busNum);
                return;
            } else if (dir == "B") {
                line.getDirectionB().addBussStop(input);
                BusStop::addBusStop(input, busNum);
                return;
            } else {
                cout << "ERROR: Wrong direction" << endl;
            }
        }
    }
    cout << "ERROR: Ne postoji zadata linija" << endl;
}

void Network::removeBusStop(string busStopID) {
    BusStop::removeFromMap(busStopID);
}

void Network::removeLine(string busNum) {
    for (int i = 0; i < lines.size(); i++) {
        if (lines[i].getBusNum() == busNum) {
            lines[i].getDirectionA().removeBusStops();
            lines[i].getDirectionB().removeBusStops();
            lines.erase(lines.begin() + i);
        }
    }
}

void Network::updateLine(string oldBusNum, string newBusNum) {
    for (auto &line : lines) {
        if (line.getBusNum() == newBusNum) {
            cout << "ERROR: Bus already exists" << endl;
            return;
        }
    }

    for (auto &line : lines) {
        if (line.getBusNum() == oldBusNum) {
            line.setBusNum(newBusNum);
            break;
        }
    }

    BusStop::changeBusLines(oldBusNum, newBusNum);
}

void Network::printBusStops(string busNum) const {
    for (auto line:lines) {
        if (line.getBusNum() == busNum) {
            for (auto sigma:line.getDirectionA().getBusStops()) {
                cout << sigma.getIdBusStop() << " ";
                cout << sigma.getName() << endl;
            }
            cout << "//////////////////////////" << endl;
            for (auto sigma:line.getDirectionB().getBusStops()) {
                cout << sigma.getIdBusStop() << " ";
                cout << sigma.getName() << endl;
            }
            return;
        }
    }
}
