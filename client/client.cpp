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
    write(); // Program Start Here!

    return socket_.is_open();
}

void Client::Properties::separate_filename(std::string fn)
{
    unsigned short symb_counter = fn.size();

    // file type

    unsigned short file_Type_Name_length = 0;
    unsigned short symb_counter_copy = symb_counter;
    while (fn[symb_counter_copy] != '.')
    {
        file_Type_Name_length += 1;
        symb_counter_copy -= 1;
    }

    // just patch
    // the best way is truncate file name or you can increase "filename_length"
    assert(file_Type_Name_length < filetype_length - 1);

    filetype[file_Type_Name_length] = '*';
    while (file_Type_Name_length != 0)
    {
        filetype[file_Type_Name_length - 1] += fn[symb_counter];
        symb_counter -= 1;
        file_Type_Name_length -= 1;
    }
    symb_counter -= 1;

    // file name

    file_Type_Name_length = 0;
    symb_counter_copy = symb_counter;
    while (fn[symb_counter_copy] != '/')
    {
        file_Type_Name_length += 1;
        symb_counter_copy -= 1;
    }

    // just patch
    // the best way is truncate file name or you can increase "filename_length"
    assert(file_Type_Name_length < filename_length - 1);

    filename[file_Type_Name_length] = '*';
    while (file_Type_Name_length != 0)
    {
        filename[file_Type_Name_length - 1] += fn[symb_counter];
        symb_counter -= 1;
        file_Type_Name_length -= 1;
    }

    for (int i = 0; i != filename_length - 1; i++)
        std::cout << filename[i];

    std::cout << std::endl;

    for (int j = 0; j != filetype_length - 1; j++)
        std::cout << filetype[j];
}

void Client::write()
{
    std::cout << '\n' << "write" << std::endl;

    unsigned int bytes_transferred = boost::asio::write(socket_, boost::asio::buffer(file_data), ec);

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

/*
void Client::read()
{
    std::cout << '\n' << "read" << std::endl;

    unsigned int bytes_transferred = boost::asio::read(socket_, read_buffer, boost::asio::transfer_all(), ec);

    if (ec && ec != boost::asio::error::eof)
    {
        std::cerr << "Client::read error: " << ec.message() << std::endl;
        socket_.close();
    }
    else
    {
        std::cout << "bytes_transferred: " << bytes_transferred << std::endl;

        // get data from buffer
        std::istream is(&read_buffer);
        std::string status_message;

        is >> status_message;

        std::cout << status_message << std::endl;

        read_buffer.consume( read_buffer.size() );
    }
}

void Client::write()
{
    std::cout << '\n' << "write" << std::endl;

    unsigned int bytes_transferred = boost::asio::write(socket_, write_buffer.data(), ec);

    if (ec && ec != boost::asio::error::eof)
    {
        std::cerr << "Handler : " << ec.message() << std::endl;
        socket_.close();
    }
    else
    {
        std::cout << "bytes_transferred: " << bytes_transferred << std::endl;

        write_buffer.consume( write_buffer.size() );

        read();
    }
}

void Client::send_file_prop()
{
    std::string file_properties = file_prop.filename + '#' + file_prop.filetype + '#' + std::to_string(file_prop.length) + '#';

    // save file properties to streambuffer
    std::ostream os(&write_buffer);
    os << file_properties;

    write();

    send_file();
}

void Client::send()
{
    file_prop.fin.read(file_prop.file, file_prop.length);

    // save file to streambuffer
    std::ostream os(&write_buffer);
    os << file_prop.file;

    write();

    delete [] file_prop.file;
    file_prop.fin.close();
}

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

*/