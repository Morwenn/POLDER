/*
 * Headers
 */
#include <cstdlib>
#include <iostream>
#include <string>
#include <POLDER/path.h>

using polder::path::make_path;


int main()
{
    std::string path = make_path("trololo", "lala", "lulu");
    std::cout << path << std::endl;

    return EXIT_SUCCESS;
}
