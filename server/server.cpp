#include "server.hpp"

bool Server::waiting()
{
    tcp_acceptor.async_accept(tcp_socket,
        [this](const boost::system::error_code& ec)
        {
            if (ec)
                std::cerr << "async_accept() error: " << ec.message() << std::endl;
            else
                reading();
        }
    );
    
    return tcp_acceptor.is_open();
}

void Server::reading()
{
    boost::asio::streambuf data;

    boost::asio::async_read_until(tcp_socket, data, '#', 
        [](const boost::system::error_code& ec, std::size_t size)
        {
            if (ec)
            {
                std::cerr << "Error: " << ec.message() << std::endl;
            }
            else
            {
                std::cout << "Size: " << size << std::endl;
            }
        }
    ); 
}