#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <vector>
#include <iterator>
#include <math.h>
#include <set>

using namespace std;

const string filename = "input.txt";

int numYesAnyone(string);
int numYesAnyone(string groupStr){
    int length = groupStr.length();
    set<char> groupSet;

    for (int i = 0; i < length; i++){
        groupSet.insert(groupStr.at(i));
    }

    return groupSet.size();
}

int answer1(fstream &);
int answer1(fstream &file){
    string line, groupStr;
    int count = 0;
    file.open(filename);

    while (getline(file, line)){
        groupStr += line;
        if (line == ""){
            count += numYesAnyone(groupStr);
            groupStr = "";
        }
    }

    file.close();

    return count;
}

int numYesEveryone(string);
int numYesEveryone(string groupStr){
    stringstream ss(groupStr);
    string line;
    set<char> groupSet = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

    ss << groupStr;
    while (ss >> line){
        set<char> personSet;
        set<char> intersect = {};
        for (int i = 0; i < line.length(); i++){
            personSet.insert(line.at(i));
        }
        set_intersection(groupSet.begin(), groupSet.end(), personSet.begin(), personSet.end(), inserter(intersect, intersect.begin()));
        groupSet = intersect;
    }
    
    return groupSet.size();
}

int answer2(fstream &);
int answer2(fstream &file){
    string line, groupStr;
    int count = 0;
    file.open(filename);

    while (getline(file, line)){
        groupStr += line + "\n";
        if (line == ""){
            count += numYesEveryone(groupStr);
            groupStr = "";
        }
    }

    file.close();

    return count;
}

int main(){
    fstream file;
    // answer1(file);
    // answer2(file);
    cout << answer2(file) << endl;
}