cmake_minimum_required(VERSION 3.14)


project(MediaScanner)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include(FetchContent)


FetchContent_Declare(json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.2
)
FetchContent_MakeAvailable(json)


FetchContent_Declare(httplib
    GIT_REPOSITORY https://github.com/yhirose/cpp-httplib.git
    GIT_TAG v0.14.1
)
FetchContent_MakeAvailable(httplib)


add_executable(media_scanner src/main.cpp
 src/Scanner.cpp
 src/ContentType.hpp
 src/Server.cpp
 src/SharedState.hpp)

 

find_package(Threads REQUIRED)


target_link_libraries(media_scanner PRIVATE 
    nlohmann_json::nlohmann_json 
    httplib 
    Threads::Threads
)