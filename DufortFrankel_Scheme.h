/*  Computational Methods Assignment
    @author :       John Hoarau, Clémence-Philomène Hinot
    @date :         16/10/2025
    @file :         DufortFrankel_Scheme.h
    @description:   ...
*/

/****** Prevention for mulitple definition ******/
#ifndef DUFORTFRANKEL_SCHEME_H
#define DUFORTFRANKEL_SCHEME_H

/****** Libraries and other inclusions ******/
#include "Scheme.h"
#include <iostream>
using namespace std;

/****** Declaration of class DufortFrankel_Scheme ******/

class DufortFrankel_Scheme : public Scheme
{
    private:
        // TO DO if it's necessary
    public:
        // default class constructor
        DufortFrankel_Scheme();

        // class constructor with parameter
        DufortFrankel_Scheme(double param); // TO DO

        // methods
        // TO DO
};

/****** End of the prevention for mulitple definition ******/
#endif