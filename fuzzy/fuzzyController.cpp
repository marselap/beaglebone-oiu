/*
 * variable.cpp
 *
 *  Created on: Mar 31, 2018
 *      Author: marselap
 */

#include "fuzzyController.h"

using namespace std;

    FuzzyController::FuzzyController() {

    }

    FuzzyController::~FuzzyController() {
    }

    void FuzzyController::FuzzyControllerInit(int inputVarNo, int outputVarNo, string variant, string tnorm, string implication, string aggregation, string defuzz) {
        this->inputVarNo = inputVarNo;
        this->outputVarNo = outputVarNo;
        this->variant = variant;
        this->tnorm = tnorm;
        this->implication = implication;
        this->defuzz = defuzz;
        if (!this->defuzz.compare("COA")) {
            this->aggregation = aggregation;
        }
        this->ruleTable.clear();
        FuzzyVar initInput;
        FuzzyOutput initOutput;
        for(int i = 0; i < inputVarNo; i++)
            this->inputVar.push_back(initInput);
        for(int i = 0; i < outputVarNo; i++)
            this->outputVar.push_back(initOutput);
    }

    void FuzzyController::BuildTable(vector<vector<string> > table){
        this->ruleTable = table;
    }

    vector<vector<string> > FuzzyController::GetRuleTable() {
        return this->ruleTable;
    }

    void FuzzyController::AddRule(vector<string> rule) {
        this->ruleTable.push_back(rule);
    }

    bool FuzzyController::RemoveRule(vector<string> rule) {

        int i = 0;
        bool found = false;
        while (!found && (i < ruleTable.size())) {
            if (!(this->ruleTable.at(i)==rule)) {
                i++;
            }
            else {
                found = true;
                this->ruleTable.erase(this->ruleTable.begin() + i);
                return found;
            }
        }
        return found;
    }

    vector<map<string, double> > FuzzyController::CalculateInputMFs(vector<float> inputs) {
        vector<map<string, double> > mfMapVector;
        map<string, double> mfMap;
        for (int i = 0; i < inputVarNo; i++) {
            FuzzyVar temp;
            temp = this->inputVar.at(i);
            for (int iMfs = 0; iMfs < temp.mfsNames.size(); iMfs++) {
                mfMap[temp.mfsNames.at(iMfs)] = temp.CheckMembership(temp.mfsNames.at(iMfs), inputs.at(i));
            }
            mfMapVector.push_back(mfMap);
            mfMap.clear();
        }
        return mfMapVector;
    }

    float FuzzyController::TnormInputs(float *mfs) {
        float result = 0.0;
        if (!(this->tnorm.compare("min"))) {
            result = mfs[0];
            for (int i = 0; i < this->inputVarNo; i++){
                if (mfs[i] < result) {
                    result = mfs[i];
                }
            }
        }
        if (!(this->tnorm.compare("product"))) {
            result = 1.0;
            for (int i = 0; i < this->inputVarNo; i++){
                result *= mfs[i];
            }
        }
        return result;
    }

    float FuzzyController::Defuzzification(vector<float> input, vector<float> output){
        float temp_num, temp_den;
        temp_num = 0;
        temp_den = 0;

        if (!(this->defuzz.compare("COA"))) {
            //aggregation...
        }
        if (!(this->defuzz.compare("COG"))) {
            for (int i = 0; i < output.size(); i++) {
                temp_num += output.at(i) * input.at(i);
                temp_den += input.at(i);
            }
            return temp_num/temp_den;
        }

    }


    vector<float> FuzzyController::CalculateOutputVariantA(vector<float> inputs) {
        vector<float> result;
        if (!(inputs.size() == inputVarNo)) {
            result.push_back(0.0);
            result.push_back(0.0);
            return result;
        }

        vector<map<string, double> > mfMapVector;
        mfMapVector = CalculateInputMFs(inputs);

        vector<string> rule;
        double numdenResult[2] = {0,0};
        vector<float> inputSideVector;
        vector<float> outputSideVector;

        for (int iRule = 0; iRule < this->ruleTable.size(); iRule++) {
            rule = this->ruleTable.at(iRule);

            float mfValueInput[inputVarNo];
            for (int iVar = 0; iVar < inputVarNo; iVar++) {
                mfValueInput[iVar] = mfMapVector.at(iVar)[rule.at(iVar)];
            }
            float input_side;
            input_side = TnormInputs(mfValueInput);
            //cout << input_side << endl;
            float output_side;
            output_side = this->outputVar.at(0).GetSingletoneByName(rule.at(inputVarNo));
            //cout << rule.at(inputVarNo) << " " << output_side << endl;

            inputSideVector.push_back(input_side);
            outputSideVector.push_back(output_side);
            //singletoni - implikacija nema smisla - input side na coa/cog sa singletonima;
            //trokutaste mfs - implikacija input side i mf aktiviranog outputa -> vektor vrijednosti
        }

        float temp_result;
        temp_result = Defuzzification(inputSideVector, outputSideVector);

        cout << "e " << inputs.at(0) << " de " << inputs.at(1) << endl;
        for (int i = 0; i < inputSideVector.size(); i++) {
            if (inputSideVector.at(i)    > 0) {
                cout << "mfs " << this->ruleTable.at(i).at(0) << " " << this->ruleTable.at(i).at(1) << endl;
            }
        }

        result.push_back(1.0);
        result.push_back(temp_result);
        return result;
    }
