#ifndef _FUNCTION_H_
#define _FUNCTION_H_
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include<Windows.h>
#include <stdio.h>
#include <iomanip>

using namespace std;

#define ColorCode_Back			0
#define ColorCode_DarkBlue		1
#define ColorCode_DarkGreen		2
#define ColorCode_DarkCyan		3
#define ColorCode_DarkRed		4
#define ColorCode_DarkPink		5
#define ColorCode_DarkYellow	6
#define ColorCode_DarkWhite		7
#define ColorCode_Grey			8
#define ColorCode_Blue			9
#define ColorCode_Green			10
#define ColorCode_Cyan			11
#define ColorCode_Red			12
#define ColorCode_Pink			13
#define ColorCode_Yellow		14
#define ColorCode_White			15

#define default_ColorCode		7


#define key_Up		72
#define key_Down	80
#define key_Left	75
#define key_Right	77
#define key_none	-1

//--------------------------------------------------------

#include <windows.h>
int inputKey();

//--------------------------------------------------------

//-------------------------Screen-------------------------
void clrscr();

//screen: goto [x,y]
void gotoXY(int column, int line);

void TextColor(int color);
//end----------------------Screen----------------------end
void Menu(string &username);
void MenuStudent(string &username);
void MenuLecturer(string &username);
//class
void MenuClassAdmin(string &username);
void MenuCourseAdmin(string &username);
void MenuSemester(string &nameyear, string &username);
void MenuCourse(string &nameyear, string &namesemester, string &username);
void OperationCourse(string &nameyear, string &namesemester, string &username);
void MoveMouse(int key, int &x, int &y, int upperlimit, int downlimit);
void MoveAndEdit(int key, int &x, int &y, int &i, int &leftlimit, int &rightlimit, int &upperlimitleft, int &downlimitleft, int &upperlimitright, int &downlimitright);
struct Course
{
	string No;
	string ID;
	string Name;
	string Class;
	string LecturerAcc;
	string LectureName;
	string StartDate;
	string EndDate;
	string DayofWeek;
	string StartHour;
	string EndHour;
	string Room;
	Course* pNext;
};
struct CourseList
{
	Course* pHead = nullptr;
	Course* pTail = nullptr;
};
struct scoreboard
{
	string No;
	string ID;
	string mid;
	string Final;
	string bonus;
	string aveg;
	scoreboard* pNext;
};
struct ScoreBoardList
{
	scoreboard* pHead = nullptr;
	scoreboard* pTail = nullptr;
};
struct student
{
	string No;
	string ID;
	string Lastname;
	string Firstname;
	string Gender;
	string DoB;
	string classname;
	student* pNext;
};
struct StudentList
{
	student* pHead = nullptr;
	student* pTail = nullptr;
};
struct AccountStudent
{
	string ID;
	string DoB;
	AccountStudent* pNext;
};
struct AccountStudentList
{
	AccountStudent* pHead = nullptr;
	AccountStudent* pTail = nullptr;
};
struct AccountLecturer
{
	string lecturer_account;
	string password;
	AccountLecturer* pNext;
};
struct AccountLecturerList
{
	AccountLecturer* pHead = nullptr;
	AccountLecturer* pTail = nullptr;
};
struct Classes
{
	string name;
	Classes* pNext;
};
struct ClassList
{
	Classes* pHead = nullptr;
	Classes* pTail = nullptr;
};
struct year
{
	string name;
	year* pNext;
};
struct YearList
{
	year* pHead = nullptr;
	year* pTail = nullptr;
};
struct Semester
{
	string name;
	Semester* pNext;
};
struct SemesterList
{
	Semester* pHead = nullptr;
	Semester* pTail = nullptr;
};
void loadYear(string &namefile, YearList &ylst);
void loadSemester(string &namefile, SemesterList &selst);
void loadClass(string &namefile, ClassList &clst);
void loadStudent(string &namefile, StudentList &slst);
void loadAccountStudent(AccountStudentList &acslst);
void loadAccountLecturer(AccountLecturerList &lecslst);
void loadScoreboard(string &filename, ScoreBoardList &sclst);
void loadCourse(string &namefile, CourseList &colst);
int LengthofStudenlist(StudentList &slst);
int LengthofScoreBoardlist(ScoreBoardList &sclst);
int LengthofClasslist(ClassList &clst);
int LengthofSemeterlist(SemesterList &selst);
int LengthofYearlist(YearList &ylst);
int LengthofCourselist(CourseList &colst);
void login(string &username);
void changePassAdmin(string username);
void changePassStudent(string username);
void changePassLecturer(string username);
void importStudent(string &namefile);
void importCourses(string &nameyear, string &namesemester);
void importScoreboard(string &courseID, string &classname);
void exportScoreboard(string &courseID, string &classname);
bool SavetoListofClass(string namefile);
bool SaveStudent(string &namefile, int n, StudentList &slst);
bool SaveClass(string &namefile, ClassList &clst);
bool SaveYear(string &namefile, YearList &ylst);
bool SaveSemester(string &namefile, SemesterList &selst);
bool SaveScoreboard(string &namefile, int n, ScoreBoardList &sclst);
bool SaveCourse(string &namefile, int n, CourseList &colst);
bool SaveAccountStudent(AccountStudentList &aclst);
void RemoveYear(YearList &ylst);
void RemoveSemester(SemesterList &selst);
void RemoveClass(ClassList &clst);
void RemoveStudent(StudentList &slst);
void RemoveAccountStudent(AccountStudentList &acslst);
void RemoveAccountLecturer(AccountLecturerList &lecslst);
void RemoveCourse(CourseList &colst);
void RemoveScoreboard(ScoreBoardList &sclst);
bool AddAccountStudent(string &id, string &dob);
bool AddAccountLeturer(string &account, string &password);
bool CreatNewScoreBoard(string &namefile, int n);
string CalculateAverage(string &mid, string &final, string &bonus, string &average);
void UpdateClassofCourse(string &ID, string &newID, string &Lastname, string &Firstname, string &Gender, string &DoB, string &classname);
void AddStudenttoClassofCourse(string &ID, string &Lastname, string &Firstname, string &Gender, string &DoB, string &classname);
void RemoveStudentInClassofCourse(string &ID, string &classname);
void ChangeStudentInClassofCourse(string &ID, string &Lastname, string &Firstname, string &Gender, string &DoB, string &classname1, string &classname2);
#endif