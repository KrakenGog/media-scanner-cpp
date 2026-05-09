#include "nlohmann/json.hpp"
#include "iostream"

int main()
{
    nlohmann::json j;
    j["hello world"] = "yeees";

    std::cout << j.dump();

    return 0;
}