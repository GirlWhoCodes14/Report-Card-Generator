#include "IllegalInputException.h"

//IllegalInputException::IllegalInputException()
//{
//    //ctor
//}
//
//IllegalInputException::~IllegalInputException()
//{
//    //dtor
//}
//
//virtual const char* IllegalInputException::what() const noexcept {
//    return "\n\nERROR: Invalid input. Please Try Again.\n";
//}

 void IllegalInputException::clearInput() {// clears input stream after illegal inputs are entered
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
 }
