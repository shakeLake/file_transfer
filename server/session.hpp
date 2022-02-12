#ifndef SESSION_HPP_
#defince SESSION_HPP_

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

    void reading();

    void writing();
public:
    Session(boost::asio::ip::tcp::socket socket) : socket_(std::move(socket)) 
    {
    }

    void read_write_cycle();

    ~Session();
}; 

#endif /* SESSION_HPP_ */