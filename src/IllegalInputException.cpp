#include "IllegalInputException.h"

/*
IllegalInputException::IllegalInputException(){
}
IllegalInputException::~IllegalInputException() {
}
*/

void IllegalInputException::clearInput() {// clears input stream after illegal inputs are entered
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void IllegalInputException::setConsoleColor(WORD c){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void IllegalInputException::errorCatch(std::string message) {
    setConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
    std::cerr << std::setw(5) << std::right << "<" << what() << " " << message << " Try Again.>" << std::endl;
    setConsoleColor(7);
}

void IllegalInputException::coloredMessage(WORD c, std::string message) {
    setConsoleColor(c);
    std::cout << message;
    resetColorAndPause();
}

void IllegalInputException::resetColorAndPause() {
    setConsoleColor(7);
    system("pause");
}
