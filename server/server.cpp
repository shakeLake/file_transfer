#include "server.hpp"

bool Server::waiting()
{
    tcp_acceptor.async_accept(tcp_socket,
        [this](const boost::system::error_code& ec)
        {
            if (ec)
                std::cerr << "async_accept() error: " << ec.message() << std::endl;
            else
                reading < std::string >();
        }
    );
    
    return tcp_acceptor.is_open();
}