/***
* Makes use of Dictionary ADT to quickly store and access key/value pairs
***/
#include<iostream>
#include<string>
#include<stdexcept>
#include<fstream>
#include"Dictionary.h"

int main(int argc, char * argv[]) {

    // check command line for correct number of arguments
    if( argc != 3 ){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
    }


    std::ifstream inputFile(argv[1]);
    std::ofstream outputFile(argv[2]);

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open input file." << std::endl;
        return 1;
    }

    // Create a Dictionary to store strings and their corresponding line numbers
    Dictionary myDictionary;

    // Read lines from the input file and insert them into the Dictionary
    std::string line;
    int lineNumber = 1;

    while (std::getline(inputFile, line)) {
        myDictionary.setValue(line, lineNumber);
        lineNumber++;
    }

    outputFile << myDictionary;
    outputFile<<"\n";
    outputFile << myDictionary.pre_string();

    // Close the files
    inputFile.close();
    outputFile.close();

    return 0;
}