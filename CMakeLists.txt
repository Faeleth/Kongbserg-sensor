cmake_minimum_required(VERSION 3.0.0)
project(kongsberg_sensor VERSION 0.1.0 LANGUAGES C CXX)

# include(CTest)
# enable_testing()

find_package(Boost REQUIRED COMPONENTS system)
include_directories(${Boost_INCLUDE_DIRS})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

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

add_executable(kongsberg_sensor_server ${SERVER_SOURCES})
target_link_libraries(kongsberg_sensor_server ${Boost_LIBRARIES})

add_executable(kongsberg_sensor_client ${CLIENT_SOURCES})
target_link_libraries(kongsberg_sensor_client ${Boost_LIBRARIES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
