#pragma once

#include <boost/asio.hpp>
#include <iostream>
#include <Sensor.hpp>
#include <mutex>
class Server {
    Sensor* sensor;
    unsigned short port;
    boost::asio::io_context io_context;
    std::unique_ptr<boost::asio::ip::tcp::acceptor> acceptor;
    std::vector<std::shared_ptr<boost::asio::ip::tcp::socket>> clientSockets;
    std::mutex socketMutex;

    void send_message(int value);

    public:
        enum class Protocol{
            IPV4,
            IPV6
        };
        Server(Sensor * _sensor, unsigned short _port = 0, Protocol protocol = Protocol::IPV4);
        void listen_connections();
        void broadcast();

        unsigned short get_port() const { return port; }
};