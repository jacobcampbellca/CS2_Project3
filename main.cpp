//  PROGRAM FILE NAME: Project 4.cpp        ASSIGNMENT #: 4
//
//  PROGRAM AUTHOR: Jacob Campbell
//                  Dominique Dobbs
//                  Andrei Ciot
//
//  COURSE: CSC 24400     SEMESTER: FALL 2018     PROFESSOR: Dr. Miller
//
//  DUE DATE: December 5th, 2018
//
//  DESCRIPTION: For your fourth programming assignment, you are to write a
//  program to open and read an input file, which contain an unknown number
//  of records and process the student data in accordance with the instructions
//  given below. Your program is to be modularized with functions to read the
//  data from the input file, write data to an output file, as well as with
//  overloaded functions to sort and print, similar to project 3. It should
//  also include any other functions you deem necessary.

//
//  FUNCTIONS: header()
//             footer()
//             executeReadCommand()
//             executeWriteCommand()
//             executeAddCommand()
//             executeDeleteCommand()
//             executeUpdateCommand()
//             printAllAscending()
//             printAllDescending()
//             printRangeAscending()
//             printRangeDescending()
//             executePrintCommand()
//             main()

#include <iostream>
#include <istream>
#include <iomanip>
#include <string>
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
    cout << " --------------------------------- " << endl;
    cout << "|      END OF PROGRAM OUTPUT      |" << endl;
    cout << " --------------------------------- " << endl;
    cout << endl;
    return;
}

//create arrays
const int arraySize = 100;
int studentID[arraySize];
string studentName[arraySize][2];
double testScores[arraySize][4];
double averageTestScores[arraySize];
char letterGrade[arraySize];

//initialize values in arrays
void initializeArrays() {
    for(int row = 0; row < 100; row++) {
        for(int col = 0; col < 2; col++) {
            studentName[row][col] = ' ';
        }
        for(int col = 0; col < 4; col++) {
            testScores[row][col] = -1;
        }
        studentID[row] = -1;
        averageTestScores[row] = -1;
        letterGrade[row] = ' ';
    }
}

//read data from file into arrays
void executeReadCommand() {
    //reset values previously stored in array
    for(int row = 0; row < 100; row++) {
        for(int col = 0; col < 2; col++) {
            studentName[row][col] = ' ';
        }
        for(int col = 0; col < 4; col++) {
            testScores[row][col] = -1;
        }
        studentID[row] = -1;
        averageTestScores[row] = -1;
        letterGrade[row] = ' ';
    }
    
    //select in file
    string dataFile;
    cin >> dataFile;
    
    ifstream inFile;            // Create an ifstream and call it inFile
    inFile.open(dataFile);      // Use inFile to open the document named "data3.txt"
    //if infile is good, read data from file into arrays
    if(inFile.good()) {
        for(int row = 0; row < 100; row++) {
            inFile >> studentID[row];
            for(int col = 0; col < 2; col++) {
                inFile >> studentName[row][col];
            }
            
            for(int col = 0; col < 4; col++) {
                inFile >> testScores[row][col];
            }
            if(studentID[row] < 0) {
                for(int col = 0; col < 2; col++) {
                    studentName[row][col] = ' ';
                }
                for(int col = 0; col < 4; col++) {
                    testScores[row][col] = -1;
                }
                studentID[row] = -1;
                averageTestScores[row] = -1;
                letterGrade[row] = ' ';
            }
        }
        cout << "Read data from " << dataFile << endl;
        cout << "*************************************************************************************" << endl;
    }
    else{
        cout << "Data file " << dataFile << " does not exist." << endl;
        cout << "*************************************************************************************" << endl;
    }
    
    //calculate average test score adn write to array
    double sum = 0;
    double average = 0;
    for(int row = 0; row < 100; row++) {
        for(int col = 0; col < 4; col++) {
            if(testScores[row][col] > 0) {
                sum = sum + testScores[row][col];
                average = sum/4;
            }
        }
        averageTestScores[row] = average;
        sum = 0;
        average = 0;
    }
    //calculate letter grade and write to array
    for(int row = 0; row < 100; row++) {
        if(averageTestScores[row] <= 100 && averageTestScores[row] >= 89.5) {
            letterGrade[row] = 'A';
        }
        else if(averageTestScores[row] < 90 && averageTestScores[row] >= 79.5) {
            letterGrade[row] = 'B';
        }
        else if(averageTestScores[row] < 80 && averageTestScores[row] >= 69.5) {
            letterGrade[row] = 'C';
        }
        else if(averageTestScores[row] < 70 && averageTestScores[row] >= 59.5) {
            letterGrade[row] = 'D';
        }
        else if(averageTestScores[row] < 70 && averageTestScores[row] > 0) {
            letterGrade[row] = 'F';
        }
        else {
            letterGrade[row] = 'U';
        }
    }
}

//execute write command
void executeWriteCommand() {
    //select name of file to be written
    string outputFile;
    cin >> outputFile;
    
    //create outfile
    ofstream outFile;
    outFile.open(outputFile);
    
    //if outfile is good, sort arrays in ascending order according to student ID
    if(outFile.good()) {
        for(int i = 0; i < 100; i++) {
            for(int j = i + 1; j < 100; j++) {
                if(studentID[i] > studentID[j]) {
                    for(int col = 0; col < 4; col++) {
                        double temp = testScores[j][col];
                        testScores[j][col] = testScores[i][col];
                        testScores[i][col] = temp;
                    }
                    
                    for(int col = 0; col < 2; col++) {
                        string temp2 = studentName[j][col];
                        studentName[j][col] = studentName[i][col];
                        studentName[i][col] = temp2;
                    }
                    
                    int temp3 = studentID[j];
                    studentID[j] = studentID[i];
                    studentID[i] = temp3;
                }
            }
        }
        
        //write sorted arrays to outfile
        for(int row = 0; row < 100; row++) {
            if(studentID[row] != -1) {
                outFile << studentID[row] << endl;
                for(int col = 0; col < 2; col++) {
                    if(col == 1) {
                        outFile << studentName[row][col];
                    }
                    else {
                        outFile << studentName[row][col] << " ";
                    }
                }
                outFile << endl;
                for(int col = 0; col < 4; col++) {
                    if(col == 3) {
                        outFile << setprecision(1) << fixed << testScores[row][col];
                    }
                    else {
                        outFile << setprecision(1) << fixed << testScores[row][col] << " ";
                    }
                }
                outFile << endl;
            }
        }
        
        //reset values stored in arrays
        for(int row = 0; row < 100; row++) {
            for(int col = 0; col < 2; col++) {
                studentName[row][col] = ' ';
            }
            for(int col = 0; col < 4; col++) {
                testScores[row][col] = -1;
            }
            studentID[row] = -1;
            averageTestScores[row] = -1;
            letterGrade[row] = ' ';
        }
        cout << "Write data to " << outputFile << endl;
        cout << "*************************************************************************************" << endl;

    }
    else {
        cout << "Output file " << outputFile << " failed to open" << endl;
        cout << "*************************************************************************************" << endl;

    }
}

//execute add command
void executeAddCommand() {
    //ID of student to be added
    int ID;
    cin >> ID;
    //if ID already exists, do not add
    for(int row = 0; row < 100; row++) {
        if(studentID[row] == ID) {
            cout << "Add record failed - Duplicate ID " << ID << endl;
            cout << "*************************************************************************************" << endl;
            return;
        }
    }
    //add ID to next available index in array
    for(int row = 0; row < 100; row++) {
        if(studentID[row] == -1) {
            studentID[row] = ID;
            break;
        }
    }
    
    //get student name to be added
    string firstName;
    cin >> firstName;
    string lastName;
    cin >> lastName;
    // add name to next available spot in array
    for(int row = 0; row < 100; row++) {
        if(studentName[row][0] == " " && studentName[row][1] == " ") {
            studentName[row][0] = firstName;
            studentName[row][1] = lastName;
            break;
        }
    }
    
    //get test scores
    double testOne, testTwo, testThree, testFour;
    cin >> testOne;
    cin >> testTwo;
    cin >> testThree;
    cin >> testFour;
    // adda test scores to next available spot in array
    for(int row = 0; row < 100; row++) {
        if(testScores[row][0] == -1 && testScores[row][1] == -1) {
            testScores[row][0] = testOne;
            testScores[row][1] = testTwo;
            testScores[row][2] = testThree;
            testScores[row][3] = testFour;
            break;
        }
    }
    
    //calculate average score and add to next available spot in array
    double sum = 0;
    double average = 0;
    for(int row = 0; row < 100; row++) {
        for(int col = 0; col < 4; col++) {
            if(testScores[row][col] != -1) {
                sum = sum + testScores[row][col];
                average = sum/4;
            }
        }
        averageTestScores[row] = average;
        sum = 0;
        average = 0;
    }
    
    //calculate letter greade and add to next available spot in array
    for(int row = 0; row < 100; row++) {
        if(averageTestScores[row] >= 89.5) {
            letterGrade[row] = 'A';
        }
        else if(averageTestScores[row] < 90 && averageTestScores[row] >= 79.5) {
            letterGrade[row] = 'B';
        }
        else if(averageTestScores[row] < 80 && averageTestScores[row] >= 69.5) {
            letterGrade[row] = 'C';
        }
        else if(averageTestScores[row] < 70 && averageTestScores[row] >= 59.5) {
            letterGrade[row] = 'D';
        }
        else if(averageTestScores[row] < 70 && averageTestScores[row] > 0) {
            letterGrade[row] = 'F';
        }
        else {
            letterGrade[row] = 'U';
        }
    }
    cout << "Add record completed - ID " << ID << endl;
    cout << "*************************************************************************************" << endl;

}

