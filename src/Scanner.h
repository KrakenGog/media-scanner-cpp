#pragma once

#include <unordered_map>
#include <vector>
#include <string>
#include <filesystem>
#include "ContentType.hpp"
#include <algorithm>


struct ScanInfo{
    size_t filesScanned = 0;
    size_t situableFiles = 0;
};

struct ScanResult{
    std::unordered_map<ContentType, std::vector<std::string>> map;
    ScanInfo info;
};



class Scanner
{
public:
    Scanner();

    ScanResult scan(std::string_view path);
private:
    std::unordered_map<std::string, ContentType> _extensionToType;
};