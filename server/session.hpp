#ifndef SESSION_HPP_
#define SESSION_HPP_

// std::cerr, std::cout, std::endl
#include <iostream>

// boost
#include <boost/asio.hpp>
#include <boost/asio/buffer.hpp>

// std::string
#include <cstring>

//headers
#include "server.hpp"

class Session
{
private:
    boost::asio::ip::tcp::socket socket_;

    boost::system::error_code ec;

    void reading();

    void writing();
public:
    Session(boost::asio::ip::tcp::socket socket) : socket_(std::move(socket)) 
    {
    }

    void read_write_cycle()
    {
        reading();
    }

    ~Session() 
    { }
}; 

#endif /* SESSION_HPP_ */