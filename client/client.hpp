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
#include <vector>

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

    std::string filename;

    void read();

    void write();

    void input_data();
    /*
        if you want to get data from server
        void output_data();
    */
public:
    Client(std::string host, std::string port) : r(io_c), q(host, port), socket_(io_c), filename("/home/mark/Desktop/11.jpg")
    {
    }

    bool connect();

    void read_write_cycle()
    {
        write();
    }

    ~Client() 
    {
        io_c.run();
        std::cout << "End" << std::endl;
    }
};

#endif /* CLIENT_HPP_ */