#ifndef SESSION_HPP_
#define SESSION_HPP_

// std::cerr, std::cout, std::endl
#include <iostream>

// boost
#include <boost/asio.hpp>
#include <boost/asio/buffer.hpp>

// data
#include <fstream>
#include <cstring>

// assert
#include <cassert>

class Session
{
private:
    boost::asio::ip::tcp::socket socket_;

    boost::system::error_code ec;

    boost::asio::streambuf buffer;

    void read();

    void write();

    /*
        if you need to send data to client
        void input_data();
    */
    void output_data();
public:
    Session(boost::asio::ip::tcp::socket socket) : socket_(std::move(socket)) 
    {
    }

    void read_write_cycle()
    {
        read();
    }

    ~Session() 
    { }
}; 

#endif /* SESSION_HPP_ */