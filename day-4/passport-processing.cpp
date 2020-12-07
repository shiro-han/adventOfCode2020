#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;

const string filename = "input.txt";

int processFile(fstream &, vector<string> &);
string formatRaw_pp(string);
void populatePassports(vector <struct pp> &, vector<string> &);
struct pp constructPP(string);
int presentPassports(vector <struct pp> &);

struct pp{
    string byr;
    string iyr;
    string eyr;
    string hgt;
    string hcl;
    string ecl;
    string pid;
    string cid;
};

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
        passports.push_back(constructPP(raw_pps.at(i)));
    }
}

struct pp constructPP(string raw_pp){
    stringstream ss(raw_pp);
    string line;
    pp passport;

    ss << raw_pp;
    while (ss >> line){
        int pos = line.find(":");
        string field = line.substr(0, pos);
        string info = line.substr(pos+1);

        if (field == "byr"){
            passport.byr = info;
        } else if (field == "iyr"){
            passport.iyr = info;
        } else if (field == "eyr"){
            passport.eyr = info;
        } else if (field == "hgt"){
            passport.hgt = info;
        } else if (field == "hcl"){
            passport.hcl = info;
        } else if (field == "ecl"){
            passport.ecl = info;
        } else if (field == "pid"){
            passport.pid = info;
        } else if (field == "cid"){
            passport.cid = info;
        }
    }

    return passport;
}

int presentPassports(vector <struct pp> &passports){
    int count = 0;
    int numValid = 0;
    int numPassports = passports.size();

    for (int i = 0; i < numPassports; i++){
        bool present = true;
        bool valid = false;
        pp passport = passports.at(i);

        if (passport.byr == ""){
            present = false;
        } else if (passport.iyr == ""){
            present = false;
        } else if (passport.eyr == ""){
            present = false;
        } else if (passport.hgt == ""){
            present = false;
        } else if (passport.hcl == ""){
            present = false;
        } else if (passport.ecl == ""){
            present = false;
        } else if (passport.pid == ""){
            present = false;
        }

        if (stoi(passport.byr)){
            valid = true;
        } else if (passport.iyr == ""){
            valid = true;
        } else if (passport.eyr == ""){
            valid = true;
        } else if (passport.hgt == ""){
            valid = true;
        } else if (passport.hcl == ""){
            valid = true;
        } else if (passport.ecl == ""){
            valid = true;
        } else if (passport.pid == ""){
            valid = true;
        }
        
        if (present){count++;};
        if (valid){numValid++;};
    }

    cout << "With Required Fields: " << count << endl;
    cout << "With Valid Info: " << numValid << endl;

    return count;
}

bool byrValid(string input){
    if(input.length() > 4){return false;}
    int byr = stoi(input);
    return (1920 <= byr && byr <= 2002);
}

bool iyrValid(string input){
    if(input.length() > 4){return false;}
    int iyr = stoi(input);
    return (2010 <= iyr && iyr <= 2020);
}

bool eyrValid(string input){
    if(input.length() > 4){return false;}
    int eyr = stoi(input);
    return (2020 <= eyr && eyr <= 2030);
}

bool hgtValid(string input){
    int cmPos = input.find("cm");
    int inPos = input.find("in");
    int hgt;

    if (cmPos == -1 && inPos == -1){
        return false;
    } else if (cmPos != -1){
        hgt = stoi(input.substr(0, cmPos));
        return (150 <= hgt && hgt <= 193);
    } else if (inPos != -1){
        hgt = stoi(input.substr(0, inPos));
        return (59 <= hgt && hgt <= 76);
    }
}

// bool hclValid(string input){
//     string hclMod = input.substr(1);
//     if (input.at(0) != '#'){
//         return false;
//     } else {
//         if (hclMod.length() == 6){
//             for (int i = 0; i < 6; i++){
                
//             }
//         } else {
//             return false;
//         }
//     }
// }

bool eclValid(string input){
    if (input == "amb"){return true;}
    else if (input == "blu"){return true;}
    else if (input == "brn"){return true;}
    else if (input == "gry"){return true;}
    else if (input == "grn"){return true;}
    else if (input == "hzl"){return true;}
    else if (input == "oth"){return true;}
    else {return false;}
}

bool pidValid(string input){
    if (input.length() == 9){
        int pid = stoi(input);
        return (typeid(pid) == typeid(1));
    } else {
        return false;
    }
}


int main(){
    fstream file;
    vector<pp> passports;
    vector<string> raw_pps;

    // cout << raw_pps.size() << endl;
    
    processFile(file, raw_pps);
    populatePassports(passports, raw_pps);

    presentPassports(passports);
}