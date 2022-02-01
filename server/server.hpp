#ifndef SERVER_HPP_
#define SERVER_HPP_

// I / O
#include <iostream>

// boost
#include <boost/asio.hpp>
#include <boost/asio/buffer.hpp>

// STL
#include <array>


class Server
{
private:
    boost::asio::io_context io_context;
    boost::asio::ip::tcp::endpoint tcp_endpoint;
    boost::asio::ip::tcp::acceptor tcp_acceptor;
    boost::asio::ip::tcp::socket tcp_socket;
    boost::system::error_code ec;
public:
    Server() : tcp_socket(io_context), tcp_endpoint(boost::asio::ip::tcp::v4(), 2014), tcp_acceptor(io_context, tcp_endpoint)
    { 
    }

    void waiting();

    template <typename T>
    void accepting();

    ~Server() 
    { 
        io_context.run(); 
    }
};

template <typename T>
void Server::accepting()
{
    T data;

    boost::asio::async_read(tcp_socket, boost::asio::buffer(data),
        [this, data](const boost::system::error_code& ec, std::size_t bytes_transferred)
        {
            if (!ec)
            {
                std::cout << "bytes transferred: " << bytes_transferred << std::endl;
            }
            else 
            {
                std::cerr << "Error: " << ec.message() << std::endl;
            }
        }
    ); 
}

#endif /* SERVER_HPP_ */
