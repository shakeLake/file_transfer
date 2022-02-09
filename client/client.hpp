#ifndef CLIENT_HPP_
#define CLIENT_HPP_

// std::cerr, std::cout, std::endl
#include <iostream>

// boost
#include <boost/asio.hpp>
#include <boost/asio/buffer.hpp>

// std::string
#include <cstring>

using namespace boost::asio::ip;

class Client
{
private:
    boost::asio::io_context io_c;
    tcp::resolver r;
    tcp::resolver::query q;
    tcp::socket s;
    boost::system::error_code ec;
public:
    Client(std::string host, std::string port) : r(io_c), q(host, port), s(io_c)
    {
    }

    bool connect();

    void send(boost::asio::streambuf&);

    ~Client() 
    {
        io_c.run();
        std::cout << "End" << std::endl;
    }
};

#endif /* CLIENT_HPP_ */