#pragma once

#include <DeviceManager.hpp>
#include <Sensor.hpp>

// inicjalizacja sensorów z pliku json i zarządzanie ich stanem
class SensorManager: public DeviceManager<Sensor>{
    void readJson(std::string _path_to_file) override;
    
    public:
        SensorManager(std::string _path_to_file){
            devices = nullptr; 
            devicesCount = 0; 
            readJson(_path_to_file);
        }
        ~SensorManager();
};
