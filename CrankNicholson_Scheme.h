/*  Computational Methods Assignment
    @author :       John Hoarau, Clémence-Philomène Hinot
    @date :         16/10/2025
    @file :         CrankNicholson_Scheme.h
    @description:   ...
*/

/****** Prevention for mulitple definition ******/
#ifndef CRANKNICHOLSON_SCHEME_H
#define CRANKNICHOLSON_SCHEME_H

/****** Libraries and other inclusions ******/
#include "Scheme.h"
#include <iostream>
using namespace std;

/****** Declaration of class CrankNicholson_Scheme ******/

class CrankNicholson_Scheme : public Scheme
{
    private:
        // TO DO if it's necessary
    public:
        // default class constructor
        CrankNicholson_Scheme();

        // class constructor with parameter
        CrankNicholson_Scheme(double param); // TO DO

        // methods
        // TO DO
};

/****** End of the prevention for mulitple definition ******/
#endif