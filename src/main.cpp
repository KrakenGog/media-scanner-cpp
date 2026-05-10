#include "nlohmann/json.hpp"
#include "iostream"
#include "Scanner.h"



int main()
{
    Scanner scanner;
    auto [map, info] = scanner.scan("/home/kraken/", 2);
    for (auto &entry : map)
    {
        std::cout << to_string(entry.first) << " {";
        for (auto &item : entry.second)
        {
            std::cout << item << " ";
        }
        std::cout << "}\n";
    }

    std::cout << "Files scanned: " << info.filesScanned << '\n';
    std::cout << "Files skipped: " << info.filesSkipped << '\n';
    std::cout << "Situable files: " << info.situableFiles << '\n';

    return 0;
}