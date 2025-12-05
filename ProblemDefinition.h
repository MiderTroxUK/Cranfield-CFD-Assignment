/*  Computational Methods Assignment
    @author :       Clémence-Philomène Hinot
    @date :         16/10/2025
    @file :         ProblemDefinition.h
*/

/****** Prevention for mulitple definition ******/
#ifndef PROBLEMDEFINITION_H
#define PROBLEMDEFINITION_H

/****** Libraries and other inclusions ******/
#include <iostream>
#include <vector>
using namespace std;

/****** Declaration of class ProblemDefinition ******/
class ProblemDefinition
{
    private:
    private:
        double dx = 0.0;        ///< Spatial grid spacing [m]
        double tMax = 0.0;      ///< Maximum simulation time [s]
        double dt = 0.0;        ///< Time step size [s]
        int N = 0;              ///< Number of grid points
        double Tin = 0.0;       ///< Initial temperature [K]
        double Tsur = 0.0;      ///< Surface temperature [K]
        double thickness = 0.0; ///< Material thickness [m]
        double D = 0.0;         ///< Thermal diffusivity [m^2/s]
    
    public:
        /**
         * @brief Default constructor.
         * Initializes all parameters to zero.
         */
        ProblemDefinition();
        
        /**
         * @brief Parameterized constructor.
         * @param thickness Material thickness [m]
         * @param dx Spatial grid spacing [m]
         * @param tMax Maximum simulation time [s]
         * @param dt Time step size [s]
         * @param N Number of grid points
         * @param Tin Initial temperature [K]
         * @param Tsur Surface temperature [K]
         * @param D Thermal diffusivity [m^2/s]
         */
        ProblemDefinition(double thickness, double dx, double tMax, double dt, int N, double Tin, double Tsur, double D);

        /** @brief Gets the spatial grid spacing. @return dx [m] */
        double Get_dx() const;
        
        /** @brief Gets the maximum simulation time. @return tMax [s] */
        double Get_tMax() const;
        
        /** @brief Gets the time step size. @return dt [s] */
        double Get_dt() const;
        
        /** @brief Gets the number of grid points. @return N */
        int Get_N() const;
        
        /** @brief Gets the initial temperature. @return Tin [K] */
        double Get_Tin() const;
        
        /** @brief Gets the surface temperature. @return Tsur [K] */
        double Get_Tsur() const;
        
        /** @brief Gets the material thickness. @return thickness [m] */
        double Get_thickness() const;
        
        /** @brief Gets the thermal diffusivity. @return D [m^2/s] */
        double Get_D() const;

        /** @brief Sets the spatial grid spacing. @param value dx [m] */
        void Set_dx(double value);
        
        /** @brief Sets the maximum simulation time. @param value tMax [s] */
        void Set_tMax(double value);
        
        /** @brief Sets the time step size. @param value dt [s] */
        void Set_dt(double value);
        
        /** @brief Sets the number of grid points. @param value N */
        void Set_N(int value);
        
        /** @brief Sets the initial temperature. @param value Tin [K] */
        void Set_Tin(double value);
        
        /** @brief Sets the surface temperature. @param value Tsur [K] */
        void Set_Tsur(double value);
        
        /** @brief Sets the material thickness. @param value thickness [m] */
        void Set_thickness(double value);
        
        /** @brief Sets the thermal diffusivity. @param value D [m^2/s] */
        void Set_D(double value);

        /**
         * @brief Computes the analytic solution for the heat equation.
         * @return A 2D vector representing the temperature distribution over time and space.
         */
        vector<vector<double>> Analytic_Solution();
};

/****** End of the prevention for mulitple definition ******/
#endif