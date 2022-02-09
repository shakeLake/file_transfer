#include "client.hpp"

bool Client::connect()
{
    if (ec)
    {
        std::cerr << "Resolver error: " << ec.message() << std::endl;
        return s.is_open();
    }

    boost::asio::connect(s, r.resolve(q, ec),
        [](const boost::system::error_code& ec, const::tcp::endpoint& next)
        {      
            if (ec)
            {
                std::cerr << ec.message() << std::endl;
                return false;
            }
            else
            {
                std::cout << "Trying: " << next << std::endl;
                return true;
            }
        }
    );

    return s.is_open();
}

void Client::send(boost::asio::streambuf& buf)
{
    boost::asio::async_write(s, buf.data(),
        [](const boost::system::error_code& error, std::size_t bytes_transferred)
        {
            if (error)
            {
                std::cerr << "Error: " << error.message() << std::endl;
            }
            else
            {
                std::cout << "Bytes transferred: " << bytes_transferred << std::endl;
            }
        }
    );
}