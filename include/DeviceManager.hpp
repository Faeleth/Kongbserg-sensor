#pragma once

#include <string>

template <typename T>
class DeviceManager{
    protected: 
        T ** devices;
        unsigned int devices_count;

        virtual void read_json(std::string _path_to_file) = 0;

    public:
        ~DeviceManager(){
            for(int i{}; i< devices_count; i++){
                delete devices[i];
            }
            delete[] devices;
        }
        T ** get_devices() const { return devices; }
        unsigned int get_devices_count() const { return devices_count; }
};