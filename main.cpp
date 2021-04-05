//  PROGRAM FILE NAME: Project 3.cpp        ASSIGNMENT #: 3
//
//  PROGRAM AUTHOR: Jacob Campbell
//
//  COURSE: CSC 24400     SEMESTER: FALL 2018     PROFESSOR: Dr. Miller
//
//  DUE DATE: October 22nd, 2018
//
//  DESCRIPTION: open and read input files which contain an unknown number
//               of records and process the student data in accordance with
//               the instructions given below. Your program is to be
//               modularized with functions to sort, print, and read. It is
//               also to include any other functions you deem necessary.
//
//  FUNCTIONS: header()
//             footer()
//             main()

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

// Display Header
void header() {
    cout << endl;
    cout << " --------------------------------- " << endl;
    cout << "|     START OF PROGRAM OUTPUT     |" << endl;
    cout << " --------------------------------- " << endl;
    cout << endl;
    return;
}

// Display Footer
void footer() {
    cout << endl;
    cout << " --------------------------------- " << endl;
    cout << "|      END OF PROGRAM OUTPUT      |" << endl;
    cout << " --------------------------------- " << endl;
    return;
}

int main() {
    
    header();
    
    const int arraySize = 100;  // constant array size of 100
    int studentID[arraySize];           // student ID array of size 100
    double testScores[arraySize][4];    // test score array of size 100x4
    double averageScores[arraySize];    // average score array of size 100
    char letterGrade[arraySize];        // letter grade array of size 100

    // For all rows of all 4 arrays...
    for(int row = 0; row < 100; row++) {
        // For all columns of the two dimensional array...
        for(int col = 0; col < 4; col++) {
            testScores[row][col] = -1;  // Initialize to -1
        }
        studentID[row] = -1;            // Initialize to -1
        averageScores[row] = -1;        // Initialize to -1
        letterGrade[row] = ' ';         // Iniliatize to a blank space
    }
    
    
    ifstream inFile;            // Create an ifstream and call it inFile
    inFile.open("data3.txt");   // Use inFile to open the document named "data3.txt"
    
    // For all rows of arrays studentID and testScores...
    for(int row = 0; row < 100; row++) {
        inFile >> studentID[row];               // Input inFile data into this row of studentID array
      
        // If the value read from the inFile is less than 0...
        if(studentID[row] < 0) {
            break;  // Break from the loop
        }
        
        // Else, for all columns of the two dimensional array...
        for(int col = 0; col < 4; col++) {
            inFile >> testScores[row][col]; // Input inFile data into this row/column of the testScores Array
        }
    }
    
    // Display Headers
    cout << "The original student data is:" << endl;
    cout << " Student ID   Test 1  Test 2  Test 3  Test 4  " << endl;
    cout << "------------  ------  ------  ------  ------  " << endl;
    
    // For all rows and columns of the studentID and testScores arrays,
    // show the data that was previously read in as long as it does not equal -1
    for(int row = 0; row < 100; row++) {
        if(studentID[row] != -1) {
            cout << "  " << setfill('0') << setw(10) << right << studentID[row] << "  ";
            for(int col = 0; col < 4; col++) {
                if(testScores[row][col] != -1) {
                    if(col != 3) {
                        cout << setfill(' ') << setw(6) << fixed << setprecision(1) << testScores[row][col] << "  ";
                    }
                    else {
                        cout << setfill(' ') << setw(6) << fixed << setprecision(1) << testScores[row][col];
                    }
                }
            }
            cout << endl;
        }
    }
    cout << endl;
    
    // Sort the data stored in studentID and testScores arrays in
    // descending order according to the studentID
    for(int i = 0; i < 100; i++) {
        for(int j = i + 1; j < 100; j++) {
            if(studentID[i] < studentID[j]) {
                int temp = studentID[j];
                studentID[j] = studentID[i];
                studentID[i] = temp;
                
                for(int col = 0; col < 4; col++) {
                    double temp = testScores[j][col];
                    testScores[j][col] = testScores[i][col];
                    testScores[i][col] = temp;
                }
            }
        }
    }
    
    // Display Headers
    cout << "The list of student data sorted by ID number from low to high is:" << endl;
    cout << " Student ID   Test 1  Test 2  Test 3  Test 4  " << endl;
    cout << "------------  ------  ------  ------  ------  " << endl;
    
    // For all rows and columns of the studentID and testScores arrays,
    // show the data that was previously sorted as long as it does not equal -1
    for(int row = 0; row < 100; row++) {
        if(studentID[row] != -1) {
            cout << "  " << setfill('0') << setw(10) << right << studentID[row] << "  ";
            for(int col = 0; col < 4; col++) {
                if(testScores[row][col] != -1) {
                    if(col != 3) {
                        cout << setfill(' ') << setw(6) << fixed << setprecision(1) << testScores[row][col] << "  ";
                    }
                    else {
                        cout << setfill(' ') << setw(6) << fixed << setprecision(1) << testScores[row][col];
                    }
                }
            }
            cout << endl;
        }
    }
    cout << endl;
    
    // Caluculate the average test score for each student
    double sum = 0;
    double average = 0;
    for(int row = 0; row < 100; row++) {
        for(int col = 0; col < 4; col++) {
            if(testScores[row][col] != -1) {
                sum = sum + testScores[row][col];
                average = sum/4;
            }
        }
        averageScores[row] = average;
        sum = 0;
        average = 0;
    }
    
    // Calculate the appropriate letter grade for each student according to their test averages
    for(int row = 0; row < 100; row++) {
        if(averageScores[row] <= 100 && averageScores[row] >= 89.5) {
            letterGrade[row] = 'A';
        }
        else if(averageScores[row] < 90 && averageScores[row] >= 79.5) {
            letterGrade[row] = 'B';
        }
        else if(averageScores[row] < 80 && averageScores[row] >= 69.5) {
            letterGrade[row] = 'C';
        }
        else if(averageScores[row] < 70 && averageScores[row] >= 59.5) {
            letterGrade[row] = 'D';
        }
        else {
            letterGrade[row] = 'F';
        }
        
    }
    
    // Display Headers
    cout << "The list of students with their test average and course grade is:" << endl;
    cout << "                                              Test     Course" << endl;
    cout << " Student ID   Test 1  Test 2  Test 3  Test 4  Average  Grade " << endl;
    cout << "------------  ------  ------  ------  ------  -------  ------" << endl;
    
    // For all rows and columns of the studentID, testScores, averageScores, and letterGrade arrays,
    // show the data with the averages and letter grades as long as it does not equal -1
    for(int row = 0; row < 100; row++) {
        if(studentID[row] != -1) {
            cout << "  " << setfill('0') << setw(10) << right << studentID[row] << "  ";
            for(int col = 0; col < 4; col++) {
                if(testScores[row][col] != -1) {
                        cout << setfill(' ') << setw(6) << fixed << setprecision(1) << testScores[row][col] << "  ";
                }
            }
            cout << setfill(' ') << setw(7) << right << fixed << setprecision(2) << averageScores[row] << "  ";
            cout << setfill(' ') << setw(5) << right << letterGrade[row] << endl;
        }
    }
    cout << endl;
    
    // Sort the data stored in studentID, testScores, averageScores, and letterGrade arrays in
    // descending order according to the average test scores
    for(int i = 0; i < 100; i++) {
        for(int j = i + 1; j < 100; j++) {
            if(averageScores[i] < averageScores[j]) {
                double temp = averageScores[j];
                averageScores[j] = averageScores[i];
                averageScores[i] = temp;
                
                for(int col = 0; col < 4; col++) {
                    double temp = testScores[j][col];
                    testScores[j][col] = testScores[i][col];
                    testScores[i][col] = temp;
                }
                
                int temp2 = studentID[j];
                studentID[j] = studentID[i];
                studentID[i] = temp2;
                
                char temp3 = letterGrade[j];
                letterGrade[j] = letterGrade[i];
                letterGrade[i] = temp3;
            }
        }
    }
    
    // Display Headers
    cout << "The list of students sorted by test average high to low is:" << endl;
    cout << "                                              Test     Course" << endl;
    cout << " Student ID   Test 1  Test 2  Test 3  Test 4  Average  Grade " << endl;
    cout << "------------  ------  ------  ------  ------  -------  ------" << endl;
    
    // For all rows and columns of the studentID, testScores, averageScores, and letterGrade arrays,
    // show the data that was previously sorted according to test averages as long as it does not equal -1
    for(int row = 0; row < 100; row++) {
        if(studentID[row] != -1) {
            cout << "  " << setfill('0') << setw(10) << right << studentID[row] << "  ";
            for(int col = 0; col < 4; col++) {
                if(testScores[row][col] != -1) {
                    cout << setfill(' ') << setw(6) << fixed << setprecision(1) << testScores[row][col] << "  ";
                }
            }
            cout << setfill(' ') << setw(7) << right << fixed << setprecision(2) << averageScores[row] << "  ";
            cout << setfill(' ') << setw(5) << right << letterGrade[row] << endl;
        }
    }
    cout << endl;
    
    // Show Outout
    cout << "Opening output file: outfile.txt" << endl;
    
    string outputFile = "output3.txt";
    ofstream outFile;
    outFile.open(outputFile);
    
    if(outFile.good()) {
        for(int i = 0; i < 100; i++) {
            for(int j = i + 1; j < 100; j++) {
                if(studentID[i] > studentID[j]) {
                    double temp = averageScores[j];
                    averageScores[j] = averageScores[i];
                    averageScores[i] = temp;
                    
                    for(int col = 0; col < 4; col++) {
                        double temp = testScores[j][col];
                        testScores[j][col] = testScores[i][col];
                        testScores[i][col] = temp;
                    }
                    
                    int temp2 = studentID[j];
                    studentID[j] = studentID[i];
                    studentID[i] = temp2;
                    
                    char temp3 = letterGrade[j];
                    letterGrade[j] = letterGrade[i];
                    letterGrade[i] = temp3;
                }
            }
        }
        
        for(int row = 0; row < 100; row++) {
            if(studentID[row] != -1) {
                outFile << setfill('0') << setw(10) << right << studentID[row] << endl;
                for(int col = 0; col < 4; col++) {
                    outFile << setprecision(1) << fixed << testScores[row][col] << " ";
                }
                outFile << setprecision(2) << fixed << averageScores[row] << " ";
                outFile << letterGrade[row];
                outFile << endl;
            }
            
        }
        
        for(int row = 0; row < 100; row++) {
            for(int col = 0; col < 4; col++) {
                testScores[row][col] = -1;
            }
            studentID[row] = -1;
            averageScores[row] = -1;
            letterGrade[row] = ' ';
        }
        cout << "Writing data to output file" << endl;
        cout << "Closing output file: outfile.txt" << endl;
        cout << endl;
    }
    else {
        cout << "Output file data3.txt failed to open" << endl;
        cout << endl;
    }
   
    // Display Footer
    footer();
    cout << endl;
}

