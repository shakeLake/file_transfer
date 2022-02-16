#ifndef CLIENT_HPP_
#define CLIENT_HPP_

// std::cerr, std::cout, std::endl
#include <iostream>

// boost
#include <boost/asio.hpp>
#include <boost/asio/buffer.hpp>

// std::string
#include <cstring>

class Client
{
private:
    boost::asio::io_context io_c;

    boost::system::error_code ec;

    boost::asio::ip::tcp::resolver r;
    boost::asio::ip::tcp::socket socket_;

    boost::asio::ip::tcp::resolver::query q;

    void read();

    void write(boost::asio::streambuf&);
public:
    Client(std::string host, std::string port) : r(io_c), q(host, port), socket_(io_c)
    {
    }

    bool connect();

    boost::asio::streambuf input_data();

    void read_write_cycle(boost::asio::streambuf& buf)
    {
        write(buf);
    }

    ~Client() 
    {
        io_c.run();
        std::cout << "End" << std::endl;
    }
};

#endif /* CLIENT_HPP_ */