#ifndef GRADING_H
#define GRADING_H

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

class Grading
{
    public:
        Grading();
        void display() const;
        virtual ~Grading();

    private:
};

#endif // GRADING_H
