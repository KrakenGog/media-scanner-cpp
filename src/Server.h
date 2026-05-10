#pragma once

#include <string>
#include "httplib.h"
#include "SharedState.hpp"

class MediaServer {
public:
    
    MediaServer(const std::string& host, int port, SharedState& sharedState);

    
    void start();

    
    void stop();

private:
    std::string _host;
    int _port;
    SharedState& _sharedState;
    httplib::Server _svr;
};