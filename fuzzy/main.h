/*! \file  main.h
    \brief include libraries for fuzzy controller test.
 */

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <yaml-cpp/yaml.h>

#include "fuzzyController.h"


using namespace std;

    void setInputMFs(YAML::Node fzy);
    void setOutputMFs(YAML::Node fzy);
    void buildTable(YAML::Node fzy);

    int inputVars, outputVars;
    string variant, tnorm, implication, defuzzification, aggregation;
    string emfs, demfs, ddemfs;

    FuzzyController fuzzyCtrl;
