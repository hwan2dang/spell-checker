#ifndef dataReader_hpp
#define dataReader_hpp
#include <vector>
#include <string>
#include <fstream>

class DataReader {
public:

    DataReader();
    DataReader(const std::string& inputFile);
    void setDictionary(std::vector<std::string> inputDictionary);
    std::vector<std::string> getDictionary();
    ~DataReader();

private:
    std::vector<std::string> dictionary;
    void readFile(std::string inputFile);

};

#include "dataReader.cpp"
#endif