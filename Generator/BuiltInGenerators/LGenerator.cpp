#include "LGenerator.h"

void LGenerator::build(const unordered_map<int, BusStop>& busStops) {
    LGraph.clear();

    for (const auto& [stopID, stop] : busStops) {
        auto nextStops = func.getNextStops(stopID, false);

        for (const auto& ns : nextStops) {
            int nextID = ns.first;
            LGraph[stopID].insert(nextID);
            LGraph[nextID].insert(stopID);
        }
    }
}

void LGenerator::print() const {
    for (const auto& [stop, neighbors] : LGraph) {
        cout << "Station " << stop << " is connected with: ";
        for (int n : neighbors) {
            cout << n << " ";
        }
        cout << endl;
    }
}

void LGenerator::exportGraph(const string &filename) const {
    ofstream out("output/" + filename);
    if (!out.is_open()) {
        cerr << "Cant open file for writing: " << filename << endl;
        return;
    }

    if (format == Format::GML) {
        out << "graph\n[\n";
        for (const auto& [node, neighbors] : LGraph) {
            out << "  node\n  [\n";
            out << "    id " << node << "\n";
            out << "    label \"" << node << "\"\n";
            out << "  ]\n";
        }
        unordered_set<string> addedEdges;
        for (const auto& [node, neighbors] : LGraph) {
            for (int n : neighbors) {
                string edgeKey = to_string(node) + "-" + to_string(n);
                string edgeKeyRev = to_string(n) + "-" + to_string(node);
                if (addedEdges.count(edgeKey) || addedEdges.count(edgeKeyRev)) continue;
                addedEdges.insert(edgeKey);
                out << "  edge\n  [\n";
                out << "    source " << node << "\n";
                out << "    target " << n << "\n";
                out << "    label \"Edge " << node << " to " << n << "\"\n";
                out << "  ]\n";
            }
        }
        out << "]\n";
    } else if (format == Format::CSV) {
        for (const auto& [node, neighbors] : LGraph) {
            out << node;
            for (int n : neighbors) {
                out << ";" << n;
            }
            out << "\n";
        }
    }

    out.close();
    cout << "Graf is exported into file: output/" << filename << endl;
}
