#pragma once

#include <DeviceManager.hpp>
#include <Receiver.hpp>

// inicjalizacja odbiornikow z pliku json i zarządzanie ich stanem
class ReceiverManager: public DeviceManager<Receiver>{
    void readJson(std::string _path_to_file) override;
    
    public:
        ReceiverManager(std::string _path_to_file){
            devices = nullptr; 
            devicesCount = 0; 
            readJson(_path_to_file);
        }
        ~ReceiverManager();
};
