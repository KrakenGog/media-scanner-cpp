#pragma once
#include <string>
#include <mutex>

struct SharedState
{
    std::string json_data = "{}";
    std::mutex mtx;
};