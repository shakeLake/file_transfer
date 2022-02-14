#include "server.hpp"

void Server::waiting()
{
    tcp_acceptor.async_accept(
        [this](const boost::system::error_code& ec, boost::asio::ip::tcp::socket socket_)
        {
            if (!ec)
            {
                std::cerr << "New connections" << std::endl;
                std::make_shared<Session>(std::move(socket_))->read_write_cycle();
            }

            waiting();
        }
    );
}