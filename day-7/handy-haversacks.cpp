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
bool checkBags(vector <struct bag> &bags, string inAdj){
    bool output = false;
    bag foundBag;

    // cout << "Input:" << inAdj << endl;

    if (inAdj == keyword2){return false;};
    
    //find the bag in bags where bag.adj = parameter adj
    auto adjMatch = [inAdj](const bag& b){return (b.adj == inAdj);};
    auto p = find_if(bags.begin(), bags.end(), adjMatch); 

    if (p != bags.end()){
        foundBag = *p;

        if (foundBag.rules.at(0).adj == keyword2){
            // cout << "no other bags" << endl;
            return false;
        };

        for (int i = 0; i < foundBag.rules.size(); i++){
        string currAdj = foundBag.rules.at(i).adj;
            if (currAdj == keyword0){
                return true;
            } else {
                output = (output || checkBags(bags, currAdj));
            }
        }
    }
    // cout << "loop closed" << endl;
    return output;
}

bool canContainShinyGold(vector <struct bag> &, string);
bool canContainShinyGold(vector <struct bag> &bags, string input){
    int pos1 = input.find(keyword1);
    string currBagAdj = input.substr(0, pos1);
    input = input.substr(pos1 + keyword1.length());

    stringstream ss(input);
    string ruleStr, word;
    int count = 0;
    ss << input;
    while(ss >> word){
        if (word.back() == ',' || word.back() == '.'){
            ruleStr.erase(ruleStr.length()-1);
            if (checkBags(bags, ruleStr)){return true;};
            count = -1;
            ruleStr = "";
        } else if (count > 0){
            ruleStr += word + " ";
        }
        count++;
    }

    return false;
};

int answer1(fstream &, vector <struct bag> &);
int answer1(fstream &file, vector <struct bag> &bags){
    int count = 0;
    string line;
    file.open(filename);

    // getline(file, line);
    // getline(file, line);
    // getline(file, line);
    // getline(file, line);
    // if(canContainShinyGold(bags, line)){count++;};
    
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
    cout << answer1(file, bags);
    // cout << bags.at(0).rules.at(0).adj;
}