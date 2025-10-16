/*  Computational Methods Assignment
    @author :       John Hoarau, Clémence-Philomène Hinot
    @date :         16/10/2025
    @file :         Verification.cpp
    @description:   ...
*/

/******* Inclusion of classes ******/
#include "Verification.h"

/****** Libraries and other inclusions ******/
#include <cmath>
#include <vector>
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
bool Verification::Verify_Stability(double CFL)
{
    // TO DO
    bool result;
    return result;
}

double Verification::Calculation_Norm(vector<double>)
{
    // TO DO
    double norm;
    return norm;
}