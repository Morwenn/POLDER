/*
 * Headers
 */
#include <iostream>
#include <string>
#include <POLDER/path.h>

using std::cout;
using std::endl;
using std::string;
using polder::path::make_path;


int main()
{
    string path = make_path("trololo", "lala", "lulu");
    cout << path << endl;
}
