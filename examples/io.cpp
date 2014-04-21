/*
 * Headers
 */
#include <cstdio>
#include <iostream>
#include <string>
#include <POLDER/io.h>

using std::cerr;
using std::cout;
using std::endl;
using std::string;
using polder::io::fgetl;
using polder::io::open;
using polder::io::print;
using polder::io::File;


/**
 * @brief Entry point of application
 *
 * @return Application exit code
 */
int main()
{
    ////////////////////////////////////////////////////////////
    {
        cout << "fgetl example" << endl;

        // Open a file
        FILE* f = fopen("io_example.txt", "r");
        if (f == nullptr)
        {
            cerr << "Can't open the file.'" << endl;
            exit(1);
        }

        // line is the file reader.
        // Be sure to set it to nullptr before calling the function;
        // otherwise it "may" work but won't be safe.
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
        cout << endl << "print examples" << endl;

        int a = 5;
        double b = 6.3;
        string c = "Hello";

        // This function is some kind of wrapper around std::ostream.
        // You can pass any type that can be added to an ostream by
        // the << operator.
        print(a, b, c, "World!");

        // The results can be forwarded to the given output stream
        // instead of always being fed to std::cout.
        print(cerr, 5.3, 2, "Hey!");
    }

    ////////////////////////////////////////////////////////////
    {
        cout << endl << "File/open example" << endl;

        // Open a file
        File f = open("io_example.txt", "r");

        // Read and display all the lines
        for (const string& line: f)
        {
            cout << line;
        }
        // Close the file
        f.close();
    }
}
