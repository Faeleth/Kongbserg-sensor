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
    
    // otworzenie i wczytanie pliku configuracyjnego json
    SensorManager * sensorManager = new SensorManager(SENSORS_PATH);
    auto sensors = sensorManager->get_devices();

    Server** servers = new Server*[sensorManager->get_devices_count()];
    unsigned short port = 9999;

    // takich watkow jest tyle ile jest sensorow
    for (int i{}; i<sensorManager->get_devices_count(); i++) {
        servers[i] = new Server(
            sensors[i], 
            port--
        );
        // stworz watki zajmujace sie akceptowaniem polaczen z klientami
        std::thread(&Server::listen_connections, servers[i]).detach();
        // logowanie portow
        std::cout << "Server with sensor [" << sensors[i]->get_id() << "] works on port: " << servers[i]->get_port() << std::endl;

        // stworz watki zajmujace sie generowaniem i wysylaniem wiadomosci do swoich odbiorcow
        std::thread(&Server::broadcast, servers[i]).detach();
    }

    // utrzymanie glownego watku programu przed zakonczeniem
    while(true){}

    for (int i{}; i<sensorManager->get_devices_count(); i++) {
        delete servers[i];
    }
    delete[] servers;
    delete sensorManager;
    return 0;
}
