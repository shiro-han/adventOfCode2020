#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;

const string filename = "input.txt";

const 

int processFile(fstream &, vector<string> &);
string formatRaw_pp(string);
void populatePassports(vector <struct pp> &, vector<string> &);
void constructPP(string);

struct pp{
    string byr;
    string eyr;
    string hgt;
    string hcl;
    string ecl;
    string pid;
    string cid;
};

int main(){
    fstream file;
    vector<pp> passports;
    vector<string> raw_pps;

    // cout << raw_pps.size() << endl;
    
    processFile(file, raw_pps);
    populatePassports(passports, raw_pps);

    // cout << raw_pps.at(259);
}

int processFile(fstream &file, vector<string> &raw_pps){
    int count = 0;
    string line;
    string raw_pp;
    
    file.open(filename);
    
    while (getline(file, line)){
        raw_pp += (line + "\n");
        if (line == ""){
            raw_pps.push_back(formatRaw_pp(raw_pp));
            count++;
            raw_pp = "";
        }
        
    }

    file.close();
    cout << "Total passports: " << count << endl;

    return count;
}

string formatRaw_pp(string pp){
    stringstream ss(pp);
    string word;

    ss << pp;
    pp = "";

    while (ss >> word){
        pp = pp + word + "\n";
    }

    return pp;
}

void populatePassports(vector <struct pp> &passports, vector<string> &raw_pps){
    int numPassports = raw_pps.size();

    for (int i = 0; i < numPassports; i++){
        constructPP(raw_pps.at(i));
    }
}

// struct pp
void constructPP(string raw_pp){
    stringstream ss(raw_pp);
    string line;

    ss << raw_pp;

    while (ss >> line){
        int pos = line.find(":");
        string field = line.substr(0, pos);
        string info = line.substr(pos+1);

        if (field == "")
    }

    cout << endl;

    
}