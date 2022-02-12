#ifndef SERVER_HPP_
#define SERVER_HPP_

// STD
#include <iostream>

// boost
#include <boost/asio.hpp>
#include <boost/asio/buffer.hpp>

// std::string
#include <cstring>

class Server
{
private:
    boost::asio::io_context io_c;

    boost::asio::ip::tcp::endpoint tcp_endpoint;
    boost::asio::ip::tcp::acceptor tcp_acceptor;
public:
    Server() : tcp_endpoint(boost::asio::ip::tcp::v4(), 2014), tcp_acceptor(io_c, tcp_endpoint)
    {
    }

    void waiting();

    ~Server() 
    { 
        io_c.run();
        std::cout << "End" << std::endl;
    }
};

#endif /* SERVER_HPP_ */