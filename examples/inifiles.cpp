/*
 * Headers
 */
#include <cstdio>
#include <iostream>
#include <POLDER/ini.h>

using namespace polder;


/**
 * @brief Entry point of application
 *
 * @return Application exit code
*/
int main()
{
    char ini_file[] = "ini_test.ini";

    ini::write_string(ini_file, "Workgroup", "Computer01", "Windows");

    return EXIT_SUCCESS;
}
