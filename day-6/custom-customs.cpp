#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <algorithm>
#include <iterator>
#include <math.h>
#include <set>

using namespace std;

const string filename = "input.txt";

int numYesPerGroup(string);
int numYesPerGroup(string groupStr){
    int length = groupStr.length();
    set<char> groupSet;

    for (int i = 0; i < length; i++){
        groupSet.insert(groupStr.at(i));
    }

    return groupSet.size();
}

int processFile(fstream &);
int processFile(fstream &file){
    string line, groupStr;
    int count = 0;
    file.open(filename);

    while (getline(file, line)){
        groupStr += line;
        if (line == ""){
            count += numYesPerGroup(groupStr);
            groupStr = "";
        }
    }

    file.close();

    return count;
}

int main(){
    fstream file;
    cout << processFile(file) << endl;
}