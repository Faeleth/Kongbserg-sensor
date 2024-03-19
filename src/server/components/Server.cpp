#include <Server.hpp>
#include <thread>

Server::Server(Sensor* _sensor, unsigned short _port, Protocol _p)
    : sensor(_sensor), port(_port), acceptor(nullptr), clientSockets() {
    boost::asio::ip::tcp::endpoint endpoint(
        (_p == Protocol::IPV4) ? boost::asio::ip::tcp::v4() : boost::asio::ip::tcp::v6(),
        _port
    );
    acceptor = std::make_unique<boost::asio::ip::tcp::acceptor>(io_context, endpoint);
    port = acceptor->local_endpoint().port();
}

void Server::listen_connections() {
    try {
        while (true) {
            auto socket = std::make_shared<boost::asio::ip::tcp::socket>(io_context);

            acceptor->accept(*socket);

            auto remote_endpoint = socket->remote_endpoint();
            std::cout << "New connection from: " << remote_endpoint.address().to_string() << ":" << remote_endpoint.port() << std::endl;

            clientSockets.push_back(socket); // Add this client socket to the list

        }
    } catch (std::exception& e) {
        std::cerr << "Exception in run(): " << e.what() << std::endl;
    }
}

// wygenerowana wartosc przeslij wszystkim klientom
void Server::send_message(int value) {
    std::string message =
        "$FIX, " +
        sensor->to_string_broadcast() +
        ", " + std::to_string(value) +
        ", " + sensor->classify_value(value) +
        "*\n";

    std::vector<std::shared_ptr<boost::asio::ip::tcp::socket>> errorSockets;

    // w przypadku gdy klient zerwie połaczenie zapisujemy dany socket do usuniecia z vectora i pozniej usuwamy
    for (auto it = clientSockets.begin(); it != clientSockets.end(); ++it) {
        try {
            boost::asio::write(*(*it), boost::asio::buffer(message));
        } catch (std::exception& e) {
            std::cerr << "Error sending message to client: " << e.what() << std::endl;
            errorSockets.push_back(*it); // Add socket to error list
        }
    }

    // usuniecie socketow klientow ktorzy zerwali polaczenie
    for (auto& socket : errorSockets) {
        clientSockets.erase(std::remove(clientSockets.begin(), clientSockets.end(), socket), clientSockets.end());
    }
}

// glowna petla wysylania wiadomosci w okreslonej przez symulator czestotliwosci
// pod uwage brany jest rowniez czas wyslania wszystkim klientom wiadomosci przez
// co watek zostanie uspiony na czas od 0 do planned_sleep, nie mniej, nie wiecej
void Server::broadcast() {
    try{
        while (true) {
            auto start_time = std::chrono::high_resolution_clock::now();
            int value = sensor->generate_value();
            send_message(value);
            auto end_time = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
            
            long planned_sleep = 1000 / sensor->getFrequency();
            long sleep_time = std::max(0L, planned_sleep - duration.count());

            std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
        }
    }
    catch(const std::exception& e){
        std::cerr << "Exception in broadcastValue(): " << e.what() << std::endl;
    }
}