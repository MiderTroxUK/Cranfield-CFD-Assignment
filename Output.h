/*  Computational Methods Assignment
    @author :       John Hoarau, Clémence-Philomène Hinot
    @date :         16/10/2025
    @file :         Output.h
    @description:   ...
*/

/****** Libraries and other inclusions ******/
#include <iostream>

/****** Declaration of class Output ******/
class Output
{
    private:
        string filename;

    public:
        // default class contructor
        Output();

        // class constructor with parameters
        Output(string filename);

        // methods to get attributes
        string Get_filename() const;

        // methods to set attributes
        void Set_filename(string value_filename);

        // method to generate an output file
        void Generate_File(string filename);
};