#include <iostream>

#include "Functionality.h"
#include "Filteri/Filter.h"
#include "Generator/BuiltInGenerators/CGenerator.h"
#include "Generator/BuiltInGenerators/LGenerator.h"
#include "Skelet/BusStop.h"
#include "Skelet/Network.h"

using namespace std;

void option1(Network& t) {
    ifstream file("data/_lines.txt");
    if (!file.is_open()) {
        cerr << "Greska: fajl se ne moze otvoriti!" << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        t.addLine(line);
    }

    file.close();
}

int main() {
    Network network;
    while (true) {
        cout << "--- GSP APP ---" << endl;
        cout << " 1. Load from data/_lines" << endl;
        cout << " 2. Add line" << endl;
        cout << " 3. Delete line" << endl;
        cout << " 4. Add Station" << endl;
        cout << " 5. Delete Station" << endl;
        cout << " 6. Update Station" << endl;
        cout << " 7. Update Line" << endl;
        cout << " 8. Search Line" << endl;
        cout << " 9. Search Station" << endl;
        cout << "10. Print map" << endl;
        cout << "11. Options" << endl;
        cout << "12. Filter" << endl;
        cout << "13. Generate output file" << endl;
        cout << "14. Exit" << endl;
        cout << "---------------" << endl;

        int x;
        cin >> x;
        cout << "---------------" << endl;

        switch (x) {
            case 1:
                option1(network);
                break;
            case 2: {
                cout << "Add line in next format: \"number!start!end\"";
                string addLineLine;
                cin >> addLineLine;
                network.addLine(addLineLine);
                break;
            }
            case 3: {
                cout << "What line would you like to remove?" << endl;
                string deleteLineLine;
                cin >> deleteLineLine;
                network.removeLine(deleteLineLine);
                break;
            }
            case 4: {
                cout << "Add bus that you want to attach the station to" << endl;
                string addStationID;
                cin >> addStationID;
                cout << "Add direction that you want this station to be" << endl;
                string addStationDirection;
                cin >> addStationDirection;
                cout << "Add station information in format stationID!Name!lon!lat!zone" << endl;
                string addStationInput;
                cin >> addStationInput;
                network.addBusStop(addStationID, addStationDirection, addStationInput);
                break;
            }
            case 5: {
                cout << "What station would you like to be removed?" << endl;
                string deleteStationID;
                cin >> deleteStationID;
                network.removeBusStop(deleteStationID);
                break;
            }
            case 6: {
                cout << "--- UPDATE ---" << endl;
                cout << "1. Update Name" << endl;
                cout << "2. Update Zone" << endl;
                cout << "3. Update Location" << endl;

                int sigma;
                cin >> sigma;
                if (sigma == 1) {
                    cout << "Insert StationID" << endl;
                    int stationID;
                    cin >> stationID;
                    cout << "Insert new station name" << endl;
                    string stationName;
                    cin >> stationName;
                    BusStop::changeBusStopName(stationID, stationName);
                } else if(sigma == 2) {
                    cout << "Insert StationID" << endl;
                    int stationID;
                    cin >> stationID;
                    cout << "Insert new station zone" << endl;
                    int stationZone;
                    cin >> stationZone;
                    BusStop::changeBusStopZone(stationID, stationZone);
                } else if (sigma == 3) {
                    cout << "Insert StationID" << endl;
                    int stationID;
                    cin >> stationID;
                    cout << "Insert lat" << endl;
                    double lat;
                    cin >> lat;
                    cout << "Insert lon" << endl;
                    double lon;
                    cin >> lon;
                    Location location(lat, lon);
                    BusStop::changeBusStopLocation(stationID, location);
                } else {
                    cout << "Invalid input" << endl;
                }
                break;
            }
            case 7: {
                break;
            }
            case 8: {
                cout << "What line whould you like to see?" << endl;
                string searchLine;
                cin >> searchLine;
                network.printBusStops(searchLine);
                break;
            }
            case 9: {
                cout << "What station would you like to search?" << endl;
                Functionality functionality;
                string searchStationID;
                cin >> searchStationID;
                functionality.searchStation(searchStationID);
                break;
            }
            case 10: {
                BusStop::printMap();
                break;
            }
            case 11: {
                Functionality functionality;
                cout << "--- OPTIONS ---" << endl;
                cout << "1. Common lines with line " << endl;
                cout << "2. Check if line passes through 2 stations in same direction" << endl;
                cout << "3. Most common lines with line" << endl;
                cout << "4. Closest station" << endl;
                cout << "5. Count common stops" << endl;
                cout << "6. Lines that goes through selected stop" << endl;
                cout << "7. Next Stops" << endl;
                cout << "8. Minimal Transfers" << endl;
                cout << "9. Shortest Stops" << endl;
                cout << "10. Exit" << endl;
                cout << "---------------" << endl;

                int t;
                cin >> t;

                if (t == 1) {
                    cout << "Insert line" << endl;
                    string line;
                    cin >> line;
                    functionality.getCommonLines(line);
                } else if (t == 2) {
                    cout << "Insert line" << endl;
                    string line;
                    cin >> line;
                    cout << "Insert station 1" << endl;
                    int stationID1;
                    cin >> stationID1;
                    cout << "Insert station 2" << endl;
                    int stationID2;
                    cin >> stationID2;
                    functionality.passesThroughInSameDirection(line, stationID1, stationID2);
                } else if (t == 3) {
                    cout << "Insert line" << endl;
                    string line;
                    cin >> line;
                    functionality.getMostCommonLines(line);
                } else if (t == 4) {
                    cout << "--- OPTIONS --- " << endl;
                    cout << "1. Overall closest location" << endl;
                    cout << "2. Closest location to line" << endl;
                    cout << "---------------" << endl;
                    int k;
                    cin >> k;
                    if (k != 1 && k != 2) cout << "Invalid input" << endl;
                    cout << "Insert lat" << endl;
                    double lat;
                    cin >> lat;
                    cout << "Insert lon" << endl;
                    double lon;
                    cin >> lon;
                    if (k == 1) functionality.findNearestStop(lat, lon);
                    else {
                        cout << "Insert line" << endl;
                        string line;
                        cin >> line;
                        functionality.findNearestStop(lat, lon, line);
                    }
                } else if (t == 5) {
                    cout << "--- OPTIONS --- " << endl;
                    cout << "1. All pairs" << endl;
                    cout << "2. At least X stations" << endl;
                    cout << "---------------" << endl;
                    int k;
                    cin >> k;
                    if (k != 1 && k != 2) cout << "Invalid input" << endl;
                    if (k == 1) functionality.countCommonStops(1);
                    if (k == 2) {
                        cout << "Insert X" << endl;
                        int number;
                        cin >> number;
                        functionality.countCommonStops(number);
                    }
                } else if (t == 6) {
                    cout << "Insert BusStopID" << endl;
                    int busStopID;
                    cin >> busStopID;
                    functionality.getLinesForStop(busStopID);
                } else if (t == 7) {
                    cout << "Insert BusStopID" << endl;
                    int busStopID;
                    cin >> busStopID;
                    functionality.getNextStops(busStopID);
                } else if (t == 8) {
                    cout << "Insert BussStopID 1" << endl;
                    int busStopID1;
                    cin >> busStopID1;
                    cout << "Insert BussStopID 2" << endl;
                    int busStopID2;
                    cin >> busStopID2;
                    functionality.minTransfers(busStopID1, busStopID2);
                } else if (t == 9) {
                    cout << "Insert BussStopID 1" << endl;
                    int busStopID1;
                    cin >> busStopID1;
                    cout << "Insert BussStopID 2" << endl;
                    int busStopID2;
                    cin >> busStopID2;
                    functionality.shortestStops(busStopID1, busStopID2);
                } else if (t == 10){
                    break;
                } else {
                    cout << "Invalid input" << endl;
                }
                break;
            }
            case 12: {
                Filter filter;
                while (true) {
                    cout << "--- FILTERS ---" << endl;
                    cout << "1. Zone filter" << endl;
                    cout << "2. Number filter" << endl;
                    cout << "3. StopCountFilter" << endl;
                    cout << "4. Remove Filter" << endl;
                    cout << "5. Exit" << endl;
                    cout << "---------------" << endl;

                    int y; cin >> y;

                    if (y == 1) {
                        filter.apply(1);
                    } else if (y == 2) {
                        filter.apply(2);
                    } else if (y == 3) {
                        filter.apply(3);
                    } else if (y == 4) {
                        filter.apply(4);
                    } else if (y == 5) {
                        break;
                    } else {
                        cout << "Invalid Option" << endl;
                    }
                }
                break;
            }
            case 13: {
                Functionality functionality;
                cout << "--- GENERATORS ---" << endl;
                cout << "1. C Generator" << endl;
                cout << "2. L Generator" << endl;
                cout << "------------------" << endl;

                int p;
                cin >> p;

                cout << "--- MODELS ---" << endl;
                cout << "1. GML" << endl;
                cout << "2. CSV" << endl;
                cout << "--------------" << endl;

                int pp;
                cin >> pp;

                if (p == 1 && pp == 1) {
                    LGenerator lg(functionality, Generator::Format::GML);
                    lg.build(BusStop::getBusStops());
                    lg.exportGraph("LGraph.gml");
                } else if (p == 1 && pp == 2) {
                    LGenerator lg(functionality, Generator::Format::CSV);
                    lg.build(BusStop::getBusStops());
                    lg.exportGraph("LGraph.csv");
                } else if (p == 2 && pp == 1) {
                    CGenerator cg(Generator::Format::GML);
                    cg.build(BusStop::getBusStops());
                    cg.exportGraph("CGraph.gml");
                } else if (p == 2 && pp == 2) {
                    CGenerator cg(Generator::Format::CSV);
                    cg.exportGraph("CGraph.csv");
                    cg.build(BusStop::getBusStops());
                }
                break;
            }
            case 14:
                return 0;
                break;
            default:
                cout << "Invalid option." << endl << endl;
        }
    }
}