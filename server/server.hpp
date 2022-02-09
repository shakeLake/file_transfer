#ifndef SERVER_HPP_
#define SERVER_HPP_

// I / O
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
    boost::asio::ip::tcp::socket tcp_socket;
    boost::system::error_code ec;
public:
    Server() : tcp_socket(io_c), tcp_endpoint(boost::asio::ip::tcp::v4(), 2014), tcp_acceptor(io_c, tcp_endpoint)
    {
    }

    bool waiting();

    void reading();

    ~Server() 
    { 
        io_c.run();
        std::cout << "End" << std::endl;
    }
};

#endif /* SERVER_HPP_ */