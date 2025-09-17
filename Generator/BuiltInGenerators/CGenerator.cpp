#include "CGenerator.h"

void CGenerator::build(const unordered_map<int, BusStop> &busStops) {
    CGraph.clear();

    // Prolazimo kroz sva stajalista
    for (const auto& [stopID, stop] : busStops) {
        const auto& lines = stop.getBusLines();
        for (auto it1 = lines.begin(); it1 != lines.end(); ++it1) {
            for (auto it2 = next(it1); it2 != lines.end(); ++it2) {
                // povezi linije sa zajednickim stajalistem
                CGraph[*it1].insert(*it2);
                CGraph[*it2].insert(*it1);
            }
        }
    }
}

void CGenerator::print() const {
    cout << "C-Model (Lines as nodes):\n";
    for (const auto& [line, neighbors] : CGraph) {
        cout << "Line " << line << " -> ";
        for (const auto& n : neighbors) {
            cout << n << " ";
        }
        cout << "\n";
    }
}

void CGenerator::exportGraph(const string& filename) const {
    ofstream out("output/" + filename);
    if (!out.is_open()) {
        cerr << "Ne mogu da otvorim fajl za pisanje: " << filename << endl;
        return;
    }

    if (format == Format::GML) {
        out << "graph\n[\n";
        for (const auto& [node, neighbors] : CGraph) {
            out << "  node\n  [\n";
            out << "    id \"" << node << "\"\n";
            out << "    label \"" << node << "\"\n";
            out << "  ]\n";
        }

        unordered_set<string> addedEdges;
        for (const auto& [node, neighbors] : CGraph) {
            for (const auto& n : neighbors) {
                string edgeKey = node + "-" + n;
                string edgeKeyRev = n + "-" + node;
                if (addedEdges.count(edgeKey) || addedEdges.count(edgeKeyRev)) continue;
                addedEdges.insert(edgeKey);

                out << "  edge\n  [\n";
                out << "    source \"" << node << "\"\n";
                out << "    target \"" << n << "\"\n";
                out << "    label \"Edge " << node << " to " << n << "\"\n";
                out << "  ]\n";
            }
        }

        out << "]\n";
    } else if (format == Format::CSV) {
        for (const auto& [node, neighbors] : CGraph) {
            out << node;
            for (const auto& n : neighbors) {
                out << ";" << n;
            }
            out << "\n";
        }
    }

    out.close();
    cout << "Graf je exportovan u fajl: output/" << filename << endl;
}