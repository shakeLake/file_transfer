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
    send_file_prop(); // Program Start Here!

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

std::string Client::read()
{
    boost::asio::read_until(socket_, buffer, '#', ec);

    if (ec && ec != boost::asio::error::eof)
        std::cerr << "Client::read error: " << ec.message() << std::endl;

    // get data from buffer
    std::istream is(&buffer);
    std::string status_message;
    
    getline(is, status_message, '#');

    return status_message;
}

void Client::write()
{
    unsigned int bytes_transferred = boost::asio::write(socket_, buffer.data(), boost::asio::transfer_all(), ec);

    if (ec && ec != boost::asio::error::eof)
        std::cerr << "Handler : " << ec.message() << std::endl;
    else
        std::cout << '\n' << "bytes_transferred: " << bytes_transferred << std::endl;

    buffer.consume( buffer.size() );
}

void Client::send_file_prop()
{
    std::string file_properties = file_prop.filename + '#' + file_prop.filetype + '#' + std::to_string(file_prop.length) + '#';

    // save file properties to streambuffer
    std::ostream os(&buffer);
    os << file_properties;

    write();

    send_file();
}

void Client::send_file()
{
    file_prop.fin.read(file_prop.file, file_prop.length);

    // save file to streambuffer
    std::ostream os(&buffer);
    os << file_prop.file;

    write();

    delete [] file_prop.file;
    file_prop.fin.close();
}