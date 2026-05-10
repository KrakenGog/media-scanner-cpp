#include "Scanner.h"

namespace fs = std::filesystem;

ScanResult Scanner::scan(std::string_view path, size_t limitForCategory)
{
    ScanResult res;

    fs::path targetDir = path;

    for (auto &entry : fs::recursive_directory_iterator(targetDir, fs::directory_options::skip_permission_denied))
    {
        if (!entry.is_regular_file())
            continue;

        std::string ext = entry.path().extension().string();

        auto findIt = _extensionToType.find(ext);

        if (findIt != _extensionToType.end())
        {
            ++res.info.situableFiles;

            ContentType type = findIt->second;
            if (res.map[type].size() < limitForCategory)
                res.map[type].push_back(entry.path().filename().string());
        }

        ++res.info.filesScanned;
    }

    return res;
}
