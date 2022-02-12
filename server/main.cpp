#include "server.cpp"

int main()
{
    Server test;
    
    std::cout << "Listening" << std::endl;

    test.waiting();

    return 0;
}
