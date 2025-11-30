/*  Computational Methods Assignment
    @author :       John Hoarau, Clémence-Philomène Hinot
    @date :         16/10/2025
    @file :         Verification.cpp
    @description:   This class provides methods for verifying numerical results and conditions.
*/

/******* Inclusion of classes ******/
#include "Verification.h"

/****** Libraries and other inclusions ******/
#include <cmath>
#include <vector>
#include <iostream> // Added for cout and cerr
#include <string>   // Added for string type
using namespace std;

/****** Methods for class Verification ******/

// default class constructor
Verification::Verification()
{
    this->CFL = 0.0;
}

// class constructor with parameters
Verification::Verification(double CFL)
{
    this->CFL = CFL;
}

// method to get attributes
double Verification::Get_CFL() const
{
    return this->CFL;
}

// method to set attributes
void Verification::Set_CFL(double value)
{
    this->CFL = value;
}

// methods to do the verifications
bool Verification::Verify_Stability(double CFL, string schemeName)
{
    if (schemeName == "Richardson") {
        cout << "Richardson scheme is unconditionally unstable." << endl;
        return false;
    } else if (schemeName == "Laasonen" || schemeName == "CrankNicholson" || schemeName == "DufortFrankel") {
        cout << schemeName << " scheme is unconditionally stable." << endl;
        return true;
    } else if (schemeName == "Explicit") {
        if (CFL <= 0.5) return true;
        else return false;
    }
    return true;
}

double Verification::Calculation_Norm(const vector<double>& numerical, const vector<double>& analytical)
{
    double sum_sq_diff = 0.0;
    int n = numerical.size();
    
    if (n != analytical.size()) {
        cerr << "Error: Vector sizes do not match for Norm calculation." << endl;
        return -1.0;
    }

    for (int i = 0; i < n; ++i) {
        double diff = numerical[i] - analytical[i];
        sum_sq_diff += diff * diff;
    }

    return sqrt(sum_sq_diff / n);
}