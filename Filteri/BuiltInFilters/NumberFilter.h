#ifndef NUMBERFILTER_H
#define NUMBERFILTER_H

#include <unordered_set>
#include <vector>
#include <string>
#include <cctype>
#include <iostream>
#include <sstream>

using namespace std;

class NumberFilter {
public:
    NumberFilter(int option, int num1, int num2 = 0) : option(option), num1(num1), num2(num2) {}

    unordered_set<string> apply(const vector<string>& allLines) const;

private:
    int option; // 1 = < num, 2 = > num, 3 = between num1 and num2
    int num1;
    int num2;

    // Funkcija koja iz stringa izvuce broj linije
    int extractNumber(const string& s) const {
        string digits;
        for (char c : s) {
            if (isdigit(c)) digits += c;
        }
        if (!digits.empty()) return stoi(digits);
        return 0;
    }
};

#endif