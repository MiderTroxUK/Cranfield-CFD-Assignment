/*  Computational Methods Assignment
    @author :       John Hoarau, Github copilot
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
// methods to do the verifications
bool Verification::Verify_Stability(double error, double tolerance)
{
    // Check for NaN or Infinity (Explosion)
    if (std::isnan(error) || std::isinf(error)) {
        return false;
    }
    
    // Check against tolerance
    if (error > tolerance) {
        return false;
    }

    // Otherwise, stable
    return true;
}

double Verification::Calculation_L2_Norm(const vector<double>& numerical, const vector<double>& analytical, double dx)
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

    // Correct L2 Norm definition: sqrt( integral |u|^2 dx ) approx sqrt( sum * dx )
    return sqrt(sum_sq_diff * dx);
}

double Verification::Calculation_Relative_Error(const vector<double>& numerical, const vector<double>& analytical, double dx)
{
    // Calculate Absolute L2 Eror (Numerator)
    double abs_error = Calculation_L2_Norm(numerical, analytical, dx);
    if (abs_error < 0) return -1.0; // Error in calculation

    // Calculate L2 Norm of Analytical Solution (Denominator)
    // We pass a zero vector as the "second" vector to calculate the norm of 'analytical' directly
    // Or just re-implement the sum squares for 'analytical'
    
    double sum_sq_ana = 0.0;
    // size_t n = analytical.size(); // Unused
    for (double val : analytical) {
        sum_sq_ana += val * val;
    }
    double ana_norm = sqrt(sum_sq_ana * dx);

    if (ana_norm == 0.0) {
        cerr << "Error: Analytical solution norm is zero, cannot calculate relative error." << endl;
        return -1.0;
    }

    return abs_error / ana_norm;
}