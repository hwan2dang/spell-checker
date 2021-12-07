#include "dataReader.hpp"
#include <fstream>
#include <vector>
#include <iostream>
#include <string>

DataReader::DataReader() {

}

DataReader::~DataReader() {

}

DataReader::DataReader(const std::string& inputFile) {
    readFile(inputFile);
}

std::vector<std::string> DataReader::getDictionary() {
    return dictionary;
}

void DataReader::setDictionary(std::vector<std::string> inputDictionary) {
    dictionary = inputDictionary;
}

void DataReader::readFile(std::string inputFile) {
    std::string line = "";
    std::ifstream file(inputFile);
    
    if(file.is_open()) {
        while(getline(file, line)) {
            dictionary.push_back(line);
        }
    }
    
    file.close();
}
