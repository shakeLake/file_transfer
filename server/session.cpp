#include "session.hpp"

void Session::read()
{
    boost::asio::read_until(socket_, buffer, '\n', ec);

    if (ec)
        std::cerr << "Session::read error: " << ec.message() << std::endl;

    std::cout << "Session::read size: " << buffer.size() << std::endl;

    std::istream input(&buffer);
    std::string line;
    getline(input, line, '\n');

    std::cout << line << std::endl;

    buffer.consume( buffer.size() );

    read();
    //write();
}

void Session::write()
{
    /*
        extern boost::asio::streambuf buffer; // Variable determined in session.hpp

        std::istream input(&buffer);
        std::string line;
        getline(input, line, '\n');    
    */

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
