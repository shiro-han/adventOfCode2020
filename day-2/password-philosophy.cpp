#include <iostream>
#include <fstream>
#include <string.h>
#include <algorithm>
using namespace std;

const string filename = "input.txt";

struct pp{
    int low;
    int high;
    char letter;
    string password;
};

int countLines(fstream &file);
void populatePParray(fstream &, pp[]);
int findAnswer(pp [], int);
bool isPPprotected1(pp);
bool isPPprotected2(pp);


int main(){
    fstream file;
    int num_lines = countLines(file);
    pp passwords[num_lines];

    populatePParray(file, passwords);
    cout << "Answer: " << findAnswer(passwords, num_lines) << endl;
}

int findAnswer(pp passwords[], int size){
    int x = 0;

    for (int i = 0; i < size; i++){
        if(isPPprotected2(passwords[i])){x++;};
    }

    return x;
}

bool isPPprotected1(pp pp){
    int count = 0;

    for(char const &c : pp.password){
        if (c == pp.letter){
            count++;
        }
    }

    if(pp.low <= count && count <= pp.high){
        return true;
    } else {
        return false;
    }
}

bool isPPprotected2(pp pp){
    bool pos1, pos2;

    pos1 = (pp.password[pp.low-1] == pp.letter);
    pos2 = (pp.password[pp.high-1] == pp.letter);

    if((pos1 || pos2) && !(pos1 && pos2)){
        return true;
    } else {
        return false;
    }
}

int countLines(fstream &file){
    int count = 0;
    string line;
    file.open(filename);
    
    while (getline(file, line)){
        count++;
    }

    file.close();
    cout << "Lines Counted in File: " << count << endl;

    return count;
}

void populatePParray(fstream &file, pp passwords[]){
    file.open(filename);
    string raw_range, raw_char, password;
    int count = 0;
    int n1, n2;
    char c1;

    while(file >> raw_range >> raw_char >> password){
        int pos = raw_range.find("-");
        n1 = stoi(raw_range.substr(0, pos));
        n2 = stoi(raw_range.substr(pos+1));
        c1 = raw_char[0];

        passwords[count].low = n1;
        passwords[count].high = n2;
        passwords[count].letter = c1;
        passwords[count].password = password;

        count++;
    }

    file.close();
}