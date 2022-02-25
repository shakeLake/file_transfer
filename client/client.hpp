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

    struct
    {
        std::string path;
        std::string filename;
        std::string filetype;
        void separate_filename(char*);

        unsigned int length;
        char* file;

        std::ifstream fin;
    } file_prop;

    void read();

    template <typename T>
    void write();

    void input_data();
public:
    Client(std::string host, std::string port, char* fn) : r(io_c), q(host, port), socket_(io_c)
    {
        path = fn;
        file_prop.fin.open(fn, std::ios_base::binary);

        file_prop.fin.seekg(0, file_prop.fin.end);
        file_prop.length = file_prop.fin.tellg();
        file_prop.fin.seekg(0, file_prop.fin.beg);

        file_prop.file = new char[length];
    }

    bool connect();

    ~Client() 
    {
        io_c.run();
        std::cout << "End" << std::endl;
    }
};

template <typename T>
void Client<T>::write(T data)
{
    boost::asio::write(socket_, data, boost::asio::transfer_all(), ec);

    if (ec)
        std::cerr << "Client::write error: " << ec.message() << std::endl;

    buffer.consume( buffer.size() );

    read();
}

#endif /* CLIENT_HPP_ */