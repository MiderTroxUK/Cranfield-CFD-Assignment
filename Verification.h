/*  Computational Methods Assignment
    @author :       John Hoarau, Clémence-Philomène Hinot
    @date :         16/10/2025
    @file :         Verification.h
    @description:   ...
*/

/****** Prevention for mulitple definition ******/
#ifndef VERIFICATION_H
#define VERIFICATION_H

/****** Libraries and other inclusions ******/
#include <iostream>
#include <vector>
using namespace std;

/****** Declaration of class Verification ******/
class Verification
{
    private:
        double CFL;
    public:
        // default class constructor
        Verification();

        // class constructor with parameters
        Verification(double CFL);

        // method to get attributes
        double Get_CFL() const;

        // method to set attributes
        void Set_CFL(double value);

        // methods to do the verifications
        bool Verify_Stability(double CFL);
        double Calculation_Norm(vector<double>);
};

/****** End of the prevention for mulitple definition ******/
#endif