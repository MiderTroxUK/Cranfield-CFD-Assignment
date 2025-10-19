/*  Computational Methods Assignment
    @author :       John Hoarau, Clémence-Philomène Hinot
    @date :         16/10/2025
    @file :         Output.cpp
    @description:   ...
*/

/******* Inclusion of classes ******/
#include "Output.h"

/****** Libraries and other inclusions ******/
#include <string>
using namespace std;

/****** Methods for class ProblemDefinition ******/

// default class contructor
Output::Output()
{
    this->filename = "";
}

// class constructor with parameters
Output::Output(string filename)
{
    this->filename = filename;
}

// methods to get attributes
string Output::Get_filename() const
{
    return this->filename;
}

// methods to set attributes
void Output::Set_filename(string value_filename)
{
    this->filename = filename;
}

// method to generate an output file
void Output::Generate_File(string filename)
{
    // TO DO
}