//
// Created by Tom on 18/11/2025.
//

#ifndef SECRETNUMBERDILEMMA_UTILS_H
#define SECRETNUMBERDILEMMA_UTILS_H

#include <vector>
#include <set>

using uchar = unsigned char;

using State = std::vector<std::set<uchar>>;

enum class OperationType : uchar {
    SUM,        // +
    MUL,        // x
    DIV,        // %
    ZEROCOUNT   // 0
};

#endif //SECRETNUMBERDILEMMA_UTILS_H