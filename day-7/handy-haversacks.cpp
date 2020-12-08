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
const string keyword0 = "shiny gold";
const string keyword1 = " bags contain ";
const string keyword2 = "other";

struct rule {
    string adj;
    int num;
};

struct bag {
    string adj;
    vector<rule> rules;
};

struct rule constructRule(string);
struct rule constructRule(string raw_rule){
    struct rule output;
    bool firstWord = true;
    string adj = "";
    stringstream ss(raw_rule);
    string word;
    ss << raw_rule;

    while (ss >> word){
        if (firstWord){
            if (word == "no"){
                output.num = 0;
            } else {
                output.num = stoi(word);
            }
        } else {
            adj += " " + word;
        }
        firstWord = false;
    }
    output.adj = adj.erase(0, 1);

    return output;
}

void populateBags(vector <struct bag> &, string);
void populateBags(vector <struct bag> &bags, string input){
    bag currBag;

    int pos1 = input.find(keyword1);
    currBag.adj = input.substr(0, pos1);
    input = input.substr(pos1 + keyword1.length());
    
    stringstream ss(input);
    string raw_rule, word;
    ss << input;
    while(ss >> word){
        if (word.back() == ',' || word.back() == '.'){
            currBag.rules.push_back(constructRule(raw_rule));
            raw_rule = "";
        } else {
            raw_rule += word + " ";
        }
    }
    bags.push_back(currBag);
}

void openFile(fstream &, vector <struct bag> &);
void openFile(fstream &file, vector <struct bag> &bags){
    string line;
    file.open(filename);
    while (getline(file, line)){
        populateBags(bags, line);
    }
    file.close();
}

bool checkBags(vector <struct bag> &, string);
bool checkBags(vector <struct bag> &bags, string adj){
    bool output = false;
    //find the bag in bags where bag.adj = parameter adj
    // bag foundBag = search(bags.begin(), bags.end(), );
    //check bag rules to see if shiny gold is an adj of one of its rules
    //if not, then call checkBags on each rule adj
    return output;
};

bool canContainShinyGold(vector <struct bag> &, string);
bool canContainShinyGold(vector <struct bag> &bags, string input){
    int pos1 = input.find(keyword1);
    string currBagAdj = input.substr(0, pos1);
    input = input.substr(pos1 + keyword1.length());

    stringstream ss(input);
    string ruleStr, word;
    ss << input;
    while(ss >> word){
        if (word.back() == ',' || word.back() == '.'){
            if (checkBags(bags, ruleStr)){return true;};
            ruleStr = "";
        } else {
            ruleStr += word + " ";
        }
    }
    cout << endl;

    return false;
};

int answer1(fstream &, vector <struct bag> &);
int answer1(fstream &file, vector <struct bag> &bags){
    int count = 0;
    string line;
    file.open(filename);
    
    while (getline(file, line)){
        if(canContainShinyGold(bags, line)){count++;};
    }

    file.close();
    return count;
}

int main(){
    fstream file;
    vector<bag> bags;
    openFile(file, bags);
    // answer1(file, bags);
    cout << bags.at(589).rules.at(0).adj << endl;
}