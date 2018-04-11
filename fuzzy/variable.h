/*! \file i2cDevice.h
 * \brief Definition of I2CDevice class.
 */

#ifndef MFS_H
#define MFS_H

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

//namespace Fuzzy {
using namespace std;

    class FuzzyVar {

    public:

        /*! \brief
         * Constructor.
         *
         * Initializes dummy MF
         * Assumes left < maximum < right !!
         */
        explicit FuzzyVar();

        /*! Destructor.
         */
        virtual ~FuzzyVar();

        void AddMF(std::string name, double left, double maximum, double right);

        float GetMembership(vector<double> mf, double input);
        float CheckMembership(std::string name, double input);

        void PrintMF(string name);
        vector<double> GetMF(string name);

        int noMFs;

        vector<vector<double> > mfsVector;
        vector<string> mfsNames;

    };
//}
#endif /* MFS_H */
