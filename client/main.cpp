#include "client.hpp"

int main()
{
    Client test("127.0.0.1", "2014");

    if (test.connect())
        std::cout << "Connected" << std::endl;

    /* TYPE */
    test.send< /* TYPE */ >(name);

    return 0;
}

