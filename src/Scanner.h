#pragma once

#include <unordered_map>
#include <vector>
#include <string>
#include <filesystem>
#include <format>
#include "ContentType.hpp"



struct ScanInfo{
    int filesScanned = 0;
    int filesSkipped = 0;
    int situableFiles = 0;
};

struct ScanResult{
    std::unordered_map<ContentType, std::vector<std::string>> map;
    ScanInfo info;
};



class Scanner
{
public:
    Scanner(){
        _extensionToType = {
            {".png", ContentType::images}, {".jpg", ContentType::images},
            {".mp4", ContentType::video}, {".mkv", ContentType::video},
            {".mp3", ContentType::audio}, {".wav", ContentType::audio}
        };
    }

    ScanResult scan(std::string_view path, size_t limitForCategory);
private:
    std::unordered_map<std::string, ContentType> _extensionToType;
};