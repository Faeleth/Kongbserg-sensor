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

  // otworzenie i wczytanie pliku configuracyjnego json
  ReceiverManager * receiverManager = new ReceiverManager(RECEIVERS_PATH);
  auto receivers = receiverManager->get_devices();

  Client** clients = new Client*[receiverManager->get_devices_count()];

  for(int i{}; i<receiverManager->get_devices_count(); i++){
    // utworzenie nadajnika i proba polaczenia sie
    clients[i] = new Client(
      receivers[i]->get_ip(), 
      receivers[i]->get_port(),
      receivers[i]->get_is_active()
    );
    // stworz watki ktore nasluchuja symulatora na odpowiednim porcie zdefiniowanym w configu
    std::thread(&Client::listen, clients[i]).detach();
  }

  // utrzymanie glownego watku programu przed zakonczeniem
  while(true){}

  for(int i{}; i<receiverManager->get_devices_count(); i++){
    delete clients[i];
  }
  delete[] clients;
  delete receiverManager;
  return 0;
}