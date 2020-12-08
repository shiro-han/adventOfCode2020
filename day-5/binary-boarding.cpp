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
    double high_limit = 7;
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

bool compareIds(bp, bp);
bool compareIds(bp b1, bp b2){
    return (b1.id < b2.id);
}

int myId(vector <struct bp> &);
int myId(vector <struct bp> &boarding_passes){
    sort(boarding_passes.begin(), boarding_passes.end(), compareIds);
    int length = boarding_passes.size();

    // for (int i = 0; i < length; i++){
    //     cout << boarding_passes.at(i).id << endl;
    // }

    for (int i = 1; i < length; i++){
        int prevID = boarding_passes.at(i-1).id;
        int currID = boarding_passes.at(i).id;
        int nextID = boarding_passes.at(i+1).id;

        cout << "prevID: " << prevID << endl;
        cout << "currID: " << currID << endl;
        cout << "nextID: " << nextID << endl;
        cout << endl;

        if (nextID - prevID != 2){return currID+1;};
    }

    return -1;
}

int main(){
    fstream file;
    vector<bp> boarding_passes;
    processFile(file, boarding_passes);
    int answer = myId(boarding_passes);
    cout << "\nYour ID: " << answer << endl;
}