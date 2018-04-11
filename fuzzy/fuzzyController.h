/*! \file i2cDevice.h
 * \brief Definition of I2CDevice class.
 */

#ifndef FuzzyController_H
#define FuzzyController_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include <map>

#include "variable.h"
#include "fuzzyOutput.h"

/*! \brief Implements triangular membership function
 *
 * Defines membership function by left and right edges and maximum point
 * calculates membership fcn value for given input
 */

using namespace std;

class FuzzyController {

    public:

        /*! \brief
         * Constructor.
         *
         * Initializes dummy Controller variable
         */
        FuzzyController();

        void FuzzyControllerInit(int inputVarNo, int outputVarNo, string variant, string tnorm, string implication, string aggregation, string defuzz);

        /*! Destructor.
         */
        ~FuzzyController();

        void BuildTable(vector<vector<string> > table);
        vector<vector<string> > GetRuleTable();

        void AddRule(vector<string> rule);

        bool RemoveRule(vector<string> rule);

        vector<map<string, double> > CalculateInputMFs(vector<float> inputs);

        vector<float> CalculateOutputVariantA(vector<float> inputs);

        float TnormInputs(float *mfs);

        float Defuzzification(vector<float> input, vector<float> output);

        string variant, tnorm, implication, aggregation, defuzz;
        int inputVarNo, outputVarNo;
        vector<vector<string> > ruleTable;

        vector<FuzzyVar> inputVar;
        vector<FuzzyOutput> outputVar;
    };

#endif /* FuzzyController_H */
