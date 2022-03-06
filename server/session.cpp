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

void Session::read_file_properties()
{
    boost::asio::read(socket_, file_data, boost::asio::transfer_all(), ec);

    if (ec && ec != boost::asio::error::eof)
        std::cerr << "Session::read error: " << ec.message() << std::endl;
    
    assert( file_data.size() > 0 );
}

void Session::read_file()
{
    std::cout << "read_file" << std::endl;

    boost::asio::read(socket_, buffer, boost::asio::transfer_all(), ec);

    if (ec && ec != boost::asio::error::eof)
    {   
        // write("Server: error");
        std::cerr << "Session::read error: " << ec.message() << std::endl;
    }
    else
    {
        // write("Message transferred");
        std::cout << "Transferring completed" << std::endl;
    }
}

void Session::get_file_prop()
{   
    read_file_properties();

    std::array<std::string, 3>* file_properties = static_cast<std::array<std::string, 3>*>(file_data.data());

    file_prop.filename = file_properties->at(0);
    file_prop.filetype = file_properties->at(1);
    file_prop.length =  std::stoi(file_properties->at(2));

    check_access();
}

void Session::get_file()
{
    read_file();

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

void Session::check_access()
{
    std::cout << "File properties: " << std::endl;
    std::cout << "File name: " << file_prop.filename << std::endl;
    std::cout << "File type: " << file_prop.filetype << std::endl;
    std::cout << "File length: " << file_prop.length << "bytes" << std::endl;

    char status;
    std::cout << "Do you want to get this file: (y/n) " << std::endl;
    std::cin >> status;

    if (status == 'n')
    {
        std::cout << "Socket is closed" << std::endl;
        socket_.close();
    }
    else
    {
        //write("yes");
        get_file();
    }
}
