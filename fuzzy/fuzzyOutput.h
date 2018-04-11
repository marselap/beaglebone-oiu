/*! \file i2cDevice.h
 * \brief Definition of I2CDevice class.
 */

#ifndef FuzzyOutput_H
#define FuzzyOutput_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <unistd.h>
#include <iostream>
#include <fcntl.h>

/*! \brief Implements triangular membership function
 *
 * Defines membership function by left and right edges and maximum point
 * calculates membership fcn value for given input
 */

using namespace std;

class FuzzyOutput {

    public:

        /*! \brief
         * Constructor.
         *
         * Initializes dummy output variable
         */
        FuzzyOutput();

        /*! Destructor.
         */
        ~FuzzyOutput();

        void AddMF(string name, double singletone);
        float GetSingletone(int iter);
        float GetSingletoneByName(string name);

        int noMFs;
        vector<double> singletones;
        vector<string> names;

    };

#endif /* FuzzyOutput_H */
