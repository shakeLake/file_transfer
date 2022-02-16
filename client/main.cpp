#include "client.hpp"

int main()
{
    Client test("127.0.0.1", "2014");

    if (test.connect())
        std::cout << "Connected" << std::endl;

    test.read_write_cycle
    (
        test.input_data()
    );

    return 0;
}

