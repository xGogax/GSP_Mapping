#include "BusStop.h"

unordered_map<int, BusStop> BusStop::BusStops = unordered_map<int, BusStop>();

BusStop BusStop::createBusStop(string input, string busNum) {
    regex re("!");
    sregex_token_iterator it(input.begin(), input.end(), re, -1);
    sregex_token_iterator end;

    vector<string> tokens;
    for (; it != end; ++it) {
        if (!it->str().empty()) {
            tokens.push_back(*it);
        }
    }

    if (tokens.size() < 5) {
        cout << "ERROR: NOT VALID FORMAT" << endl;
    }

    //ukoliko ne nadje (valid)
    if(BusStops.find(stoi(tokens[0])) == BusStops.end()) {
        BusStop busStop = BusStop(stoi(tokens[0]), tokens[1], stod(tokens[2]), stod(tokens[3]), stoul(tokens[4]));
        busStop.busLines.insert(busNum);
        BusStops.emplace(busStop.idBusStop, busStop);
        return busStop;
    }
    //ukoliko ga nadje u mapi
    else {
        auto it = BusStops.find(stoi(tokens[0]));
        if (it != BusStops.end()) {
            it->second.busLines.insert(busNum);
        }
        return it->second;
    }
}

void BusStop::fillMap(string filename, vector<BusStop>& vec) {
    // --- izvuci busNum iz imena fajla ---
    size_t pos = filename.find('_');
    string busNum = (pos != string::npos) ? filename.substr(0, pos) : filename;

    // --- dodaj liniju u mapu preko createBusStop ---
    ifstream file("data/" + filename);
    if (!file.is_open()) {
        cerr << "ERROR: Ne mogu da otvorim fajl: " << filename << endl;
        throw 1;
    }

    string line;
    while (getline(file, line)) {
        if (!line.empty()) {
            vec.push_back(createBusStop(line, busNum));
        }
    }
    file.close();
}

void BusStop::printMap() {
    cout << "=== BUS STOPS MAP ===" << endl;
    for (const auto &pair : BusStops) {
        const BusStop &bs = pair.second;
        cout << "ID: " << bs.idBusStop
             << " | Name: " << bs.name
             << " | Zone: " << bs.zone
             << " | Location: (" << bs.location.getLat()
             << ", " << bs.location.getLon() << ")"
             << " | Lines: ";

        for (const auto &line : bs.busLines) {
            cout << line << " ";
        }
        cout << endl;
    }
}