#pragma once

#include <boost/asio.hpp>
#include <iostream>
#include <Sensor.hpp>
class Server {
    Sensor* sensor;
    unsigned short port;
    boost::asio::io_context io_context;
    std::unique_ptr<boost::asio::ip::tcp::acceptor> acceptor;
    std::vector<std::shared_ptr<boost::asio::ip::tcp::socket>> clientSockets;

    public:
        enum class Protocol{
            IPV4,
            IPV6
        };
        Server(Sensor * _sensor, unsigned short _port = 0, Protocol protocol = Protocol::IPV4);
        void listen_connections();
        void send_message(int value);
        void broadcast();

        unsigned short getPort() const { return port; }
};