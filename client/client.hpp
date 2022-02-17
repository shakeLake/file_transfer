#ifndef CLIENT_HPP_
#define CLIENT_HPP_

// std::cerr, std::cout, std::endl
#include <iostream>

// boost
#include <boost/asio.hpp>
#include <boost/asio/buffer.hpp>

// data
#include <cstring>
#include <vector>

class Client
{
private:
    boost::asio::io_context io_c;

    boost::system::error_code ec;

    boost::asio::ip::tcp::resolver r;
    boost::asio::ip::tcp::socket socket_;

    boost::asio::ip::tcp::resolver::query q;

    boost::asio::streambuf buffer;

    /*
        All data which send from this Client and get from other Client

        DATA in this example is std::string

        std::vector< DATA_TYPE > saved
    */

    void read();

    void write();

    void input_data();
    void output_data();
public:
    Client(std::string host, std::string port) : r(io_c), q(host, port), socket_(io_c)
    {
    }

    bool connect();

    void read_write_cycle()
    {
        write();
    }

    ~Client() 
    {
        io_c.run();
        std::cout << "End" << std::endl;
    }
};

#endif /* CLIENT_HPP_ */