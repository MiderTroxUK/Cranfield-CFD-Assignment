/*  Computational Methods Assignment
    @author :       John Hoarau, Clémence-Philomène Hinot
    @date :         16/10/2025
    @file :         ProblemDefinition.cpp
    @description:   ...
*/

/******* Inclusion of classes ******/
#include "ProblemDefinition.h"

/****** Libraries and other inclusions ******/
#include <cmath>
#include <vector>
using namespace std;

/****** Methods for class ProblemDefinition ******/

// default class contructor
ProblemDefinition::ProblemDefinition()
{
    // coordinates
    this->xMin = 0.0;
    this->xMax = 0.0;
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
ProblemDefinition::ProblemDefinition(double xMin, double xMax, double dx, double tMax, double dt, int N, double Tin, double Tsur, double thickness, double D)
{
    // coordinates
    this->xMin += xMin;
    this->xMax += xMax;
    this->dx += dx;
    // time
    this->tMax += tMax;
    this->dt += dt;
    // grid space
    this->N += N;
    // temperatures
    this->Tin += Tin;
    this->Tsur += Tsur;
    // wall
    this->thickness += thickness;
    // material
    this->D += D;
}

// methods to get attributes
double ProblemDefinition::Get_xMin() const
{
    return this->xMin;
}

double ProblemDefinition::Get_xMax() const
{
    return this->xMax;
}

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
void ProblemDefinition::Set_xMin(double value)
{
    this->xMin = value;
}

void ProblemDefinition::Set_xMax(double value)
{
    this->xMax = value;
}

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
vector<double> ProblemDefinition::ProblemDefinition::Analytic_Solution(double dx, int N, double tMax, double dt, double Tin, double Tsur, double thickness, double D)
{
    // TO DO
    vector<double> result;
    return result;
}