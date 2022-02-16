#ifndef SESSION_HPP_
#define SESSION_HPP_

// std::cerr, std::cout, std::endl
#include <iostream>

// boost
#include <boost/asio.hpp>
#include <boost/asio/buffer.hpp>

// std::string
#include <cstring>

class Session
{
private:
    boost::asio::ip::tcp::socket socket_;

    boost::system::error_code ec;

    void read();

    void write(boost::asio::streambuf&);
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