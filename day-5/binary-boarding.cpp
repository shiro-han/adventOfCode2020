#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

const string filename = "input.txt";

struct bp {
    int row;
    int column;
    int id;
};

int findRow(string);
int findRow(string rowIn){
    int length = rowIn.length();
    double high_limit = 127;
    double low_limit = 0;

    for (int i = 0; i < length ; i++){
        char c = rowIn[i];
        int half = ceil((high_limit-low_limit)/2);

        if (c == 'F'){
            high_limit -= half;
        } else if (c == 'B'){
            low_limit += half;
        }
    }

    if (high_limit != low_limit){
        return -1;
    }

    return low_limit;
}

int findColumn(string);
int findColumn(string columnIn){
    int length = columnIn.length();
    double high_limit = 127;
    double low_limit = 0;

    for (int i = 0; i < length ; i++){
        char c = columnIn[i];
        int half = ceil((high_limit-low_limit)/2);

        if (c == 'L'){
            high_limit -= half;
        } else if (c == 'R'){
            low_limit += half;
        }
    }

    if (high_limit != low_limit){
        return -1;
    }

    return low_limit;
}

struct bp bpConstruct(string);
struct bp bpConstruct(string line){
    struct bp output;
    string rowIn = line.substr(0,7);
    string columnIn = line.substr(7);

    output.row = findRow(rowIn);
    output.column = findColumn(columnIn);
    output.id = output.row * 8 + output.column;

    return output;
}

void processFile(fstream &, vector<struct bp> &);
void processFile(fstream &file, vector<struct bp> &boarding_passes){
    file.open(filename);
    string line;

    while (getline(file, line)){
        boarding_passes.push_back(bpConstruct(line));
    }

    file.close();
}

int highestID(vector <struct bp> &);
int highestID(vector <struct bp> &boarding_passes){
    int highestID = 0;
    int length = boarding_passes.size();

    for (int i = 0; i < length; i++){
        int currentid = boarding_passes.at(i).id;
        if (highestID < currentid){
            highestID = currentid;
        }
    }

    return highestID;
}

int main(){
    fstream file;
    vector<bp> boarding_passes;
    processFile(file, boarding_passes);

    cout << highestID(boarding_passes);

}