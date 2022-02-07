#ifndef CLIENT_HPP_
#define CLIENT_HPP_

// std::cerr, std::cout, std::endl
#include <iostream>

// boost
#include <boost/asio.hpp>
#include <boost/asio/buffer.hpp>

// STL
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

    template<typename T>
    void send( T );

    ~Client() 
    {
        io_c.run();
        std::cout << "End" << std::endl;
    }
};

template <typename T>
void Client::send(T data)
{
    boost::asio::async_write(s, boost::asio::buffer(data),
        [](const boost::system::error_code& error, std::size_t bytes_transferred)
        {
            if (error)
            {
                std::cerr << "Error: " << error.message() << std::endl;
            }
            else
            {
                std::cout << "Bytes transferred: " << bytes_transferred << std::endl;
            }
        }
    );
}

#endif /* CLIENT_HPP_ */