#include "server.hpp"

void Server::waiting()
{
    tcp_acceptor.listen();

    tcp_acceptor.async_accept(tcp_socket,
        [](const boost::system::error_code& ec)
        {
            if (!ec)
            {
                std::cout << "Connection established" << std::endl;
            }
        }
    );

    io_context.run();
}