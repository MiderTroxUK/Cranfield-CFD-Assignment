/*  Computational Methods Assignment
    @author :       John Hoarau, Clémence-Philomène Hinot
    @date :         16/10/2025
    @file :         ProblemDefinition.h
    @description:   ...
*/

/****** Libraries and other inclusions ******/
#include <iostream>
#include <vector>

/****** Declaration of class ProblemDefinition ******/
class ProblemDefinition
{
    private:
        // coordinates
        double xMin;
        double xMax;
        double dx;
        // time
        double tMax;
        double dt;
        // grid space
        int N;
        // temperatures
        double Tin;
        double Tsur;
        // wall
        double thickness;
        // material
        double D;
    
    public:
        // default class contructor
        ProblemDefinition();
        
        // class constructor with parameters
        ProblemDefinition(double xMin, double xMax, double dx, double tMax, double dt, int N, double Tin, double Tsur, double thickness, double D);

        // methods to get attributes
        double Get_xMin() const;
        double Get_xMax() const;
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
        void Set_xMax(double value);
        void Set_dx(double value);
        void Set_tMax(double value);
        void Set_dt(double value);
        void Set_N(int value);
        void Set_Tin(double value);
        void Set_Tsur(double value);
        void Set_thickness(double value);
        void Set_D(double value);

        // method for the analytic solution
        vector<double> Analytic_Solution(double dx, int N, double tMax, double dt, double Tin, double Tsur, double thickness, double D);
};