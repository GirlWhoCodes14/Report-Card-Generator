#include "Grading.h"

//constructor
Grading::Grading() {
}

bool Grading::openFile() {
  inGradeTable.open("grade_table.txt");
  if (!inGradeTable.is_open()) {
    throw std::runtime_error("grade_table.txt was NOT found!\n"); // Throw an exception
  }
  return true; // Indicate success
}

//other methods
void Grading::display() {
    std::cout << std::setw(30) << std::right << "*** Grade Table ***" << std::endl << std::endl;

    try {
        if (!openFile()) { // Check if file opened successfully
            return; // Exit the function if file open fails
        }

        std::string letter{""};
        float gpi{0.0}, lowerPercent{0.0}, upperPercent{0.0};

        std::cout << std::setw(15) << std::left << "Letter"
                    << std::setw(15) << "GPI"
                    << std::setw(15) << "Lower %"
                    << std::setw(15) << "Upper %" << std::endl << std::endl;

        while (inGradeTable >> letter >> gpi >> lowerPercent >> upperPercent){ //read in the grade details
            std::cout << std::setw(15) << std::left << letter
                    << std::setw(15) << std::setprecision(2) << std::fixed << gpi
                    << std::setw(15) << std::setprecision(0) << lowerPercent
                    << std::setw(15) << upperPercent << std::endl;
        } std::cout << std::endl;
        system("pause");

    } catch (const std::exception& e) {
        illegal.setConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
        std::cerr << "ERROR: " << e.what() << std::endl;
        illegal.resetColorAndPause();
    }
}

//deconstructor
Grading::~Grading(){
    inGradeTable.close(); //close the file
}
