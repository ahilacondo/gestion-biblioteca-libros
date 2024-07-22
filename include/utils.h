#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <algorithm>

inline bool validarNumero(const std::string& str) {
    return std::all_of(str.begin(), str.end(), ::isdigit);
}

#endif // UTILS_H