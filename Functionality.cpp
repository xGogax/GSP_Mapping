#include "Functionality.h"

#include "Exception/BuiltInExceptions/FileCantBeOpenException.h"
#include "Exception/BuiltInExceptions/StationNotExists.h"

unordered_set<string> Functionality::getCommonLines(const string &line) const {
    unordered_set<string> result;

    for (const auto& pair : busStops) {
        const BusStop& stop = pair.second;

        if (stop.getBusLines().count(line)) {
            for (const auto& otherLine : stop.getBusLines()) {
                if (otherLine != line) {
                    result.insert(otherLine);
                }
            }
        }
    }

    //ispis
    cout << "Lines that divide a stop with a line " << line << ": ";
    for (const auto& l : result) {
        cout << l << " ";
    }
    cout << endl;

    return result;
}

vector<string> Functionality::getMostCommonLines(const string &line) const {
    unordered_map<string, int> counter;

    for (const auto& pair : busStops) {
        const BusStop& stop = pair.second;
        if (stop.getBusLines().count(line)) {
            for (const auto& otherLine : stop.getBusLines()) {
                if (otherLine != line) {
                    counter[otherLine]++;
                }
            }
        }
    }

    // Nadji maksimalan broj
    int maxCount = 0;
    for (const auto& p : counter) {
        if (p.second > maxCount) {
            maxCount = p.second;
        }
    }

    // Skupi sve linije koje imaju maxCount
    vector<string> result;
    for (const auto& p : counter) {
        if (p.second == maxCount) {
            result.push_back(p.first);
        }
    }

    // Ispis
    cout << "Line " << line << " has most common lines with: ";
    for (size_t i = 0; i < result.size(); i++) {
        cout << result[i];
        if (i < result.size() - 1) cout << ", ";
    }
    cout << " (" << maxCount << " common)" << endl;

    return result;
}

pair<int, string> Functionality::findNearestStop(double lat, double lon, const string &line) const {
    // Lambda za racunanje rastojanja
    auto distance = [](double lat1, double lon1, double lat2, double lon2) -> double {
        double dLat = lat2 - lat1;
        double dLon = lon2 - lon1;
        return sqrt(dLat*dLat + dLon*dLon);
    };

    double minDist = numeric_limits<double>::max();
    int nearestID = -1;
    string nearestName;

    for (const auto& pair : busStops) {
        const BusStop& stop = pair.second;

        // Ako je linija zadana, proveri da li stop ima tu liniju
        if (!line.empty()) {
            const auto& stopLines = stop.getBusLines();
            if (find(stopLines.begin(), stopLines.end(), line) == stopLines.end()) {
                continue; // preskoci ako linija nije tu
            }
        }

        double stopLat = stop.getLocation().getLat();
        double stopLon = stop.getLocation().getLon();
        double d = distance(lat, lon, stopLat, stopLon);

        if (d < minDist) {
            minDist = d;
            nearestID = stop.getIdBusStop();
            nearestName = stop.getName();
        }
    }

    if (nearestID != -1) {
        cout << "Closest station: " << nearestID << " (" << nearestName << ")"
                << ", distance: " << minDist << endl;
    } else {
        cout << "There are no stations on inserted line." << endl;
    }

    return {nearestID, nearestName};
}

void Functionality::countCommonStops(int minCommon) const {
    // 1. Pravimo mapu linija -> set stajalista
    unordered_map<string, unordered_set<int>> lineStops;
    for (const auto& pair : busStops) {
        const BusStop& stop = pair.second;
        int stopID = stop.getIdBusStop();
        for (const auto& line : stop.getBusLines()) {
            lineStops[line].insert(stopID);
        }
    }

    // 2. Idemo kroz sve parove linija
    for (size_t i = 0; i < lines.size(); ++i) {
        const string& line1 = lines[i];
        const auto& stops1 = lineStops[line1];

        for (size_t j = i + 1; j < lines.size(); ++j) {
            const string& line2 = lines[j];
            const auto& stops2 = lineStops[line2];

            // 3. Racunamo broj zajednickih stajalista
            int commonCount = 0;
            for (int s : stops1) {
                if (stops2.count(s)) ++commonCount;
            }

            // 4. Filtriramo po minCommon
            if (commonCount >= minCommon) {
                cout << "Line pair: " << line1 << " i " << line2
                        << " -> Common stations: " << commonCount << endl;
            }
        }
    }
}

