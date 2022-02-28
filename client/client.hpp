#ifndef CLIENT_HPP_
#define CLIENT_HPP_

// std::cerr, std::cout, std::endl
#include <iostream>

// boost
#include <boost/asio.hpp>
#include <boost/asio/buffer.hpp>

// data
#include <fstream>
#include <cstring>
#include <array>

// assert
#include <cassert>

class Client
{
private:
    boost::asio::io_context io_c;

    boost::system::error_code ec;

    boost::asio::ip::tcp::resolver r;
    boost::asio::ip::tcp::socket socket_;

    boost::asio::ip::tcp::resolver::query q;

    boost::asio::streambuf buffer;

    struct Properties
    {
        std::string path;
        std::string filename;
        std::string filetype;
        void separate_filename(std::string);

        unsigned int length;

        char* file;

        std::ifstream fin;
    } file_prop;

    void read();

    template <typename T>
    void write(T);

    void input_file();
    void input_file_prop();
public:
    Client(std::string host, std::string port, char* fn) : r(io_c), q(host, port), socket_(io_c)
    {
        file_prop.path = fn;
        file_prop.fin.open(fn, std::ios_base::binary);

        file_prop.separate_filename(fn);

        assert(file_prop.fin.is_open());

        file_prop.fin.seekg(0, file_prop.fin.end);
        file_prop.length = file_prop.fin.tellg();
        file_prop.fin.seekg(0, file_prop.fin.beg);

        file_prop.file = new char[file_prop.length];
    }

    bool connect();

    ~Client() 
    {
        io_c.run();
        std::cout << "End" << std::endl;
    }
};

template <typename T>
void Client::write(T data)
{
    boost::asio::write(socket_, data, boost::asio::transfer_all(), ec);

    if (ec)
        std::cerr << "Client::write error: " << ec.message() << std::endl;

    buffer.consume( buffer.size() );

    read();
}

#endif /* CLIENT_HPP_ */