#include "session.hpp"

void Session::read()
{
    boost::asio::read_until(socket_, buffer, '\n', ec);

    if (ec && ec != boost::asio::error::eof)
        std::cerr << "Session::read error: " << ec.message() << std::endl;

    std::cout << "Session::read size: " << buffer.size() << std::endl;

    output_data();

    buffer.consume( buffer.size() );

    write();
}

void Session::write()
{
    /*
        async_write send nothing 

        You should add something in buffer
    */

    input_data("Completed");

    boost::asio::async_write(socket_, buffer.data(),
        [](const boost::system::error_code& error, std::size_t bytes_transferred)
        {
            if (error)
            {
                std::cerr << "Session::write error: " << error.message() << std::endl;
            }
            else
            {
                std::cout << "Session::write bytes transferred: " << bytes_transferred << std::endl;
            }
        }
    );

    buffer.consume( buffer.size() );

    read();
}

void Session::input_data(std::string data)
{
    std::ostream output(&buffer);

    data += '\n';

    output << data;
}

void Session::output_data()
{
    std::istream input(&buffer);
    std::string data;
    getline(input, data, '\n');

    std::cout << data << std::endl;
}