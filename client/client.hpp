#ifndef CLIENT_HPP_
#define CLIENT_HPP_

// std::cerr, std::endl
#include <iostream>

// boost
#include <boost/asio.hpp>

// header
#include "client.hpp"

using namespace boost::asio::ip;

class Client
{
private:
    boost::asio::io_context io_context;
    tcp::resolver r;
    tcp::resolver::query q;
    tcp::resolver::results_type endpoint;
    tcp::socket socket;
    boost::system::error_code ec;
public:
    Client(std::string host, std::string protocol) : r(io_context), q(host, protocol), socket(io_context)
    {
        endpoint = r.resolve(q, ec);
    }

    bool connect();

    ~Client() {};
};

#endif /* CLIENT_HPP_ */
