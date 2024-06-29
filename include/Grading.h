#ifndef GRADING_H
#define GRADING_H

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <windows.h>

#include "IllegalInputException.h"

class Grading
{
    public:
        // constructor
        Grading();

        bool openFile();
        void display();

        // deconstructor
        virtual ~Grading();

    private:
        std::ifstream inGradeTable;
        IllegalInputException illegal;
};

#endif // GRADING_H
