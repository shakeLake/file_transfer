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

void Client::input_data()
{
    std::ostream output(&buffer);

    std::string data;

    std::cout << "Input: " << std::endl;
    getline(std::cin, data, '\n');

    output << data;
}

void Client::output_data()
{
    std::istream input(&buffer);
    std::string data;
    getline(input, data, '\n');

    std::cout << data << std::endl;
}

void Client::write()
{
    input_data();

    boost::asio::async_write(socket_, buffer.data(),
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

    saved.push_back(buffer);

    buffer.consume( buffer.size() );

    //read();
}

void Client::read()
{
    boost::asio::read_until(socket_, buffer, '\n', ec);

    if (ec)
        std::cerr << "Client::read error: " << ec.message() << std::endl;

    std::cout << "Client::read size: " << buffer.size() << std::endl;

    output_data();

    saved.push_back(buffer);

    buffer.consume( buffer.size() );

    write();
}