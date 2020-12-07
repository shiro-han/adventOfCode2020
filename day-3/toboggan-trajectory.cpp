#include <iostream>
#include <fstream>
#include <string.h>
#include <algorithm>
using namespace std;

const string filename = "input.txt";

int countLines(fstream &);
void populateMap(fstream &, string[]);
bool treeAtPos(string, int);
int checkTrees(string[], int, int, int);

int main(){
    fstream file;
    int num_lines = countLines(file);
    string map[num_lines];

    populateMap(file, map);
    
    unsigned long long int answer;
    answer = checkTrees(map, num_lines, 1, 1) * checkTrees(map, num_lines, 3, 1) * checkTrees(map, num_lines, 5, 1) * checkTrees(map, num_lines, 7, 1) * checkTrees(map, num_lines, 1, 2);
    cout << "Multiplied Answer: " << answer << endl;
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

void populateMap(fstream &file, string map[]){
    file.open(filename);
    string line;
    int n1 = 0;

    while(file >> line){
        map[n1] = line;
        n1++;
    }

    file.close();
}

bool treeAtPos(string line, int pos){
    return (line[pos] == '#');
}

int checkTrees(string map[], int yLength, int xInc, int yInc){
    int xLength = map[0].length();
    int treeCount = 0;
    int xPos = 0;
    int yPos = 0;

    while (yPos < yLength){
        yPos += yInc;
        xPos += xInc;
        string currentLine = map[yPos];
        
        if (xPos >= xLength){xPos -= xLength;};

        if(treeAtPos(currentLine, xPos)){treeCount++;};
    }

    cout << "x: " << xInc << " y: " << yInc << " - Tree Count: " << treeCount << endl;

    return treeCount;
}