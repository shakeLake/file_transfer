#include "client.hpp"

int main()
{
    Client test("127.0.0.1", "2014");

    if (test.connect())
        std::cout << "Connected" << std::endl;

    //std::array<char, 32> name = {'M', 'a', 'r', 'k'};
    std::string name = "Mark\n";
    test.send< std::string >(name);

    return 0;
}

