#include "Direction.h"

void Direction::printDirection() const {
    cout << "Filename: " << filename << endl;
    cout << "Bus Stops:" << endl;
    for (const auto &bs : busStops) {
        cout << "ID: " << bs.getIdBusStop()
             << " | Name: " << bs.getName()
             << " | Zone: " << bs.getZone()
             << " | Location: (" << bs.getLocation().getLat()
             << ", " << bs.getLocation().getLon() << ")"
             << endl;
    }
}
