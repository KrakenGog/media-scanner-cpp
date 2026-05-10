#include "Server.h"
#include <iostream>

MediaServer::MediaServer(const std::string &host, int port, SharedState &sharedState)
    : _host(host), _port(port), _sharedState(sharedState)
{

    _svr.Get("/media_files", [this](const httplib::Request &req, httplib::Response &res)
             {
        
        std::string responseJson;
        
        {
            std::lock_guard<std::mutex> lock(_sharedState.mtx);
            responseJson = _sharedState.json_data;
        }
        
        res.set_content(responseJson, "application/json");
        
        std::cout << "[Server] Handled GET request for /media_files\n\n"; });
}

void MediaServer::start()
{
    std::cout << "[Server] Listening on http://" <<_host << ':' << _port << "/media_files\n";

    if (!_svr.listen(_host.c_str(), _port))
    {
        std::cerr << "[Server] Error: Failed to start server on port " << _port << '\n';
    }
}

void MediaServer::stop()
{
    _svr.stop();
}