//execute delete command
void executeDeleteCommand() {
    //get ID of student to be deleted
    int ID;
    cin >> ID;
    bool found = false;
   
    //if student ID found, reset values stored in arrays
    for(int row = 0; row < 100; row++) {
        if(studentID[row] == ID) {
            found = true;
            if(studentID[row] == ID) {
                studentID[row] = -1;
                for(int col = 0; col < 2; col++) {
                    studentName[row][col] = ' ';
                }
                for(int col = 0; col < 4; col++) {
                    testScores[row][col] = -1;
                }
                averageTestScores[row] = -1;
                letterGrade[row] = ' ';
            }
            
        }
    }
    
    //sort array in ascending order of student ID
    for(int i = 0; i < 100; i++) {
        for(int j = i + 1; j < 100; j++) {
            if(studentID[i] > studentID[j]) {
                for(int col = 0; col < 4; col++) {
                    double temp = testScores[j][col];
                    testScores[j][col] = testScores[i][col];
                    testScores[i][col] = temp;
                }
                
                for(int col = 0; col < 2; col++) {
                    string temp2 = studentName[j][col];
                    studentName[j][col] = studentName[i][col];
                    studentName[i][col] = temp2;
                }
                
                int temp3 = studentID[j];
                studentID[j] = studentID[i];
                studentID[i] = temp3;
                
                double temp4 = averageTestScores[j];
                averageTestScores[j] = averageTestScores[i];
                averageTestScores[i] = temp4;
                
                char temp5 = letterGrade[j];
                letterGrade[j] = letterGrade[i];
                letterGrade[i] = temp5;
            }
        }
    }
    
    if(found == true) {
        cout << "Delete record completed - ID " << ID << endl;
        cout << "*************************************************************************************" << endl;

    }
    else {
        cout << "Delete record failed - Could not find ID " << ID << endl;
        cout << "*************************************************************************************" << endl;

        return;
    }
}

//execute update command
void executeUpdateCommand() {
    //get student ID to be updated
    int ID;
    cin >> ID;
    
    //if student ID found continue. else, terminmate function
    bool found = false;
    for(int row = 0; row < 100; row++) {
        if (studentID[row] == ID) {
            found = true;
            break;
        }
    }
    if(found == false) {
        cin.ignore(100, '\n');
        cout << "Update record failed - Could not find ID " << ID << endl;
        cout << "*************************************************************************************" << endl;
        return;
    }
    
    //get field number to be updated
    int fieldNumber;
    cin >> fieldNumber;
    
    //update student ID
    if(fieldNumber == 1) {
       //get new ID, and update record
        int updatedID;
        cin >> updatedID;
        bool found = false;
        for(int row = 0; row < 100; row++) {
            if(studentID[row] == ID) {
                found = true;
                break;
            }
        }
        //terminate function if ID does not currently exist
        if(found == false) {
            cin.ignore(100, '\n');
            cout << "Update record failed - invalid ID " << ID << endl;
            cout << "*************************************************************************************" << endl;
            return;
        }
        
        //terminate function if new ID already exists
        bool unique = true;
        for(int row = 0; row < 100; row++) {
            if(studentID[row] == updatedID) {
                unique = false;
                cout << "Update failed - Updated ID " << updatedID << " is not unique" << endl;
                cout << "*************************************************************************************" << endl;
                return;
            }
        }
        for(int row = 0; row < 100; row++) {
            if(studentID[row] == ID && unique == true) {
                studentID[row] = updatedID;
                cout << "Update record completed - ID " << ID << endl;
                cout << "*************************************************************************************" << endl;
                break;
            }
        }
    }
    
    //update first name of student
    else if(fieldNumber == 2) {
        //get new first name
        string firstName;
        cin >> firstName;
        bool found = false;
        
        //see if ID exists
        for(int row = 0; row < 100; row++) {
            if(studentID[row] == ID) {
                found = true;
                break;
            }
        }
        //if ID doesnt exist, terminate function
        if(found == false) {
            cout << "Update record failed - invalid ID " << ID << endl;
            cout << "*************************************************************************************" << endl;
            return;
        }
        
        //update name in array
        for(int row = 0; row < 100; row++) {
            if(studentID[row] == ID) {
                studentName[row][0] = firstName;
                cout << "Update record completed - ID " << ID << endl;
                cout << "*************************************************************************************" << endl;
                break;
            }
        }
    }
    
    // update last name
    else if(fieldNumber == 3) {
        //get new last name
        string lastName;
        cin >> lastName;
        bool found = false;
        
        //see if ID exists
        for(int row = 0; row < 100; row++) {
            if(studentID[row] == ID) {
                found = true;
                break;
            }
        }
        
        //if ID does not exist, terminate program
        if(found == false) {
            cout << "Update record failed - invalid ID " << ID << endl;
            cout << "*************************************************************************************" << endl;
            return;
        }
        
        //if ID does exist, update last name
        for(int row = 0; row < 100; row++) {
            if(studentID[row] == ID) {
                studentName[row][1] = lastName;
                cout << "Update record completed - ID " << ID << endl;
                cout << "*************************************************************************************" << endl;
                break;
            }
        }
    }
    
    //update test score one
    else if(fieldNumber == 4) {
        //get new test score
        double testOne;
        cin >> testOne;
        bool found = false;
        //see if student ID exists
        for(int row = 0; row < 100; row++) {
            if(studentID[row] == ID) {
                found = true;
                break;
            }
        }
        
        //if ID does not exist, terminate program
        if(found == false) {
            cout << "Update record failed - invalid ID " << ID << endl;
            cout << "*************************************************************************************" << endl;
            return;
        }
        
        //if ID does exist, update test score
        for(int row = 0; row < 100; row++) {
            if(studentID[row] == ID) {
                testScores[row][0] = testOne;
                cout << "Update record completed - ID " << ID << endl;
                cout << "*************************************************************************************" << endl;
                break;
            }
        }
    }
    //update test score two
    else if(fieldNumber == 5) {
        double testTwo;
        cin >> testTwo;
        bool found = false;
        for(int row = 0; row < 100; row++) {
            if(studentID[row] == ID) {
                found = true;
                break;
            }
        }
        if(found == false) {
            cout << "Update record failed - invalid ID " << ID << endl;
            cout << "*************************************************************************************" << endl;
            return;
        }
        
        for(int row = 0; row < 100; row++) {
            if(studentID[row] == ID) {
                testScores[row][1] = testTwo;
                cout << "Update record completed - ID " << ID << endl;
                cout << "*************************************************************************************" << endl;
                break;
            }
        }
    }
    //update exam score three
    else if(fieldNumber == 6) {
        double testThree;
        cin >> testThree;
        bool found = false;
        for(int row = 0; row < 100; row++) {
            if(studentID[row] == ID) {
                found = true;
                break;
            }
        }
        if(found == false) {
            cout << "Update record failed - invalid ID " << ID << endl;
            cout << "*************************************************************************************" << endl;
            return;
        }
        for(int row = 0; row < 100; row++) {
            if(studentID[row] == ID) {
                testScores[row][2] = testThree;
                cout << "Update record completed - ID " << ID << endl;
                cout << "*************************************************************************************" << endl;
                break;
            }
        }
    }
    //update test score four
    else if(fieldNumber == 7) {
        double testFour;
        cin >> testFour;
        bool found = false;
        for(int row = 0; row < 100; row++) {
            if(studentID[row] == ID) {
                found = true;
                break;
            }
        }
        if(found == false) {
            cout << "Update record failed - invalid ID " << ID << endl;
            cout << "*************************************************************************************" << endl;
            return;
        }
        
        for(int row = 0; row < 100; row++) {
            if(studentID[row] == ID) {
                testScores[row][3] = testFour;
                cout << "Update record completed - ID " << ID << endl;
                cout << "*************************************************************************************" << endl;
                break;
            }
        }
    }
    
    //calculate average with updated score
    double sum = 0;
    double average = 0;
    for(int row = 0; row < 100; row++) {
        for(int col = 0; col < 4; col++) {
            if(testScores[row][col] > 0) {
                sum = sum + testScores[row][col];
                average = sum/4;
            }
        }
        averageTestScores[row] = average;
        sum = 0;
        average = 0;
    }
    
    //calculate letter grade with updated score
    for(int row = 0; row < 100; row++) {
        if(averageTestScores[row] <= 100 && averageTestScores[row] >= 89.5) {
            letterGrade[row] = 'A';
        }
        else if(averageTestScores[row] < 90 && averageTestScores[row] >= 79.5) {
            letterGrade[row] = 'B';
        }
        else if(averageTestScores[row] < 80 && averageTestScores[row] >= 69.5) {
            letterGrade[row] = 'C';
        }
        else if(averageTestScores[row] < 70 && averageTestScores[row] >= 59.5) {
            letterGrade[row] = 'D';
        }
        else if(averageTestScores[row] < 70 && averageTestScores[row] > 0) {
            letterGrade[row] = 'F';
        }
        else {
            letterGrade[row] = 'U';
        }
    }
}

