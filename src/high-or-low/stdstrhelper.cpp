#include <algorithm>
#include <string>
#include "sdtstrhelper.h"
//
// Created by nickganter on 8/3/25.
//
std::string to_lower(const std::string& str) {
    std::string result = str;
    std::ranges::transform(result, result.begin(), [](unsigned const char c) {
        return std::tolower(c);
    });
    return result;
}