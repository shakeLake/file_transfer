#include "client.hpp"

bool Client::connect()
{
    if (ec)
    {
        std::cerr << "Resolver error: " << ec.message() << std::endl;
        return socket_.is_open();
    }

    boost::asio::connect(socket_, r.resolve(q, ec),
        [](const boost::system::error_code& ec, const boost::asio::ip::tcp::endpoint& next)
        {      
            if (ec)
            {
                std::cerr << ec.message() << std::endl;
                return false;
            }
            else
            {
                std::cout << "Trying: " << next << std::endl;
                return true;
            }
        }
    );

    std::cout << "Connected" << std::endl;

    write_prop(); // Program Start Here!

    return socket_.is_open();
}

void Client::Properties::separate_filename(std::string fn)
{
    unsigned short symb_counter = fn.size();
    while (fn[symb_counter] != '.')
    {
        filetype += fn[symb_counter];
        symb_counter -= 1;
    }
    symb_counter -= 1;

    // string reverse 
    char buf;
    for (unsigned short i = filetype.size() - 1, j = 0; j != (filetype.size() / 2); i--, j++)
    {
        buf = filetype[j];
        filetype[j] = filetype[i];
        filetype[i] = buf;
    }

    while (fn[symb_counter] != '/')
    {
        filename += fn[symb_counter];
        symb_counter -= 1;
    }

    // string reverse
    for (unsigned short i = filename.size() - 1, j = 0; j != (filename.size() / 2); i--, j++)
    {
        buf = filename[j];
        filename[j] = filename[i];
        filename[i] = buf;
    }
}

void Client::write_prop()
{
    std::cout << '\n' << "write" << std::endl;

    unsigned int bytes_transferred = boost::asio::write(socket_, write_buffer.data(), boost::asio::transfer_all(), ec);

    if (ec && ec != boost::asio::error::eof)
    {
        std::cerr << "Handler : " << ec.message() << std::endl;
        socket_.close();
    }
    else
    {
        std::cout << "bytes_transferred: " << bytes_transferred << std::endl;

        // Set an expiry time relative to now.
        timer.expires_from_now(boost::posix_time::milliseconds(1));

        // Wait for the timer to expire.
        timer.wait();

        write_file();
    }
}

void Client::write_file()
{
    std::cout << '\n' << "write" << std::endl;

    unsigned int bytes_transferred = boost::asio::write(socket_, write_file_buffer.data(), boost::asio::transfer_all(), ec);

    if (ec && ec != boost::asio::error::eof)
    {
        std::cerr << "Handler : " << ec.message() << std::endl;
        socket_.close();
    }
    else
    {
        std::cout << "bytes_transferred: " << bytes_transferred << std::endl;
    }
}