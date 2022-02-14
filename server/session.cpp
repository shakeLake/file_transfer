#include "session.hpp"

void Session::reading()
{
    boost::asio::streambuf buf;

    boost::asio::read_until(socket_, buf, '#', ec);

    if (ec)
        std::cerr << "Error: " << ec.message() << std::endl;

    std::cout << "Size: " << buf.size() << std::endl;

    std::istream input(&buf);
    std::string line;
    getline(input, line, '#');

    std::cout << line << std::endl;
}

void Session::writing()
{

}
