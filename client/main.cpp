#include "client.hpp"

int main(int argc, char *argv[])
{
    assert(argc > 1 && argc < 3);

    Client one("127.0.0.1", "2014", argv[1]);

    one.connect();

    return 0;
}