cmake_minimum_required(VERSION 3.0.0)
project(kongsberg_sensor VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 14)

find_package(Boost REQUIRED COMPONENTS system)

set(SERVER_SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/server/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/server/components/Sensor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/server/components/SensorManager.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/server/components/Server.cpp
)  

set(CLIENT_SOURCES  
    ${CMAKE_CURRENT_SOURCE_DIR}/src/client/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/client/components/Client.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/client/components/ReceiverManager.cpp 
)

add_executable(${PROJECT_NAME}_server ${SERVER_SOURCES})
target_link_libraries(${PROJECT_NAME}_server PRIVATE Boost::system)

add_executable(${PROJECT_NAME}_client ${CLIENT_SOURCES})
target_link_libraries(${PROJECT_NAME}_client PRIVATE Boost::system)

target_include_directories(${PROJECT_NAME}_server PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME}_client PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

