#include "ClientHandler.h"

ClientHandler& ClientHandler::get() {
    static ClientHandler handler;
    return handler;
}
ClientHandler::ClientHandler() {
    debug = true;
    try {
        io = std::make_unique<boost::asio::io_context>();
        socket = std::make_unique<tcp::socket>(*io);
        socket->connect(tcp::endpoint(boost::asio::ip::make_address("127.0.0.1"), 12345));

    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}
int ClientHandler::send(std::vector<std::string>& target)
{
    std::string line = "";
    for (int i = 0; i < target.size(); i++) {
        line += target[i];
        if (i != target.size() - 1) line += " ";
    }
    try {

        boost::asio::write(*socket, boost::asio::buffer(line));
        if (debug) std::cout << "sending : " << line << " " << std::endl;
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}

std::vector<std::string> ClientHandler::receive()
{
    char reply[1024];
    std::string res;
    std::string shard;
    size_t length;

    std::vector<std::string> split;

    try {
        boost::system::error_code ec;
        length = socket->read_some(boost::asio::buffer(reply));
        res += std::string(reply, length);
    
        std::stringstream ss(res);
        if (debug) std::cout << "getting : ";
        while (std::getline(ss, shard, ' ')) {
            if (debug) std::cout << shard << " ";
            split.push_back(shard);
        }
        std::cout << std::endl;
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    
    
    return split;
}
