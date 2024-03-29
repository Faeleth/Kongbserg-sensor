#include <SensorManager.hpp>
#include <fstream>
#include <nlohmann/json.hpp>

// wczytaj dane z pliku konfiguracyjnego symulatorow
void SensorManager::read_json(const std::string & _path_to_file){
    std::ifstream file(_path_to_file);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file!");
    }
    nlohmann::json jsonData;
    file >> jsonData;
    file.close();

    auto sensors_json = jsonData["Sensors"];
    devices = new Sensor*[sensors_json.size()];
    for(int i{}; i<sensors_json.size(); i++){
        devices[i] = new Sensor(
            sensors_json[i]["MinValue"], 
            sensors_json[i]["MaxValue"], 
            sensors_json[i]["Frequency"], 
            sensors_json[i]["Type"],
            sensors_json[i]["ID"],
            sensors_json[i]["Port"]
        );
        devices_count++;
    }
}
