// https://www.youtube.com/watch?v=802Fn_kHHTU&ab_channel=KyoHeo

// basic file operations
// 2 class make
#include <iostream>
#include <fstream>
#include "dataReader.hpp"
#include "spellChecker.hpp"
using namespace std;

int main() {

    DataReader myReader("EngDictionary.txt");
    SpellChecker spellChecker(myReader.getDictionary(), "check.txt");
    //spellChecker.makeResult("result.txt");
    //when we read the file
    int count = 0;
    vector<string> v1 = spellChecker.getAnswer();
    for(int i = 0; i < v1.size(); i++) {
        if(v1[i] == "\n") {
            cout << v1[i];    
        } else {
            for(int j = 0; j < v1[i].size(); j++) {
                if(v1[i][j] == ',' || v1[i][j] == '{') {
                    count++;
                }
            }
            if(count > 0) {
                cout << v1[i];    
            } else {
                cout << v1[i] << ' ';            
            }
        }
        count = 0;
    }
    cout << endl;

    //ofstream myfile;
    //myfile.open ("title.txt"); //tile
    //myfile << "Writing this to a file\n";
    //myfile << "I love C++";
    //myfile.close();
    return 0;
}