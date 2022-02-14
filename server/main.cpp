#include "server.cpp"

int main()
{
    boost::asio::io_context io_c;

    Server test(io_c);
    
    std::cout << "Listening" << std::endl;

    test.waiting();

    io_c.run();

    return 0;
}
