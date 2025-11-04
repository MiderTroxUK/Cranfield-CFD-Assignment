/*  Computational Methods Assignment
    @author :       John Hoarau, Clémence-Philomène Hinot
    @date :         16/10/2025
    @file :         ProblemDefinition.h
    @description:   ...
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
        // coordinates
        double xMin = 0.0;
        double dx = 0.0;
        // time
        double tMax = 0.0;
        double dt = 0.0;
        // grid space
        int N = 0;
        // temperatures
        double Tin = 0.0;
        double Tsur = 0.0;
        // wall
        double thickness = 0.0;
        // material
        double D = 0.0;
    
    public:
        // default class contructor
        ProblemDefinition();
        
        // class constructor with parameters
        ProblemDefinition(double xMin, double thickness, double dx, double tMax, double dt, int N, double Tin, double Tsur, double D);

        // methods to get attributes
        double Get_xMin() const;
        double Get_dx() const;
        double Get_tMax() const;
        double Get_dt() const;
        int Get_N() const;
        double Get_Tin() const;
        double Get_Tsur() const;
        double Get_thickness() const;
        double Get_D() const;

        // methods to set attributes
        void Set_xMin(double value);
        void Set_dx(double value);
        void Set_tMax(double value);
        void Set_dt(double value);
        void Set_N(int value);
        void Set_Tin(double value);
        void Set_Tsur(double value);
        void Set_thickness(double value);
        void Set_D(double value);

        // method for the analytic solution
        vector<vector<double>> Analytic_Solution();
};

/****** End of the prevention for mulitple definition ******/
#endif