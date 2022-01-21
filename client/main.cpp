#include <iostream>
#include "client.hpp"

int main()
{
    // "towel.blinkenlights.nl", "telnet"
    Client test("towel.blinkenlights.nl", "telnet");

    test.connect();

    return 0;
}
