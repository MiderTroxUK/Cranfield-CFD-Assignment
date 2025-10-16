/*  Computational Methods Assignment
    @author :       John Hoarau, Clémence-Philomène Hinot
    @date :         16/10/2025
    @file :         Scheme.h
    @description:   ...
*/

/****** Libraries and other inclusions ******/
#include <iostream>

/****** Declaration of class Scheme ******/
class Scheme
{
    private:
        // grid spacing
        double dx;
        int N;
        // time
        double dt;
        // material
        double D;

    public:
        // default class contructor
        Scheme();
        
        // class constructor with parameters
        Scheme(double dx, int N, double dt, double D);

        // methods to get attributes
        double Get_dx() const;
        int Get_N() const;
        double Get_dt() const;
        double Get_D() const;

        // methods to set attributes
        void Set_dx(double value);
        void Set_N(int value);
        void Set_dt(double value);
        void Set_D(double value);
};