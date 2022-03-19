#include "session.hpp"

void Session::write()
{   
    std::cout<< '\n' << "write" << std::endl;

    std::ostream os(&write_buffer);
    os << "received";

    unsigned int bytes_transferred =  boost::asio::write(socket_, write_buffer.data(), boost::asio::transfer_all(), ec);

    if (ec && ec != boost::asio::error::eof)
    {
        std::cerr << "Handler : " << ec.message() << std::endl;
        socket_.close();
    }
    else
    {
        std::cout << "bytes_transferred: " << bytes_transferred << std::endl;

        write_buffer.consume( write_buffer.size() );
    }
}

void Session::read_prop()
{
    std::cout << '\n' << "read" << std::endl;

    unsigned int bytes_transferred =  boost::asio::read_until(socket_, read_buffer, '*', ec);

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

void Session::read_file()
{
    std::cout << '\n' << "read" << std::endl;

    unsigned int bytes_transferred =  boost::asio::read(socket_, read_file_buffer, boost::asio::transfer_all(), ec);

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

void Session::separate_data(std::string data)
{
    std::string buffer_str[3];

    for (unsigned short i = 0, j = 0; i != data.size(); i++)
    {
        if (data[i] != '#')
        {
            buffer_str[j] += data[i];
        }
        else
        {
            j += 1;
        }
    }

    file_prop.filename = buffer_str[0];
    file_prop.filetype = buffer_str[1];
    file_prop.length = std::stoi( buffer_str[2] );
}

void Session::get_file_prop()
{   
    read_prop();

    std::string file_properties;

    std::istream is(&read_buffer);
    is >> file_properties;

    separate_data(file_properties);

    std::cout << '\n' << "File properties: " << std::endl;
    std::cout << "File name: " << file_prop.filename << std::endl;
    std::cout << "File type: " << file_prop.filetype << std::endl;
    std::cout << "File size: " << file_prop.length << " bytes" << std::endl;

    get_file();
}

void Session::get_file()
{
    read_file();
    
    assert(read_file_buffer.size() == file_prop.length);

    file_prop.file = new char[file_prop.length];
    
    std::string str_file((std::istreambuf_iterator<char>(&read_file_buffer)), std::istreambuf_iterator<char>());

    for (unsigned int i = 0; i != file_prop.length; i++)
        file_prop.file[i] = str_file[i];

    std::ofstream fout;

    std::string full_name = file_prop.filename + '.' + file_prop.filetype;
    fout.open(full_name, std::ios_base::binary);

    assert(fout.is_open());

    fout.write(file_prop.file, file_prop.length);

    delete [] file_prop.file;
    fout.close();
}