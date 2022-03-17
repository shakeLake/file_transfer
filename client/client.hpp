#ifndef CLIENT_HPP_
#define CLIENT_HPP_

// std::cerr, std::cout, std::endl
#include <iostream>

// boost
#include <boost/asio.hpp>
#include <boost/asio/buffer.hpp>

// data
#include <fstream>
#include <cstring>
#include <array>
#include <vector>

// assert
#include <cassert>

class Client
{
private:
    boost::asio::io_context io_c;

    boost::system::error_code ec;

    boost::asio::ip::tcp::resolver r;
    boost::asio::ip::tcp::socket socket_;

    boost::asio::ip::tcp::resolver::query q;

    boost::asio::streambuf read_buffer;

    std::vector<boost::asio::const_buffer> file_data;

    struct Properties
    {
        const unsigned short filename_length = 50;
        const unsigned short filetype_length = 10;

        std::array<char, 50> filename;
        std::array<char, 10> filetype;
        void separate_filename(std::string);

        unsigned int length;

        char* file;

        std::ifstream fin;
    } file_prop;

    void read();

    void write();

    void send_file();
public:
    Client(std::string host, std::string port, char* fn) : r(io_c), q(host, port), socket_(io_c)
    {
        file_prop.filename[30];
        file_prop.filetype[20];

        file_prop.fin.open(fn, std::ios_base::binary);

        assert(file_prop.fin.is_open());

        file_prop.separate_filename(fn);

        file_prop.fin.seekg(0, file_prop.fin.end);
        file_prop.length = file_prop.fin.tellg();
        file_prop.fin.seekg(0, file_prop.fin.beg);

        file_prop.file = new char[file_prop.length];

        file_prop.fin.read(file_prop.file, file_prop.length);

        file_data.push_back( boost::asio::buffer(file_prop.filename) );
        file_data.push_back( boost::asio::buffer(file_prop.filetype) );
        file_data.push_back( file_prop.file );
    }

    bool connect();

    ~Client() 
    {
        delete [] file_prop.file;

        file_prop.fin.close();

        io_c.run();

        std::cout << "End" << std::endl;
    }
};

#endif /* CLIENT_HPP_ */