//print all ascending
void printAllAscending(int sortField) {
    bool valid = true;
    string field;
    
    //sort by ascending ID number
    if(sortField == 1) {
        field = "student ID";
        for(int i = 0; i < 100; i++) {
            for(int j = i + 1; j < 100; j++) {
                if(studentID[i] > studentID[j]) {
                    for(int col = 0; col < 4; col++) {
                        double temp = testScores[j][col];
                        testScores[j][col] = testScores[i][col];
                        testScores[i][col] = temp;
                    }
                    
                    for(int col = 0; col < 2; col++) {
                        string temp2 = studentName[j][col];
                        studentName[j][col] = studentName[i][col];
                        studentName[i][col] = temp2;
                    }
                    
                    int temp3 = studentID[j];
                    studentID[j] = studentID[i];
                    studentID[i] = temp3;
                    
                    double temp4 = averageTestScores[j];
                    averageTestScores[j] = averageTestScores[i];
                    averageTestScores[i] = temp4;
                    
                    char temp5 = letterGrade[j];
                    letterGrade[j] = letterGrade[i];
                    letterGrade[i] = temp5;
                }
            }
        }
    }
    //sort by ascending first name
    else if(sortField == 2) {   //sort by first name
        field = "first name";
        for(int i = 0; i < 100; i++) {
            for(int j = i + 1; j < 100; j++) {
                if(studentName[i][0] > studentName[j][0]) {
                    for(int col = 0; col < 4; col++) {
                        double temp = testScores[j][col];
                        testScores[j][col] = testScores[i][col];
                        testScores[i][col] = temp;
                    }
                    
                    for(int col = 0; col < 2; col++) {
                        string temp2 = studentName[j][col];
                        studentName[j][col] = studentName[i][col];
                        studentName[i][col] = temp2;
                    }
                    
                    int temp3 = studentID[j];
                    studentID[j] = studentID[i];
                    studentID[i] = temp3;
                    
                    double temp4 = averageTestScores[j];
                    averageTestScores[j] = averageTestScores[i];
                    averageTestScores[i] = temp4;
                    
                    char temp5 = letterGrade[j];
                    letterGrade[j] = letterGrade[i];
                    letterGrade[i] = temp5;
                }
            }
        }
    }
    //sort by ascending last name
    else if(sortField == 3) {   //sort by last name
        field = "last name";
        for(int i = 0; i < 100; i++) {
            for(int j = i + 1; j < 100; j++) {
                if(studentName[i][1] > studentName[j][1]) {
                    for(int col = 0; col < 4; col++) {
                        double temp = testScores[j][col];
                        testScores[j][col] = testScores[i][col];
                        testScores[i][col] = temp;
                    }
                    
                    for(int col = 0; col < 2; col++) {
                        string temp2 = studentName[j][col];
                        studentName[j][col] = studentName[i][col];
                        studentName[i][col] = temp2;
                    }
                    
                    int temp3 = studentID[j];
                    studentID[j] = studentID[i];
                    studentID[i] = temp3;
                    
                    double temp4 = averageTestScores[j];
                    averageTestScores[j] = averageTestScores[i];
                    averageTestScores[i] = temp4;
                    
                    char temp5 = letterGrade[j];
                    letterGrade[j] = letterGrade[i];
                    letterGrade[i] = temp5;
                }
            }
        }
    }
    //sort by test score one
    else if(sortField == 4) {
        field = "first test score";
        for(int i = 0; i < 100; i++) {
            for(int j = i + 1; j < 100; j++) {
                if(testScores[i][0] > testScores[j][0]) {
                    for(int col = 0; col < 4; col++) {
                        double temp = testScores[j][col];
                        testScores[j][col] = testScores[i][col];
                        testScores[i][col] = temp;
                    }
                    
                    for(int col = 0; col < 2; col++) {
                        string temp2 = studentName[j][col];
                        studentName[j][col] = studentName[i][col];
                        studentName[i][col] = temp2;
                    }
                    
                    int temp3 = studentID[j];
                    studentID[j] = studentID[i];
                    studentID[i] = temp3;
                    
                    double temp4 = averageTestScores[j];
                    averageTestScores[j] = averageTestScores[i];
                    averageTestScores[i] = temp4;
                    
                    char temp5 = letterGrade[j];
                    letterGrade[j] = letterGrade[i];
                    letterGrade[i] = temp5;
                }
                else if(studentName[i][0] > studentName[j][0]) {
                    for(int col = 0; col < 4; col++) {
                        double temp = testScores[j][col];
                        testScores[j][col] = testScores[i][col];
                        testScores[i][col] = temp;
                    }
                    
                    for(int col = 0; col < 2; col++) {
                        string temp2 = studentName[j][col];
                        studentName[j][col] = studentName[i][col];
                        studentName[i][col] = temp2;
                    }
                    
                    int temp3 = studentID[j];
                    studentID[j] = studentID[i];
                    studentID[i] = temp3;
                    
                    double temp4 = averageTestScores[j];
                    averageTestScores[j] = averageTestScores[i];
                    averageTestScores[i] = temp4;
                    
                    char temp5 = letterGrade[j];
                    letterGrade[j] = letterGrade[i];
                    letterGrade[i] = temp5;
                }
            }
        }
    }
    //sort by test score two
    else if(sortField == 5) {
        field = "second test score";
        for(int i = 0; i < 100; i++) {
            for(int j = i + 1; j < 100; j++) {
                if(testScores[i][1] > testScores[j][1]) {
                    for(int col = 0; col < 4; col++) {
                        double temp = testScores[j][col];
                        testScores[j][col] = testScores[i][col];
                        testScores[i][col] = temp;
                    }
                    
                    for(int col = 0; col < 2; col++) {
                        string temp2 = studentName[j][col];
                        studentName[j][col] = studentName[i][col];
                        studentName[i][col] = temp2;
                    }
                    
                    int temp3 = studentID[j];
                    studentID[j] = studentID[i];
                    studentID[i] = temp3;
                    
                    double temp4 = averageTestScores[j];
                    averageTestScores[j] = averageTestScores[i];
                    averageTestScores[i] = temp4;
                    
                    char temp5 = letterGrade[j];
                    letterGrade[j] = letterGrade[i];
                    letterGrade[i] = temp5;
                }
            }
        }
    }
    //sort by test score three
    else if(sortField == 6) {
        field = "third test score";
        for(int i = 0; i < 100; i++) {
            for(int j = i + 1; j < 100; j++) {
                if(testScores[i][2] > testScores[j][2]) {
                    for(int col = 0; col < 4; col++) {
                        double temp = testScores[j][col];
                        testScores[j][col] = testScores[i][col];
                        testScores[i][col] = temp;
                    }
                    
                    for(int col = 0; col < 2; col++) {
                        string temp2 = studentName[j][col];
                        studentName[j][col] = studentName[i][col];
                        studentName[i][col] = temp2;
                    }
                    
                    int temp3 = studentID[j];
                    studentID[j] = studentID[i];
                    studentID[i] = temp3;
                    
                    double temp4 = averageTestScores[j];
                    averageTestScores[j] = averageTestScores[i];
                    averageTestScores[i] = temp4;
                    
                    char temp5 = letterGrade[j];
                    letterGrade[j] = letterGrade[i];
                    letterGrade[i] = temp5;
                }
            }
        }
    }
    //sort by test score four
    else if(sortField == 7) {
        field = "fourth test score";
        for(int i = 0; i < 100; i++) {
            for(int j = i + 1; j < 100; j++) {
                if(testScores[i][3] > testScores[j][3]) {
                    for(int col = 0; col < 4; col++) {
                        double temp = testScores[j][col];
                        testScores[j][col] = testScores[i][col];
                        testScores[i][col] = temp;
                    }
                    
                    for(int col = 0; col < 2; col++) {
                        string temp2 = studentName[j][col];
                        studentName[j][col] = studentName[i][col];
                        studentName[i][col] = temp2;
                    }
                    
                    int temp3 = studentID[j];
                    studentID[j] = studentID[i];
                    studentID[i] = temp3;
                    
                    double temp4 = averageTestScores[j];
                    averageTestScores[j] = averageTestScores[i];
                    averageTestScores[i] = temp4;
                    
                    char temp5 = letterGrade[j];
                    letterGrade[j] = letterGrade[i];
                    letterGrade[i] = temp5;
                }
            }
        }
    }
    //sort by average test score
    else if(sortField == 8) {
        field = "average test score";
            for(int i = 0; i < 100; i++) {
            for(int j = i + 1; j < 100; j++) {
                if(averageTestScores[i] > averageTestScores[j]) {
                    for(int col = 0; col < 4; col++) {
                        double temp = testScores[j][col];
                        testScores[j][col] = testScores[i][col];
                        testScores[i][col] = temp;
                    }
                    
                    for(int col = 0; col < 2; col++) {
                        string temp2 = studentName[j][col];
                        studentName[j][col] = studentName[i][col];
                        studentName[i][col] = temp2;
                    }
                    
                    int temp3 = studentID[j];
                    studentID[j] = studentID[i];
                    studentID[i] = temp3;
                    
                    double temp4 = averageTestScores[j];
                    averageTestScores[j] = averageTestScores[i];
                    averageTestScores[i] = temp4;
                    
                    char temp5 = letterGrade[j];
                    letterGrade[j] = letterGrade[i];
                    letterGrade[i] = temp5;
                }
            }
        }
    }
    //sort by letter grade
    else if(sortField == 9) {
        field = "letter grade";
        for(int i = 0; i < 100; i++) {
            for(int j = i + 1; j < 100; j++) {
                if(letterGrade[i] > letterGrade[j]) {
                    for(int col = 0; col < 4; col++) {
                        double temp = testScores[j][col];
                        testScores[j][col] = testScores[i][col];
                        testScores[i][col] = temp;
                    }
                    
                    for(int col = 0; col < 2; col++) {
                        string temp2 = studentName[j][col];
                        studentName[j][col] = studentName[i][col];
                        studentName[i][col] = temp2;
                    }
                    
                    int temp3 = studentID[j];
                    studentID[j] = studentID[i];
                    studentID[i] = temp3;
                    
                    double temp4 = averageTestScores[j];
                    averageTestScores[j] = averageTestScores[i];
                    averageTestScores[i] = temp4;
                    
                    char temp5 = letterGrade[j];
                    letterGrade[j] = letterGrade[i];
                    letterGrade[i] = temp5;
                }
                //if letter grades the same, sort by average test score
                else if(averageTestScores[i] > averageTestScores[j]) {
                    for(int col = 0; col < 4; col++) {
                        double temp = testScores[j][col];
                        testScores[j][col] = testScores[i][col];
                        testScores[i][col] = temp;
                    }
                    
                    for(int col = 0; col < 2; col++) {
                        string temp2 = studentName[j][col];
                        studentName[j][col] = studentName[i][col];
                        studentName[i][col] = temp2;
                    }
                    
                    int temp3 = studentID[j];
                    studentID[j] = studentID[i];
                    studentID[i] = temp3;
                    
                    double temp4 = averageTestScores[j];
                    averageTestScores[j] = averageTestScores[i];
                    averageTestScores[i] = temp4;
                    
                    char temp5 = letterGrade[j];
                    letterGrade[j] = letterGrade[i];
                    letterGrade[i] = temp5;
                }
            }
        }
    }
    //if invalid command, ignore line
    else {
        cin.ignore(100, '\n');
        valid = false;
    }
    
    //if valid commands, print ascending according to command
    if(valid == true) {
        cout << "                                                                      Test     Course" << endl;
        cout << " Student ID   Firstname   Lastname    Test 1  Test 2  Test 3  Test 4  Average  Grade " << endl;
        cout << "------------  ----------  ----------  ------  ------  ------  ------  -------  ------" << endl;
        for(int row = 0; row < 100; row++) {
            if(studentID[row] != -1) {
                cout << setfill(' ') << setw(12) << right << studentID[row] << "  ";
                for(int col = 0; col < 2; col++) {
                    string name = studentName[row][col];
                    name = name.substr(0, 10);
                    cout << setfill(' ') << setw(10) << left << name << "  ";
                }
                for(int col = 0; col < 4; col++) {
                    cout << setfill(' ') << setw(6) << right << fixed << setprecision(1) << testScores[row][col] << "  ";
                }
                cout << setfill(' ') << setw(7) << right << fixed << setprecision(2) << averageTestScores[row] << "  ";
                cout << setfill(' ') << setw(4) << right << letterGrade[row] << endl;
            }
        }
        cout << "*************************************************************************************" << endl;
    }
    //print records failed
    else {
        
        cout << "Print all records failed - Invalid field or direction" << endl;
        cout << "*************************************************************************************" << endl;
    }
}

