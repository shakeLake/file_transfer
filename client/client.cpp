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

    return socket_.is_open();
}

void Client::Properties::separate_filename(char* fn)
{
    unsigned short length = sizeof(fn) / sizeof(fn[0]);

    unsigned short symb_counter = length;
    while (fn[symb_counter] != '.')
    {
        symb_counter -= 1;
        filetype += fn[symb_counter];
    }

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
        symb_counter -= 1;
        filename += fn[symb_counter];
    }

    // string reverse
    for (unsigned short i = filename.size() - 1, j = 0; j != (filename.size() / 2); i--, j++)
    {
        buf = filename[j];
        filename[j] = filename[i];
        filename[i] = buf;
    }
}

void Client::read()
{
    boost::asio::read_until(socket_, buffer, '#', ec);

    if (ec && ec != boost::asio::error::eof)
        std::cerr << "Client::read error: " << ec.message() << std::endl;

    // get data from buffer
    std::istream is(&buffer);
    std::string status_message;
    
    getline(is, status_message, '#');

    buffer.consume( buffer.size() );
}

void Client::input_file_prop()
{
    std::array<std::string, 3> file_properties = {file_prop.filename, file_prop.filetype, std::to_string( file_prop.length )};

    write<boost::asio::mutable_buffer> ( boost::asio::buffer(file_properties) );
}

void Client::input_file()
{
    file_prop.fin.read(file_prop.file, file_prop.length);

    // save file to streambuffer
    std::ostream os(&buffer);
    os << file_prop.file;

    write< boost::asio::const_buffer > (buffer.data());

    delete [] file_prop.file;
    file_prop.fin.close();
}