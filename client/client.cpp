#include "client.hpp"

bool Client::connect()
{
    if (ec)
    {
        std::cerr << "Resolver error: " << ec.message() << std::endl;
        return socket.is_open();
    }

    boost::asio::connect(socket, endpoint,
        [](const boost::system::error_code& ec, const::tcp::endpoint& next)
        {       
            std::cout << "Trying: " << next << std::endl;
            return true;
        }
    );

    return socket.is_open();
}
