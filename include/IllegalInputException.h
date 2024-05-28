#ifndef ILLEGALINPUTEXCEPTION_H
#define ILLEGALINPUTEXCEPTION_H

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

#include <exception>
#include <limits>

//exception class to handle illegal inputs
class IllegalInputException : public std::exception
{
    public:
        IllegalInputException() noexcept = default;
        ~IllegalInputException() = default;
        virtual const char* what() const noexcept {
            return "\n\nERROR: Invalid input. Please Try Again.\n";
        }

        void clearInput();
};

#endif // ILLEGALINPUTEXCEPTION_H
