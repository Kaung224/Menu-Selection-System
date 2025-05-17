#pragma once
#include <iostream>
#include <cstring>

using namespace std;
namespace seneca {
    class Utils {
    public:
        char* makeBillFileName(char* filename, int billNo) const;
    };
};