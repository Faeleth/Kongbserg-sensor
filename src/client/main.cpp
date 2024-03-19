#include <iostream>
#include <Client.hpp>
#include <ReceiverManager.hpp>
#include <thread>

int main(int argc, char* argv[]){
  if(argc < 2){
      std::cerr << "Not enough arguments\n";
      return 1;
  }
  const std::string RECEIVERS_PATH = argv[1];
  ReceiverManager * receiverManager = new ReceiverManager(RECEIVERS_PATH);
  auto receivers = receiverManager->getDevices();

  Client** clients = new Client*[receiverManager->getDevicesCount()];

  for(int i{}; i<receiverManager->getDevicesCount(); i++){
    clients[i] = new Client(
      receivers[i]->get_ip(), 
      receivers[i]->get_port(),
      receivers[i]->get_is_active()
    );
    std::thread(&Client::listen, clients[i]).detach();
  }

  while(true){}

  for(int i{}; i<receiverManager->getDevicesCount(); i++){
    delete clients[i];
  }
  delete[] clients;
  delete receiverManager;
  return 0;
}