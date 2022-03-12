#include "session.hpp"

void Session::write(std::string message)
{
    input_data(message);

        boost::asio::async_write(socket_, buffer.data(),
            [](const boost::system::error_code& error, std::size_t bytes_transferred)
            {
                if (error)
                {
                    std::cerr << "Session::write error: " << error.message() << std::endl;
                }
                else
                {
                    std::cout << "Session::write bytes transferred: " << bytes_transferred << std::endl;
                }
            }
        );

    buffer.consume( buffer.size() );
}

void Session::read()
{
    unsigned int bytes_transferred = boost::asio::read(socket_, buffer, boost::asio::transfer_all(), ec);

    if (ec && ec != boost::asio::error::eof)
        std::cerr << "Handler : " << ec.message() << std::endl;
    else
        std::cout << '\n' << "bytes_transferred: " << bytes_transferred << std::endl;
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
    read();

    std::string file_properties;

    std::istream is(&buffer);
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
    read();

    std::istream is(&buffer);

    char* file = new char[file_prop.length];

    is >> file;

    std::ofstream fout;

    std::string full_name = file_prop.filename + '.' + file_prop.filetype;
    fout.open(full_name, std::ios_base::binary);

    assert(fout.is_open());

    fout.write(file, file_prop.length);

    buffer.consume( buffer.size() );
    delete [] file;
    fout.close();
}

void Session::input_data(std::string status_message)
{
    std::ostream os(&buffer);

    os << (status_message += '#');
}