//print all descending, commands same as previous function
void printAllDescending(int sortField) {
    
    bool valid = true;
    string field;
    if(sortField == 1) {    //sort by ID number
        field = "student ID";
        for(int i = 0; i < 100; i++) {
            for(int j = i + 1; j < 100; j++) {
                if(studentID[i] < studentID[j]) {
                    for(int col = 0; col < 4; col++) {
                        double temp = testScores[j][col];
                        testScores[j][col] = testScores[i][col];
                        testScores[i][col] = temp;
                    }
                    
                    for(int col = 0; col < 2; col++) {
                        string temp2 = studentName[j][col];
                        studentName[j][col] = studentName[i][col];
                        studentName[i][col] = temp2;
                    }
                    
                    int temp3 = studentID[j];
                    studentID[j] = studentID[i];
                    studentID[i] = temp3;
                    
                    double temp4 = averageTestScores[j];
                    averageTestScores[j] = averageTestScores[i];
                    averageTestScores[i] = temp4;
                    
                    char temp5 = letterGrade[j];
                    letterGrade[j] = letterGrade[i];
                    letterGrade[i] = temp5;
                }
            }
        }
    }
    else if(sortField == 2) {   //sort by first name
        field = "first name";
        for(int i = 0; i < 100; i++) {
            for(int j = i + 1; j < 100; j++) {
                if(studentName[i][0] < studentName[j][0]) {
                    for(int col = 0; col < 4; col++) {
                        double temp = testScores[j][col];
                        testScores[j][col] = testScores[i][col];
                        testScores[i][col] = temp;
                    }
                    
                    for(int col = 0; col < 2; col++) {
                        string temp2 = studentName[j][col];
                        studentName[j][col] = studentName[i][col];
                        studentName[i][col] = temp2;
                    }
                    
                    int temp3 = studentID[j];
                    studentID[j] = studentID[i];
                    studentID[i] = temp3;
                    
                    double temp4 = averageTestScores[j];
                    averageTestScores[j] = averageTestScores[i];
                    averageTestScores[i] = temp4;
                    
                    char temp5 = letterGrade[j];
                    letterGrade[j] = letterGrade[i];
                    letterGrade[i] = temp5;
                }
            }
        }
    }
    else if(sortField == 3) {   //sort by last name
        field = "last name";
        for(int i = 0; i < 100; i++) {
            for(int j = i + 1; j < 100; j++) {
                if(studentName[i][1] < studentName[j][1]) {
                    for(int col = 0; col < 4; col++) {
                        double temp = testScores[j][col];
                        testScores[j][col] = testScores[i][col];
                        testScores[i][col] = temp;
                    }
                    
                    for(int col = 0; col < 2; col++) {
                        string temp2 = studentName[j][col];
                        studentName[j][col] = studentName[i][col];
                        studentName[i][col] = temp2;
                    }
                    
                    int temp3 = studentID[j];
                    studentID[j] = studentID[i];
                    studentID[i] = temp3;
                    
                    double temp4 = averageTestScores[j];
                    averageTestScores[j] = averageTestScores[i];
                    averageTestScores[i] = temp4;
                    
                    char temp5 = letterGrade[j];
                    letterGrade[j] = letterGrade[i];
                    letterGrade[i] = temp5;
                }
            }
        }
    }
    else if(sortField == 4) {
        field = "first test score";
        for(int i = 0; i < 100; i++) {
            for(int j = i + 1; j < 100; j++) {
                if(testScores[i][0] < testScores[j][0]) {
                    for(int col = 0; col < 4; col++) {
                        double temp = testScores[j][col];
                        testScores[j][col] = testScores[i][col];
                        testScores[i][col] = temp;
                    }
                    
                    for(int col = 0; col < 2; col++) {
                        string temp2 = studentName[j][col];
                        studentName[j][col] = studentName[i][col];
                        studentName[i][col] = temp2;
                    }
                    
                    int temp3 = studentID[j];
                    studentID[j] = studentID[i];
                    studentID[i] = temp3;
                    
                    double temp4 = averageTestScores[j];
                    averageTestScores[j] = averageTestScores[i];
                    averageTestScores[i] = temp4;
                    
                    char temp5 = letterGrade[j];
                    letterGrade[j] = letterGrade[i];
                    letterGrade[i] = temp5;
                }
            }
        }
    }
    else if(sortField == 5) {
        field = "second test score";
        for(int i = 0; i < 100; i++) {
            for(int j = i + 1; j < 100; j++) {
                if(testScores[i][1] < testScores[j][1]) {
                    for(int col = 0; col < 4; col++) {
                        double temp = testScores[j][col];
                        testScores[j][col] = testScores[i][col];
                        testScores[i][col] = temp;
                    }
                    
                    for(int col = 0; col < 2; col++) {
                        string temp2 = studentName[j][col];
                        studentName[j][col] = studentName[i][col];
                        studentName[i][col] = temp2;
                    }
                    
                    int temp3 = studentID[j];
                    studentID[j] = studentID[i];
                    studentID[i] = temp3;
                    
                    double temp4 = averageTestScores[j];
                    averageTestScores[j] = averageTestScores[i];
                    averageTestScores[i] = temp4;
                    
                    char temp5 = letterGrade[j];
                    letterGrade[j] = letterGrade[i];
                    letterGrade[i] = temp5;
                }
            }
        }
    }
    else if(sortField == 6) {
        field = "third test score";
        for(int i = 0; i < 100; i++) {
            for(int j = i + 1; j < 100; j++) {
                if(testScores[i][2] < testScores[j][2]) {
                    for(int col = 0; col < 4; col++) {
                        double temp = testScores[j][col];
                        testScores[j][col] = testScores[i][col];
                        testScores[i][col] = temp;
                    }
                    
                    for(int col = 0; col < 2; col++) {
                        string temp2 = studentName[j][col];
                        studentName[j][col] = studentName[i][col];
                        studentName[i][col] = temp2;
                    }
                    
                    int temp3 = studentID[j];
                    studentID[j] = studentID[i];
                    studentID[i] = temp3;
                    
                    double temp4 = averageTestScores[j];
                    averageTestScores[j] = averageTestScores[i];
                    averageTestScores[i] = temp4;
                    
                    char temp5 = letterGrade[j];
                    letterGrade[j] = letterGrade[i];
                    letterGrade[i] = temp5;
                }
            }
        }
    }
    else if(sortField == 7) {
        field = "fourth test score";
        for(int i = 0; i < 100; i++) {
            for(int j = i + 1; j < 100; j++) {
                if(testScores[i][3] < testScores[j][3]) {
                    for(int col = 0; col < 4; col++) {
                        double temp = testScores[j][col];
                        testScores[j][col] = testScores[i][col];
                        testScores[i][col] = temp;
                    }
                    
                    for(int col = 0; col < 2; col++) {
                        string temp2 = studentName[j][col];
                        studentName[j][col] = studentName[i][col];
                        studentName[i][col] = temp2;
                    }
                    
                    int temp3 = studentID[j];
                    studentID[j] = studentID[i];
                    studentID[i] = temp3;
                    
                    double temp4 = averageTestScores[j];
                    averageTestScores[j] = averageTestScores[i];
                    averageTestScores[i] = temp4;
                    
                    char temp5 = letterGrade[j];
                    letterGrade[j] = letterGrade[i];
                    letterGrade[i] = temp5;
                }
            }
        }
    }
    else if(sortField == 8) {
        field = "average test score";
        for(int i = 0; i < 100; i++) {
            for(int j = i + 1; j < 100; j++) {
                if(averageTestScores[i] < averageTestScores[j]) {
                    for(int col = 0; col < 4; col++) {
                        double temp = testScores[j][col];
                        testScores[j][col] = testScores[i][col];
                        testScores[i][col] = temp;
                    }
                    
                    for(int col = 0; col < 2; col++) {
                        string temp2 = studentName[j][col];
                        studentName[j][col] = studentName[i][col];
                        studentName[i][col] = temp2;
                    }
                    
                    int temp3 = studentID[j];
                    studentID[j] = studentID[i];
                    studentID[i] = temp3;
                    
                    double temp4 = averageTestScores[j];
                    averageTestScores[j] = averageTestScores[i];
                    averageTestScores[i] = temp4;
                    
                    char temp5 = letterGrade[j];
                    letterGrade[j] = letterGrade[i];
                    letterGrade[i] = temp5;
                }
            }
        }
    }
    else if(sortField == 9) {
        field = "letter grade";
        for(int i = 0; i < 100; i++) {
            for(int j = i + 1; j < 100; j++) {
                if(letterGrade[i] < letterGrade[j]) {
                    for(int col = 0; col < 4; col++) {
                        double temp = testScores[j][col];
                        testScores[j][col] = testScores[i][col];
                        testScores[i][col] = temp;
                    }
                    
                    for(int col = 0; col < 2; col++) {
                        string temp2 = studentName[j][col];
                        studentName[j][col] = studentName[i][col];
                        studentName[i][col] = temp2;
                    }
                    
                    int temp3 = studentID[j];
                    studentID[j] = studentID[i];
                    studentID[i] = temp3;
                    
                    double temp4 = averageTestScores[j];
                    averageTestScores[j] = averageTestScores[i];
                    averageTestScores[i] = temp4;
                    
                    char temp5 = letterGrade[j];
                    letterGrade[j] = letterGrade[i];
                    letterGrade[i] = temp5;
                }
            }
        }
    }
    else {
        cin.ignore(100, '\n');
        valid = false;
    }
    
    if(valid == true) {
        cout << "                                                                      Test     Course" << endl;
        cout << " Student ID   Firstname   Lastname    Test 1  Test 2  Test 3  Test 4  Average  Grade " << endl;
        cout << "------------  ----------  ----------  ------  ------  ------  ------  -------  ------" << endl;
        for(int row = 0; row < 100; row++) {
            if(studentID[row] != -1) {
                cout << setfill(' ') << setw(12) << right << studentID[row] << "  ";
                for(int col = 0; col < 2; col++) {
                    string name = studentName[row][col];
                    name = name.substr(0, 10);
                    cout << setfill(' ') << setw(10) << left << name << "  ";
                }
                for(int col = 0; col < 4; col++) {
                    cout << setfill(' ') << setw(6) << right << fixed << setprecision(1) << testScores[row][col] << "  ";
                }
                cout << setfill(' ') << setw(7) << right << fixed << setprecision(2) << averageTestScores[row] << "  ";
                cout << setfill(' ') << setw(4) << right << letterGrade[row] << endl;
            }
        }
        cout << "*************************************************************************************" << endl;
    }
    else {
        cout << "Print all record failed - Invalid field or direction" << endl;
        cout << "*************************************************************************************" << endl;
    }
}

