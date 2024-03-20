#pragma once

#include <string>

template <typename T>
class DeviceManager{
    protected: 
        T ** devices;
        unsigned int devices_count;

        virtual void read_json(const std::string & _path_to_file) = 0;

    public:
        ~DeviceManager(){
            for(int i{}; i< devices_count; i++){
                delete devices[i];
                devices[i] = nullptr;
            }
            delete[] devices;
            devices = nullptr;
        }
        T ** get_devices() const { return devices; }
        unsigned int get_devices_count() const { return devices_count; }
};