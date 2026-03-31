#include "server.h"
#include "nand_storage.h"
#include "validator.h"
#include "constants.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/asio.hpp>


using boost::asio::ip::tcp;

void runServer(int port) {
    boost::asio::io_context io;
    tcp::acceptor acceptor(io, tcp::endpoint(tcp::v4(), port));

    while (true) {
        tcp::socket socket(io);
        acceptor.accept(socket);

        while (true) {
            char input_data[1024];
            boost::system::error_code ec;
            size_t length = socket.read_some(boost::asio::buffer(input_data), ec);
            if (ec == boost::asio::error::eof) break;
            else if (ec) throw boost::system::system_error(ec);

            std::string cmd_str(input_data, length);
            std::stringstream ss(cmd_str);
            std::string command, LBA;
            if (!(ss >> command >> LBA)) continue;

            int LBAInt = transformInt(LBA);
            if (LBAInt == -1) {
                boost::asio::write(socket, boost::asio::buffer("ERROR: Invalid LBA\n"));
                continue;
            }

            std::ifstream findfile(FILE_NAME);
            if (!findfile.is_open()) init();

            if (command == "read") {
                std::ifstream readfile(FILE_NAME);
                std::string line = read(LBAInt, readfile);
                boost::asio::write(socket, boost::asio::buffer(line));
            }
            else if (command == "write") {
                std::string value;
                ss >> value;
                if (!isValidValue(value)) {
                    boost::asio::write(socket, boost::asio::buffer("ERROR: Invalid Value\n"));
                    continue;
                }
                std::fstream fs(FILE_NAME, std::ios::in | std::ios::out | std::ios::binary);
                write(value, LBAInt, fs);
                boost::asio::write(socket, boost::asio::buffer("SUCCESS\n"));
            }
        }
    }
}