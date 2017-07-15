#include "gen_head.h"

#include <iostream>


int main(int argc, char *argv[])
{
    // Read system parameters.
    if (argc != 3)
    {
        std::cerr << "Bad arguments count" << std::endl;
        return 1;
    }

    String xml_path = argv[1];
    String out_path = argv[2];

    std::cout << "xml = " << (std::string)xml_path << std::endl;
    std::cout << "out = " << (std::string)out_path << std::endl;

    return 0;
}
