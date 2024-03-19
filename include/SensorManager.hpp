#pragma once

#include <DeviceManager.hpp>
#include <Sensor.hpp>

// inicjalizacja sensorów z pliku json i zarządzanie ich stanem
class SensorManager: public DeviceManager<Sensor>{
    void read_json(std::string _path_to_file) override;
    
    public:
        SensorManager(std::string _path_to_file){
            devices = nullptr; 
            devices_count = 0; 
            read_json(_path_to_file);
        }
        ~SensorManager();
};
