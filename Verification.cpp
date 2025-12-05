/*  Computational Methods Assignment
    @author :       John Hoarau
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
bool Verification::Verify_Stability(double CFL, double L2_Norm, string schemeName)
{
    // Check for NaN or Infinity (Explosion)
    if (std::isnan(L2_Norm) || std::isinf(L2_Norm)) {
        cout << schemeName << " scheme is unconditionally unstable (Solution exploded)." << endl;
        return false;
    }
    
    // Check for large errors (Inconsistency or Instability)
    double errorThreshold = 100.0; // Arbitrary threshold for "acceptable" error
    if (L2_Norm > errorThreshold) {
        cout << schemeName << " scheme is unstable or inconsistent (L2 Norm " << L2_Norm << " > " << errorThreshold << ")." << endl;
        return false;
    }

    // Otherwise, assume stable
    cout << schemeName << " scheme is stable (L2 Norm " << L2_Norm << " within tolerance)." << endl;
    return true;
}

double Verification::Calculation_Norm(const vector<double>& numerical, const vector<double>& analytical)
{
    double sum_sq_diff = 0.0;
    size_t n = numerical.size();
    
    if (n != analytical.size()) {
        cerr << "Error: Vector sizes do not match for Norm calculation." << endl;
        return -1.0;
    }

    for (size_t i = 0; i < n; ++i) {
        double diff = numerical[i] - analytical[i];
        sum_sq_diff += diff * diff;
    }

    return sqrt(sum_sq_diff / n);
}