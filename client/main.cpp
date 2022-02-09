#include "client.hpp"

int main()
{
    Client test("127.0.0.1", "2014");

    if (test.connect())
        std::cout << "Connected" << std::endl;

    boost::asio::streambuf buf;
    std::ostream os(&buf);
    os << "Hello World#";

    test.send(buf);

    return 0;
}