//print range of students in ascending order
void printRangeAscending(int IDmin, int IDmax, int sortField) {
    bool valid = true;
    string field;
    if(sortField == 1) {    //sort by ID number
        field = "student ID";
        for(int i = 0; i < 100; i++) {
            for(int j = i + 1; j < 100; j++) {
                if(studentID[i] > studentID[j]) {
                    for(int col = 0; col < 4; col++) {
                        double temp = testScores[j][col];
                        testScores[j][col] = testScores[i][col];
                        testScores[i][col] = temp;
                    }
                    
                    for(int col = 0; col < 2; col++) {
                        string temp2 = studentName[j][col];
                        studentName[j][col] = studentName[i][col];
                        studentName[i][col] = temp2;
                    }
                    
                    int temp3 = studentID[j];
                    studentID[j] = studentID[i];
                    studentID[i] = temp3;
                    
                    double temp4 = averageTestScores[j];
                    averageTestScores[j] = averageTestScores[i];
                    averageTestScores[i] = temp4;
                    
                    char temp5 = letterGrade[j];
                    letterGrade[j] = letterGrade[i];
                    letterGrade[i] = temp5;
                }
            }
        }
    }
    else if(sortField == 2) {   //sort by first name
        field = "first name";
        for(int i = 0; i < 100; i++) {
            for(int j = i + 1; j < 100; j++) {
                if(studentName[i][0] > studentName[j][0]) {
                    for(int col = 0; col < 4; col++) {
                        double temp = testScores[j][col];
                        testScores[j][col] = testScores[i][col];
                        testScores[i][col] = temp;
                    }
                    
                    for(int col = 0; col < 2; col++) {
                        string temp2 = studentName[j][col];
                        studentName[j][col] = studentName[i][col];
                        studentName[i][col] = temp2;
                    }
                    
                    int temp3 = studentID[j];
                    studentID[j] = studentID[i];
                    studentID[i] = temp3;
                    
                    double temp4 = averageTestScores[j];
                    averageTestScores[j] = averageTestScores[i];
                    averageTestScores[i] = temp4;
                    
                    char temp5 = letterGrade[j];
                    letterGrade[j] = letterGrade[i];
                    letterGrade[i] = temp5;
                }
                else if(studentName[i][0] == studentName[j][0]) {
                    if(averageTestScores[i] < averageTestScores[j]) {
                        for(int col = 0; col < 4; col++) {
                            double temp = testScores[j][col];
                            testScores[j][col] = testScores[i][col];
                            testScores[i][col] = temp;
                        }
                        
                        for(int col = 0; col < 2; col++) {
                            string temp2 = studentName[j][col];
                            studentName[j][col] = studentName[i][col];
                            studentName[i][col] = temp2;
                        }
                        
                        int temp3 = studentID[j];
                        studentID[j] = studentID[i];
                        studentID[i] = temp3;
                        
                        double temp4 = averageTestScores[j];
                        averageTestScores[j] = averageTestScores[i];
                        averageTestScores[i] = temp4;
                        
                        char temp5 = letterGrade[j];
                        letterGrade[j] = letterGrade[i];
                        letterGrade[i] = temp5;
                    }
                }
            }
        }
    }
    else if(sortField == 3) {   //sort by last name
        field = "last name";
        for(int i = 0; i < 100; i++) {
            for(int j = i + 1; j < 100; j++) {
                if(studentName[i][1] > studentName[j][1]) {
                    for(int col = 0; col < 4; col++) {
                        double temp = testScores[j][col];
                        testScores[j][col] = testScores[i][col];
                        testScores[i][col] = temp;
                    }
                    
                    for(int col = 0; col < 2; col++) {
                        string temp2 = studentName[j][col];
                        studentName[j][col] = studentName[i][col];
                        studentName[i][col] = temp2;
                    }
                    
                    int temp3 = studentID[j];
                    studentID[j] = studentID[i];
                    studentID[i] = temp3;
                    
                    double temp4 = averageTestScores[j];
                    averageTestScores[j] = averageTestScores[i];
                    averageTestScores[i] = temp4;
                    
                    char temp5 = letterGrade[j];
                    letterGrade[j] = letterGrade[i];
                    letterGrade[i] = temp5;
                }
            }
        }
    }
    else if(sortField == 4) {
        field = "first test score";
        for(int i = 0; i < 100; i++) {
            for(int j = i + 1; j < 100; j++) {
                if(testScores[i][0] > testScores[j][0]) {
                    for(int col = 0; col < 4; col++) {
                        double temp = testScores[j][col];
                        testScores[j][col] = testScores[i][col];
                        testScores[i][col] = temp;
                    }
                    
                    for(int col = 0; col < 2; col++) {
                        string temp2 = studentName[j][col];
                        studentName[j][col] = studentName[i][col];
                        studentName[i][col] = temp2;
                    }
                    
                    int temp3 = studentID[j];
                    studentID[j] = studentID[i];
                    studentID[i] = temp3;
                    
                    double temp4 = averageTestScores[j];
                    averageTestScores[j] = averageTestScores[i];
                    averageTestScores[i] = temp4;
                    
                    char temp5 = letterGrade[j];
                    letterGrade[j] = letterGrade[i];
                    letterGrade[i] = temp5;
                }
            }
        }
    }
    else if(sortField == 5) {
        field = "second test score";
        for(int i = 0; i < 100; i++) {
            for(int j = i + 1; j < 100; j++) {
                if(testScores[i][1] > testScores[j][1]) {
                    for(int col = 0; col < 4; col++) {
                        double temp = testScores[j][col];
                        testScores[j][col] = testScores[i][col];
                        testScores[i][col] = temp;
                    }
                    
                    for(int col = 0; col < 2; col++) {
                        string temp2 = studentName[j][col];
                        studentName[j][col] = studentName[i][col];
                        studentName[i][col] = temp2;
                    }
                    
                    int temp3 = studentID[j];
                    studentID[j] = studentID[i];
                    studentID[i] = temp3;
                    
                    double temp4 = averageTestScores[j];
                    averageTestScores[j] = averageTestScores[i];
                    averageTestScores[i] = temp4;
                    
                    char temp5 = letterGrade[j];
                    letterGrade[j] = letterGrade[i];
                    letterGrade[i] = temp5;
                }
            }
        }
    }
    else if(sortField == 6) {
        field = "third test score";
        for(int i = 0; i < 100; i++) {
            for(int j = i + 1; j < 100; j++) {
                if(testScores[i][2] > testScores[j][2]) {
                    for(int col = 0; col < 4; col++) {
                        double temp = testScores[j][col];
                        testScores[j][col] = testScores[i][col];
                        testScores[i][col] = temp;
                    }
                    
                    for(int col = 0; col < 2; col++) {
                        string temp2 = studentName[j][col];
                        studentName[j][col] = studentName[i][col];
                        studentName[i][col] = temp2;
                    }
                    
                    int temp3 = studentID[j];
                    studentID[j] = studentID[i];
                    studentID[i] = temp3;
                    
                    double temp4 = averageTestScores[j];
                    averageTestScores[j] = averageTestScores[i];
                    averageTestScores[i] = temp4;
                    
                    char temp5 = letterGrade[j];
                    letterGrade[j] = letterGrade[i];
                    letterGrade[i] = temp5;
                }
            }
        }
    }
    else if(sortField == 7) {
        field = "fourth test score";
        for(int i = 0; i < 100; i++) {
            for(int j = i + 1; j < 100; j++) {
                if(testScores[i][3] > testScores[j][3]) {
                    for(int col = 0; col < 4; col++) {
                        double temp = testScores[j][col];
                        testScores[j][col] = testScores[i][col];
                        testScores[i][col] = temp;
                    }
                    
                    for(int col = 0; col < 2; col++) {
                        string temp2 = studentName[j][col];
                        studentName[j][col] = studentName[i][col];
                        studentName[i][col] = temp2;
                    }
                    
                    int temp3 = studentID[j];
                    studentID[j] = studentID[i];
                    studentID[i] = temp3;
                    
                    double temp4 = averageTestScores[j];
                    averageTestScores[j] = averageTestScores[i];
                    averageTestScores[i] = temp4;
                    
                    char temp5 = letterGrade[j];
                    letterGrade[j] = letterGrade[i];
                    letterGrade[i] = temp5;
                }
            }
        }
    }
    else if(sortField == 8) {
        field = "average test score";
        for(int i = 0; i < 100; i++) {
            for(int j = i + 1; j < 100; j++) {
                if(averageTestScores[i] > averageTestScores[j]) {
                    for(int col = 0; col < 4; col++) {
                        double temp = testScores[j][col];
                        testScores[j][col] = testScores[i][col];
                        testScores[i][col] = temp;
                    }
                    
                    for(int col = 0; col < 2; col++) {
                        string temp2 = studentName[j][col];
                        studentName[j][col] = studentName[i][col];
                        studentName[i][col] = temp2;
                    }
                    
                    int temp3 = studentID[j];
                    studentID[j] = studentID[i];
                    studentID[i] = temp3;
                    
                    double temp4 = averageTestScores[j];
                    averageTestScores[j] = averageTestScores[i];
                    averageTestScores[i] = temp4;
                    
                    char temp5 = letterGrade[j];
                    letterGrade[j] = letterGrade[i];
                    letterGrade[i] = temp5;
                }
            }
        }
    }
    else if(sortField == 9) {
        field = "letter grade";
        for(int i = 0; i < 100; i++) {
            for(int j = i + 1; j < 100; j++) {
                if(letterGrade[i] > letterGrade[j]) {
                    for(int col = 0; col < 4; col++) {
                        double temp = testScores[j][col];
                        testScores[j][col] = testScores[i][col];
                        testScores[i][col] = temp;
                    }
                    
                    for(int col = 0; col < 2; col++) {
                        string temp2 = studentName[j][col];
                        studentName[j][col] = studentName[i][col];
                        studentName[i][col] = temp2;
                    }
                    
                    int temp3 = studentID[j];
                    studentID[j] = studentID[i];
                    studentID[i] = temp3;
                    
                    double temp4 = averageTestScores[j];
                    averageTestScores[j] = averageTestScores[i];
                    averageTestScores[i] = temp4;
                    
                    char temp5 = letterGrade[j];
                    letterGrade[j] = letterGrade[i];
                    letterGrade[i] = temp5;
                }
                else if(averageTestScores[i] > averageTestScores[j]) {
                    for(int col = 0; col < 4; col++) {
                        double temp = testScores[j][col];
                        testScores[j][col] = testScores[i][col];
                        testScores[i][col] = temp;
                    }
                    
                    for(int col = 0; col < 2; col++) {
                        string temp2 = studentName[j][col];
                        studentName[j][col] = studentName[i][col];
                        studentName[i][col] = temp2;
                    }
                    
                    int temp3 = studentID[j];
                    studentID[j] = studentID[i];
                    studentID[i] = temp3;
                    
                    double temp4 = averageTestScores[j];
                    averageTestScores[j] = averageTestScores[i];
                    averageTestScores[i] = temp4;
                    
                    char temp5 = letterGrade[j];
                    letterGrade[j] = letterGrade[i];
                    letterGrade[i] = temp5;
                }
            }
        }
    }
    else {
        cin.ignore(100, '\n');
        valid = false;
    }
    
    if(valid == true) {
        cout << "                                                                      Test     Course" << endl;
        cout << " Student ID   Firstname   Lastname    Test 1  Test 2  Test 3  Test 4  Average  Grade " << endl;
        cout << "------------  ----------  ----------  ------  ------  ------  ------  -------  ------" << endl;
        
        for(int row = 0; row < 100; row++) {
            if(studentID[row] >= IDmin && studentID[row] <= IDmax) {
                if(studentID[row] != -1) {
                    cout << setfill(' ') << setw(12) << right << studentID[row] << "  ";
                    for(int col = 0; col < 2; col++) {
                        string name = studentName[row][col];
                        name = name.substr(0, 10);
                        cout << setfill(' ') << setw(10) << left << name << "  ";
                    }
                    for(int col = 0; col < 4; col++) {
                        cout << setfill(' ') << setw(6) << right << fixed << setprecision(1) << testScores[row][col] << "  ";
                    }
                    cout << setfill(' ') << setw(7) << right << fixed << setprecision(2) << averageTestScores[row] << "  ";
                    cout << setfill(' ') << setw(4) << right << letterGrade[row] << endl;
                }
            }
        }
        cout << "*************************************************************************************" << endl;
        return;
    }
    else {
        
        cout << "Print record failed - Invalid field or direction" << endl;
        cout << "*************************************************************************************" << endl;
    }
}

