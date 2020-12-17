#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <vector>
#include <math.h>
#include <set>

using namespace std;

const string filename = "input.txt";

struct instruct{
    string opp;
    int arg;
};

inline bool operator<(const instruct& lhs, const instruct& rhs){
    return (lhs.arg < rhs.arg || lhs.opp < rhs.opp);
}

void populateInstructs(fstream &file, vector<instruct> &instructs){
    string line;
    file.open(filename);
    while(getline(file, line)){
        instruct inst;
        inst.opp = line.substr(0, 3);
        inst.arg = stoi(line.substr(4));
        instructs.push_back(inst);
    }
    file.close();
};

int answer1(vector<instruct> &instructs){
    int accum = 0, i = 0;
    set<int> firstloop;
    
    while (i < instructs.size()){
        instruct currInst = instructs.at(i);
        bool valid = firstloop.insert(i).second;

        if (valid == false){
            auto it = firstloop.end();
            it--;
            instruct lastInst = instructs.at(*it);

            if (lastInst.opp == "jmp"){
                lastInst.opp = "nop";
            } else if(lastInst.opp == "nop"){
                lastInst.opp = "jmp";
            }
            return accum;
        }

        if (currInst.opp == "acc"){
            accum += currInst.arg;
        }
        
        if (currInst.opp == "jmp"){
            i += currInst.arg;
        } else {
            i++;
        }
    }

    return -1;
}

int answer2(vector<instruct> &instructs){
    instructs;
};

int main(){
    fstream file;
    vector<instruct> instructs;
    populateInstructs(file, instructs);
    cout << answer1(instructs);
}