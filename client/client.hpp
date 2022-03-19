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

#include <chrono>

class Client
{
private:
    boost::asio::io_context io_c;

    boost::system::error_code ec;

    boost::asio::ip::tcp::resolver r;
    boost::asio::ip::tcp::socket socket_;

    boost::asio::ip::tcp::resolver::query q;

    boost::asio::streambuf read_buffer;

    boost::asio::streambuf write_buffer;
    boost::asio::streambuf write_file_buffer;

    // Construct a timer without setting an expiry time.
    boost::asio::deadline_timer timer;

    struct Properties
    {
        std::string filename;
        std::string filetype;
        void separate_filename(std::string);

        unsigned int length;

        std::string str_file;
        char* file;

        std::ifstream fin;
    } file_prop;

    void read();

    void write_prop();
    void write_file();
public:
    Client(std::string host, std::string port, char* fn) : r(io_c), q(host, port), socket_(io_c), timer(io_c)
    {
        file_prop.fin.open(fn, std::ios_base::binary);

        assert(file_prop.fin.is_open());

        file_prop.separate_filename(fn);

        file_prop.fin.seekg(0, file_prop.fin.end);
        file_prop.length = file_prop.fin.tellg();
        file_prop.fin.seekg(0, file_prop.fin.beg);

        file_prop.file = new char[file_prop.length];

        std::string file_properties = file_prop.filename + '#' + file_prop.filetype + '#' + std::to_string(file_prop.length) + '*';

        // save file properties to streambuffer
        std::ostream os_file_prop(&write_buffer);
        os_file_prop << file_properties;

        file_prop.fin.read(file_prop.file, file_prop.length);

        // save file to streambuffer
        file_prop.str_file.resize(file_prop.length);
        for (unsigned int i = 0; i != file_prop.length; i++)
            file_prop.str_file[i] = file_prop.file[i];

        std::ostream os_file(&write_file_buffer);
        os_file << file_prop.str_file;
    }

    bool connect();

    ~Client() 
    {
        file_prop.fin.close();

        delete [] file_prop.file;

        io_c.run();

        std::cout << '\n' << "End" << std::endl;
    }
};

#endif /* CLIENT_HPP_ */