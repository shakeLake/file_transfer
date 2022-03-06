#ifndef SESSION_HPP_
#define SESSION_HPP_

// std::cerr, std::cout, std::endl
#include <iostream>

// boost
#include <boost/asio.hpp>
#include <boost/asio/buffer.hpp>

// data
#include <fstream>
#include <cstring>

// assert
#include <cassert>

class Session
{
private:
    boost::asio::ip::tcp::socket socket_;

    boost::system::error_code ec;

    struct
    {
        std::string path;
        std::string filename;
        std::string filetype;

        unsigned int length;

        char* file;
    } file_prop;

    boost::asio::mutable_buffer file_data;
    boost::asio::streambuf buffer;

    template <typename T>
    void read(T);

    void write(std::string);

    void input_data(std::string);

    void get_file();
    void get_file_prop();

    void check_access();
public:
    Session(boost::asio::ip::tcp::socket socket) : socket_(std::move(socket)) 
    {
    }

    void start()
    {
        get_file_prop();
    }

    ~Session() 
    { }
}; 

template <typename T>
void Session::read(T data)
{
    boost::asio::read(socket_, data, boost::asio::transfer_all(), ec);

    if (ec && ec != boost::asio::error::eof)
    {   
        write("Server: error");
        std::cerr << "Session::read error: " << ec.message() << std::endl;
    }
    else
    {
        write("Message transferred");
        std::cout << "Transferring completed" << std::endl;
    }
}

#endif /* SESSION_HPP_ */