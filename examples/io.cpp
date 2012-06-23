// Headers
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <POLDER/io.h>

using std::cerr;
using std::cout;
using std::endl;
using std::string;
using polder::io::fgetl;
using polder::io::print;


/**
 * @brief Entry point of application
 *
 * @return Application exit code
 */
int main()
{
    ////////////////////////////////////////////////////////////
    {
        // For people who like C
        cout << "fgetl example" << endl;

        // Open a file
        FILE* f = fopen("io_example.txt", "r");
        if (f == nullptr)
        {
            cerr << "Can't open the file.'" << endl;
            exit(1);
        }

        // line is the file reader
        char* line = nullptr;
        // This function reads the file the same way fgets does
        // However, it can read a line, no matter its size.
        while (fgetl(line, f))
        {
            cout << line;
        }
    }

    ////////////////////////////////////////////////////////////
    {
        // For people who like Python
        cout << endl << "print example" << endl;

        int a = 5;
        double b = 6.3;
        string c = "Hello";

        // This function is some kind of wrapper around std::ostream.
        // You can pass any type that can be added to an ostream by
        // the << operator.
        print(a, b, c, "World!");
    }

    return EXIT_SUCCESS;
}
