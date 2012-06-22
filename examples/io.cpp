// Headers
#include <cstdlib>
#include <string>
#include <POLDER/io.h>


using polder::io::print;

int main()
{
    int a = 5;
    double b = 6.3;
    std::string c = "Hello";

    // This function is some kind of wrapper around std::ostream.
    // You can pass any type that can be added to an ostream by
    // the << operator.
    print(a, b, c, "World!");

    return EXIT_SUCCESS;
}
