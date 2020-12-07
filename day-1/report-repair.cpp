#include <iostream>
#include <fstream>
#include <string.h>
#include <algorithm>
using namespace std;

int findAnswerP1(int [], int);
int findAnswerP2(int [], int);

int countNums(fstream &);
void populateArray(fstream &, int []);
void printArray(int [], int);
void printResult(int);

const int SUM = 2020;
const string filename = "input.txt";

int main(){
    fstream file;
    int count;

    count = countNums(file);
    int input[count];

    populateArray(file, input);
    sort(input, input+count);
    // printArray(input, count);

    printResult(findAnswerP2(input, count));
    return 0;
}

int findAnswerP1(int array[], int size){
    int n1 = 0;
    int n2 = size - 1;

    while (n1 < n2){
        if (array[n1] + array[n2] == SUM) {
            cout << "Numbers: " << array[n1] << ", " << array[n2] << endl;
            return array[n1] * array[n2];
        } else if (array[n1] + array[n2] < SUM) {
            n1++;
        } else {
            n2--;
        }
    }

    return 0;
}

int findAnswerP2(int array[], int size){
    int n1 = 0;
    int n2 = 1;
    int n3 = size - 1;

    for (int i = 0; i < size; i++){
        while (n2 < n3){
            if (array[n1] + array[n2] + array[n3] == SUM) {
                cout << "Numbers: " << array[n1] << ", " << array[n2] << ", " << array[n3] << endl;
                return array[n1] * array[n2] * array[n3];
            } else if (array[n1] + array[n2] + array[n3] < SUM) {
                n2++;
            } else {
                n3--;
            }
        }

        n1++;
        n2 = 1;
        n3 = size - 1;
    }

    return 0;
}

int countNums(fstream &file){
    file.open(filename);
    int currentNum;
    int count = 0;

    while(file >> currentNum){
        count++;
    }

    cout << "Count: " << count << endl;
    file.close();
    return count;
}

void populateArray(fstream &file, int array[]){
    file.open(filename);
    int currentNum;
    int count = 0;

    while(file >> currentNum){
        array[count] = currentNum;
        count++;
    }

    cout << "Array populated. Size: " << count << endl;
    file.close();
}

void printArray(int array[], int size){
    cout << "Printing Array" << endl;
    for (int i = 0; i < size; i++){
        cout << i << ". " << array[i] << endl;
    }
}

void printResult(int answer){
    if (answer == 0) {
        cout << "Numbers adding to 2020 were not found.";
    } else {
        cout << "Answer: " << answer;
    }
    cout << endl;
}