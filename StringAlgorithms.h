// StringAlgorithms.h (same as before)
#ifndef STRING_ALGORITHMS_H
#define STRING_ALGORITHMS_H

#include <vector>
#include <string>

class StringAlgorithms {
public:
    static std::vector<int> naiveStringSearch(const std::string &text, const std::string &pattern);
    // Other algorithms...i
    static std::vector<int> KMPSearch(const std::string &text, const std::string &pattern);


};

#endif