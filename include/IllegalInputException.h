#ifndef ILLEGALINPUTEXCEPTION_H
#define ILLEGALINPUTEXCEPTION_H

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <windows.h>
#include <exception>
#include <limits>
#include <algorithm> // for using transform
#include <cctype> // for using toupper

//exception class to handle illegal inputs
class IllegalInputException : public std::exception
{
    public:
        IllegalInputException() noexcept = default;
        ~IllegalInputException() = default;

        virtual const char* what() const noexcept {
            return "ERROR: ";
        }

        void clearInput();
        void setConsoleColor(WORD c);
        void errorCatch(std::string message);
        void coloredMessage(WORD c, std::string message);
        void resetColorAndPause();

};

#endif // ILLEGALINPUTEXCEPTION_H
