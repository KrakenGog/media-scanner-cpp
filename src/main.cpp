#include <iostream>
#include <thread>
#include <chrono>
#include "SharedState.hpp"
#include "Server.h"
#include "Scanner.h"
#include <nlohmann/json.hpp>
#include <filesystem>

namespace fs = std::filesystem;

void scannerWorker(SharedState &state, const std::string &targetPath, int intervalSec)
{
    Scanner scanner;

    while (true)
    {
        try
        {
            auto result = scanner.scan(targetPath);

            nlohmann::json j;
            for (const auto &[type, files] : result.map)
            {
                j[std::string(to_string(type))] = files;
            }

            std::string new_json_str = j.dump(4);

            {
                std::lock_guard<std::mutex> lock(state.mtx);
                state.json_data = new_json_str;
            }
            std::cout << "[Scanner] Data successfully updated. Suitable files found: " << result.info.situableFiles << '\n';
        }
        catch (const std::exception &e)
        {
            std::cerr << "[Scanner] Error during scanning: \n" << e.what() << '\n';
        }

        std::this_thread::sleep_for(std::chrono::seconds(intervalSec));
    }
}

void printHelp()
{
    std::cout << "Usage: media_scanner [options]\n"
              << "Options:\n"
              << "  -p, --path <dir>       Path to scan (default: current directory)\n"
              << "  -i, --interval <sec>   Scan interval in seconds (default: 10)\n"
              << "  -h, --help             Show this help message\n";
}

int main(int argc, char *argv[])
{
    std::string pathToScan = ".";
    int interval = 10;
    int port = 1234;

    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];

        if (arg == "-h" || arg == "--help")
        {
            printHelp();
            return 0;
        }
        else if ((arg == "-p" || arg == "--path") && i + 1 < argc)
        {
            pathToScan = argv[++i];
        }
        else if ((arg == "-i" || arg == "--interval") && i + 1 < argc)
        {
            try
            {
                interval = std::stoi(argv[++i]);
            }
            catch (const std::exception &e)
            {
                std::cerr << "Error: Invalid interval value.\n";
                return 1;
            }
        }
        else
        {
            std::cerr << "Unknown argument: " << arg << "\n";
            printHelp();
            return 1;
        }
    }

    std::string absolutePath;

    try
    {
        absolutePath = fs::absolute(pathToScan).string();
    }
    catch (const std::exception &e)
    {
        std::cerr << "[Config] Error resolving path: " << e.what() << "\n";
        return 1;
    }

    std::cout << "[Config] Target path: " << absolutePath << "\n";
    std::cout << "[Config] Scan interval: " << interval << " seconds\n";

    SharedState sharedState;
    std::thread scannerThread(scannerWorker, std::ref(sharedState), absolutePath, interval);
    scannerThread.detach();

    MediaServer server("localhost", port, sharedState);
    server.start();

    return 0;
}