vector<string> Functionality::getLinesForStop(int stopID, bool print) const {
    unordered_set<string> resultSet;

    for (const auto& pair : busStops) {
        const BusStop& stop = pair.second;
        if (stop.getIdBusStop() == stopID) {
            for (const auto& line : stop.getBusLines()) {
                resultSet.insert(line);
            }
        }
    }

    vector<string> result(resultSet.begin(), resultSet.end());
    sort(result.begin(), result.end());

    if (print) {
        cout << "Station " << stopID << " has lines: ";
        for (size_t i = 0; i < result.size(); i++) {
            cout << result[i];
            if (i < result.size() - 1) cout << ", ";
        }
        cout << endl;
    }

    return result;
}

vector<pair<int,string>> Functionality::getNextStops(int stopID, bool print) const {
    vector<pair<int,string>> result;
    unordered_set<int> added;

    vector<string> linesForStop = getLinesForStop(stopID, false);

    for (const auto& line : linesForStop) {
        for (const string& dir : {"_dirA.txt", "_dirB.txt"}) {
            string path = "data/" + line + dir;
            ifstream in(path);
            if (!in.is_open()) continue;

            vector<int> stops;
            string lineStr;
            while (getline(in, lineStr)) {
                size_t pos = lineStr.find('!');
                if (pos == string::npos) continue;
                stops.push_back(stoi(lineStr.substr(0,pos)));
            }
            in.close();

            auto it = find(stops.begin(), stops.end(), stopID);
            if (it != stops.end()) {
                int nextID;
                if (it + 1 != stops.end()) nextID = *(it + 1);
                else continue; // poslednji u ovom fajlu -> preskoci za sada

                if (added.find(nextID) == added.end()) {
                    string nextName = busStops.count(nextID) ? busStops.at(nextID).getName() : "Unknown name";
                    result.push_back({nextID, nextName});
                    added.insert(nextID);
                }
            }
        }
    }

    if (print) {
        cout << "From station " << stopID << " the following stops can be reached with one ride:" << endl;
        for (const auto& s : result) {
            cout << s.first << " (" << s.second << ")" << endl;
        }
    }

    return result;
}

int Functionality::minTransfers(int a, int b) const {
    // uzimamo linije sa startne i krajnje stanice
    vector<string> startLines = getLinesForStop(a, false);
    vector<string> endLines   = getLinesForStop(b, false);

    unordered_set<string> endSet(endLines.begin(), endLines.end());

    // odmah resenje ako postoji zajednicka linija
    for (const auto& l : startLines) {
        if (endSet.count(l)) {
            cout << "Direct with bus " << l << "\n";
            return 0;
        }
    }

    // graf linija: povezujemo sve linije koje dele stajaliste
    unordered_map<string, unordered_set<string>> lineGraph;
    for (const auto& [stopID, stop] : busStops) {
        const auto& lines = stop.getBusLines();
        for (auto it1 = lines.begin(); it1 != lines.end(); ++it1) {
            for (auto it2 = next(it1); it2 != lines.end(); ++it2) {
                lineGraph[*it1].insert(*it2);
                lineGraph[*it2].insert(*it1);
            }
        }
    }

    // BFS
    unordered_map<string,int> dist;
    unordered_map<string,string> parent;
    queue<string> q;

    for (const auto& l : startLines) {
        dist[l] = 0;
        parent[l] = "";
        q.push(l);
    }

    string found = "";
    while (!q.empty()) {
        string u = q.front(); q.pop();
        int d = dist[u];

        if (endSet.count(u)) {
            found = u;
            break;
        }

        for (const auto& v : lineGraph[u]) {
            if (!dist.count(v)) {
                dist[v] = d + 1;
                parent[v] = u;
                q.push(v);
            }
        }
    }

    if (found == "") return -1;

    vector<string> path;
    for (string cur = found; cur != ""; cur = parent[cur]) {
        path.push_back(cur);
    }
    reverse(path.begin(), path.end());

    // ispis
    cout << "Putanja: ";
    for (size_t i = 0; i < path.size(); i++) {
        cout << path[i];
        if (i + 1 < path.size()) cout << " -> ";
    }
    cout << "\n";

    return dist[found];
}

