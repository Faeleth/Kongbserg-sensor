#include <ReceiverManager.hpp>
#include <fstream>
#include <nlohmann/json.hpp>

void ReceiverManager::readJson(std::string _path_to_file){
    std::ifstream file(_path_to_file);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file!");
    }
    nlohmann::json jsonData;
    file >> jsonData;
    file.close();

    auto receivers_json = jsonData["Receivers"];
    devices = new Receiver*[receivers_json.size()];
    for(int i{}; i<receivers_json.size(); i++){
        devices[i] = new Receiver(
            receivers_json[i]["Ip"],
            receivers_json[i]["Port"], 
            receivers_json[i]["Active"]
        );
        devicesCount++;
    }
}
