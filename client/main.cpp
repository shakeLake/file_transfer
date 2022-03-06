#include "client.hpp"

int main(int argc, char *argv[])
{
    assert(argc > 1 && argc < 3);

    Client test("127.0.0.1", "2014", argv[1]);

    if (test.connect())
        std::cout << "Connected" << std::endl;

    return 0;
}