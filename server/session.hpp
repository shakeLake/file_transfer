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
#include <array>

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

    boost::asio::streambuf read_buffer;
    boost::asio::streambuf read_file_buffer;

    boost::asio::streambuf write_buffer;

    void read_prop();
    void read_file();

    void write();

    void get_file_prop();
    void get_file();

    void separate_data(std::string);
public:
    Session(boost::asio::ip::tcp::socket socket) : socket_(std::move(socket))
    { }

    void start()
    {
        get_file_prop();
    }

    ~Session() 
    {
        read_buffer.consume( read_buffer.size() );
        read_file_buffer.consume( read_file_buffer.size() );
    }
}; 

#endif /* SESSION_HPP_ */