#include "session.hpp"

void Session::read()
{
    boost::asio::read_until(socket_, buffer, '\n', ec);

    if (ec && ec != boost::asio::error::eof)
        std::cerr << "Session::read error: " << ec.message() << std::endl;

    output_data();

    buffer.consume( buffer.size() );

    // write();
}

void Session::write()
{
    // input_data();

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

    read();
}

void Session::output_data()
{
    std::istream is(&buffer);

    char* file = new char[/* */];

    is >> file;

    std::ofstream fout;
    fout.open("test.jpg", std::ios_base::binary);

    assert(fout.is_open() == 1);

    fout.write(file, /* */);

    delete [] file;

    fout.close();
}

/*
void Session::input_data(std::string data)
{
    // read and save to array
    std::ifstream fin;
    fin.open(filename, std::ios_base::binary);

    fin.seekg(0, fin.end);
    int length = fin.tellg();
    fin.seekg(0, fin.beg);

    char* file = new char[length];

    fin.read(file, length);

    // save file to streambuffer
    std::ostream os(&buffer);

    os << file;

    delete [] file;
    fin.close();
}
*/