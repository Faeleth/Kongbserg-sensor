#pragma once

#include <string>

template <typename T>
class DeviceManager{
    protected: 
        T ** devices;
        unsigned int devicesCount;

        virtual void readJson(std::string _path_to_file) = 0;

    public:
        ~DeviceManager(){
            for(int i{}; i< devicesCount; i++){
                delete devices[i];
            }
            delete[] devices;
        }
        T ** getDevices() { return devices; }
        unsigned int getDevicesCount() { return devicesCount; }
};