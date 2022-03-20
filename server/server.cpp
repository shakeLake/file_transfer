#include "server.hpp"

void Server::waiting()
{
    tcp_acceptor.async_accept(
        [this](const boost::system::error_code& ec, boost::asio::ip::tcp::socket socket_)
        {
            if (!ec)
            {
                std::cout << "New connection" << std::endl;
                std::make_shared<Session>(std::move(socket_))->start();
            }
            
            waiting(); 
        }
    );
}