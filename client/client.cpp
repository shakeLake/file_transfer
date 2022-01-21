// std::cerr, std::endl
#include <iostream>

// boost
#include <boost/asio.hpp>

// header
#include "client.hpp"

bool Client::connect()
{
    if (ec)
    {
        std::cerr << "Resolver error" << std::endl;
        return socket.is_open();
    }

    boost::asio::connect(socket, endpoint,
        [](const boost::system::error_code& ec, const::tcp::endpoint& next)
        {
            if (ec)
                std::cout << "Error: " << ec.message() << std::endl;
                
            std::cout << "Trying: " << next << std::endl;

            return true;
        }
    );

    std::cout << "Connected!" << std::endl;
    return socket.is_open();
}
