/*  Computational Methods Assignment
    @author :       John Hoarau, Clémence-Philomène Hinot
    @date :         16/10/2025
    @file :         Scheme.h
*/

/****** Prevention for mulitple definition ******/
#ifndef SCHEME_H
#define SCHEME_H

/****** Libraries and other inclusions ******/
#include <iostream>
using namespace std;

/****** Declaration of class Scheme ******/
/**
 * @class Scheme
 * @brief Base class for numerical schemes.
 * 
 * This class serves as a parent class for all specific numerical schemes (e.g., Dufort-Frankel, Richardson, Laasonen, Crank-Nicholson).
 * It holds common parameters like grid spacing, time step, and material properties.
 */
class Scheme
{
    private:
        double dx;      ///< Spatial grid spacing (cm)
        int N;          ///< Fourier Number
        double dt;      ///< Time step size (h)
        double D;       ///< Thermal diffusivity (cm^2/h)
        double r;       ///< CFL number (Courant-Friedrichs-Lewy condition)

    public:
        /**
         * @brief Default constructor.
         */
        Scheme();
        
        /**
         * @brief Parameterized constructor.
         * @param dx Spatial grid spacing (cm)
         * @param N Fourier Number
         * @param dt Time step size (h)
         * @param D Thermal diffusivity (cm^2/h)
         */
        Scheme(double dx, int N, double dt, double D);

        // Getters
        double Get_dx() const;      ///< Get spatial grid spacing
        int Get_N() const;          ///< Get Fourier Number
        double Get_dt() const;      ///< Get time step size
        double Get_D() const;       ///< Get thermal diffusivity

        // Setters
        void Set_dx(double value);  ///< Set spatial grid spacing
        void Set_N(int value);      ///< Set Fourier Number
        void Set_dt(double value);  ///< Set time step size
        void Set_D(double value);   ///< Set thermal diffusivity

        /**
         * @brief Calculates and returns the CFL number.
         * @return The CFL number (r = D * dt / dx^2).
         */
        double Get_CFL();
};

/****** End of the prevention for mulitple definition ******/
#endif