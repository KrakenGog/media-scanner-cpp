#include "Scanner.h"

namespace fs = std::filesystem;

ScanResult Scanner::scan(std::string_view path)
{
    ScanResult res;

    fs::path targetDir = path;

    for (const auto &entry : fs::recursive_directory_iterator(targetDir, fs::directory_options::skip_permission_denied))
    {
        if (!entry.is_regular_file())
            continue;

        std::string ext = entry.path().extension().string();

        std::transform(ext.begin(), ext.end(), ext.begin(),
                       [](unsigned char c)
                       { return std::tolower(c); });

        auto findIt = _extensionToType.find(ext);

        if (findIt != _extensionToType.end())
        {
            ContentType type = findIt->second;
            res.map[type].push_back(entry.path().filename().string());

            ++res.info.situableFiles;
        }

        ++res.info.filesScanned;
    }

    return res;
}
