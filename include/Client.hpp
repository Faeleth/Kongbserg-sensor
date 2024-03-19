#pragma once

#include <boost/asio.hpp>
#include <iostream>

class Client {
    std::string ip_address;
    unsigned short port_num;
    bool is_active;
    boost::asio::io_context io_context;
    std::unique_ptr<boost::asio::ip::tcp::socket> socket;

    std::string receive_message() const;
    std::string parse_message(const std::string &message) const;
    public:
        Client(const std::string _ip_address, const unsigned short _port_num, const bool _is_active = true);
        void listen() const;
};