//print range of students in descending order
void printRangeDescending(int IDmin, int IDmax, int sortField) {
    bool valid = true;
    string field;
    if(sortField == 1) {    //sort by ID number
        field = "student ID";
        for(int i = 0; i < 100; i++) {
            for(int j = i + 1; j < 100; j++) {
                if(studentID[i] < studentID[j]) {
                    for(int col = 0; col < 4; col++) {
                        double temp = testScores[j][col];
                        testScores[j][col] = testScores[i][col];
                        testScores[i][col] = temp;
                    }
                    
                    for(int col = 0; col < 2; col++) {
                        string temp2 = studentName[j][col];
                        studentName[j][col] = studentName[i][col];
                        studentName[i][col] = temp2;
                    }
                    
                    int temp3 = studentID[j];
                    studentID[j] = studentID[i];
                    studentID[i] = temp3;
                    
                    double temp4 = averageTestScores[j];
                    averageTestScores[j] = averageTestScores[i];
                    averageTestScores[i] = temp4;
                    
                    char temp5 = letterGrade[j];
                    letterGrade[j] = letterGrade[i];
                    letterGrade[i] = temp5;
                }
            }
        }
    }
    else if(sortField == 2) {   //sort by first name
        field = "first name";
        for(int i = 0; i < 100; i++) {
            for(int j = i + 1; j < 100; j++) {
                if(studentName[i][0] < studentName[j][0]) {
                    for(int col = 0; col < 4; col++) {
                        double temp = testScores[j][col];
                        testScores[j][col] = testScores[i][col];
                        testScores[i][col] = temp;
                    }
                    
                    for(int col = 0; col < 2; col++) {
                        string temp2 = studentName[j][col];
                        studentName[j][col] = studentName[i][col];
                        studentName[i][col] = temp2;
                    }
                    
                    int temp3 = studentID[j];
                    studentID[j] = studentID[i];
                    studentID[i] = temp3;
                    
                    double temp4 = averageTestScores[j];
                    averageTestScores[j] = averageTestScores[i];
                    averageTestScores[i] = temp4;
                    
                    char temp5 = letterGrade[j];
                    letterGrade[j] = letterGrade[i];
                    letterGrade[i] = temp5;
                }
            }
        }
    }
    else if(sortField == 3) {   //sort by last name
        field = "last name";
        for(int i = 0; i < 100; i++) {
            for(int j = i + 1; j < 100; j++) {
                if(studentName[i][1] < studentName[j][1]) {
                    for(int col = 0; col < 4; col++) {
                        double temp = testScores[j][col];
                        testScores[j][col] = testScores[i][col];
                        testScores[i][col] = temp;
                    }
                    
                    for(int col = 0; col < 2; col++) {
                        string temp2 = studentName[j][col];
                        studentName[j][col] = studentName[i][col];
                        studentName[i][col] = temp2;
                    }
                    
                    int temp3 = studentID[j];
                    studentID[j] = studentID[i];
                    studentID[i] = temp3;
                    
                    double temp4 = averageTestScores[j];
                    averageTestScores[j] = averageTestScores[i];
                    averageTestScores[i] = temp4;
                    
                    char temp5 = letterGrade[j];
                    letterGrade[j] = letterGrade[i];
                    letterGrade[i] = temp5;
                }
            }
        }
    }
    else if(sortField == 4) {
        field = "first test score";
        for(int i = 0; i < 100; i++) {
            for(int j = i + 1; j < 100; j++) {
                if(testScores[i][0] < testScores[j][0]) {
                    for(int col = 0; col < 4; col++) {
                        double temp = testScores[j][col];
                        testScores[j][col] = testScores[i][col];
                        testScores[i][col] = temp;
                    }
                    
                    for(int col = 0; col < 2; col++) {
                        string temp2 = studentName[j][col];
                        studentName[j][col] = studentName[i][col];
                        studentName[i][col] = temp2;
                    }
                    
                    int temp3 = studentID[j];
                    studentID[j] = studentID[i];
                    studentID[i] = temp3;
                    
                    double temp4 = averageTestScores[j];
                    averageTestScores[j] = averageTestScores[i];
                    averageTestScores[i] = temp4;
                    
                    char temp5 = letterGrade[j];
                    letterGrade[j] = letterGrade[i];
                    letterGrade[i] = temp5;
                }
            }
        }
    }
    else if(sortField == 5) {
        field = "second test score";
        for(int i = 0; i < 100; i++) {
            for(int j = i + 1; j < 100; j++) {
                if(testScores[i][1] < testScores[j][1]) {
                    for(int col = 0; col < 4; col++) {
                        double temp = testScores[j][col];
                        testScores[j][col] = testScores[i][col];
                        testScores[i][col] = temp;
                    }
                    
                    for(int col = 0; col < 2; col++) {
                        string temp2 = studentName[j][col];
                        studentName[j][col] = studentName[i][col];
                        studentName[i][col] = temp2;
                    }
                    
                    int temp3 = studentID[j];
                    studentID[j] = studentID[i];
                    studentID[i] = temp3;
                    
                    double temp4 = averageTestScores[j];
                    averageTestScores[j] = averageTestScores[i];
                    averageTestScores[i] = temp4;
                    
                    char temp5 = letterGrade[j];
                    letterGrade[j] = letterGrade[i];
                    letterGrade[i] = temp5;
                }
            }
        }
    }
    else if(sortField == 6) {
        field = "third test score";
        for(int i = 0; i < 100; i++) {
            for(int j = i + 1; j < 100; j++) {
                if(testScores[i][2] < testScores[j][2]) {
                    for(int col = 0; col < 4; col++) {
                        double temp = testScores[j][col];
                        testScores[j][col] = testScores[i][col];
                        testScores[i][col] = temp;
                    }
                    
                    for(int col = 0; col < 2; col++) {
                        string temp2 = studentName[j][col];
                        studentName[j][col] = studentName[i][col];
                        studentName[i][col] = temp2;
                    }
                    
                    int temp3 = studentID[j];
                    studentID[j] = studentID[i];
                    studentID[i] = temp3;
                    
                    double temp4 = averageTestScores[j];
                    averageTestScores[j] = averageTestScores[i];
                    averageTestScores[i] = temp4;
                    
                    char temp5 = letterGrade[j];
                    letterGrade[j] = letterGrade[i];
                    letterGrade[i] = temp5;
                }
            }
        }
    }
    else if(sortField == 7) {
        field = "fourth test score";
        for(int i = 0; i < 100; i++) {
            for(int j = i + 1; j < 100; j++) {
                if(testScores[i][3] < testScores[j][3]) {
                    for(int col = 0; col < 4; col++) {
                        double temp = testScores[j][col];
                        testScores[j][col] = testScores[i][col];
                        testScores[i][col] = temp;
                    }
                    
                    for(int col = 0; col < 2; col++) {
                        string temp2 = studentName[j][col];
                        studentName[j][col] = studentName[i][col];
                        studentName[i][col] = temp2;
                    }
                    
                    int temp3 = studentID[j];
                    studentID[j] = studentID[i];
                    studentID[i] = temp3;
                    
                    double temp4 = averageTestScores[j];
                    averageTestScores[j] = averageTestScores[i];
                    averageTestScores[i] = temp4;
                    
                    char temp5 = letterGrade[j];
                    letterGrade[j] = letterGrade[i];
                    letterGrade[i] = temp5;
                }
            }
        }
    }
    else if(sortField == 8) {
        field = "average test score";
        for(int i = 0; i < 100; i++) {
            for(int j = i + 1; j < 100; j++) {
                if(averageTestScores[i] < averageTestScores[j]) {
                    for(int col = 0; col < 4; col++) {
                        double temp = testScores[j][col];
                        testScores[j][col] = testScores[i][col];
                        testScores[i][col] = temp;
                    }
                    
                    for(int col = 0; col < 2; col++) {
                        string temp2 = studentName[j][col];
                        studentName[j][col] = studentName[i][col];
                        studentName[i][col] = temp2;
                    }
                    
                    int temp3 = studentID[j];
                    studentID[j] = studentID[i];
                    studentID[i] = temp3;
                    
                    double temp4 = averageTestScores[j];
                    averageTestScores[j] = averageTestScores[i];
                    averageTestScores[i] = temp4;
                    
                    char temp5 = letterGrade[j];
                    letterGrade[j] = letterGrade[i];
                    letterGrade[i] = temp5;
                }
            }
        }
    }
    else if(sortField == 9) {
        field = "letter grade";
        for(int i = 0; i < 100; i++) {
            for(int j = i + 1; j < 100; j++) {
                if(letterGrade[i] < letterGrade[j]) {
                    for(int col = 0; col < 4; col++) {
                        double temp = testScores[j][col];
                        testScores[j][col] = testScores[i][col];
                        testScores[i][col] = temp;
                    }
                    
                    for(int col = 0; col < 2; col++) {
                        string temp2 = studentName[j][col];
                        studentName[j][col] = studentName[i][col];
                        studentName[i][col] = temp2;
                    }
                    
                    int temp3 = studentID[j];
                    studentID[j] = studentID[i];
                    studentID[i] = temp3;
                    
                    double temp4 = averageTestScores[j];
                    averageTestScores[j] = averageTestScores[i];
                    averageTestScores[i] = temp4;
                    
                    char temp5 = letterGrade[j];
                    letterGrade[j] = letterGrade[i];
                    letterGrade[i] = temp5;
                }
            }
        }
    }
    else {
        cin.ignore(100, '\n');
        valid = false;
    }
    
    if(valid == true) {
        cout << "                                                                      Test     Course" << endl;
        cout << " Student ID   Firstname   Lastname    Test 1  Test 2  Test 3  Test 4  Average  Grade " << endl;
        cout << "------------  ----------  ----------  ------  ------  ------  ------  -------  ------" << endl;
       
        for(int row = 0; row < 100; row++) {
            if(studentID[row] >= IDmin && studentID[row] <= IDmax) {
                if(studentID[row] != -1) {
                    cout << setfill(' ') << setw(12) << right << studentID[row] << "  ";
                    for(int col = 0; col < 2; col++) {
                        string name = studentName[row][col];
                        name = name.substr(0, 10);
                        cout << setfill(' ') << setw(10) << left << name << "  ";
                    }
                    for(int col = 0; col < 4; col++) {
                        cout << setfill(' ') << setw(6) << right << fixed << setprecision(1) << testScores[row][col] << "  ";
                    }
                    cout << setfill(' ') << setw(7) << right << fixed << setprecision(2) << averageTestScores[row] << "  ";
                    cout << setfill(' ') << setw(4) << right << letterGrade[row] << endl;
                }
            }
        }
        cout << "*************************************************************************************" << endl;
        return;
    }
    else {
        cout << "Print record failed - Invalid field or direction" << endl;
        cout << "*************************************************************************************" << endl;
    }
}


