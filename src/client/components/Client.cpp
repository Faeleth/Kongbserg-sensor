#include <Client.hpp>

Client::Client(const std::string _ip_address, const unsigned short _port_num, const bool _is_active)
    : ip_address(_ip_address), port_num(_port_num), is_active(_is_active), socket(std::make_unique<boost::asio::ip::tcp::socket>(io_context)) {
    boost::asio::ip::tcp::resolver resolver(io_context);
    boost::asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(ip_address, std::to_string(port_num));
    if(is_active)
        boost::asio::connect(*socket, endpoints);
}

// wczytaj z socketa przekazana wiadomosc
std::string Client::receive_message() const {
    boost::asio::streambuf response;
    boost::asio::read_until(*socket, response, "\n");
    return boost::asio::buffer_cast<const char*>(response.data());
}

// podczas gdy czujnik jest aktywny loguj otrzymane wiadomosci
void Client::listen() const {
    try{
        while(is_active){
            std::string response = receive_message();
            std::cout << parse_message(response);
        }
    }catch(boost::system::system_error &e){
        std::cerr
            << "Error occured! Error code = " << e.code()
            << ". Message: " << e.what()
            << std::endl;
        exit(EXIT_FAILURE);
    }
}

// funkcja sluzaca do wyrozniania otrzymanej wiadomosci na podstawie klasyfikacji symulatora
std::string Client::parse_message(const std::string &message) const {
    std::string parsed_message = message;
    if(message.find("Warning") != std::string::npos){
        parsed_message.pop_back();
        parsed_message += "\t⚠️\n";
    } else if(message.find("Alarm") != std::string::npos){
        parsed_message.pop_back();
        parsed_message += "\t🚨\n";
    }
    return parsed_message;
}