/*  Computational Methods Assignment
    @author :       Clémence-Philomène Hinot
    @date :         16/10/2025
    @file :         ProblemDefinition.cpp
    @description:   ...
*/

/******* Inclusion of classes ******/
#include "ProblemDefinition.h"

/****** Libraries and other inclusions ******/
#include <cmath>
#define M_PI 3.141592653589793
#include <vector>
using namespace std;

/****** Methods for class ProblemDefinition ******/

// default class contructor
ProblemDefinition::ProblemDefinition()
{
    // coordinates
    this->dx = 0.0;
    // time
    this->tMax = 0.0;
    this->dt = 0.0;
    // grid space
    this->N = 0;
    // temperatures
    this->Tin = 0.0;
    this->Tsur = 0.0;
    // wall
    this->thickness = 0.0;
    // material
    this->D = 0.0;
}

// class constructor with parameters
ProblemDefinition::ProblemDefinition(double thickness, double dx, double tMax, double dt, int N, double Tin, double Tsur, double D)
{
    // coordinates
    this->dx = dx;
    // time
    this->tMax = tMax;
    this->dt = dt;
    // grid space
    this->N = N;
    // temperatures
    this->Tin = Tin;
    this->Tsur = Tsur;
    // wall
    this->thickness = thickness;
    // material
    this->D = D;
}

// methods to get attributes
double ProblemDefinition::Get_dx() const
{
    return this->dx;
}

double ProblemDefinition::Get_tMax() const
{
    return this->tMax;
}

double ProblemDefinition::Get_dt() const
{
    return this->dt;
}

int ProblemDefinition::Get_N() const
{
    return this->N;
}

double ProblemDefinition::Get_Tin() const
{
    return this->Tin;
}

double ProblemDefinition::Get_Tsur() const
{
    return this->Tsur;
}

double ProblemDefinition::Get_thickness() const
{
    return this->thickness;
}

double ProblemDefinition::Get_D() const
{
    return this->D;
}

// methods to set attributes
void ProblemDefinition::Set_dx(double value)
{
    this->dx = value;
}

void ProblemDefinition::Set_tMax(double value)
{
    this->tMax = value;
}

void ProblemDefinition::Set_dt(double value)
{
    this->dt = value;
}

void ProblemDefinition::Set_N(int value)
{
    this->N = value;
}

void ProblemDefinition::Set_Tin(double value)
{
    this->Tin = value;
}

void ProblemDefinition::Set_Tsur(double value)
{
    this->Tsur = value;
}

void ProblemDefinition::Set_thickness(double value)
{
    this->thickness = value;
}

void ProblemDefinition::Set_D(double value)
{
    this->D = value;
}

// method for the analytic solution
vector<vector<double>> ProblemDefinition::ProblemDefinition::Analytic_Solution()
{
    // size of the vector result
    int size_x = static_cast<int>(Get_thickness() / Get_dx()) + 1;  // +1 to include endpoint
    int size_t = static_cast<int>(Get_tMax() / Get_dt()) + 1;       // +1 to include endpoint
    
    // vector for the storage of the result
    vector<vector<double>> analytic_result(size_x, vector<double>(size_t, 0.0));

    // initialisation of variables
    double x = 0.0;
    double t = 0.0;
    double sum = 0.0;

    // first loop to store the result for each x position
    for (int i=0; i<size_x; i++) {
        t = 0.0; // initialisation of the t

        // second loop to calculte the sum for each t
        for (int j=0; j<size_t; j++) {
            sum = 0.0; // initialisation of the sum

            // third loop to calculate the sum
            for (int k=1; k<=Get_N(); k++) {
                sum += exp(- Get_D() * pow((k*M_PI / Get_thickness()), 2) * t) * ((1-pow(-1, k))/(k*M_PI)) * sin(k*M_PI*x/Get_thickness());
            }

            analytic_result[i][j] = Get_Tsur() + 2 * (Get_Tin() - Get_Tsur()) * sum;

            t += Get_dt(); // increment the time
        }

        x += Get_dx(); // increment the position
    }

    return analytic_result;
}