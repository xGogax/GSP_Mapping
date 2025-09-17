#include "Functionality.h"

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

    // Konačan ispis
    cout << "Linije koje dele stajalista sa linijom " << line << ": ";
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
    cout << "Linija " << line << " ima najvise zajednickih stajalista sa: ";
    for (size_t i = 0; i < result.size(); i++) {
        cout << result[i];
        if (i < result.size() - 1) cout << ", ";
    }
    cout << " (" << maxCount << " zajednickih)" << endl;

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
        cout << "Najblize stajaliste: " << nearestID << " (" << nearestName << ")"
                << " na rastojanju " << minDist << endl;
    } else {
        cout << "Nema stajalista za zadatu liniju." << endl;
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
                cout << "Par linija: " << line1 << " i " << line2
                        << " -> zajednickih stajalista: " << commonCount << endl;
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
        cout << "Stajaliste " << stopID << " ima linije: ";
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
                    string nextName = busStops.count(nextID) ? busStops.at(nextID).getName() : "Nepoznat naziv";
                    result.push_back({nextID, nextName});
                    added.insert(nextID);
                }
            }
        }
    }

    if (print) {
        cout << "Iz stajalista " << stopID << " moze se stici do sledecih stajalista uz jednu voznju:" << endl;
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

    // odmah resenje ako postoji zajednička linija
    for (const auto& l : startLines) {
        if (endSet.count(l)) {
            cout << "Direktno autobusom " << l << "\n";
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
    unordered_map<string,string> parent;  // pamti roditelja linije
    queue<string> q;

    for (const auto& l : startLines) {
        dist[l] = 0;
        parent[l] = ""; // koren nema roditelja
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

    if (found == "") return -1; // nema veze

    // rekonstrukcija puta
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

        if (u == b) break; // stigli smo

        // svi sledeći susedi preko linija
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

    cout << "Najkraci put (" << dist[b] << " stajalista): ";
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
        std::cout << "Nevalidan ID stanice." << std::endl;
        return;
    }

    auto it = BusStop::getBusStops().find(id);
    if (it == BusStop::getBusStops().end()) {
        std::cout << "Stanica " << stationID << " ne postoji u mapi." << std::endl;
        return;
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
        cout << "Linija " << line << " ne postoji u mapi." << endl;
        return false;
    }

    // Helper lambda da proveri datu datoteku
    auto checkFile = [&](const string& path) -> bool {
        ifstream in(path);
        if (!in.is_open()) {
            cout << "Ne mogu da otvorim fajl: " << path << endl;
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
        cout << "Linija " << line << " prolazi kroz stajalista "
                << stop1 << " i " << stop2 << " u smeru dirA." << endl;
        return true;
    }

    // 3. Ako ne, proveri dirB
    string pathB = "data/" + line + "_dirB.txt";
    if (checkFile(pathB)) {
        cout << "Linija " << line << " prolazi kroz stajalista "
                << stop1 << " i " << stop2 << " u smeru dirB." << endl;
        return true;
    }

    // 4. Ni u jednom smeru
    cout << "Linija " << line << " ne prolazi kroz oba stajalista u istom smeru." << endl;
    return false;
}
