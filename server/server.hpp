#ifndef SERVER_HPP_
#define SERVER_HPP_

// STD
#include <iostream>

// boost
#include <boost/asio.hpp>
#include <boost/asio/buffer.hpp>

// std::string
#include <cstring>

// headers
#include "session.hpp"

class Server
{
private:
    boost::asio::ip::tcp::endpoint tcp_endpoint;
    boost::asio::ip::tcp::acceptor tcp_acceptor;
public:
    Server(boost::asio::io_context& io_c) : tcp_endpoint(boost::asio::ip::tcp::v4(), 2014), tcp_acceptor(io_c, tcp_endpoint)
    {
    }

    void waiting();

    ~Server()
    { }
};

#endif /* SERVER_HPP_ */