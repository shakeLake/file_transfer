#include "client.hpp"

int main()
{
    Client test("127.0.0.1", "2014");

    if (test.connect())
        std::cout << "Connected" << std::endl;

    std::vector<char> name = {'M', 'a', 'r', 'k', '\n'};
    test.send<std::vector<char>>(name);

    return 0;
}

