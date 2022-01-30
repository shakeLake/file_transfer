#include "client.hpp"

int main()
{
    Client test("127.0.0.1", "2014");

    if (test.connect())
        std::cout << "Connected" << std::endl;

    std::string name = "Mark";
    test.send<std::string>(name);

    return 0;
}

