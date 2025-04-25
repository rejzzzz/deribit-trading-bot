cmake_minimum_required(VERSION 3.10)

# Set project name
project(TradingApp)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)

# Find Boost libraries
find_package(Boost REQUIRED COMPONENTS system thread)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

# Add source files
set(SOURCES
    main.cpp
    trade.cpp
    threads.cpp
    websocket.cpp
    latency.cpp
)

# Add executable
add_executable(TradingApp ${SOURCES})

# Link libraries
target_link_libraries(TradingApp PRIVATE
    ${Boost_LIBRARIES}
    ssl
    crypto
    pthread
)