/*! \file  mainApp.cpp
    \brief Example of CASU_Interface class usage.
 */


#include "main.h"

using namespace std;

/*! \brief Main function for fuzzy controller test.
 *
 *  An .fzy file *MUST* be provided as the only argument when invoking the program:
 *
 *  main <controller_config>.fzy
 *
 */

int main(int argc, char **argv) {

    if (argc < 2)
    {
        cout << "Please provide the .fzy file name as the program argument." << endl;
        exit(1);
    }

    char *fzy_file = argv[1];
    YAML::Node fzy = YAML::LoadFile(fzy_file);

    inputVars = fzy["input_vars"].as<int>();
    outputVars = fzy["output_vars"].as<int>();
    variant = fzy["variant"].as<string>();
    tnorm = fzy["tnorm"].as<string>();
    implication = fzy["implication"].as<string>();
    defuzzification = fzy["defuzzification"].as<string>();
    aggregation = fzy["aggregation"].as<string>();


    fuzzyCtrl.FuzzyControllerInit(inputVars, outputVars, variant, tnorm, implication, aggregation, defuzzification);

    setInputMFs(fzy);
    setOutputMFs(fzy);

    buildTable(fzy);

    vector<float> inputs;
    inputs.push_back(0.4);
    inputs.push_back(-0.6);

    fuzzyCtrl.CalculateOutputVariantA(inputs);
    return 0;
}

void setInputMFs(YAML::Node fzy) {

    vector<string> cfgFileTags;
    cfgFileTags.push_back("inputVar1MFS");
    cfgFileTags.push_back("inputVar2MFS");
    cfgFileTags.push_back("inputVar3MFS");

    for (int i = 0; i < inputVars; i++) {
        YAML::Node _mfs = fzy[cfgFileTags.at(i)];
        for (YAML::iterator it = _mfs.begin(); it != _mfs.end(); ++it) {
            const YAML::Node& mf = *it;
            string name = mf["name"].as<string>();
            double left = mf["left"].as<double>();
            double maximum = mf["maximum"].as<double>();
            double right = mf["right"].as<double>();
            fuzzyCtrl.inputVar.at(i).AddMF(name, left, maximum, right);
        }
    }
}


void setOutputMFs(YAML::Node fzy) {

    vector<string> cfgFileTags;
    cfgFileTags.push_back("outputVar1MFS");
    cfgFileTags.push_back("outputVar2MFS");
    cfgFileTags.push_back("outputVar3MFS");

    for (int i = 0; i < outputVars; i++) {
        YAML::Node _mfs = fzy[cfgFileTags.at(i)];
        for (YAML::iterator it = _mfs.begin(); it != _mfs.end(); ++it) {
            const YAML::Node& mf = *it;
            string name = mf["name"].as<string>();
            double value = mf["value"].as<double>();
            fuzzyCtrl.outputVar.at(i).AddMF(name, value);
            //fuzzyCtrl.ufc1.AddMF(name, value);
        }
    }
}

void buildTable(YAML::Node fzy) {

    if (!variant.compare("A")) {
        int rule_size = inputVars + outputVars;
        vector<string> oneRuleVector;
        vector<vector<string> > table;
        YAML::Node _mfs = fzy["table1"];
        int rulesNo = _mfs.size();
        for (YAML::iterator it = _mfs.begin(); it != _mfs.end(); ++it) {
            const YAML::Node& mf = *it;
            const YAML::Node& rule = mf["rule"];
            for (int i = 0; i < inputVars; i++) {
                oneRuleVector.push_back(rule[i].as<string>());
            }
            for (int i = inputVars; i < inputVars+outputVars; i++) {
                oneRuleVector.push_back(rule[i].as<string>());
            }
            table.push_back(oneRuleVector);
            oneRuleVector.clear();
        }
        fuzzyCtrl.BuildTable(table);
    }
}
