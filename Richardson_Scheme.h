/*  Computational Methods Assignment
    @author :       John Hoarau, Clémence-Philomène Hinot
    @date :         16/10/2025
    @file :         Richardson_Scheme.h
    @description:   ...
*/

/****** Prevention for mulitple definition ******/
#ifndef RICHARDSON_SCHEME_H
#define RICHARDSON_SCHEME_H

/****** Libraries and other inclusions ******/
#include "Scheme.h"
#include <iostream>
using namespace std;

/****** Declaration of class Richardson_Scheme ******/

class Richardson_Scheme : public Scheme
{
    private:
        // TO DO if it's necessary
    public:
        // default class constructor
        Richardson_Scheme();

        // class constructor with parameter
        Richardson_Scheme(double param); // TO DO

        // methods
        // TO DO
};

/****** End of the prevention for mulitple definition ******/
#endif