int Functionality::shortestStops(int a, int b) const {
    if (a == b) return 0;

    unordered_map<int,int> dist;
    unordered_map<int,int> parent;
    queue<int> q;

    dist[a] = 0;
    parent[a] = -1;
    q.push(a);

    while (!q.empty()) {
        int u = q.front(); q.pop();

        if (u == b) break;

        auto nextStops = getNextStops(u, false);
        for (const auto& [v, _] : nextStops) {
            if (!dist.count(v)) {
                dist[v] = dist[u] + 1;
                parent[v] = u;
                q.push(v);
            }
        }
    }

    if (!dist.count(b)) return -1; // nema puta

    // rekonstrukcija puta
    vector<int> path;
    for (int cur = b; cur != -1; cur = parent[cur]) {
        path.push_back(cur);
    }
    reverse(path.begin(), path.end());

    cout << "Shortest path (" << dist[b] << " stations): ";
    for (size_t i = 0; i < path.size(); i++) {
        cout << path[i];
        if (i + 1 < path.size()) cout << " -> ";
    }
    cout << "\n";

    return dist[b];
}

void Functionality::searchStation(const string &stationID) const {
    int id;
    try { id = stoi(stationID); }
    catch (...) {
        throw StationNotExists(stationID);
    }

    auto it = BusStop::getBusStops().find(id);
    if (it == BusStop::getBusStops().end()) {
        throw StationNotExists(stationID);
    }

    const BusStop& stop = it->second;
    std::cout << "Stanica " << stop.getIdBusStop()
            << " - " << stop.getName()
            << " (Lon: " << stop.getLocation().getLon()
            << ", Lat: " << stop.getLocation().getLat()
            << ", Zona: " << stop.getZone() << ")" << std::endl;
}

bool Functionality::passesThroughInSameDirection(const string &line, int stop1, int stop2) const {
    // 1. Proveri da li linija postoji u mapi
    if (find(lines.begin(), lines.end(), line) == lines.end()) {
        cout << "Line " << line << " does not exist in BusStops." << endl;
        return false;
    }

    // Helper lambda da proveri datu datoteku
    auto checkFile = [&](const string& path) -> bool {
        ifstream in(path);
        if (!in.is_open()) {
            throw FileCantBeOpenException();
            return false;
        }

        bool found1 = false, found2 = false;
        string lineStr;

        while (getline(in, lineStr)) {
            // Uzmemo prvi token pre prvog "!"
            size_t pos = lineStr.find('!');
            if (pos == string::npos) continue;

            int id = stoi(lineStr.substr(0, pos));

            if (id == stop1) found1 = true;
            if (id == stop2) found2 = true;
        }
        in.close();
        return (found1 && found2);
    };

    // 2. Proveri dirA
    string pathA = "data/" + line + "_dirA.txt";
    if (checkFile(pathA)) {
        cout << "Line " << line << " goes through stations "
                << stop1 << " i " << stop2 << " in direction dirA" << endl;
        return true;
    }

    // 3. Ako ne, proveri dirB
    string pathB = "data/" + line + "_dirB.txt";
    if (checkFile(pathB)) {
        cout << "Line " << line << " goes through stations "
                << stop1 << " i " << stop2 << " in direction dirB." << endl;
        return true;
    }

    // 4. Ni u jednom smeru
    cout << "Line " << line << " does not go through this stations in same direction" << endl;
    return false;
}
