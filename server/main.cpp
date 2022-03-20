#include "server.cpp"

int main()
{
    boost::asio::io_context io_c;

    Server one(io_c);
    
    std::cout << "Listening" << std::endl;

    one.waiting();

    io_c.run();

    return 0;
}
