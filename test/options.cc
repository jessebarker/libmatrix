#include <iostream>
#include <iomanip>
#include <getopt.h>
#include "libmatrix_test.h"

using std::cout;
using std::endl;

const std::string Options::verbose_name_("verbose");
const std::string Options::help_name_("help");

void
Options::parseArgs(int argc, char** argv)
{
    static struct option long_options[] = {
        {"verbose", 0, 0, 0},
        {"help", 0, 0, 0},
        {0, 0, 0, 0}
    };
    int option_index(0);
    int c =  getopt_long(argc, argv, "", long_options, &option_index);
    while (c != -1) 
    {
        std::string optname(long_options[option_index].name);

        if (optname == verbose_name_)
        {
            verbose_ = true;
        }
        else if (optname == help_name_)
        {
            show_help_ = true;
        }
        c = getopt_long(argc, argv, "",
                        long_options, &option_index);
    }
}


static void
emitColumnOne(const std::string& text)
{
    cout << std::setw(16) << text;
}

void
Options::printUsage()
{
    cout << app_name_ << ": directed functional test utility for libmatrix." << endl;
    cout << "Options:" << endl;
    emitColumnOne("--verbose"); 
    cout << std::setw(0) << " Enable verbose output during test runs." << endl;
    emitColumnOne("--help");
    cout << std::setw(0) << " Print this usage text." << endl;   
}

