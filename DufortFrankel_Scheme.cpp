/*  Computational Methods Assignment
    @author :       John Hoarau, Clémence-Philomène Hinot
    @date :         16/10/2025
    @file :         DufortFrankel_Scheme.cpp
    @description:   ...
*/

/******* Inclusion of classes ******/
#include "DufortFrankel_Scheme.h"

/****** Libraries and other inclusions ******/
#include <cmath>
#include <vector>
using namespace std;

/****** Methods for class DufortFrankel_Scheme ******/

// default class contructor
DufortFrankel_Scheme::DufortFrankel_Scheme()
{
    // TO DO
}

// class constructor with parameters
// to do
DufortFrankel_Scheme::DufortFrankel_Scheme(double dx, double x_max, double dt, double t_max, int N, double D) {
    // CFL number
    double CFL = D * dt/dx;
    
    // statement of x variable
    vector<double> x(N);
    x[0] = 0.0;
    x[N-1] = x_max;
    for (int i=1; i<N-1; i++) {
        x[i] = x[0] + i * dx;
    }

    // statement of functions
    vector<double> fn0(N);
    vector<double> fn1(N);
    fn0[0] = Tin;
    fn0[N-1] = Tsur;
    fn1[0] = Tsur;
    fn1[N-1] = Tsur;
    for (int i=1; i<N-1; i++) {
        
    }

    // calculation of the first steps
    vector<vector<double>> lax = LaxScheme(t_max, dt, N, dx, CFL, fn0, fn1);
    
    // initialiation of vectors 
    vector<double> dufort0(N);
    dufort0 = lax[0];
    vector<double> dufort1(N);
    dufort1 = lax[1];
    vector<double> dufort2(N);

    for (int n=0; n<N; n++) {
        dufort2[n] = (D*2*dt/pow(dx, 2)) * (dufort1[n+1] - dufort0[n] + dufort1[n-1]) + dufort0[n] * (1- (D*2*dt/pow(dx,2)));
    }

    return dufort2;
}

// methods
// TO DO
vector<vector<double>> LaxScheme(double t_max, double dt, double N, double dx, double CFL, vector<double> fn, vector<double> fn1) {
    vector<vector<double>> v(2);
	vector<double> lax0(N);
	vector<double> lax1(N);

	// boundary conditions
	lax0[0] = fn[0];
	lax0[N - 1] = fn[N - 1];
	lax1[0] = fn1[0];
	lax1[N - 1] = fn1[N - 1];

	for (double t = 0.0; t < t_max; t += dt) {
		for (int i = 1; i < N - 1; i++) {
			lax0[i] = 0.5 * (fn[i + 1] + fn[i - 1] - CFL * (fn[i + 1] - fn[i - 1]));
			lax1[i] = 0.5 * (fn1[i + 1] + fn1[i - 1] - CFL * (fn1[i + 1] - fn1[i - 1]));
		}
		fn = lax0;
		fn1 = lax1;
	}

	v[0] = lax0;
	v[1] = lax1;

	return v;
}