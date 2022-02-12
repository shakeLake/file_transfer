#ifndef CLIENT_HPP_
#define CLIENT_HPP_

// std::cerr, std::cout, std::endl
#include <iostream>

// boost
#include <boost/asio.hpp>
#include <boost/asio/buffer.hpp>

// std::string
#include <cstring>

class Client
{
private:
    boost::asio::io_context io_c;

    boost::system::error_code ec;

    boost::asio::ip::tcp::resolver r;
    boost::asio::ip::tcp::socket s;

    boost::asio::ip::tcp::resolver::query q;
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