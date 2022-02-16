#include "session.hpp"

void Session::read()
{
    boost::asio::streambuf buf;

    boost::asio::read_until(socket_, buf, '#', ec);

    if (ec)
        std::cerr << "Session::read error: " << ec.message() << std::endl;

    std::cout << "Session::read size: " << buf.size() << std::endl;

    std::istream input(&buf);
    std::string line;
    getline(input, line, '#');

    std::cout << line << std::endl;

    write(buf);
}

void Session::write(boost::asio::streambuf& buf)
{
    boost::asio::async_write(socket_, buf.data(),
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
}
