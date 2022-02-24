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

void Client::write()
{
    input_data();

    boost::asio::write(socket_, buffer.data(), boost::asio::transfer_all(), ec);

    if (ec)
        std::cerr << "Client::write error: " << ec.message() << std::endl;

    buffer.consume( buffer.size() );

    //read();
}

void Client::read()
{
    boost::asio::read_until(socket_, buffer, '\n', ec);

    if (ec && ec != boost::asio::error::eof)
        std::cerr << "Client::read error: " << ec.message() << std::endl;

    //output_data();

    buffer.consume( buffer.size() );
}

void Client::input_data()
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

/*
void Client::output_data()
{
    std::ofstream fout;
    fout.open(FILENAME, std::ios_base::binary);

    if (!fout.is_open())
        std::cerr << "Error" << std::endl;

    fout.write(file, LENGTH);
}
*/