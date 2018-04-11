/*
 * variable.cpp
 *
 *  Created on: Mar 31, 2018
 *      Author: marselap
 */

#include "variable.h"

using namespace std;

//namespace Fuzzy {

    FuzzyVar::FuzzyVar() {
        this->noMFs = 0;
    }

    FuzzyVar::~FuzzyVar() {
    }

    void FuzzyVar::AddMF(string name, double left, double maximum, double right) {
        vector<double> mf;
        mf.push_back(left);
        mf.push_back(maximum);
        mf.push_back(right);

        this->mfsVector.push_back(mf);
        this->mfsNames.push_back(name);
        this->noMFs += 1;
    }

    float FuzzyVar::GetMembership(vector<double> mf, double input) {
        double left = mf.at(0);
        double maximum = mf.at(1);
        double right = mf.at(2);
        if ((input > left) and (input < maximum))
            return (input - left) / (maximum - left);
        if ((input >= maximum) and (input < right))
            return (right - input) / (right - maximum);
        return 0;
    }

    float FuzzyVar::CheckMembership(string name, double input) {

        for(int i = 0; i < this->mfsVector.size(); i++) {
            if (!this->mfsNames.at(i).compare(name)) {
                vector<double> found_mf;
                found_mf = this->mfsVector.at(i);
                return GetMembership(found_mf, input);
            }
        }

        return -1;
    }

    void FuzzyVar::PrintMF(string name) {
        for(int i = 0; i < this->mfsVector.size(); i++) {
            if (!this->mfsNames.at(i).compare(name)) {
                vector<double> temp = this->mfsVector.at(i);
                cout << "name: " << name << "; mf : ";
                for(int j=0; j<temp.size(); cout << temp[j++] << " ");
                cout << endl;
            }
        }

    }

    vector<double> FuzzyVar::GetMF(string name) {
        for(int i = 0; i < this->mfsVector.size(); i++) {
            if (!this->mfsNames.at(i).compare(name)) {
                return this->mfsVector.at(i);
            }
        }
        return vector<double>();
    }


//}
