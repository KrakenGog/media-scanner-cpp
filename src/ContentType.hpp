#include <string>

enum class ContentType
{
    video,
    audio,
    images
};

constexpr std::string_view to_string(ContentType type)
{
    switch (type)
    {
    case ContentType::audio:
        return "audio";
    case ContentType::video:
        return "video";
    case ContentType::images:
        return "images";
    default:
        return "unknown";
    }
}