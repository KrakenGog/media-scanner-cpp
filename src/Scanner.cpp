#include "Scanner.h"

namespace fs = std::filesystem;

Scanner::Scanner()
{
    _extensionToType = {
        {".png", ContentType::images},
        {".jpg", ContentType::images},
        {".jpeg", ContentType::images},
        {".bmp", ContentType::images},
        {".gif", ContentType::images},
        {".webp", ContentType::images},
        {".tiff", ContentType::images},
        {".svg", ContentType::images},
        {".ico", ContentType::images},

        {".mp4", ContentType::video},
        {".mkv", ContentType::video},
        {".avi", ContentType::video},
        {".mov", ContentType::video},
        {".wmv", ContentType::video},
        {".flv", ContentType::video},
        {".webm", ContentType::video},
        {".mpeg", ContentType::video},
        {".mpg", ContentType::video},
        {".m4v", ContentType::video},
        {".3gp", ContentType::video},

        {".mp3", ContentType::audio},
        {".wav", ContentType::audio},
        {".flac", ContentType::audio},
        {".ogg", ContentType::audio},
        {".aac", ContentType::audio},
        {".m4a", ContentType::audio},
        {".wma", ContentType::audio},
        {".alac", ContentType::audio},
        {".aiff", ContentType::audio}};
}

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
