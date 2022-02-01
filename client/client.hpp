#ifndef CLIENT_HPP_
#define CLIENT_HPP_

// std::cerr, std::cout, std::endl
#include <iostream>

// boost
#include <boost/asio.hpp>
#include <boost/asio/buffer.hpp>

// STL
#include <array>

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
    Client(std::string host, std::string port) : r(io_context), q(host, port), socket(io_context)
    {
        endpoint = r.resolve(q, ec);
    }

    bool connect();

    template<typename T>
    void send( T );

    void read();

    ~Client() 
    {
        io_context.run();
    }
};

template <typename T>
void Client::send(T data)
{
    boost::asio::async_write(socket, boost::asio::buffer(data),
        [](const boost::system::error_code& error, std::size_t bytes_transferred)
        {
            if (error)
                std::cerr << "Error: " << error.message() << std::endl;

            std::cout << "Bytes transferred: " << bytes_transferred << std::endl;
        }
    ); 
}

#endif /* CLIENT_HPP_ */