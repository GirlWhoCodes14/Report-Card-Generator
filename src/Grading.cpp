#include "Grading.h"

//constructor
Grading::Grading(){
}

//other methods
void Grading::display() const {
    std::ifstream inGradeTable{"ndhuGradeTable.txt"}; //open file
    std::string letter{""};
    float gpi{0.0}, lowerPercent{0.0}, upperPercent{0.0};

    std::cout << std::setw(30) << std::right << "Grade Table" << std::endl << std::endl;
    std::cout << std::setw(15) << std::left << "Letter"
                << std::setw(15) << "GPI"
                << std::setw(15) << "Lower %"
                << std::setw(15) << "Upper %" << std::endl << std::endl;

    if (!inGradeTable){ //check if file is open
        std::cerr << "\n\nndhuGradeTable.txt was NOT found!\n";
        //return 1; //exit the program (main)
    }

    while (inGradeTable >> letter >> gpi >> lowerPercent >> upperPercent){ //read in the grade details
        std::cout << std::setw(15) << std::left << letter
                << std::setw(15) << std::setprecision(2) << std::fixed << gpi
                << std::setw(15) << std::setprecision(0) << lowerPercent
                << std::setw(15) << upperPercent << std::endl;
    } std::cout << std::endl;
    inGradeTable.close(); //close the file
}

//deconstructor
Grading::~Grading(){
}
