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
#include <iomanip>
using namespace std;

double weightedGPA (double hr, double gpa, int& cnt, double grd);

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
					ostrDataPlus << "\t" << hours << "\t" << desigCode << endl;
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
				hours = 3.;
				desigCode = "RNL";
				ostrDataPlus << "\t" << hours << "\t" << desigCode << endl;
			}
		} 
		istrStudent.close();
		istrCourse.close();
		ostrDataPlus.close();
	}

	istrDataPlus.open("StudentDataPlus.tsv");
	ostrSummary.open("StudentSummary.tsv");

	ostrSummary.setf(ios::fixed);
	ostrSummary.setf(ios::showpoint);
	ostrSummary.precision(2);

	if (istrDataPlus.fail() || ostrSummary.fail())
	{
		cout << "Failed to open file.";
		exit(1);
	}

	int emplID1, emplID2, semester1, semester2;
	double numGrade2, hours1 = 0., hours2;
	string desigCode2, letterGrade2;

	istrDataPlus >> emplID1 >> semester1 >> subjectCode1 >> catCode1 >> letterGrade >> numGrade
		>> hours1 >> desigCode;

	int count1 = 1, gpacount = 0, cscount = 0;
        double gpaSum = 0., gpa = 0., csciGpaSum = 0., csciGpa = 0., nonLibPercent = 0., nonLibCount = 0.;

	while (istrDataPlus.eof() == 0)
	{
		istrDataPlus >> emplID2 >> semester2 >> subjectCode2 >> catCode2 >> letterGrade2 >> numGrade2
			>> hours2 >> desigCode2;
	
        /*	if (count1 == 1)
		{
			if (numGrade > 0.)
			{
				gpa = weightedGPA (hours1, gpa, gpacount, numGrade);
                                //gpa = numGrade;
				//gpaSum = numGrade;
				//gpacount++;
			}
			if (subjectCode1 == "CSCI" && numGrade > 0)
			{
				csciGpa = numGrade;
				csciGpaSum = numGrade;
				cscount++;
			}
			if (desigCode == "RNL" || desigCode == "MNL" || desigCode == "GNL")
			{
				nonLibPercent = 1.0;
				nonLibCount++;
			}

			if (emplID1 != emplID2)
			{
				ostrSummary << emplID1 << "\t" << gpa << "\t" << csciGpa << "\t" << nonLibPercent << endl;
				count1 = 1;
				cscount = 0;
				nonLibCount = 0;
				gpacount = 0;
				gpa = 0.;
				gpaSum = 0.;
				csciGpa = 0.;
				csciGpaSum = 0.;
			}
			else
			{
				count1++;
			}
			emplID1 = emplID2;
			semester1 = semester2;
			subjectCode1 = subjectCode2;
			catCode1 = catCode2;
			letterGrade = letterGrade2;
			numGrade = numGrade2;
			hours1 = hours2;
			desigCode = desigCode2;
		}
		else
		{ */
			if (numGrade > 0.)
			{
				// gpacount++;
				gpaSum += weightedGPA(hours1, gpa, gpacount, numGrade);
			}
			if (subjectCode1 == "CSCI" && numGrade > 0.)
			{
			//	cscount++;
				csciGpaSum += weightedGPA(hours1, csciGpa, cscount, numGrade);
			}
			if (desigCode == "RNL" || desigCode == "MNL" || desigCode == "GNL")
			{
				nonLibCount++;
			}
			if (emplID1 != emplID2)
			{
				gpa = gpaSum / gpacount;
				csciGpa = csciGpaSum / cscount;
				nonLibPercent = nonLibCount / count1;

				ostrSummary << emplID1 << "\t" << gpa << "\t" << csciGpa << "\t" << nonLibPercent << endl;

				count1 = 1;
				cscount = 0;
				nonLibCount = 0;
				gpacount = 0;
				gpa = 0.;
				gpaSum = 0.;
				csciGpa = 0.;
				csciGpaSum = 0.;
			}
			else
			{
				count1++;
			}
	//	}
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

	return 0;
}

double weightedGPA (double hours, double gpa, int& count, double grade)
{
        for (int i = 1; i <= hours; i++)
        {
                count++;
                gpa += grade;
        }
        return gpa;
}