void executePrintCommand() {
    char command;
    cin >> command;
    
    //if command A, print all
    if(command == 'A'|| command == 'a') {
        int sortField;
        cin >> sortField;
        
        char fieldDirection;
        cin >> fieldDirection;
        
        //if command "A", print in ascending order
        if(fieldDirection == 'A' || fieldDirection == 'a') {
            printAllAscending(sortField);
        }
        //if command "D", print in descending order
        else if(fieldDirection == 'D' || fieldDirection == 'd') {
            printAllDescending(sortField);
        }
        //if command invalid, display error
        else {
            cout << "Print all records failed - Invalid field or direction" << endl;
            cout << "*************************************************************************************" << endl;
        }
    }
    //if command "R", print range of students
    else if(command == 'R' || command == 'r') {
        int IDmin;
        cin >> IDmin;
        int IDmax;
        cin >> IDmax;
        
        int sortField;
        cin >> sortField;
        
        char fieldDirection;
        cin >> fieldDirection;
        
        //if command "A", print in ascending order
        if(fieldDirection == 'A' || fieldDirection == 'a') {
            printRangeAscending(IDmin, IDmax, sortField);
        }
        //if command "D", print in descending order
        else if(fieldDirection == 'D' || fieldDirection == 'd') {
            printRangeDescending(IDmin, IDmax, sortField);
        }
        //show error if invalid command
        else {
            cout << "Print record failed - Invalid field or direction" << endl;
            cout << "*************************************************************************************" << endl;
            return;
        }
    }
    //if command "S", print single record
    else if(command == 'S' || command == 's') {
        int ID;
        cin >> ID;
        
        //if student ID matches desired ID, print record
        for(int row = 0; row < 100; row++) {
            if(studentID[row] == ID) {
                cout << "                                                                      Test     Course" << endl;
                cout << " Student ID   Firstname   Lastname    Test 1  Test 2  Test 3  Test 4  Average  Grade " << endl;
                cout << "------------  ----------  ----------  ------  ------  ------  ------  -------  ------" << endl;
                cout << setfill(' ') << setw(12) << right << studentID[row] << "  ";
                for(int col = 0; col < 2; col++) {
                    string name = studentName[row][col];
                    name = name.substr(0, 10);
                    cout << setfill(' ') << setw(10) << left << name << "  ";
                }
                for(int col = 0; col < 4; col++) {
                    cout << setfill(' ') << setw(6) << right << fixed << setprecision(1) << testScores[row][col] << "  ";
                }
                cout << setfill(' ') << setw(7) << right << fixed << setprecision(2) << averageTestScores[row] << "  ";
                cout << setfill(' ') << setw(4) << right << letterGrade[row] << endl;
                cout << "*************************************************************************************" << endl;
                return;
            }
        }
        cout << "Print record failed - Could not find ID " << ID << endl;
        cout << "*************************************************************************************" << endl;
    }
    else {
        cin.ignore(100, '\n');
        cout << "Print failed - invalid action " << command << endl;
        cout << "*************************************************************************************" << endl;
    }
}

