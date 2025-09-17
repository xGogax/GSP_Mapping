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

    Direction &getDirectionA() {
        return a;
    }
    Direction &getDirectionB() {
        return b;
    }

    string getBusNum() const {
        return busNum;
    }

    void setBusNum(string busNum) {
        this->busNum = busNum;
    }

private:
    Line(const string &busNum, const string &startPoint, const string &endPoint) :
    a(busNum + "_dirA.txt", busNum), b(busNum + "_dirB.txt", busNum), busNum(busNum), startPoint(startPoint), endPoint(endPoint) {
    }

    Direction a;
    Direction b;
    string busNum;
    string startPoint;
    string endPoint;
};

#endif
