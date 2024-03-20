#include <iostream>
#include <boost/asio.hpp>
#include <thread>
#include <Server.hpp>
#include <fstream>
#include <SensorManager.hpp>
#include <Sensor.hpp>
#include <vector>

int main(int argc, char* argv[]) {
    if(argc < 2){
        std::cerr << "Not enough arguments\n";
        return 1;
    }
    const std::string SENSORS_PATH = argv[1]; 
    
    // otworzenie i wczytanie pliku configuracyjnego json
    SensorManager sensorManager(SENSORS_PATH);
    const auto sensors = sensorManager.get_devices();

    Server** servers = new Server*[sensorManager.get_devices_count()];

    std::vector<std::thread> threads;
    // takich watkow jest tyle ile jest sensorow
    for (int i{}; i<sensorManager.get_devices_count(); i++) {
        servers[i] = new Server(
            sensors[i], 
            sensors[i]->getPort()
        );
        // stworz watki zajmujace sie akceptowaniem polaczen z klientami
        threads.push_back(std::thread(&Server::listen_connections, servers[i]));
        // logowanie portow
        std::cout << "Server with sensor [" << sensors[i]->get_id() << "] works on port: " << servers[i]->get_port() << std::endl;
        threads.push_back(std::thread(&Server::broadcast, servers[i]));
    }

    // utrzymanie glownego watku programu przed zakonczeniem
    for (auto& t : threads) {
        t.join();
    }

    for (int i{}; i<sensorManager.get_devices_count(); i++) {
        delete servers[i];
        servers[i] = nullptr;
    }
    delete[] servers;
    return 0;
}