int main() {
  
    header();
    
    initializeArrays();
    
    char command = ' ';
    bool completed = false;
    bool changesMade = false;
    while(completed == false) {
        cin >> command;
        
        //invoke read command
        if(command == 'R' || command == 'r') {
            changesMade = true;
            executeReadCommand();
            cin.ignore(100, '\n');

        }
        //invoke write command
        else if(command == 'W' || command == 'w') {
            changesMade = false;
            executeWriteCommand();
            cin.ignore(100, '\n');
        }
        //invoke add command
        else if(command == 'A' || command == 'a') {
            changesMade = true;
            executeAddCommand();
            cin.ignore(100, '\n');

        }
        //invoke delete command
        else if(command == 'D' || command == 'd') {
            changesMade = true;
            executeDeleteCommand();
            cin.ignore(100, '\n');

        }
        //invoke update command
        else if(command == 'U' || command == 'u') {
            changesMade = true;
            executeUpdateCommand();
        }
        //invoke print command
        else if(command == 'P' || command == 'p') {
            executePrintCommand();
        }
        //quit program
        else if(command == 'Q' || command == 'q') {
           
                //if changes have been made to output file, write a new one
                if(changesMade == true) {
                string outputFile = "dBase4.txt";
                ofstream outFile;
                outFile.open(outputFile);
                if(outFile.good()) {
                    
                    //sort ascending by ID number
                    for(int i = 0; i < 100; i++) {
                        for(int j = i + 1; j < 100; j++) {
                            if(studentID[i] > studentID[j]) {
                                for(int col = 0; col < 4; col++) {
                                    double temp = testScores[j][col];
                                    testScores[j][col] = testScores[i][col];
                                    testScores[i][col] = temp;
                                }
                                
                                for(int col = 0; col < 2; col++) {
                                    string temp2 = studentName[j][col];
                                    studentName[j][col] = studentName[i][col];
                                    studentName[i][col] = temp2;
                                }
                                
                                int temp3 = studentID[j];
                                studentID[j] = studentID[i];
                                studentID[i] = temp3;
                            }
                        }
                    }
                    
                    //write data to output file
                    for(int row = 0; row < 100; row++) {
                        if(studentID[row] != -1) {
                            outFile << studentID[row] << endl;
                            for(int col = 0; col < 2; col++) {
                                if(col == 1) {
                                     outFile << studentName[row][col];
                                }
                                else {
                                     outFile << studentName[row][col] << " ";
                                }
                            }
                            outFile << endl;
                            for(int col = 0; col < 4; col++) {
                                if(col == 3) {
                                    outFile << setprecision(1) << fixed << testScores[row][col];
                                }
                                else {
                                     outFile << setprecision(1) << fixed << testScores[row][col] << " ";
                                }
                            }
                            outFile << endl;
                        }
                    }
                }
                cout << "Unsaved data - writing data to file: dBase4.txt" << endl;
            }
            //print if no unsaved data
            else {
                cout << "No unsaved data" << endl;
            }
            //quit program
            cout << "Quitting Program!" << endl;
            cout << "*************************************************************************************" << endl;
            cout << endl;
            completed = true;
        }
        //display error if unrecognized command
        else {
            cin.ignore(100, '\n');
            cout << "Unrecognized command " << command << endl;
            cout << "*************************************************************************************" << endl;
        }
    }
    
    //end program
    footer();
    return 0;
}
