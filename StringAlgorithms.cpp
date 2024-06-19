#include "StringAlgorithms.h"
#include <vector>
#include <string>

std::vector<int> StringAlgorithms::naiveStringSearch(const std::string &text, const std::string &pattern) {
    std::vector<int> matches;
    int n = text.size();
    int m = pattern.size();

    for (int i = 0; i <= n - m; ++i) {
        int j = 0;
        while (j < m && text[i + j] == pattern[j]) {
            ++j;
        }
        if (j == m) {
            matches.push_back(i);
        }
    }
    return matches;
}

std::vector<int> StringAlgorithms::KMPSearch(const std::string &text, const std::string &pattern) {
    std::vector<int> matches;
    int n = text.size();
    int m = pattern.size();

    // Compute longest prefix suffix (LPS) array
    std::vector<int> lps(m, 0);
    int len = 0;  // Length of previous longest prefix suffix

    // Build LPS array
    int i = 1;
    while (i < m) {
        if (pattern[i] == pattern[len]) {
            ++len;
            lps[i] = len;
            ++i;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                ++i;
            }
        }
    }

    // Perform pattern search using LPS array
    i = 0;  // index for text[]
    int j = 0;  // index for pattern[]
    while (i < n) {
        if (pattern[j] == text[i]) {
            ++i;
            ++j;
        }

        if (j == m) {
            matches.push_back(i - j);
            j = lps[j - 1];
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                ++i;
            }
        }
    }

    return matches;
}

