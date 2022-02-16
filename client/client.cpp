#include "client.hpp"

bool Client::connect()
{
    if (ec)
    {
        std::cerr << "Resolver error: " << ec.message() << std::endl;
        return socket_.is_open();
    }

    boost::asio::connect(socket_, r.resolve(q, ec),
        [](const boost::system::error_code& ec, const boost::asio::ip::tcp::endpoint& next)
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

    return socket_.is_open();
}

boost::asio::streambuf input_data()
{
    boost::asio::streambuf buf;

    std::istream input(&buf);

    std::string data;

    std::cout << "Input: " << std::endl;
    geline(input, data, "#");

    return buf;
}

void Client::write(boost::asio::streambuf& buf)
{
    boost::asio::async_write(socket_, buf.data(),
        [](const boost::system::error_code& error, std::size_t bytes_transferred)
        {
            if (error)
            {
                std::cerr << "Client::write error: " << error.message() << std::endl;
            }
            else
            {
                std::cout << "Client::write bytes transferred: " << bytes_transferred << std::endl;
            }
        }
    );

    read();
}

void Client::read()
{
    boost::asio::streambuf buf;

    boost::asio::read_until(socket_, buf, '#', ec);

    if (ec)
        std::cerr << "Client::read error: " << ec.message() << std::endl;

    std::cout << "Client::read size: " << buf.size() << std::endl;

    std::istream input(&buf);
    std::string line;
    getline(input, line, '#');

    std::cout << line << std::endl;
}