#include <string>

class Receiver {
    unsigned short port;
    std::string ip;
    bool is_active;

    public:
        Receiver(std::string _ip, unsigned short _port, bool _is_active): ip(_ip), port(_port), is_active(_is_active) {};
        std::string get_ip() const { return ip; }
        unsigned short get_port() const { return port; }
        bool get_is_active() const { return is_active; }
};