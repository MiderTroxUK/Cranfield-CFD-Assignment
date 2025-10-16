/*  Computational Methods Assignment
    @author :       John Hoarau, Clémence-Philomène Hinot
    @date :         16/10/2025
    @file :         Scheme.cpp
    @description:   ...
*/

/******* Inclusion of classes ******/
#include "Scheme.h"

/****** Libraries and other inclusions ******/
using namespace std;

/****** Methods for class ProblemDefinition ******/

// default class contructor
Scheme::Scheme()
{
    this->dx = 0.0;
    this->N = 0;
    this->dt = 0.0;
    this->D = 0.0;
}

// class constructor with parameters
Scheme::Scheme(double dx, int N, double dt, double D)
{
    this->dx = dx;
    this->N = N;
    this->dt = dt;
    this->D = D;
}

// methods to get attributes
double Scheme::Get_dx() const 
{
    return this->dx;
}

int Scheme::Get_N() const
{
    return this->N;
}

double Scheme::Get_dt() const
{
    return this-> dt;
}

double Scheme::Get_D() const
{
    return this->D;
}

// methods to set attributes
void Scheme::Set_dx(double value)
{
    this->dx = value;
}

void Scheme::Set_N(int value)
{
    this->N = value;
}

void Scheme::Set_dt(double value)
{
    this->dt = value;
}

void Scheme::Set_D(double value)
{
    this->D = value;
}