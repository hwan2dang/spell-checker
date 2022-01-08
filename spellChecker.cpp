#include "spellChecker.hpp"
#include <vector>
#include <string>
#include <fstream>

SpellChecker::SpellChecker() {

}

SpellChecker::SpellChecker(std::vector<std::string> inputDictionary, const std::string& inputFile) {
    dictionary = inputDictionary;
    readFile(inputFile);
}

SpellChecker::~SpellChecker() {

}

void SpellChecker::readFile(std::string inputFile) {
    std::string line = "";
    int count = 0;
    int index = 0;
    std::ifstream file(inputFile);

    if(file.is_open()) {
        while(getline(file, line)) {
            if(count != 0) {
                checkWords.push_back("\n");
            }
            separateCategories(line);
            count++;
        }
        file.close();
    }

    for(int i = 0; i < checkWords.size(); i++) {
        filterWord(checkWords[i], dictionary);
    }
}

std::string SpellChecker::generateCleanWords(std::string inputCheckWord) {
    std::string temp = "";

    for(int i = 0; i < inputCheckWord.size(); i++) {
        if(inputCheckWord[i] >= 'a' && inputCheckWord[i] <= 'z') {
            temp += inputCheckWord[i];
        } else if(inputCheckWord[i] >= 'A' && inputCheckWord[i] <= 'Z') {
            temp += (inputCheckWord[i] + 32);
        }
    }

    return temp;
}

void SpellChecker::separateCategories(std::string& line) {
    std::string temp = "";

    for(int i = 0; i < line.size(); i++) {
        if(line[i] != ' ') {
            temp += line[i];
        }

        if(line[i] == ' ' || i == line.size() - 1) {
            checkWords.push_back(temp);
            temp = "";
        }
    }
}

void SpellChecker::wordSwap(std::string inputWord,
                        std::vector<std::string> inputDictionary,
                        int& position) {
    std::string changedWord = inputWord;
    int temp = 0;
    int index = 0;

    while(index < inputWord.size()) {
        for(int i = index; i < inputWord.size(); i++) {
            if(index != i) {
                temp = inputWord[index];
                inputWord[index] = inputWord[i];
                inputWord[i] = temp;

                for(int j = 0; j < inputDictionary.size(); j++) {
                    if(inputWord == inputDictionary[j]) {
                        answer.push_back("{" + inputWord);
                        position++;
                    }
                }
                inputWord = changedWord;
            }
        }
        index++;
    }
}


void SpellChecker::wordRemove(std::string inputWord,
                              std::vector<std::string> inputDictionary,
                              int& position) {
    std::string changedWord = "";
    std::string comparedWord = "";
    int temp = 0;
    int index = 0;

    while(index < inputWord.size()) {
        for(int i = 0; i < inputWord.size(); i++) {
            if(i != index) {
                changedWord += inputWord[i];
            }
        }

        while(comparedWord != changedWord) {
            for(int j = 0; j < inputDictionary.size(); j++) {
                if(changedWord == inputDictionary[j] && position == 0) {
                    answer.push_back("{" + changedWord);
                    position++;
                } else if(changedWord == inputDictionary[j]
                          && position > 0) {
                    answer.push_back(", " + changedWord);
                    position++;
                }
            }
            comparedWord = changedWord;
        }
        changedWord = "";
        index++;
    }
}

void SpellChecker::wordReplace(std::string inputWord,
                              std::vector<std::string> inputDictionary,
                              int& position) {
    std::string changedWord = inputWord;
    int index = 0;

    while(index <= inputWord.size()) {
        for(int i = 0; i < 32; i++) {
            inputWord[index] = 'a' + i;

            for(int j = 0; j < inputDictionary.size(); j++) {
                if(inputWord == inputDictionary[j] && position == 0) {
                    answer.push_back("{" + inputWord);
                    position++;
                } else if(inputWord == inputDictionary[j]
                          && position > 0) {
                    answer.push_back(", " + inputWord);
                    position++;
                }
            }
        }
        inputWord = changedWord;
        index++;
    }
}

void SpellChecker::wordAdd(std::string inputWord,
                              std::vector<std::string> inputDictionary,
                              int& position) {
    std::string changedWord = "";
    int index = 0;
    int count = 0;

    while(index <= inputWord.size()) {
        for(int i = 0; i < 32; i++) {
            for(int k = 0; k < inputWord.size(); k++) {
                if(index == 0 || index == k) {
                    changedWord += 'a' + i;
                }
                changedWord += inputWord[k];
            }

            if(index == inputWord.size()) {
                changedWord += 'a' + i;
            }

            for(int j = 0; j < inputDictionary.size(); j++) {
                if(changedWord == inputDictionary[j] && position == 0) {
                    answer.push_back("{" + changedWord);
                    position++;
                } else if(changedWord == inputDictionary[j]
                          && position > 0) {
                    answer.push_back(", " + changedWord);
                    position++;
                }

            }
            changedWord = "";
        }
        index++;
    }
}


void SpellChecker::filterWord(std::string inputCheckWord,
                              std::vector<std::string> inputDictionary) {
    bool shouldLookForSuggestions = true;
    std::string cleanWord = generateCleanWords(inputCheckWord);

    if(inputCheckWord.size() == 1) {
        shouldLookForSuggestions = false;
        answer.push_back(inputCheckWord);
    } else {
        for(int i = 0; i < inputDictionary.size(); i++) {
            if(inputCheckWord == inputDictionary[i]) {
                shouldLookForSuggestions = false;
                answer.push_back(inputCheckWord);
            }
        }
    }

    int position = 0;

    if(shouldLookForSuggestions) {
        answer.push_back(inputCheckWord);
        wordSwap(cleanWord, inputDictionary, position);
        wordRemove(cleanWord, inputDictionary, position);
        wordReplace(cleanWord, inputDictionary, position);
        wordAdd(cleanWord, inputDictionary, position);
        answer.push_back("}");
    }
}

std::vector<std::string> SpellChecker::getAnswer() {
    return answer;
}




















