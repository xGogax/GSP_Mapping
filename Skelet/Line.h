#ifndef LINE_H
#define LINE_H

#include <iostream>
#include <string>
#include <regex>
#include <vector>

#include "Direction.h"

using namespace std;

class Line {
public:
    static Line createLine(string input) {
        regex re("!");
        sregex_token_iterator it(input.begin(), input.end(), re, -1);
        sregex_token_iterator end;

        vector<string> tokens;
        for (; it != end; ++it) {
            if (!it->str().empty()) {
                tokens.push_back(*it);
            }
        }

        if (tokens.size() < 3) {
            cout << "ERROR: NOT VALID FORMAT" << endl;
        }

        return Line(tokens[0], tokens[1], tokens[2]);
    }

private:
    Line(const string &busNum, const string &startPoint, const string &endPoint) :
    busNum(busNum), startPoint(startPoint), endPoint(endPoint) {
        Direction a(busNum + "_dirA.txt");
        Direction b(busNum + "_dirB.txt");
    }

    string busNum;
    string startPoint;
    string endPoint;
};

#endif
