#include "server.hpp"

bool Server::waiting()
{
    tcp_acceptor.async_accept(tcp_socket,
        [this](const boost::system::error_code& ec)
        {
            if (ec)
                std::cerr << "async_accept() error: " << ec.message() << std::endl;
            else
                reading();
        }
    );
    
    return tcp_acceptor.is_open();
}

void Server::reading()
{
    boost::asio::streambuf buf;

    boost::asio::read_until(tcp_socket, buf, '#', ec);

    if (ec)
        std::cerr << "Error: " << ec.message() << std::endl;

    std::cout << "Size: " << buf.size() << std::endl;

    std::istream input(&buf);
    std::string line;
    getline(input, line, '#');

    std::cout << line << std::endl;
}