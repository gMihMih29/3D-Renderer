#include "StringViewSplit.h"

namespace Utilities {

std::vector<std::string_view> StringViewSplit(std::string_view str, char separator) {
    std::vector<std::string_view> res;
    int size = 0;
    for (auto i : str) {
        if (i == separator) {
            ++size;
        }
    }
    res.reserve(size + 1);
    std::string_view s = str.substr(0, str.find(separator));
    while (s.size() < str.size()) {
        res.push_back(s);
        str = str.substr(str.find(separator) + 1);
        s = str.substr(0, str.find(separator));
    }
    res.push_back(str);
    return res;
}

}