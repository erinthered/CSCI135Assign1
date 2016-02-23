/*
Author: Erin Williams
Course: 135
Instructor: Subash Shankar
Assignment: Assignment #1

This program merges two files, one containing student data and one containing
course data, into a single file called StudentDataPlus.tsv. It summerizes the 
data in the merged StudentDataPlus.tsv file in a second new file, StudentSummary.tsv. 
*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//void tester (string idCode);
//void switch1and2();

int main()
{
  // Variables for input from two files to be merged
  int emplID, semester;
  double numGrade, hours;
  string subjectCode1, subjectCode2, catCode1, catCode2, letterGrade, desigCode;
  
  // Creates input and output streams to merge files
  ifstream istrStudent, istrCourse, istrDataPlus;
  ofstream ostrDataPlus, ostrSummary;

  // Associates input and output streams with file to write from and to.
  istrStudent.open("StudentData.tsv");
  istrCourse.open("HunterCourses.tsv");
  ostrDataPlus.open("StudentDataPlus.tsv");
 
  // Error checking to make sure that file opening did not fail.
  if (istrStudent.fail() || ostrDataPlus.fail() || istrCourse.fail())
  {
    cout << "Failed to open file.\n";
    exit(1);
  }
  else
  {
    // searches through Student Data File and adds information line by line to Student Data Plus file
    while (istrStudent.eof() == 0)
    {
      istrStudent >> emplID >> semester >> subjectCode1 >> catCode1 >> letterGrade >> numGrade;
      ostrDataPlus << emplID << "\t" << semester << "\t" << subjectCode1 << "\t" << catCode1 << "\t" << letterGrade << "\t" << numGrade << "\t";

      istrCourse.clear();          // Goes to beginning of HunterCourses.tsv file to search
      istrCourse.seekg(ios::beg);
      
      // Boolean variable to determine if match was found for course code and catalog code in HunterCourses.tsv.
      bool foundFlag = true;

      // Searches HunterCourses.tsv for matching fields subject and catalog code and merges with student data if found.
      while (istrCourse.eof() == 0) 
      {  
        istrCourse >> subjectCode2 >> catCode2 >> hours >> desigCode;
 
        // Match is found.
        if (subjectCode1 == subjectCode2 && catCode1 == catCode2)
        {
          ostrDataPlus << "\t" << hours << "\t" << desigCode << "\t";
          foundFlag = true;
          break;
        }
        else
        {
          foundFlag = false;
        }
      }
      // Match is not found.
      if (foundFlag == false)
      {
        hours = 3.0;
        desigCode = "RNL";
        ostrDataPlus << "\t" << hours << "\t" << desigCode << "\t";
      }
    } 
    istrStudent.close();
    istrCourse.close();
    ostrDataPlus.close();
  }
  
  istrDataPlus.open("StudentDataPlus.tsv");
  ostrSummary.open("StudentSummary.tsv");

  if (istrDataPlus.fail())
  {
    cout << "Failed to open file. Message 2.\n";
    exit(1);
  }
  else if (ostrSummary.fail())
  {
    cout << "FAIL 3.\n";
    exit(1);
  }

  int emplID1, emplID2, semester2, count1 = 1, cscount = 0, nonLibCount = 0;
  float numGrade2, hours2, gpa, csciGpa, nonLibPercent;
  string desigCode2, letterGrade2;
  
  ofstream testStream;
  testStream.open("testfile.tsv"); 
     
  istrDataPlus >> emplID1 >> semester >> subjectCode1 >> catCode1 >> letterGrade >> numGrade
               >> hours >> desigCode;

  while (istrDataPlus.eof() == 0)
  {
    istrDataPlus >> emplID2 >> semester2 >> subjectCode2 >> catCode2 >> letterGrade2 >> numGrade2
                 >> hours2 >> desigCode2;
    if (count1 == 1)
    {
      if (numGrade < 0)
      {
        numGrade = 0;
      }
      else
      {
        numGrade = gpa;
      }
      if (subjectCode1 == "CSCI")
      {
        csciGpa = numGrade;
        cscount++;
      }
      else
      {
        csciGpa = 0;
      }
      if (desigCode == "RNL" || desigCode == "MNL" || desigCode == "GNL")
      {
        nonLibPercent = 1.0;
        nonLibCount++;
      }
      else
      {
        nonLibPercent = 0;
      }
      if (emplID1 != emplID2)
      {
        ostrSummary << emplID1 << "\t" << gpa << "\t" << csciGpa << "\t" << nonLibPercent << "\t";
        count1 = 1;
        cscount = 0;
        nonLibCount = 0;
      }
      else
      {
         count1++;
      }
      emplID1 = emplID2;
      semester = semester2;
      subjectCode1 = subjectCode2;
      catCode1 = catCode2;
      letterGrade = letterGrade2;
      numGrade = numGrade2;
      hours = hours2;
      desigCode = desigCode2;
    }
    else
    {
      if (numGrade < 0)
      {
        numGrade = 0;
        gpa = (gpa + numGrade)/count1;
      }
      else
      {
      gpa = (gpa + numGrade)/count1;
      }
      if (subjectCode1 == "CSCI")
      {
        cscount++;
        csciGpa = (csciGpa + numGrade)/cscount;
      }
      if (desigCode == "RNL" || desigCode == "MNL" || desigCode == "GNL")
      {
        nonLibPercent = nonLibCount/count1;
        nonLibCount++;
      }
      if (emplID1 != emplID2)
      {
        ostrSummary << emplID1 << "\t" << gpa << "\t" << csciGpa << "\t" << nonLibPercent << "\t";
        count1 = 1;
        cscount = 0;
        nonLibCount = 0;
      }
      else
      {
        count1++;
      }
    }
    emplID1 = emplID2;
    semester = semester2;
    subjectCode1 = subjectCode2;
    catCode1 = catCode2;
    letterGrade = letterGrade2;
    numGrade = numGrade2;
    hours = hours2;
    desigCode = desigCode2;  
  }  
  istrDataPlus.close();
  ostrSummary.close();
  testStream.close();

  return 0;
}


       
