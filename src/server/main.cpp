#include <iostream>
#include <boost/asio.hpp>
#include <thread>
#include <Server.hpp>
#include <fstream>
#include <SensorManager.hpp>
#include <Sensor.hpp>

int main(int argc, char* argv[]) {
    srand(time(NULL));
    if(argc < 2){
        std::cerr << "Not enough arguments\n";
        return 1;
    }
    const std::string SENSORS_PATH = argv[1]; 
    SensorManager * sensorManager = new SensorManager(SENSORS_PATH);
    auto sensors = sensorManager->getDevices();

    Server** servers = new Server*[sensorManager->getDevicesCount()];
    unsigned short port = 9999;

    for (int i{}; i<sensorManager->getDevicesCount(); i++) {
        servers[i] = new Server(
            sensors[i], 
            port--
        );
        std::cout << "Server with sensor [" << sensors[i]->getId() << "] works on port: " << servers[i]->getPort() << std::endl;
        std::thread(&Server::listen_connections, servers[i]).detach();
    }

    for (int i{}; i<sensorManager->getDevicesCount(); i++) {
        std::thread(&Server::broadcast, servers[i]).detach();
    }

    while(true){}

    for (int i{}; i<sensorManager->getDevicesCount(); i++) {
        delete servers[i];
    }
    delete[] servers;
    delete sensorManager;
    return 0;
}
