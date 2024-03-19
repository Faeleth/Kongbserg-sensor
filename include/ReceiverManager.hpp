#pragma once

#include <DeviceManager.hpp>
#include <Receiver.hpp>

// inicjalizacja odbiornikow z pliku json i zarządzanie ich stanem
class ReceiverManager: public DeviceManager<Receiver>{
    void read_json(std::string _path_to_file) override;
    
    public:
        ReceiverManager(std::string _path_to_file){
            devices = nullptr; 
            devices_count = 0; 
            read_json(_path_to_file);
        }
        ~ReceiverManager();
};
