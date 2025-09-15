#include "NumberFilter.h"

unordered_set<string> NumberFilter::apply(const vector<string> &allLines) const {
    unordered_set<string> filteredLines;

    for (const auto& line : allLines) {
        int lineNumber = extractNumber(line);

        if (option == 1 && lineNumber < num1) filteredLines.insert(line);
        else if (option == 2 && lineNumber > num1) filteredLines.insert(line);
        else if (option == 3 && lineNumber >= num1 && lineNumber <= num2) filteredLines.insert(line);
    }

    return filteredLines;
}
