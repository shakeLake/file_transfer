#include "server.hpp"

void Server::waiting()
{
    tcp_acceptor.async_accept(tcp_socket,
        [this](const boost::system::error_code& ec)
        {
            if (!ec)
            {
                std::cout << "Connection established" << std::endl;

                accepting< std::vector<char> >();
            }
        }
    );
}