/*
 * variable.cpp
 *
 *  Created on: Mar 31, 2018
 *      Author: marselap
 */

#include "fuzzyOutput.h"

using namespace std;

FuzzyOutput::FuzzyOutput() {
    this->noMFs = 0;
}

FuzzyOutput::~FuzzyOutput() {
}

void FuzzyOutput::AddMF(string name, double singletone) {
    this->singletones.push_back(singletone);
    this->names.push_back(name);
    this->noMFs += 1;
}

float FuzzyOutput::GetSingletone(int iter) {
    return this->singletones.at(iter-1);
}

float FuzzyOutput::GetSingletoneByName(string name) {
    for (int i = 0; i < this->names.size(); i++) {
        if (!this->names.at(i).compare(name)) {
            return this->singletones.at(i);
        }
    }
    return -1;
}
