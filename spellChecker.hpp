#ifndef spellChecker_hpp
#define spellChecker_hpp
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
//#include <ofstream>

class SpellChecker {
public:
    SpellChecker();
    SpellChecker(std::vector<std::string> inputDictionary,
                 const std::string& inputfile);
    ~SpellChecker();
    std::vector<std::string> getAnswer();

private:
    std::vector<std::string> checkWords;
    std::vector<std::string> dictionary;
    std::vector<std::string> answer;
    
    void readFile(std::string inputFile);
    void wordSwap(std::string inputWord, 
              std::vector<std::string> inputDictionary,
              int& position);
    void wordRemove(std::string inputWord, 
                    std::vector<std::string> inputDictionary,
                    int& position);
    void wordReplace(std::string inputWord, 
                    std::vector<std::string> inputDictionary,
                    int& position);
                    
    void wordAdd(std::string inputWord, 
                    std::vector<std::string> inputDictionary,
                    int& position);                
    std::string generateCleanWords(std::string inputCheckWord);
    void separateCategories(std::string& line);
    void filterWord(std::string inputCheckWord,
                    std::vector<std::string> inputDictionary);
    
};









#include "spellChecker.cpp"
#endif