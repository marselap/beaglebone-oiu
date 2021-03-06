/*! \file  mainApp.cpp
    \brief Example of CASU_Interface class usage.
 */


#include "CASU_Interface.h"

#include <yaml-cpp/yaml.h>

#include <iostream>

using namespace std;

/*! \brief Main function of the CASU interface between MCU and user controller.
 *
 *  An .fbc file *MUST* be provided as the only argument when invoking the program:
 *
 *  casu-fw <firmware board config>.fbc
 *
 *  Instantiates CASU_Interface and creates three threads for:
 *  - i2c communication
 *  - publishing ZMQ messages
 *  - receiving ZMQ messages.
 */
int main(int argc, char **argv) {

    if (argc < 3)
    {
        cout << "Please provide the .fbc and .fzy file names as the program arguments." << endl;
        exit(1);
    }

    CASU_Interface casu(argv[1], argv[2]);

    casu.run();

    return 0;
}
