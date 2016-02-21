#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{

  int emplID, semester;
  double numGrade, hours;
  string subjectCode1, subjectCode2, catCode1, catCode2, letterGrade, desigCode;
  ifstream istrStudent, istrCourse;
  ofstream ostrDataPlus, ostrSummary;

  istrStudent.open("StudentData.tsv");
  istrCourse.open("HunterCourses.tsv");
  ostrDataPlus.open("StudentDataPlus.tsv");
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
      ostrDataPlus << emplID << "\t" << semester << "\t" << subjectCode1 << "\t" << catCode1 << "\t" << letterGrade << "\t" << numGrade; // assigns one record's worth of input to vars

      istrCourse.clear();          // Goes to beginning of HunterCourses.tsv file to search
      istrCourse.seekg(ios::beg);
      //istrCourse >> subjectCode2 >> catCode2 >> hours >> desigCode; // assigns one record's worth of input to vars
      
      bool foundFlag = true;
      while (istrCourse.eof() == 0) 
      {  
        istrCourse >> subjectCode2 >> catCode2 >> hours >> desigCode;
 
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
      if (foundFlag == false)
      {
        hours = 3.0;
        desigCode = "RNL";
        ostrDataPlus << "\t" << hours << "\t" << desigCode << endl;
      }
    } 
    istrStudent.close();
    istrCourse.close();
    ostrDataPlus.close();
  }

return 0;
}
