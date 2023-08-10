#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

// Define constants
const int NUM_CLASSES_BIO = 3;
const int NUM_STUDENTS_PER_CLASS = 40;
const int NUM_STREAMS = 2;

// Function to calculate total marks
int calculateTotalMarks(const vector<int>& marks) {
    int total = 0;
    for (int mark : marks) {
        total += mark;
    }
    return total;
}

// Function to calculate ranks
void calculateRanks(vector<pair<string, int>>& students) {
    sort(students.begin(), students.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
        return a.second > b.second;
    });
}

int main() {
    vector<pair<string, int>> studentRanks;
    
    ifstream inFile("student_marks.txt"); // Replace with your file name
    
    if (!inFile) {
        cerr << "Error opening file." << endl;
        return 1;
    }
    
    string name;
    int bioMarks, mathMarks;
    
    while (inFile >> name >> bioMarks >> mathMarks) {
        int totalMarks = calculateTotalMarks({bioMarks, mathMarks});
        studentRanks.push_back(make_pair(name, totalMarks));
    }
    
    inFile.close();
    
    calculateRanks(studentRanks);
    
    // Calculate and display school rank
    for (int i = 0; i < studentRanks.size(); ++i) {
        cout << "Student: " << studentRanks[i].first << "\tTotal Marks: " << studentRanks[i].second << "\tSchool Rank: " << i + 1 << endl;
    }
    
    // Calculate and display class rank
    for (int stream = 0; stream < NUM_STREAMS; ++stream) {
        for (int cls = 0; cls < (stream == 0 ? NUM_CLASSES_BIO : NUM_CLASSES_MATH); ++cls) {
            vector<pair<string, int>> classRanks;
            
            for (int i = 0; i < studentRanks.size(); ++i) {
                if (i >= cls * NUM_STUDENTS_PER_CLASS && i < (cls + 1) * NUM_STUDENTS_PER_CLASS) {
                    classRanks.push_back(studentRanks[i]);
                }
            }
            
            calculateRanks(classRanks);
            
            for (int i = 0; i < classRanks.size(); ++i) {
                cout << "Stream: " << (stream == 0 ? "Bioscience" : "Math") << "\tClass: " << cls + 1 << "\tStudent: " << classRanks[i].first << "\tTotal Marks: " << classRanks[i].second << "\tClass Rank: " << i + 1 << endl;
            }
        }
    }
    
    return 0;
}
