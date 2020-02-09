#include <stdio.h>
#include <conio.h>
#include"project.h"




//-------------------------Screen-------------------------
void clrscr()
{
	CONSOLE_SCREEN_BUFFER_INFO	csbiInfo;
	HANDLE	hConsoleOut;
	COORD	Home = { 0,0 };
	DWORD	dummy;

	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);

	FillConsoleOutputCharacter(hConsoleOut, ' ', csbiInfo.dwSize.X * csbiInfo.dwSize.Y, Home, &dummy);
	csbiInfo.dwCursorPosition.X = 0;
	csbiInfo.dwCursorPosition.Y = 0;
	SetConsoleCursorPosition(hConsoleOut, csbiInfo.dwCursorPosition);
}
int inputKey()
{
	if (_kbhit())
	{
		int key = _getch();

		/*if (key == 224)	// special key
		{
			key = _getch();
			return key + 1000;
		}*/

		return key;//+1000;
	}
	else
	{
		return key_none;
	}

	return key_none;
}

//screen: goto [x,y]
void gotoXY(int column, int line)
{
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void TextColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
void MoveMouse(int key, int &x, int &y, int upperlimit, int downlimit)
{
	if (key == key_Down && y < upperlimit)
	{
		y += 4;
	}
	if (key == key_Up && y > downlimit)
	{
		y -= 4;
	}
}

void MoveAndEdit(int key, int &x, int &y, int &i, int &leftlimit, int &rightlimit, int &upperlimitleft, int &downlimitleft, int &upperlimitright, int &downlimitright)
{
	if (x == leftlimit && key == key_Down && y < upperlimitleft)
	{
		i++;
		y = 4 * (i + 1);
	}
	if (x == leftlimit && key == key_Up && y > downlimitleft)
	{
		i--;
		x = leftlimit;
		y = 4 * (i + 1);
	}
	if (x == leftlimit && key == key_Right)
	{
		x = rightlimit;
		y = downlimitright;
	}
	if (x == rightlimit && key == key_Down && y < upperlimitright)
	{
		y += 2;
	}

	if (x == rightlimit && key == key_Up && y > downlimitright)
	{
		y -= 2;
	}
	if (x == rightlimit && key == key_Left)
	{
		x = leftlimit;
		i = 0;
		y = 4 * (i + 1);
	}
}
void Menu(string &username)
{
	clrscr();
	gotoXY(42, 4);
	cout << "STUDENT";
	gotoXY(42, 8);
	cout << "COURSE";
	gotoXY(42, 12);
	cout << "CHANGE PASSWORD";
	gotoXY(42, 16);
	TextColor(1);
	cout << "LOG OUT";
	gotoXY(42, 20);
	TextColor(4);
	cout << "EXIT";
	TextColor(7);
	int x = 42, y = 4;
	int key = inputKey();
	int a = 20, b = 4;
	gotoXY(x, y);
	while (key != 13)
	{
		MoveMouse(key, x, y, a, b);
		gotoXY(x, y);
		key = inputKey();
	}
	if (y == 4)
	{
		MenuClassAdmin(username);
	}
	else if (y == 8)
	{
		MenuCourseAdmin(username);
	}
	else if (y == 12)
		changePassAdmin(username);
	else if (y == 16) {
		system("cls");
		cout << "You are logged out !\n";
		system("pause");
		login(username);
	}
	else exit(0);
}

void MenuStudent(string &username)
{
	clrscr();
	bool check = false;
	gotoXY(42, 4);
	cout << "View Schedule";
	gotoXY(42, 8);
	cout << "View Score Board";
	gotoXY(42, 12);
	cout << "Change Password";
	gotoXY(42, 16);
	TextColor(1);
	cout << "Log Out";
	gotoXY(42, 20);
	TextColor(4);
	cout << "Exit";
	TextColor(7);
	int x = 42, y = 4;
	int key = inputKey();
	int a = 20, b = 4;
	gotoXY(x, y);
	while (key != 13)
	{
		MoveMouse(key, x, y, a, b);
		gotoXY(x, y);
		key = inputKey();
	}
	if (y == 4)
	{
		clrscr();
		YearList ylst;
		string name = "ListofYear";
		string yearname, semestername;
		loadYear(name, ylst);
		year* cur = ylst.pHead;
		int n = LengthofYearlist(ylst);
		string* s = new string[n];
		gotoXY(20, 0);
		cout << "Please choose year you want to view schedule : ";
		for (int i = 0; i < n; i++)
		{
			gotoXY(42, 4 * (i + 1));
			cout << cur->name;
			s[i] = cur->name;
			cur = cur->pNext;
		}
		RemoveYear(ylst);
		int i = 0;
		int x = 42, y = 4 * (i + 1);
		int a = 4 * n; b = 4;
		int key = inputKey();
		gotoXY(x, y);
		while (key != 13)
		{
			MoveMouse(key, x, y, a, b);
			gotoXY(x, y);
			key = inputKey();
		}
		for (int j = 0; j < n; j++)
		{
			if (j == i)
			{
				yearname = s[j];
				delete[]s;
				clrscr();
				SemesterList selst;
				loadSemester(yearname, selst);
				n = LengthofSemeterlist(selst);
				Semester* cur = selst.pHead;
				string* se = new string[n];
				gotoXY(20, 0);
				cout << "Please choose semester you want to view schedule : ";
				for (int i = 0; i < n; i++)
				{
					gotoXY(42, 4 * (i + 1));
					cout << cur->name;
					se[i] = cur->name;
					cur = cur->pNext;
				}
				RemoveSemester(selst);
				int i = 0;
				int x = 42, y = 4 * (i + 1);
				int a = 4 * n; b = 4;
				int key = inputKey();
				gotoXY(x, y);
				while (key != 13)
				{
					MoveMouse(key, x, y, a, b);
					gotoXY(x, y);
					key = inputKey();
				}
				for (int k = 0; k < n; k++)
				{
					if (k == i)
					{
						semestername = se[k];
						delete[]se;
						clrscr();
						CourseList colst;
						string coursename = yearname + "_" + semestername;
						loadCourse(coursename, colst);
						Course* now = colst.pHead;
						TextColor(11);
						cout << "Course ID";
						gotoXY(15, 0);
						cout << "Day of Week";
						gotoXY(30, 0);
						cout << "Start Hour";
						gotoXY(45, 0);
						cout << "End Hour";
						gotoXY(60, 0);
						cout << "Room";
						TextColor(7);
						int i = 0;
						while (now != nullptr)
						{
							StudentList slst;
							string namefile = now->ID + "_" + now->Class;
							loadStudent(namefile, slst);
							student* stu = slst.pHead;
							while (stu != nullptr) {
								if (stu->ID == username)
								{
									gotoXY(0, 1 + i);
									cout << now->ID;
									gotoXY(15, 1 + i);
									cout << now->DayofWeek;
									gotoXY(30, 1 + i);
									cout << now->StartHour;
									gotoXY(45, 1 + i);
									cout << now->EndHour;
									gotoXY(60, 1 + i);
									cout << now->Room << endl;
									i++;
									check = true;
								}
								stu = stu->pNext;
							}
							now = now->pNext;
						}
						if (check == false)
						{
							gotoXY(15, 1);
							cout << "You don't have any course in " << yearname << " ( " << semestername << " ) " << endl;
						}
						RemoveCourse(colst);
						cout << "If you want to go back , Please enter esc .\n";
						key = inputKey();
						while (key != 27)
						{
							key = inputKey();
						}
						MenuStudent(username);
					}
				}
			}
		}
	}
	else if (y == 8)
	{
		clrscr();
		YearList ylst;
		string name = "ListofYear";
		string yearname, semestername, id_course, classname;
		loadYear(name, ylst);
		year* cur = ylst.pHead;
		int n = LengthofYearlist(ylst);
		string* s = new string[n];
		gotoXY(30, 0);
		TextColor(1);
		cout << "Please choose year you want to view ScoreBoard : ";
		TextColor(7);
		for (int i = 0; i < n; i++)
		{
			gotoXY(42, 4 * (i + 1));
			cout << cur->name;
			s[i] = cur->name;
			cur = cur->pNext;
		}
		RemoveYear(ylst);
		int i = 0;
		int x = 42, y = 4 * (i + 1);
		int a = 4 * n; b = 4;
		int key = inputKey();
		gotoXY(x, y);
		while (key != 13)
		{
			MoveMouse(key, x, y, a, b);
			gotoXY(x, y);
			key = inputKey();
		}
		for (int j = 0; j < n; j++)
		{
			if (j == i)
			{
				yearname = s[j];
				delete[]s;
				clrscr();
				SemesterList selst;
				loadSemester(yearname, selst);
				int n = LengthofSemeterlist(selst);
				Semester* cur = selst.pHead;
				string* se = new string[n];
				gotoXY(30, 0);
				TextColor(1);
				cout << "Please choose semester you want to view ScoreBoard : ";
				TextColor(7);
				for (int i = 0; i < n; i++)
				{
					gotoXY(42, 4 * (i + 1));
					cout << cur->name;
					se[i] = cur->name;
					cur = cur->pNext;
				}
				RemoveSemester(selst);
				int i = 0;
				int x = 42, y = 4 * (i + 1);
				int a = 4 * n; b = 4;
				int key = inputKey();
				gotoXY(x, y);
				while (key != 13)
				{
					MoveMouse(key, x, y, a, b);
					gotoXY(x, y);
					key = inputKey();
				}
				for (int k = 0; k < n; k++)
				{
					if (k == i)
					{
						semestername = se[k];
						delete[]se;
						clrscr();
						CourseList colst;
						string coursename = yearname + "_" + semestername;
						loadCourse(coursename, colst);
						n = LengthofCourselist(colst);
						TextColor(11);
						cout << "No";
						gotoXY(10, 0);
						cout << "Course ID";
						gotoXY(25, 0);
						cout << "Midterm";
						gotoXY(35, 0);
						cout << "Final";
						gotoXY(45, 0);
						cout << "Bonus";
						gotoXY(55, 0);
						cout << "Average";
						TextColor(7);
						int i = 0;
						Course* co = colst.pHead;
						while (co != nullptr)
						{
							string namefile = co->ID + "_" + co->Class;
							ScoreBoardList sclst;
							loadScoreboard(namefile, sclst);
							scoreboard* score = sclst.pHead;
							while (score != nullptr)
							{
								if (score->ID == username)
								{
									gotoXY(0, 1 + i);
									cout << i + 1;
									gotoXY(10, 1 + i);
									cout << co->ID;
									gotoXY(25, 1 + i);
									cout << score->mid;
									gotoXY(35, 1 + i);
									cout << score->Final;
									gotoXY(45, 1 + i);
									cout << score->bonus;
									gotoXY(55, 1 + i);
									cout << score->aveg << endl;
									check = true;
									i++;
									break;
								}
								score = score->pNext;
							}
							co = co->pNext;
						}
						if (check == false) {
							gotoXY(15, 1);
							cout << "You don't have any course in " << yearname << " ( " << semestername << " ) " << endl;
						}
						cout << "If you want to go back , Please enter esc .\n";
						key = inputKey();
						while (key != 27)
						{
							key = inputKey();
						}
						MenuStudent(username);
					}
				}
			}
		}
	}
	else if (y == 12) {
		changePassStudent(username);
	}
	else if (y == 16) {
		clrscr();
		cout << "You are logged out !\n";
		system("pause");
		login(username);
	}
	else exit(0);
}

void MenuLecturer(string &username)
{
	clrscr();
	bool check = false;
	string name = "ListofYear";
	string yearname, semestername, id_course, id_student, classname;
	gotoXY(42, 4);
	cout << "View List of Course And Student of a Course";
	gotoXY(42, 8);
	cout << "ScoreBoard";
	gotoXY(42, 12);
	cout << "Change Password";
	gotoXY(42, 16);
	TextColor(1);
	cout << "Log Out";
	gotoXY(42, 20);
	TextColor(4);
	cout << "Exit";
	TextColor(7);
	int x = 42, y = 4;
	int key = inputKey();
	int a = 20, b = 4;
	gotoXY(x, y);
	while (key != 13)
	{
		MoveMouse(key, x, y, a, b);
		gotoXY(x, y);
		key = inputKey();
	}
	//view
	if (y == 4)
	{
		clrscr();
		YearList ylst;
		loadYear(name, ylst);
		year* cur = ylst.pHead;
		int n = LengthofYearlist(ylst);
		string* s = new string[n];
		gotoXY(30, 0);
		TextColor(1);
		cout << "Please choose year of Course you want to view  : ";
		TextColor(7);
		for (int i = 0; i < n; i++)
		{
			gotoXY(42, 4 * (i + 1));
			cout << cur->name;
			s[i] = cur->name;
			cur = cur->pNext;
		}
		RemoveYear(ylst);
		int i = 0;
		int x = 42, y = 4 * (i + 1);
		int a = 4 * n; b = 4;
		int key = inputKey();
		gotoXY(x, y);
		while (key != 13)
		{
			MoveMouse(key, x, y, a, b);
			gotoXY(x, y);
			key = inputKey();
		}
		for (int j = 0; j < n; j++)
		{
			if (j == i)
			{
				yearname = s[j];
				delete[]s;
				clrscr();
				SemesterList selst;
				loadSemester(yearname, selst);
				n = LengthofSemeterlist(selst);
				Semester* cur = selst.pHead;
				string* se = new string[n];
				gotoXY(30, 0);
				TextColor(1);
				cout << "Please choose semester of Course you want to view  : ";
				TextColor(7);
				for (int i = 0; i < n; i++)
				{
					gotoXY(42, 4 * (i + 1));
					cout << cur->name;
					se[i] = cur->name;
					cur = cur->pNext;
				}
				RemoveSemester(selst);
				int i = 0;
				int x = 42, y = 4 * (i + 1);
				int a = 4 * n; b = 4;
				int key = inputKey();
				gotoXY(x, y);
				while (key != 13)
				{
					MoveMouse(key, x, y, a, b);
					gotoXY(x, y);
					key = inputKey();
				}
				for (int k = 0; k < n; k++)
				{
					if (k == i)
					{
						semestername = se[k];
						delete[]se;
						clrscr();
						gotoXY(35, 0);
						TextColor(1);
						cout << "What do you want to view ";
						TextColor(7);
						gotoXY(42, 4);
						cout << "View list of Course";
						gotoXY(42, 8);
						cout << "View list of Student of a Course";
						int x = 42, y = 4;
						int key = inputKey();
						int a = 8, b = 4;
						gotoXY(x, y);
						while (key != 13)
						{
							MoveMouse(key, x, y, a, b);
							gotoXY(x, y);
							key = inputKey();
						}
						CourseList colst;
						string coursename = yearname + "_" + semestername;
						loadCourse(coursename, colst);
						int l = LengthofCourselist(colst);
						//view course
						if (y == 4) {
							clrscr();
							gotoXY(40, 0);
							cout << "Here is a list of courses you charge";
							TextColor(11);
							gotoXY(0, 2);
							cout << "No";
							gotoXY(4, 2);
							cout << "Course ID";
							gotoXY(30, 2);
							cout << "Course Name";
							gotoXY(65, 2);
							cout << "Class";
							gotoXY(73, 2);
							cout << "Lecture Account";
							gotoXY(91, 2);
							cout << "Start Date";
							gotoXY(104, 2);
							cout << "End Date";
							gotoXY(117, 2);
							cout << "Day of Week";
							gotoXY(131, 2);
							cout << "Start Hour";
							gotoXY(144, 2);
							cout << "End Hour";
							gotoXY(156, 2);
							cout << "Room";
							TextColor(7);
							int i = 1;
							Course* now = colst.pHead;
							while (now != nullptr)
							{
								if (now->LecturerAcc == username)
								{
									gotoXY(0, 2 + i);
									cout << i;
									gotoXY(4, 2 + i);
									cout << now->ID;
									gotoXY(15, 2 + i);
									cout << now->Name;
									gotoXY(65, 2 + i);
									cout << now->Class;
									gotoXY(73, 2 + i);
									cout << now->LecturerAcc;
									gotoXY(91, 2 + i);
									cout << now->StartDate;
									gotoXY(104, 2 + i);
									cout << now->EndDate;
									gotoXY(117, 2 + i);
									cout << now->DayofWeek;
									gotoXY(131, 2 + i);
									cout << now->StartHour;
									gotoXY(144, 2 + i);
									cout << now->EndHour;
									gotoXY(156, 2 + i);
									cout << now->Room << endl;
									check = true;
									i++;
								}
								now = now->pNext;
							}
							RemoveCourse(colst);
							if (check == false) {
								clrscr();
								TextColor(12);
								gotoXY(20, 2);
								cout << "You are not in charge of any public courses in " << yearname << " ( " << semestername << " )" << endl << endl;
								TextColor(7);
							}
						}
						//view student from a course
						else {
							clrscr();
							gotoXY(15, 0);
							TextColor(11);
							cout << "Here is a list of courses you charge.Please choose Course ID to view List of Student of it.";
							TextColor(7);
							Course* now = colst.pHead;
							int l = LengthofCourselist(colst);
							string* co = new string[l];
							string* cla = new string[l];
							int i = 0;
							while (now != nullptr)
							{
								if (now->LecturerAcc == username)
								{
									gotoXY(42, 4 * (i + 1));
									cout << now->ID << " ( " << now->Class << " )";
									co[i] = now->ID;
									cla[i] = now->Class;
									check = true;
									i++;
								}
								now = now->pNext;
							}
							RemoveCourse(colst);
							if (check == false) {
								clrscr();
								TextColor(12);
								gotoXY(20, 2);
								cout << "You are not in charge of any public courses in " << yearname << " ( " << semestername << " )" << endl << endl;
								TextColor(7);
							}
							else {
								int j = 0;
								int x = 42, y = 4 * (j + 1);
								int key = inputKey();
								gotoXY(x, y);
								while (key != 13)
								{
									if (key == key_Down && y < 4 * i)
									{
										j++;
										y = 4 * (j + 1);
									}
									if (key == key_Up && y > 4)
									{
										j--;
										y = 4 * (j + 1);
									}
									gotoXY(x, y);
									key = inputKey();
								}
								for (int m = 0; m <= i; m++)
								{
									if (m == j)
									{
										id_course = co[m];
										delete[]co;
										classname = cla[m];
										delete[]cla;
										string namefile = id_course + "_" + classname;
										clrscr();
										StudentList slst;
										loadStudent(namefile, slst);
										student* curs = slst.pHead;
										TextColor(9);
										cout << "No";
										gotoXY(8, 0);
										cout << "Id";
										gotoXY(20, 0);
										cout << "Last Name";
										gotoXY(35, 0);
										cout << "First Name";
										gotoXY(50, 0);
										cout << "Gender";
										gotoXY(60, 0);
										cout << "Date of Birth" << endl;
										TextColor(7);
										int i = 0;
										while (curs != nullptr)
										{
											cout << curs->No;
											gotoXY(5, 1 + i);
											cout << curs->ID;
											gotoXY(20, 1 + i);
											cout << curs->Lastname;
											gotoXY(35, 1 + i);
											cout << curs->Firstname;
											gotoXY(50, 1 + i);
											cout << curs->Gender;
											gotoXY(60, 1 + i);
											cout << curs->DoB.substr(0, 2) << "/" << curs->DoB.substr(2, 2) << "/" << curs->DoB.substr(4, 4) << endl;
											curs = curs->pNext;
											i++;
										}
										RemoveStudent(slst);
										break;
									}
								}
							}
						}
						cout << "If you want to go back , Please enter esc .";
						key = inputKey();
						while (key != 27)
						{
							key = inputKey();
						}
						MenuLecturer(username);
					}
				}
			}
		}
	}
	//scoreboard
	else if (y == 8)
	{
		clrscr();
		YearList ylst;
		loadYear(name, ylst);
		year* cur = ylst.pHead;
		int n = LengthofYearlist(ylst);
		string* s = new string[n];
		gotoXY(30, 0);
		TextColor(1);
		cout << "Please choose year of Course you want to manipulate the ScoreBoard ";
		TextColor(7);
		for (int i = 0; i < n; i++)
		{
			gotoXY(42, 4 * (i + 1));
			cout << cur->name;
			s[i] = cur->name;
			cur = cur->pNext;
		}
		RemoveYear(ylst);
		int i = 0;
		int x = 42, y = 4 * (i + 1);
		int a = 4 * n; b = 4;
		int key = inputKey();
		gotoXY(x, y);
		while (key != 13)
		{
			MoveMouse(key, x, y, a, b);
			gotoXY(x, y);
			key = inputKey();
		}
		for (int j = 0; j < n; j++)
		{
			if (j == i)
			{
				yearname = s[j];
				delete[]s;
				clrscr();
				SemesterList selst;
				loadSemester(yearname, selst);
				n = LengthofSemeterlist(selst);
				Semester* cur = selst.pHead;
				string* se = new string[n];
				gotoXY(30, 0);
				TextColor(1);
				cout << "Please choose semester of Course you want to manipulate the ScoreBoard ";
				TextColor(7);
				for (int i = 0; i < n; i++)
				{
					gotoXY(42, 4 * (i + 1));
					cout << cur->name;
					se[i] = cur->name;
					cur = cur->pNext;
				}
				RemoveSemester(selst);
				int i = 0;
				int x = 42, y = 4 * (i + 1);
				int a = 4 * n; b = 4;
				int key = inputKey();
				gotoXY(x, y);
				while (key != 13)
				{
					MoveMouse(key, x, y, a, b);
					gotoXY(x, y);
					key = inputKey();
				}
				for (int k = 0; k < n; k++)
				{
					if (k == i)
					{
						semestername = se[k];
						delete[]se;
						clrscr();
						gotoXY(35, 0);
						TextColor(1);
						cout << "Please choose how to manipulate the ScoreBoard";
						TextColor(7);
						gotoXY(42, 4);
						cout << "Import ScoreBoard";
						gotoXY(42, 8);
						cout << "Edit grade of ScoreBoard";
						gotoXY(42, 12);
						cout << "View ScoreBoard";
						int x = 42, y = 4;
						int key = inputKey();
						int a = 12, b = 4;
						gotoXY(x, y);
						while (key != 13)
						{
							MoveMouse(key, x, y, a, b);
							gotoXY(x, y);
							key = inputKey();
						}
						CourseList colst;
						string coursename = yearname + "_" + semestername;
						loadCourse(coursename, colst);
						//import scoreboard
						if (y == 4) {
							clrscr();
							gotoXY(15, 0);
							TextColor(11);
							cout << "Here is a list of courses you charge.Please choose Course ID to imports ScoreBoard of it.";
							TextColor(7);
							Course* now = colst.pHead;
							int l = LengthofCourselist(colst);
							string* co = new string[l];
							string* cla = new string[l];
							int i = 0;
							while (now != nullptr)
							{
								if (now->LecturerAcc == username)
								{
									gotoXY(42, 4 * (i + 1));
									cout << now->ID << " ( " << now->Class << " )";
									co[i] = now->ID;
									cla[i] = now->Class;
									check = true;
									i++;
								}
								now = now->pNext;
							}
							RemoveCourse(colst);
							if (check == false) {
								clrscr();
								TextColor(12);
								gotoXY(20, 2);
								cout << "You are not in charge of any public courses in " << yearname << " ( " << semestername << " )" << endl << endl;
								TextColor(7);
							}
							else {
								int j = 0;
								int x = 42, y = 4 * (j + 1);
								int key = inputKey();
								gotoXY(x, y);
								while (key != 13)
								{
									if (key == key_Down && y < 4 * i)
									{
										j++;
										y = 4 * (j + 1);
									}
									if (key == key_Up && y > 4)
									{
										j--;
										y = 4 * (j + 1);
									}
									gotoXY(x, y);
									key = inputKey();
								}
								for (int m = 0; m <= i; m++)
								{
									if (m == j)
									{
										id_course = co[m];
										delete[]co;
										classname = cla[m];
										delete[]cla;
										clrscr();
										importScoreboard(id_course, classname);
										break;
									}
								}
							}
						}
						//edit grade
						else if (y == 8)
						{
							clrscr();
							gotoXY(15, 0);
							TextColor(1);
							cout << "Here is a list of courses you charge . Please choose Course ID to edit grade of a student in a Course";
							TextColor(7);
							int l = LengthofCourselist(colst);
							string* co = new string[l];
							string* cla = new string[l];
							int i = 0;
							Course* now = colst.pHead;
							while (now != nullptr)
							{
								if (now->LecturerAcc == username)
								{
									gotoXY(42, 4 * (i + 1));
									cout << now->ID << " ( " << now->Class << " )";
									co[i] = now->ID;
									cla[i] = now->Class;
									check = true;
									i++;
								}
								now = now->pNext;
							}
							RemoveCourse(colst);
							if (check == false) {
								clrscr();
								TextColor(12);
								gotoXY(20, 2);
								cout << "You are not in charge of any public courses in " << yearname << " ( " << semestername << " )" << endl << endl;
								TextColor(7);
							}
							else {
								int j = 0;
								int x = 42, y = 4 * (j + 1);
								int key = inputKey();
								gotoXY(x, y);
								while (key != 13)
								{
									if (key == key_Down && y < 4 * i)
									{
										j++;
										y = 4 * (j + 1);
									}
									if (key == key_Up && y > 4)
									{
										j--;
										y = 4 * (j + 1);
									}
									gotoXY(x, y);
									key = inputKey();
								}
								for (int m = 0; m <= i; m++)
								{
									if (m == j)
									{
										id_course = co[m];
										delete[]co;
										classname = cla[m];
										delete[]cla;
										string namefile = id_course + "_" + classname;
										clrscr();
										ScoreBoardList sclst;
										loadScoreboard(namefile, sclst);
										n = LengthofScoreBoardlist(sclst);
										int i = 0;
										string* s = new string[n];
										scoreboard* score = sclst.pHead;
										TextColor(1);
										gotoXY(15, 0);
										cout << "Please choose ID of student you want to edit grade";
										TextColor(7);
										for (int i = 0; i < n; i++)
										{
											gotoXY(42, 2 * (i + 1));
											cout << score->ID;
											s[i] = score->ID;
											score = score->pNext;
										}
										int m = 0;
										int x = 42, y = 2 * (m + 1);
										key = inputKey();
										gotoXY(x, y);
										while (key != 13)
										{
											if (key == key_Down && y < 2 * n)
											{
												m++;
												y = 2 * (m + 1);
											}
											if (key == key_Up && y > 2)
											{
												m--;
												y = 2 * (m + 1);
											}
											gotoXY(x, y);
											key = inputKey();
										}
										for (int k = 0; k < n; k++)
										{
											if (k == m)
											{
												id_student = s[k];
												delete[]s;
												clrscr();
												scoreboard* cur = sclst.pHead;
												while (cur != nullptr)
												{
													if (cur->ID == id_student) break;
													cur = cur->pNext;
												}
												TextColor(1);
												gotoXY(15, 0);
												cout << "Which grade do you want to edit : ";
												TextColor(7);
												gotoXY(11, 2);
												cout << "Midterm ";
												gotoXY(11, 4);
												cout << "Final ";
												gotoXY(11, 6);
												cout << "Bonus ";
												int x = 11, y = 2;
												int key = inputKey();
												gotoXY(x, y);
												while (key != 13)
												{
													if (key == key_Down && y < 6)
													{
														y += 2;
													}
													if (key == key_Up && y > 2)
													{
														y -= 2;
													}
													gotoXY(x, y);
													key = inputKey();
												}
												if (y == 2)
												{
													gotoXY(0, 7);
													cout << "Please enter new Midterm Grade of this student : ";
													getline(cin, cur->mid, '\n');
												}
												else if (y == 4)
												{
													gotoXY(0, 7);
													cout << "Please enter new Final Grade of this student : ";
													getline(cin, cur->Final, '\n');
												}
												else if (y == 6)
												{
													gotoXY(0, 7);
													cout << "Please enter new Bonus Grade of this student : ";
													getline(cin, cur->bonus, '\n');
												}
												string a = CalculateAverage(cur->mid, cur->Final, cur->bonus, cur->aveg);
												cur->aveg = a;
												if (SaveScoreboard(namefile, n, sclst)) cout << "Edit grade and save completely.\n";
												RemoveScoreboard(sclst);
												break;
											}
										}
									}
								}
							}
						}
						//view scoreboard
						else
						{
							clrscr();
							gotoXY(15, 0);
							TextColor(11);
							cout << "Here is a list of courses you charge.Please choose Course ID to view ScoreBoard of it.";
							TextColor(7);
							Course* now = colst.pHead;
							int l = LengthofCourselist(colst);
							string* co = new string[l];
							string* cla = new string[l];
							int i = 0;
							while (now != nullptr)
							{
								if (now->LecturerAcc == username)
								{
									gotoXY(42, 4 * (i + 1));
									cout << now->ID << " ( " << now->Class << " )";
									co[i] = now->ID;
									cla[i] = now->Class;
									check = true;
									i++;
								}
								now = now->pNext;
							}
							RemoveCourse(colst);
							if (check == false) {
								clrscr();
								TextColor(12);
								gotoXY(20, 2);
								cout << "You are not in charge of any public courses in " << yearname << " ( " << semestername << " )" << endl << endl;
								TextColor(7);
							}
							else {
								int j = 0;
								int x = 42, y = 4 * (j + 1);
								int key = inputKey();
								gotoXY(x, y);
								while (key != 13)
								{
									if (key == key_Down && y < 4 * i)
									{
										j++;
										y = 4 * (j + 1);
									}
									if (key == key_Up && y > 4)
									{
										j--;
										y = 4 * (j + 1);
									}
									gotoXY(x, y);
									key = inputKey();
								}
								for (int m = 0; m <= i; m++)
								{
									if (m == j)
									{
										id_course = co[m];
										delete[]co;
										classname = cla[m];
										delete[]cla;
										string namefile = id_course + "_" + classname;
										clrscr();
										TextColor(7);
										ScoreBoardList sclst;
										loadScoreboard(namefile, sclst);
										scoreboard* curs = sclst.pHead;
										StudentList slst;
										loadStudent(namefile, slst);
										student* stu = slst.pHead;
										TextColor(11);
										cout << "No";
										gotoXY(4, 0);
										cout << "Student ID";
										gotoXY(20, 0);
										cout << "Last Name";
										gotoXY(35, 0);
										cout << "First Name";
										gotoXY(50, 0);
										cout << "Midterm";
										gotoXY(60, 0);
										cout << "Final";
										gotoXY(70, 0);
										cout << "Bonus";
										gotoXY(80, 0);
										cout << "Average";
										TextColor(7);
										int i = 0;
										while (curs != nullptr&&stu != nullptr)
										{
											gotoXY(0, 1 + i);
											cout << curs->No;
											gotoXY(4, 1 + i);
											cout << curs->ID;
											gotoXY(20, 1 + i);
											cout << stu->Lastname;
											gotoXY(35, 1 + i);
											cout << stu->Firstname;
											gotoXY(50, 1 + i);
											cout << curs->mid;
											gotoXY(60, 1 + i);
											cout << curs->Final;
											gotoXY(70, 1 + i);
											cout << curs->bonus;
											gotoXY(80, 1 + i);
											cout << curs->aveg << endl;
											stu = stu->pNext;
											curs = curs->pNext;
											i++;
										}
										RemoveStudent(slst);
										RemoveScoreboard(sclst);
										break;
									}
								}
							}
						}
						cout << "If you want to go back , Please enter esc .";
						key = inputKey();
						while (key != 27)
						{
							key = inputKey();
						}
						MenuLecturer(username);
					}
				}
			}
		}
	}
	else if (y == 12) {
		changePassLecturer(username);
	}
	else if (y == 16) {
		clrscr();
		cout << "You are logged out !\n";
		system("pause");
		login(username);
	}
	else exit(0);
}

void login(string &username) {
	clrscr();
	string name, pass, checkname, checkpass, classname;
	char ch;
	gotoXY(0, 0);
	// APCS 
	ifstream fin2("APCS.txt");
	char c;
	while (!fin2.eof())
	{
		fin2.get(c);// lay 1 ki tu
		if (c == '1')		TextColor(10);// doi mau xanh la
		else if (c == '2')  TextColor(9); // doi mau xanh duong
		else if (c == '3')  TextColor(12);// doi mau do
		else if (c == '4')  TextColor(15);// doi mau trang
		else cout << c;// in
		Sleep(1);
	}
	fin2.close();
	gotoXY(65, 15);
	TextColor(11);
	cout << "LOGIN";
	TextColor(7);
	gotoXY(65, 18);
	cout << "Admin";
	gotoXY(65, 22);
	cout << "Student";
	gotoXY(65, 26);
	cout << "Lecturer";
	int x = 65, y = 18;
	int key = inputKey();
	int a = 26, b = 18;
	gotoXY(x, y);
	while (key != 13)
	{
		MoveMouse(key, x, y, a, b);
		gotoXY(x, y);
		key = inputKey();
	}
	if (y == 18)
	{
		//clear choice before
		gotoXY(65, 18);
		for (int i = 0; i < 5; i++) {
			gotoXY(65 + i, 18);
			cout << " ";
		}
		gotoXY(65, 22);
		for (int i = 0; i < 7; i++) {
			gotoXY(65 + i, 22);
			cout << " ";
		}
		gotoXY(65, 26);
		for (int i = 0; i < 8; i++) {
			gotoXY(65 + i, 26);
			cout << " ";
		}
		gotoXY(60, 18);
		cout << "Enter username: ";
		cin >> name;
		gotoXY(60, 20);
		cout << "Enter password: ";
		while ((ch = _getch()) != '\r')
		{
			if (ch != '\b') {
				pass.push_back(ch);
				if (ch != '\0')
					_putch('*');
				else pass.pop_back();
			}
			else {
				if (pass.size() != 0) {
					pass.pop_back();
					cout << "\b \b";
				}
			}
		}
		cout << endl;
		cin.ignore(1000, '\n');
		ifstream fin;
		fin.open("login_admin.txt");
		while (getline(fin, checkname) && getline(fin, checkpass)) {
			if (checkname == name && checkpass == pass) {
				gotoXY(60, 22);
				TextColor(10);
				fin.close();
				cout << "Login successful!\n";
				TextColor(7);
				username = checkname;
				system("pause");
				Menu(username);
			}
		}
		fin.close();
		gotoXY(55, 22);
		TextColor(12);
		cout << "Wrong username or password.";
		gotoXY(62, 24);
		TextColor(8);
		cout << "Try Agian";
		gotoXY(62, 26);
		cout << "Exit";
		TextColor(7);
		int x = 62, y = 24;
		int key = inputKey();
		gotoXY(x, y);
		while (key != 13)
		{
			if (key == key_Up && y > 24)
			{
				y -= 2;
			}
			if (key == key_Down && y < 26)
			{
				y += 2;
			}
			gotoXY(x, y);
			key = inputKey();
		}
		if (y == 24) login(username);
		else exit(0);
	}
	else if (y == 22)
	{
		//clear choice before
		gotoXY(65, 18);
		for (int i = 0; i < 5; i++) {
			gotoXY(65 + i, 18);
			cout << " ";
		}
		gotoXY(65, 22);
		for (int i = 0; i < 7; i++) {
			gotoXY(65 + i, 22);
			cout << " ";
		}
		gotoXY(65, 26);
		for (int i = 0; i < 8; i++) {
			gotoXY(65 + i, 26);
			cout << " ";
		}
		gotoXY(60, 18);
		cout << "Enter username: ";
		cin >> name;
		gotoXY(60, 20);
		cout << "Enter password: ";
		while ((ch = _getch()) != '\r')
		{
			if (ch != '\b') {
				pass.push_back(ch);
				if (ch != '\0')
					_putch('*');
				else pass.pop_back();
			}
			else {
				if (pass.size() != 0) {
					pass.pop_back();
					cout << "\b \b";
				}
			}
		}
		cout << endl;
		cin.ignore(1000, '\n');
		ifstream fin;
		fin.open("login_student.txt");
		while (getline(fin, checkname) && getline(fin, checkpass)) {
			if (checkname == name && checkpass == pass) {
				gotoXY(60, 22);
				TextColor(10);
				fin.close();
				cout << "Login successful!\n";
				TextColor(7);
				username = checkname;
				system("pause");
				MenuStudent(username);
			}
		}
		fin.close();
		gotoXY(55, 22);
		TextColor(12);
		cout << "Wrong username or password.";
		gotoXY(62, 24);
		TextColor(8);
		cout << "Try Agian";
		gotoXY(62, 26);
		cout << "Exit";
		TextColor(7);
		int x = 62, y = 24;
		int key = inputKey();
		gotoXY(x, y);
		while (key != 13)
		{
			if (key == key_Up && y > 24)
			{
				y -= 2;
			}
			if (key == key_Down && y < 26)
			{
				y += 2;
			}
			gotoXY(x, y);
			key = inputKey();
		}
		if (y == 24) login(username);
		else exit(0);
	}
	else if (y == 26) {
		//clear choice before
		gotoXY(65, 18);
		for (int i = 0; i < 5; i++) {
			gotoXY(65 + i, 18);
			cout << " ";
		}
		gotoXY(65, 22);
		for (int i = 0; i < 7; i++) {
			gotoXY(65 + i, 22);
			cout << " ";
		}
		gotoXY(65, 26);
		for (int i = 0; i < 8; i++) {
			gotoXY(65 + i, 26);
			cout << " ";
		}
		gotoXY(60, 18);
		cout << "Enter username: ";
		cin >> name;
		gotoXY(60, 20);
		cout << "Enter password: ";
		while ((ch = _getch()) != '\r')
		{
			if (ch != '\b') {
				pass.push_back(ch);
				if (ch != '\0')
					_putch('*');
				else pass.pop_back();
			}
			else {
				if (pass.size() != 0) {
					pass.pop_back();
					cout << "\b \b";
				}
			}
		}
		cout << endl;
		cin.ignore(1000, '\n');
		ifstream fin;
		fin.open("login_lecturer.txt");
		while (getline(fin, checkname) && getline(fin, checkpass)) {
			if (checkname == name && checkpass == pass) {
				gotoXY(60, 22);
				TextColor(10);
				fin.close();
				cout << "Login successful!\n";
				TextColor(7);
				username = checkname;
				system("pause");
				MenuLecturer(username);
			}
		}
		fin.close();
		gotoXY(55, 22);
		TextColor(12);
		cout << "Wrong username or password.";
		gotoXY(62, 24);
		TextColor(8);
		cout << "Try Agian";
		gotoXY(62, 26);
		cout << "Exit";
		TextColor(7);
		int x = 62, y = 24;
		int key = inputKey();
		gotoXY(x, y);
		while (key != 13)
		{
			if (key == key_Up && y > 24)
			{
				y -= 2;
			}
			if (key == key_Down && y < 26)
			{
				y += 2;
			}
			gotoXY(x, y);
			key = inputKey();
		}
		if (y == 24) login(username);
		else exit(0);
	}
}

void changePassAdmin(string username) {
	clrscr();
	string pass, checkpass, checkname, extra, newpass;
	char ch;
	cout << "Enter your current password: ";
	while ((ch = _getch()) != '\r')
	{
		if (ch != '\b') {
			pass.push_back(ch);
			if (ch != '\0')
				_putch('*');
			else pass.pop_back();
		}
		else {
			if (pass.size() != 0) {
				pass.pop_back();
				cout << "\b \b";
			}
		}
	}
	cout << endl;
	bool valid = 0;

	ifstream login;
	login.open("login_admin.txt");
	ofstream loginnew;
	loginnew.open("temp.txt");

	while (getline(login, checkname) && getline(login, checkpass)) {
		if (checkname == username && checkpass == pass) {
			cout << "Enter your new password: ";
			while ((ch = _getch()) != '\r')
			{
				if (ch != '\b') {
					newpass.push_back(ch);
					if (ch != '\0')
						_putch('*');
					else newpass.pop_back();
				}
				else {
					if (newpass.size() != 0) {
						newpass.pop_back();
						cout << "\b \b";
					}
				}
			}
			cout << endl;
			loginnew << username << endl << newpass << endl;
			valid = 1;
		}
		else loginnew << checkname << endl << checkpass << endl;
	}
	if (valid) {
		TextColor(10);
		cout << "Password changed !\n";
		TextColor(7);
		system("pause");
		login.clear();
		login.seekg(0, ios::beg);
		login.close();
		loginnew.close();
		remove("login_admin.txt");
		rename("temp.txt", "login_admin.txt");
		Menu(username);
	}
	else {
		gotoXY(5, 2);
		TextColor(12);
		cout << "Wrong password !";
		gotoXY(7, 4);
		TextColor(8);
		cout << "Try Agian";
		gotoXY(7, 6);
		cout << "Return";
		TextColor(7);
		int x = 7, y = 4;
		int key = inputKey();
		gotoXY(x, y);
		while (key != 13)
		{
			if (key == key_Up && y > 4)
			{
				y -= 2;
			}
			if (key == key_Down && y < 6)
			{
				y += 2;
			}
			gotoXY(x, y);
			key = inputKey();
		}
		login.clear();
		login.seekg(0, ios::beg);
		login.close();
		loginnew.close();
		remove("login_admin.txt");
		rename("temp.txt", "login_admin.txt");
		if (y == 4) changePassAdmin(username);
		else Menu(username);
	}
}

void changePassStudent(string username) {
	clrscr();
	string pass, checkpass, checkname, extra, newpass;
	char ch;
	cout << "Enter your current password: ";
	while ((ch = _getch()) != '\r')
	{
		if (ch != '\b') {
			pass.push_back(ch);
			if (ch != '\0')
				_putch('*');
			else pass.pop_back();
		}
		else {
			if (pass.size() != 0) {
				pass.pop_back();
				cout << "\b \b";
			}
		}
	}
	cout << endl;
	bool valid = 0;

	ifstream login;
	login.open("login_student.txt");
	ofstream loginnew;
	loginnew.open("temp1.txt");

	while (getline(login, checkname) && getline(login, checkpass)) {
		if (checkname == username && checkpass == pass && !valid) {
			cout << "Enter your new password: ";
			while ((ch = _getch()) != '\r')
			{
				if (ch != '\b') {
					newpass.push_back(ch);
					if (ch != '\0')
						_putch('*');
					else newpass.pop_back();
				}
				else {
					if (newpass.size() != 0) {
						newpass.pop_back();
						cout << "\b \b";
					}
				}
			}
			cout << endl;
			loginnew << username << endl << newpass << endl;
			valid = 1;
		}
		else loginnew << checkname << endl << checkpass << endl;
	}
	if (valid) {
		TextColor(10);
		cout << "Password changed !\n";
		TextColor(7);
		system("pause");
		login.clear();
		login.seekg(0, ios::beg);
		login.close();
		loginnew.close();
		remove("login_student.txt");
		rename("temp1.txt", "login_student.txt");
		MenuStudent(username);
	}
	else {
		gotoXY(5, 2);
		TextColor(12);
		cout << "Wrong password !";
		gotoXY(7, 4);
		TextColor(8);
		cout << "Try Agian";
		gotoXY(7, 6);
		cout << "Return";
		TextColor(7);
		int x = 7, y = 4;
		int key = inputKey();
		gotoXY(x, y);
		while (key != 13)
		{
			if (key == key_Up && y > 4)
			{
				y -= 2;
			}
			if (key == key_Down && y < 6)
			{
				y += 2;
			}
			gotoXY(x, y);
			key = inputKey();
		}
		login.clear();
		login.seekg(0, ios::beg);
		login.close();
		loginnew.close();
		remove("login_student.txt");
		rename("temp1.txt", "login_student.txt");
		if (y == 4) changePassStudent(username);
		else MenuStudent(username);
	}
}

void changePassLecturer(string username) {
	clrscr();
	string pass, checkpass, checkname, extra, newpass;
	char ch;
	cout << "Enter your current password: ";
	while ((ch = _getch()) != '\r')
	{
		if (ch != '\b') {
			pass.push_back(ch);
			if (ch != '\0')
				_putch('*');
			else pass.pop_back();
		}
		else {
			if (pass.size() != 0) {
				pass.pop_back();
				cout << "\b \b";
			}
		}
	}
	cout << endl;
	bool valid = 0;

	ifstream login;
	login.open("login_lecturer.txt");
	ofstream loginnew;
	loginnew.open("temp.txt");

	while (getline(login, checkname) && getline(login, checkpass)) {
		if (checkname == username && checkpass == pass) {
			cout << "Enter your new password: ";
			while ((ch = _getch()) != '\r')
			{
				if (ch != '\b') {
					newpass.push_back(ch);
					if (ch != '\0')
						_putch('*');
					else newpass.pop_back();
				}
				else {
					if (newpass.size() != 0) {
						newpass.pop_back();
						cout << "\b \b";
					}
				}
			}
			cout << endl;
			loginnew << username << endl << newpass << endl;
			valid = 1;
		}
		else loginnew << checkname << endl << checkpass << endl;
	}
	if (valid) {
		TextColor(10);
		cout << "Password changed !\n";
		TextColor(7);
		system("pause");
		login.clear();
		login.seekg(0, ios::beg);
		login.close();
		loginnew.close();
		remove("login_lecturer.txt");
		rename("temp.txt", "login_lecturer.txt");
		MenuLecturer(username);
	}
	else {
		gotoXY(5, 2);
		TextColor(12);
		cout << "Wrong password !";
		gotoXY(7, 4);
		TextColor(8);
		cout << "Try Agian";
		gotoXY(7, 6);
		cout << "Return";
		TextColor(7);
		int x = 7, y = 4;
		int key = inputKey();
		gotoXY(x, y);
		while (key != 13)
		{
			if (key == key_Up && y > 4)
			{
				y -= 2;
			}
			if (key == key_Down && y < 6)
			{
				y += 2;
			}
			gotoXY(x, y);
			key = inputKey();
		}
		login.clear();
		login.seekg(0, ios::beg);
		login.close();
		loginnew.close();
		remove("login_lecturer.txt");
		rename("temp.txt", "login_lecturer.txt");
		if (y == 4) changePassLecturer(username);
		else MenuLecturer(username);
	}
}

void importStudent(string &namefile) {
	student s[100];
	student* import = s;
	int n = 0, i = 0;
	ifstream fin;
	fin.open(namefile + ".csv");
	if (!fin.is_open()) {
		cout << "Can not open file csv !";
		system("pause");
		//		return ;
	}
	else
	{
		string d, m, y;
		fin.ignore(1000, '\n');
		while (fin.good() && n < 10)
		{
			getline(fin, s[i].No, ',');
			getline(fin, s[i].ID, ',');
			getline(fin, s[i].Lastname, ',');
			getline(fin, s[i].Firstname, ',');
			getline(fin, s[i].Gender, ',');
			getline(fin, d, '/');
			getline(fin, m, '/');
			getline(fin, y, '\n');
			s[i].DoB = d + m + y;
			s[i].classname = namefile;
			n++;
			i++;
		}
	}
	fin.close();
	// Save to text file
	ofstream fout;
	fout.open(namefile + ".txt");
	if (!fout.is_open()) {
		cout << "Can not open file !";
		system("pause");
		//		return NULL;
	}
	else {
		i = 0;
		fout << n << endl;
		while (n != 0) {
			fout << s[i].No << "," << s[i].ID << "," << s[i].classname << "," << s[i].Lastname << "," << s[i].Firstname << "," << s[i].Gender << "," << s[i].DoB << endl;
			n--;
			i++;
		}
		fout.close();
	}
}

void importCourses(string &nameyear, string &namesemester)
{
	Course s[100];
	Course* import = s;
	int n = 0, i = 0;
	ifstream fin;
	fin.open(nameyear + "_" + namesemester + ".csv");
	if (!fin.is_open()) {
		cout << "Can not open file csv !";
		system("pause");
		return;
	}
	else
	{
		fin.ignore(1000, '\n');
		while (getline(fin, s[i].No, ',') && getline(fin, s[i].ID, ',') && getline(fin, s[i].Name, ',') && getline(fin, s[i].Class, ',') && getline(fin, s[i].LecturerAcc, ',') && getline(fin, s[i].LectureName, ',') && getline(fin, s[i].StartDate, ',') &&
			getline(fin, s[i].EndDate, ',') && getline(fin, s[i].DayofWeek, ',') && getline(fin, s[i].StartHour, ',') && getline(fin, s[i].EndHour, ',') && getline(fin, s[i].Room, '\n'))
		{
			i++;
			n++;
		}
	}
	fin.close();

	// Save to text file
	ofstream fout;
	fout.open(nameyear + "_" + namesemester + ".txt");
	if (!fout.is_open()) {
		cout << "Can not open file !";
		system("pause");
		return;
	}
	else {
		i = 0;
		fout << n << endl;
		while (n != 0) {
			fout << s[i].No << "," << s[i].ID << "," << s[i].Name << "," << s[i].Class << "," << s[i].LecturerAcc << ","
				<< s[i].LectureName << "," << s[i].StartDate << "," << s[i].EndDate << ","
				<< s[i].DayofWeek << "," << s[i].StartHour << "," << s[i].EndHour << "," << s[i].Room << endl;
			n--;
			i++;
		}
		fout.close();
	}
	cout << "Importation complete!\n";
}

void importScoreboard(string &courseID, string &classname) {
	scoreboard s[20];
	int n = 0, i = 0;
	ifstream fin;
	fin.open(courseID + "_" + classname + "_Scoreboard.csv");
	if (!fin.is_open()) {
		cout << "Can not open file csv !";
		system("pause");
		return;
	}
	else
	{
		fin.ignore(1000, '\n');
		while (getline(fin, s[i].No, ',') && getline(fin, s[i].ID, ',') && getline(fin, s[i].mid, ',') && getline(fin, s[i].Final, ',')
			&& getline(fin, s[i].bonus, ',') && getline(fin, s[i].aveg, '\n'))
		{
			i++;
			n++;
		}
	}
	fin.close();

	// Save to text file
	ofstream fout;
	fout.open(courseID + '_' + classname + "_Scoreboard.txt");
	if (!fout.is_open()) {
		cout << "Can not open file !";
		system("pause");
		return;
	}
	else {
		i = 0;
		fout << n << endl;
		while (n != 0) {
			fout << s[i].No << "," << s[i].ID << "," << s[i].mid << "," << s[i].Final << "," << s[i].bonus << "," << s[i].aveg << endl;
			n--;
			i++;
		}
		fout.close();
	}
	cout << "Importation complete!\n";
}

void exportScoreboard(string &courseID, string &classname) {
	ifstream fin;
	scoreboard s[100];
	int n;
	fin.open(courseID + '_' + classname + "_Scoreboard.txt");
	if (!fin.is_open()) {
		cout << "Can not open file txt !";
		system("pause");
		return;
	}
	else
	{
		fin >> n;
		fin.ignore(1000, '\n');
		for (int i = 0; i < n; ++i)
		{
			getline(fin, s[i].No, ',');
			getline(fin, s[i].ID, ',');
			getline(fin, s[i].mid, ',');
			getline(fin, s[i].Final, ',');
			getline(fin, s[i].bonus, ',');
			getline(fin, s[i].aveg, '\n');
		}
	}
	fin.close();
	// Save to csv file
	ofstream fout;
	fout.open(courseID + '_' + classname + "_Scoreboard.csv");
	if (!fout.is_open()) {
		cout << "Can not open file !";
		system("pause");
		return;
	}
	else {
		int i = 0;
		fout << "No,ID,Midterm,Final,Bonus,Average\n";
		while (n != 0) {
			fout << s[i].No << "," << s[i].ID << "," << s[i].mid << "," << s[i].Final << "," << s[i].bonus << "," << s[i].aveg << endl;
			n--;
			i++;
		}
		fout.close();
	}
	cout << "Exportation completete!\n";
}

bool SavetoListofClass(string namefile)
{
	ofstream fout;
	fout.open("ListofClass.txt", ios::app);
	if (!fout.is_open()) return false;
	fout << namefile << endl;
	fout.close();
	return true;
}

int LengthofStudenlist(StudentList &slst)
{
	student* cur = slst.pHead;
	if (cur == nullptr) return 0;
	int count = 1;
	while (cur->pNext != nullptr)
	{
		cur = cur->pNext;
		count++;
	}
	return count;
}

int LengthofScoreBoardlist(ScoreBoardList &sclst)
{
	scoreboard* cur = sclst.pHead;
	if (cur == nullptr) return 0;
	int count = 1;
	while (cur->pNext != nullptr)
	{
		cur = cur->pNext;
		count++;
	}
	return count;
}

int LengthofClasslist(ClassList &clst)
{
	Classes* cur = clst.pHead;
	if (cur == nullptr) return 0;
	int count = 1;
	while (cur->pNext != nullptr)
	{
		cur = cur->pNext;
		count++;
	}
	return count;
}

int LengthofYearlist(YearList &ylst)
{
	year* cur = ylst.pHead;
	if (cur == nullptr) return 0;
	int count = 1;
	while (cur->pNext != nullptr)
	{
		cur = cur->pNext;
		count++;
	}
	return count;
}

int LengthofSemeterlist(SemesterList &selst)
{
	Semester* cur = selst.pHead;
	if (cur == nullptr) return 0;
	int count = 1;
	while (cur->pNext != nullptr)
	{
		cur = cur->pNext;
		count++;
	}
	return count;
}

int LengthofCourselist(CourseList &colst)
{
	Course* cur = colst.pHead;
	if (cur == nullptr) return 0;
	int count = 1;
	while (cur->pNext != nullptr)
	{
		cur = cur->pNext;
		count++;
	}
	return count;
}

//menu admin 
void MenuClassAdmin(string &username)
{
	clrscr();
	string name = "ListofClass";
	string namefile, namefile1, id, newid, lastname, firstname, gender, dob;
	gotoXY(42, 4);
	cout << "Import student ";
	gotoXY(42, 8);
	cout << "Add student ";
	gotoXY(42, 12);
	cout << "Edit an existing student ";
	gotoXY(42, 16);
	cout << "Remove a student ";
	gotoXY(42, 20);
	cout << "Change student ";
	gotoXY(42, 24);
	cout << "View list of class and student ";
	gotoXY(42, 28);
	TextColor(1);
	cout << "Return Menu ";
	TextColor(7);
	int x = 42, y = 4;
	int a = 28, b = 4;
	int key = inputKey();
	gotoXY(x, y);
	while (key != 13)
	{
		MoveMouse(key, x, y, a, b);
		gotoXY(x, y);
		key = inputKey();
	}
	if (y == 4) {
		clrscr();
		ClassList clst;
		cout << "Please enter namefile you want to import student : ";
		getline(cin, namefile, '\n');
		importStudent(namefile);//import student
		loadClass(name, clst);
		int lengthofclass = LengthofClasslist(clst);
		Classes* temp = new Classes;
		temp->name = namefile;
		temp->pNext = NULL;
		if (temp == NULL)
			return;
		if (clst.pHead == NULL && clst.pTail == NULL)
		{
			clst.pHead = clst.pTail = temp;
		}
		else
		{
			clst.pTail->pNext = temp;
			clst.pTail = temp;
		}
		if (SaveClass(name, clst)) cout << "Import completely." << endl;
		RemoveClass(clst);
		// creat account student
		StudentList slst;
		loadStudent(namefile, slst);
		student* cur = slst.pHead;
		while (cur != nullptr)
		{
			AddAccountStudent(cur->ID, cur->DoB);
			cur = cur->pNext;
		}
		RemoveStudent(slst);
		cout << "If you want to go back , Please enter esc." << endl;
		key = inputKey();
		while (key != 27)
		{
			key = inputKey();
		}
		MenuClassAdmin(username);
	}
	//Add a student
	else if (y == 8)
	{
		clrscr();
		ClassList clst;
		loadClass(name, clst);
		int m = LengthofClasslist(clst);
		Classes* cur = clst.pHead;
		string* c = new string[m];
		cout << "  Please choose class you want to add a student : ";
		for (int i = 0; i < m; i++)
		{
			gotoXY(42, 4 * (i + 1));
			cout << cur->name;
			c[i] = cur->name;
			cur = cur->pNext;
		}
		RemoveClass(clst);
		int i = 0;
		int x = 42, y = 4 * (i + 1);
		int key = inputKey();
		gotoXY(x, y);
		while (key != 13)
		{
			if (key == key_Down && y < 4 * m)
			{
				i++;
				y = 4 * (i + 1);
			}
			if (key == key_Up && y > 4)
			{
				i--;
				y = 4 * (i + 1);
			}
			gotoXY(x, y);
			key = inputKey();
		}
		for (int j = 0; j < m; j++)
		{
			if (j == i)
			{
				namefile = c[j];
				delete[]c;
				clrscr();
				StudentList slst;
				loadStudent(namefile, slst);
				int n = LengthofStudenlist(slst);
				student* temp = new student;
				temp->classname = namefile;
				cout << "Please enter the id of student you want to add : ";
				getline(cin, temp->ID, '\n');
				cout << "Please enter the last name of student you want to add : ";
				getline(cin, temp->Lastname, '\n');
				cout << "Please enter the first name of student you want to add : ";
				getline(cin, temp->Firstname, '\n');
				cout << "Please enter the gender of student you want to add : ";
				getline(cin, temp->Gender, '\n');
				cout << "Please enter the day of birth of student you want to add (ddmmyy) : ";
				getline(cin, temp->DoB, '\n');
				temp->pNext = nullptr;
				if (temp == NULL)
					return;
				if (slst.pHead == NULL || slst.pTail == NULL)
				{
					slst.pHead = slst.pTail = temp;
				}
				else
				{
					slst.pTail->pNext = temp;
					slst.pTail = temp;
				}
				n++;
				AddStudenttoClassofCourse(temp->ID, temp->Lastname, temp->Firstname, temp->Gender, temp->DoB, namefile);
				// update and check account student
				AccountStudentList aclst;
				loadAccountStudent(aclst);
				AccountStudent* now = aclst.pHead;
				while (now != nullptr)
				{
					if (temp->ID == now->ID) break;
					now = now->pNext;
				}
				if (now == nullptr) {
					AddAccountStudent(temp->ID, temp->DoB);
				}
				RemoveAccountStudent(aclst);
				if (SaveStudent(namefile, n, slst)) cout << "Add a student to class " << namefile << " completely.\n";
				RemoveStudent(slst);
				cout << "If you want to go back , Please enter esc." << endl;
				int key = inputKey();
				while (key != 27)
				{
					key = inputKey();
				}
				if (key == 27) MenuClassAdmin(username);
			}
		}
	}
	//edit
	else if (y == 12)
	{
		//edit existing student
		clrscr();
		ClassList clst;
		loadClass(name, clst);
		int m = LengthofClasslist(clst);
		Classes* cur = clst.pHead;
		string* c = new string[m];
		gotoXY(20, 0);
		cout << "Please choose class of student you want to edit : ";
		for (int i = 0; i < m; i++)
		{
			gotoXY(42, 4 * (i + 1));
			cout << cur->name;
			c[i] = cur->name;
			cur = cur->pNext;
		}
		RemoveClass(clst);
		int i = 0;
		int x = 42, y = 4 * (i + 1);
		int key = inputKey();
		gotoXY(x, y);
		while (key != 13)
		{
			if (key == key_Down && y < 4 * m)
			{
				i++;
				y = 4 * (i + 1);
			}
			if (key == key_Up && y > 4)
			{
				i--;
				y = 4 * (i + 1);
			}
			gotoXY(x, y);
			key = inputKey();
		}
		for (int j = 0; j < m; j++)
		{
			if (j == i)
			{
				namefile = c[j];
				delete[]c;
				clrscr();
				StudentList slst;
				loadStudent(namefile, slst);
				int n = LengthofStudenlist(slst);
				student* temp = slst.pHead;
				string* stu = new string[n];
				gotoXY(20, 0);
				cout << "Please choose the ID of student you want to edit : ";
				for (int i = 0; i < n; i++)
				{
					gotoXY(42, 2 * (i + 1));
					cout << temp->ID;
					stu[i] = temp->ID;
					temp = temp->pNext;
				}
				int m = 0;
				int x = 42, y = 2 * (m + 1);
				key = inputKey();
				gotoXY(x, y);
				while (key != 13)
				{
					if (key == key_Down && y < 2 * n)
					{
						m++;
						y = 2 * (m + 1);
					}
					if (key == key_Up && y > 2)
					{
						m--;
						y = 2 * (m + 1);
					}
					gotoXY(x, y);
					key = inputKey();
				}
				for (int k = 0; k < n; k++)
				{
					if (k == m)
					{
						id = stu[k];
						delete[]stu;
						clrscr();
						student* cur = slst.pHead;
						while (cur != nullptr)
						{
							if (cur->ID == id) break;
							cur = cur->pNext;
						}
						cout << "Which data do you want to edit : ";
						gotoXY(11, 2);
						cout << "ID ";
						gotoXY(11, 4);
						cout << "Last Name ";
						gotoXY(11, 6);
						cout << "First Name ";
						gotoXY(11, 8);
						cout << "Gender ";
						gotoXY(11, 10);
						cout << "Date of birth ";
						int x = 11, y = 2;
						int key = inputKey();
						gotoXY(x, y);
						while (key != 13)
						{
							if (key == key_Down && y < 10)
							{
								y += 2;
							}
							if (key == key_Up && y > 2)
							{
								y -= 2;
							}
							gotoXY(x, y);
							key = inputKey();
						}
						if (y == 2)
						{
							gotoXY(0, 11);
							cout << "Please enter new Id of this student : ";
							getline(cin, newid, '\n');
							cur->ID = newid;
							AccountStudentList acslst;
							loadAccountStudent(acslst);
							AccountStudent* now = acslst.pHead;
							while (now != nullptr)
							{
								if (now->ID == id)
								{
									now->ID = newid;
									break;
								}
								now = now->pNext;
							}
							if (SaveAccountStudent(acslst)) cout << "Update account student completely.\n";
							RemoveAccountStudent(acslst);
						}
						else if (y == 4)
						{
							gotoXY(0, 11);
							cout << "Please enter new last name of this student : ";
							getline(cin, cur->Lastname, '\n');
							newid = id;
						}
						else if (y == 6)
						{
							gotoXY(0, 11);
							cout << "Please enter new fisrt name of this student : ";
							getline(cin, cur->Firstname, '\n');
							newid = id;
						}
						else if (y == 8)
						{
							gotoXY(0, 11);
							cout << "Please enter new gender of this student : ";
							getline(cin, cur->Gender, '\n');
							newid = id;
						}
						else if (y == 10)
						{
							gotoXY(0, 11);
							cout << "Please enter new date of birth of this student : ";
							getline(cin, cur->DoB, '\n');
							newid = id;
							AccountStudentList acslst;
							loadAccountStudent(acslst);
							AccountStudent* now = acslst.pHead;
							while (now != nullptr)
							{
								if (now->ID == id)
								{
									now->ID = newid;
									now->DoB = cur->DoB;
									break;
								}
								now = now->pNext;
							}
							if (SaveAccountStudent(acslst)) cout << "Update account student completely.\n";
							RemoveAccountStudent(acslst);
						}
						gotoXY(0, 13);
						if (SaveStudent(namefile, LengthofStudenlist(slst), slst)) cout << "Edit a student and save completely.\n";
						UpdateClassofCourse(id, newid, cur->Lastname, cur->Firstname, cur->Gender, cur->DoB, namefile);
						RemoveStudent(slst);
						cout << "If you want to go back , Please enter esc." << endl;
						key = inputKey();
						while (key != 27)
						{
							key = inputKey();
						}
						MenuClassAdmin(username);
					}
				}
			}
		}
	}
	//remove student
	else if (y == 16)
	{
		//remove student
		clrscr();
		ClassList clst;
		loadClass(name, clst);
		int m = LengthofClasslist(clst);
		Classes* cur = clst.pHead;
		string* c = new string[m];
		cout << "   Please choose class of student you want to remove : ";
		for (int i = 0; i < m; i++)
		{
			gotoXY(42, 4 * (i + 1));
			cout << cur->name;
			c[i] = cur->name;
			cur = cur->pNext;
		}
		RemoveClass(clst);
		int i = 0;
		int x = 42, y = 4 * (i + 1);
		int key = inputKey();
		gotoXY(x, y);
		while (key != 13)
		{
			if (key == key_Down && y < 4 * m)
			{
				i++;
				y = 4 * (i + 1);
			}
			if (key == key_Up && y > 4)
			{
				i--;
				y = 4 * (i + 1);
			}
			gotoXY(x, y);
			key = inputKey();
		}
		for (int j = 0; j < m; j++)
		{
			if (j == i)
			{
				namefile = c[j];
				delete[]c;
				clrscr();
				StudentList slst;
				loadStudent(namefile, slst);
				int n = LengthofStudenlist(slst);
				student* temp = slst.pHead;
				string* stu = new string[n];
				cout << "   Please choose the ID of student you want to remove : ";
				for (int i = 0; i < n; i++)
				{
					gotoXY(42, 2 * (i + 1));
					cout << temp->ID;
					stu[i] = temp->ID;
					temp = temp->pNext;
				}
				int m = 0;
				int x = 42, y = 2 * (m + 1);
				key = inputKey();
				gotoXY(x, y);
				while (key != 13)
				{
					if (key == key_Down && y < 2 * n)
					{
						m++;
						y = 2 * (m + 1);
					}
					if (key == key_Up && y > 2)
					{
						m--;
						y = 2 * (m + 1);
					}
					gotoXY(x, y);
					key = inputKey();
				}
				for (int k = 0; k < n; k++)
				{
					if (k == m)
					{
						id = stu[k];
						delete[]stu;
						student*cur = slst.pHead;
						if (cur->ID == id)
						{
							slst.pHead = slst.pHead->pNext;
							delete cur;
						}
						else
						{
							while (cur->pNext != nullptr)
							{
								if (cur->pNext->ID == id)
								{
									student* temp = cur->pNext;
									cur->pNext = temp->pNext;
									delete temp;
									break;
								}
								cur = cur->pNext;
							}
						}
						clrscr();
						n--;
						if (SaveStudent(namefile, n, slst)) cout << "Remove the student completely .\n";
						RemoveStudent(slst);
						RemoveStudentInClassofCourse(id, namefile);
						cout << "If you want to go back , Please enter esc." << endl;
						key = inputKey();
						while (key != 27)
						{
							key = inputKey();
						}
						MenuClassAdmin(username);
					}
				}
			}
		}
	}
	//change
	else if (y == 20) {
		//change
		clrscr();
		ClassList clst;
		loadClass(name, clst);
		int m = LengthofClasslist(clst);
		Classes* now = clst.pHead;
		string* c = new string[m];
		gotoXY(20, 0);
		TextColor(1);
		cout << "Please choose class of student you want to change from it :";
		TextColor(7);
		for (int i = 0; i < m; i++)//Display list of class for you to choose
		{
			gotoXY(42, 4 * (i + 1));
			cout << now->name;
			c[i] = now->name;
			now = now->pNext;
		}
		RemoveClass(clst);
		int i = 0;
		int x = 42, y = 4 * (i + 1);
		int key = inputKey();
		gotoXY(x, y);
		while (key != 13)
		{
			if (key == key_Down && y < 4 * m)
			{
				i++;
				y = 4 * (i + 1);
			}
			if (key == key_Up && y > 4)
			{
				i--;
				y = 4 * (i + 1);
			}
			gotoXY(x, y);
			key = inputKey();
		}
		for (int j = 0; j < m; j++)
		{
			if (j == i)
			{
				namefile = c[j];
				clrscr();
				StudentList slst1;
				loadStudent(namefile, slst1);
				int n = LengthofStudenlist(slst1);
				gotoXY(20, 0);
				TextColor(1);
				cout << "Please choose the ID of student you want to change : ";
				TextColor(7);
				student* temp = slst1.pHead;
				string* stu = new string[n];
				for (int i = 0; i < n; i++)//Display list of id of student for you to choose
				{
					gotoXY(42, 2 * (i + 1));
					cout << temp->ID;
					stu[i] = temp->ID;
					temp = temp->pNext;
				}
				int i = 0;
				int x = 42, y = 2 * (i + 1);
				key = inputKey();
				gotoXY(x, y);
				while (key != 13)
				{
					if (key == key_Down && y < 2 * n)
					{
						i++;
						y = 2 * (i + 1);
					}
					if (key == key_Up && y > 2)
					{
						i--;
						y = 2 * (i + 1);
					}
					gotoXY(x, y);
					key = inputKey();
				}
				for (int k = 0; k < n; k++)
				{
					if (k == i)
					{
						id = stu[k];
						delete[]stu;
						student* cur = slst1.pHead;
						if (cur->ID == id)
						{
							slst1.pHead = slst1.pHead->pNext;
							delete cur;
						}
						else
						{
							while (cur->pNext != nullptr)
							{
								if (cur->pNext->ID == id)
								{
									student* temp = cur->pNext;
									id = temp->ID;
									lastname = temp->Lastname;
									firstname = temp->Firstname;
									gender = temp->Gender;
									dob = temp->DoB;
									cur->pNext = temp->pNext;
									delete temp;
									break;
								}
								cur = cur->pNext;
							}
						}
						SaveStudent(namefile, n - 1, slst1);
						RemoveStudent(slst1);
						clrscr();
						loadClass(name, clst);
						gotoXY(20, 0);
						TextColor(1);
						cout << "Please enter the class of the student you want to change to it : ";
						TextColor(7);
						for (int i = 0; i < m; i++)//Display list of class for you to choose
						{
							gotoXY(42, 4 * (i + 1));
							cout << c[i];
						}
						RemoveClass(clst);
						int i = 0;
						int x = 42, y = 4 * (i + 1);
						int key = inputKey();
						gotoXY(x, y);
						while (key != 13)
						{
							if (key == key_Down && y < 4 * m)
							{
								i++;
								y = 4 * (i + 1);
							}
							if (key == key_Up && y > 4)
							{
								i--;
								y = 4 * (i + 1);
							}
							gotoXY(x, y);
							key = inputKey();
						}
						for (k = 0; k < m; k++)
						{
							if (k == i)
							{
								namefile1 = c[k];
								delete[]c;
								StudentList slst2;
								loadStudent(namefile1, slst2);
								int l = LengthofStudenlist(slst2);
								student* temp = new student;
								temp->ID = id;
								temp->Lastname = lastname;
								temp->Firstname = firstname;
								temp->Gender = gender;
								temp->DoB = dob;
								temp->classname = namefile1;
								temp->pNext = nullptr;
								if (temp == NULL)
									return;
								if (slst2.pHead == NULL || slst2.pTail == NULL)
								{
									slst2.pHead = slst2.pTail = temp;
								}
								else
								{
									slst2.pTail->pNext = temp;
									slst2.pTail = temp;
								}
								clrscr();
								if (SaveStudent(namefile1, l + 1, slst2)) cout << "Change student from class " << namefile << " to class " << namefile1 << "completely .\n";
								RemoveStudent(slst2);
								ChangeStudentInClassofCourse(id, lastname, firstname, gender, dob, namefile, namefile1);
								cout << "If you want to go back , Please enter esc." << endl;
								key = inputKey();
								while (key != 27)
								{
									key = inputKey();
								}
								MenuClassAdmin(username);
							}
						}
					}
				}
			}
		}
	}
	//view all
	else if (y == 24) {
		//view all
		clrscr();
		ClassList clst;
		StudentList slst;
		string name = "ListofClass";
		loadClass(name, clst);
		Classes* cur = clst.pHead;
		int n = LengthofClasslist(clst);
		string* s = new string[n];
		for (int i = 0; i < n; i++)
		{
			gotoXY(42, 4 * (i + 1));
			cout << cur->name;
			s[i] = cur->name;
			cur = cur->pNext;
		}
		RemoveClass(clst);
		int i = 0;
		int x = 42, y = 4 * (i + 1);
		int key = inputKey();
		gotoXY(x, y);
		while (key != 13)
		{
			if (key == key_Down && y < 4 * n)
			{
				i++;
				y = 4 * (i + 1);
			}
			if (key == key_Up && y > 4)
			{
				i--;
				y = 4 * (i + 1);
			}
			gotoXY(x, y);
			key = inputKey();
		}
		for (int j = 0; j < n; j++)
		{
			if (i == j)
			{
				clrscr();
				string choice = s[j];
				delete[]s;
				loadStudent(choice, slst);
				student* curs = slst.pHead;
				TextColor(9);
				cout << "No";
				gotoXY(8, 0);
				cout << "Id";
				gotoXY(20, 0);
				cout << "Last Name";
				gotoXY(35, 0);
				cout << "First Name";
				gotoXY(50, 0);
				cout << "Gender";
				gotoXY(60, 0);
				cout << "Date of Birth" << endl;
				TextColor(7);
				int i = 0;
				while (curs != nullptr)
				{
					cout << curs->No;
					gotoXY(5, 1 + i);
					cout << curs->ID;
					gotoXY(20, 1 + i);
					cout << curs->Lastname;
					gotoXY(35, 1 + i);
					cout << curs->Firstname;
					gotoXY(50, 1 + i);
					cout << curs->Gender;
					gotoXY(60, 1 + i);
					cout << curs->DoB.substr(0, 2) << "/" << curs->DoB.substr(2, 2) << "/" << curs->DoB.substr(4, 4) << endl;
					curs = curs->pNext;
					i++;
				}
				RemoveStudent(slst);
				cout << "If you want to go back , Please enter esc." << endl;
				key = inputKey();
				while (key != 27)
				{
					key = inputKey();
				}
				MenuClassAdmin(username);
			}
		}
	}
	else
	{
		Menu(username);
	}
}

void MenuCourseAdmin(string &username)
{
	clrscr();
	YearList ylst;
	string name = "ListofYear";
	string yname;
	loadYear(name, ylst);
	year* cur = ylst.pHead;
	int n = LengthofYearlist(ylst);
	string* s = new string[n];
	for (int i = 0; i < n; i++)
	{
		gotoXY(38, 4 * (i + 1));
		cout << cur->name;
		s[i] = cur->name;
		cur = cur->pNext;
	}
	gotoXY(64, 6);
	cout << "Create Year";
	gotoXY(64, 8);
	cout << "Update Year";
	gotoXY(64, 10);
	cout << "Delete Year";
	gotoXY(64, 12);
	TextColor(1);
	cout << "Return Menu";
	TextColor(7);
	int i = 0;
	int x = 38, y = 4 * (i + 1);
	int key = inputKey();
	int leftlimit = 38, rightlimit = 64, upperlimitleft = 4 * n, downlimitleft = 4, upperlimitright = 12, downlimitright = 6;
	gotoXY(x, y);
	while (key != 13)
	{
		MoveAndEdit(key, x, y, i, leftlimit, rightlimit, upperlimitleft, downlimitleft, upperlimitright, downlimitright);
		gotoXY(x, y);
		key = inputKey();
	}
	if (x == rightlimit) {
		if (y == 6)
		{
			clrscr();
			year* temp = new year;
			cout << "Please enter name of year you want to create : ";
			getline(cin, temp->name, '\n');
			temp->pNext = nullptr;
			if (temp == NULL)
				return;
			if (ylst.pHead == NULL || ylst.pTail == NULL)
			{
				ylst.pHead = ylst.pTail = temp;
			}
			else
			{
				ylst.pTail->pNext = temp;
				ylst.pTail = temp;
			}
			cout << "Please create semeter for year .\n";
			cout << "How many semeter you want to create : ";
			cin >> n;
			cin.ignore(1000, '\n');
			ofstream fout;
			fout.open(temp->name + ".txt");
			string* se = new string[n];
			for (int i = 0; i < n; i++)
			{
				cout << "Please enter name of semester : ";
				getline(cin, se[i], '\n');
				fout << se[i] << endl;
				ofstream creatfile;
				creatfile.open(temp->name + "_" + se[i] + ".txt");
				creatfile << "0";
				creatfile.close();
			}
			fout << "0";
			fout.close();
			delete[]se;
			if (SaveYear(name, ylst)) cout << "Create a year and save completely .\n";
			cout << "If you want to go back , Please enter esc." << endl;
			key = inputKey();
			while (key != 27)
			{
				key = inputKey();
			}
			if (key == 27) MenuCourseAdmin(username);
		}
		else if (y == 8)
		{
			clrscr();
			gotoXY(25, 0);
			TextColor(1);
			cout << "Please choose the semester you want to update : ";
			TextColor(7);
			for (int i = 0; i < n; i++)
			{
				gotoXY(42, 4 * (i + 1));
				cout << s[i];
			}
			int i = 0;
			int x = 42, y = 4 * (i + 1);
			int key = inputKey();
			gotoXY(x, y);
			while (key != 13)
			{
				if (key == key_Down && y < 4 * n)
				{
					i++;
					y = 4 * (i + 1);
				}
				if (key == key_Up && y > 4)
				{
					i--;
					y = 4 * (i + 1);
				}
				gotoXY(x, y);
				key = inputKey();
			}
			for (int j = 0; j < n; j++)
			{
				if (j == i)
				{
					yname = s[i];
					delete[]s;
					gotoXY(0, 4 * (n + 1));
					cout << "Plese enter the new name of year : ";
					cur = ylst.pHead;
					while (cur != nullptr)
					{
						if (cur->name == yname)
						{
							getline(cin, cur->name, '\n');
							break;
						}
						cur = cur->pNext;
					}
					string oldfile = yname + ".txt";
					string newfile = cur->name + ".txt";
					const char* old_file = oldfile.c_str();
					const char* new_file = newfile.c_str();
					int re = rename(old_file, new_file);
					SemesterList selst;
					loadSemester(cur->name, selst);
					int change;
					Semester* temp = selst.pHead;
					while (temp != nullptr)
					{
						oldfile = yname + "_" + temp->name + ".txt";
						newfile = cur->name + "_" + temp->name + ".txt";
						const char* old_file = oldfile.c_str();
						const char* new_file = newfile.c_str();
						change = rename(old_file, new_file);
						if (change != 0) cout << "Change fail at " << yname << temp->name;
						temp = temp->pNext;
					}
					if (SaveYear(name, ylst) && re == 0) cout << "Update year and save completely .\n";
					RemoveYear(ylst);
					cout << "If you want to go back , Please enter esc." << endl;
					key = inputKey();
					while (key != 27)
					{
						key = inputKey();
					}
					if (key == 27) MenuCourseAdmin(username);
				}
			}
		}
		else if (y == 10)
		{
			clrscr();
			gotoXY(25, 0);
			TextColor(1);
			cout << "Please choose the year you want to delete : ";
			TextColor(7);
			for (int i = 0; i < n; i++)
			{
				gotoXY(42, 4 * (i + 1));
				cout << s[i];
			}
			int i = 0;
			int x = 42, y = 4 * (i + 1);
			int key = inputKey();
			gotoXY(x, y);
			while (key != 13)
			{
				if (key == key_Down && y < 4 * n)
				{
					i++;
					y = 4 * (i + 1);
				}
				if (key == key_Up && y > 4)
				{
					i--;
					y = 4 * (i + 1);
				}
				gotoXY(x, y);
				key = inputKey();
			}
			for (int j = 0; j < n; j++)
			{
				if (j == i)
				{
					yname = s[j];
					delete[]s;
					cur = ylst.pHead;
					if (cur->name == yname)
					{
						ylst.pHead = ylst.pHead->pNext;
						delete cur;
					}
					else
					{
						while (cur->pNext != nullptr)
						{
							if (cur->pNext->name == yname)
							{
								year* temp = cur->pNext;
								cur->pNext = temp->pNext;
								delete temp;
								break;
							}
							cur = cur->pNext;
						}
					}
					gotoXY(0, 4 * (n + 1));
					if (SaveYear(name, ylst)) cout << "Delete year and save completely .\n";
					cout << "If you want to go back , Please enter esc." << endl;
					key = inputKey();
					while (key != 27)
					{
						key = inputKey();
					}
					if (key == 27) MenuCourseAdmin(username);
				}
			}
		}
		else
		{
			RemoveYear(ylst);
			Menu(username);
		}
	}
	else
	{
		n = LengthofYearlist(ylst);
		RemoveYear(ylst);
		for (int j = 0; j < n; j++)
		{
			if (j == i)
			{
				string choice = s[j];
				delete[]s;
				MenuSemester(choice, username);
			}
		}
	}
}

void MenuSemester(string &nameyear, string &username)
{
	clrscr();
	string sename, newsemestername;
	SemesterList selst;
	loadSemester(nameyear, selst);
	Semester* cur = selst.pHead;
	int n = LengthofSemeterlist(selst);
	string* se = new string[n];
	for (int i = 0; i < n; i++)
	{
		gotoXY(38, 4 * (i + 1));
		cout << cur->name;
		se[i] = cur->name;
		cur = cur->pNext;
	}
	gotoXY(64, 6);
	cout << "Create Semester";
	gotoXY(64, 8);
	cout << "Update Semester";
	gotoXY(64, 10);
	cout << "Delete Semester";
	gotoXY(64, 12);
	TextColor(2);
	cout << "Return Menu of Year";
	gotoXY(64, 14);
	TextColor(1);
	cout << "Return Menu";
	TextColor(7);
	int i = 0;
	int x = 38, y = 4 * (i + 1);
	int key = inputKey();
	int leftlimit = 38, rightlimit = 64, upperlimitleft = 4 * n, downlimitleft = 4, upperlimitright = 14, downlimitright = 6;
	gotoXY(x, y);
	while (key != 13)
	{
		MoveAndEdit(key, x, y, i, leftlimit, rightlimit, upperlimitleft, downlimitleft, upperlimitright, downlimitright);
		gotoXY(x, y);
		key = inputKey();
	}
	if (x == rightlimit)
	{
		if (y == 6)
		{
			clrscr();
			Semester* temp = new Semester;
			cout << "Please enter name of semester you want to create : ";
			getline(cin, temp->name, '\n');
			temp->pNext = nullptr;
			if (temp == NULL)
				return;
			if (selst.pHead == NULL || selst.pTail == NULL)
			{
				selst.pHead = selst.pTail = temp;
			}
			else
			{
				selst.pTail->pNext = temp;
				selst.pTail = temp;
			}
			if (SaveSemester(nameyear, selst)) cout << "Create a semester and save completely .\n";
			cout << "If you want to go back , Please enter esc." << endl;
			key = inputKey();
			while (key != 27)
			{
				key = inputKey();
			}
			if (key == 27) MenuSemester(nameyear, username);
		}
		else if (y == 8)
		{
			clrscr();
			gotoXY(25, 0);
			TextColor(1);
			cout << "Please choose the semester you want to update : ";
			TextColor(7);
			for (int i = 0; i < n; i++)
			{
				gotoXY(42, 4 * (i + 1));
				cout << se[i];
			}
			int i = 0;
			int x = 42, y = 4 * (i + 1);
			int key = inputKey();
			gotoXY(x, y);
			while (key != 13)
			{
				if (key == key_Down && y < 4 * n)
				{
					i++;
					y = 4 * (i + 1);
				}
				if (key == key_Up && y > 4)
				{
					i--;
					y = 4 * (i + 1);
				}
				gotoXY(x, y);
				key = inputKey();
			}
			for (int j = 0; j < n; j++)
			{
				if (j == i)
				{
					sename = se[j];
					delete[]se;
					gotoXY(0, 4 * (n + 1));
					cout << "Plese enter the new name of semester : ";
					cur = selst.pHead;
					while (cur != nullptr)
					{
						if (cur->name == sename)
						{
							getline(cin, cur->name, '\n');
							break;
						}
						cur = cur->pNext;
					}
					string oldfile = nameyear + "_" + sename + ".txt";
					string newfile = nameyear + "_" + cur->name + ".txt";
					const char* old_file = oldfile.c_str();
					const char* new_file = newfile.c_str();
					int re = rename(old_file, new_file);
					if (SaveSemester(nameyear, selst) && re == 0) cout << "Update semeter and save completely .\n";
					cout << "If you want to go back , Please enter esc." << endl;
					key = inputKey();
					while (key != 27)
					{
						key = inputKey();
					}
					if (key == 27) MenuSemester(nameyear, username);
				}
			}
		}
		else if (y == 10)
		{
			clrscr();
			gotoXY(25, 0);
			TextColor(1);
			cout << "Please choose the semester you want to delete : ";
			TextColor(7);
			for (int i = 0; i < n; i++)
			{
				gotoXY(42, 4 * (i + 1));
				cout << se[i];
			}
			int i = 0;
			int x = 42, y = 4 * (i + 1);
			int key = inputKey();
			gotoXY(x, y);
			while (key != 13)
			{
				if (key == key_Down && y < 4 * n)
				{
					i++;
					y = 4 * (i + 1);
				}
				if (key == key_Up && y > 4)
				{
					i--;
					y = 4 * (i + 1);
				}
				gotoXY(x, y);
				key = inputKey();
			}
			for (int j = 0; j < n; j++)
			{
				if (j == i)
				{
					sename = se[j];
					delete[]se;
					cur = selst.pHead;
					if (cur->name == sename)
					{
						selst.pHead = selst.pHead->pNext;
						delete cur;
					}
					else
					{
						while (cur->pNext != nullptr)
						{
							if (cur->pNext->name == sename)
							{
								Semester* temp = cur->pNext;
								cur->pNext = temp->pNext;
								delete temp;
								break;
							}
							cur = cur->pNext;
						}
					}
					gotoXY(0, 4 * (n + 1));
					if (SaveSemester(nameyear, selst)) cout << "Delete semester and save completely .\n";
					cout << "If you want to go back , Please enter esc." << endl;
					key = inputKey();
					while (key != 27)
					{
						key = inputKey();
					}
					if (key == 27) MenuSemester(nameyear, username);
				}
			}
		}
		else if (y == 12)
		{
			RemoveSemester(selst);
			MenuCourseAdmin(username);
		}
		else
		{
			Menu(username);
		}
		RemoveSemester(selst);
	}
	else
	{
		for (int j = 0; j < n; j++)
		{
			if (i == j)
			{
				string choice = se[j];
				delete[]se;
				MenuCourse(nameyear, choice, username);
			}
		}
	}
}

void MenuCourse(string &nameyear, string &namesemester, string &username)
{
	clrscr();
	string namecourse = nameyear + "_" + namesemester, id_course, classname;
	bool check = true;
	gotoXY(42, 4);
	cout << "Course";
	gotoXY(42, 8);
	cout << "Lecture";
	gotoXY(42, 12);
	cout << "Score Board";
	gotoXY(42, 16);
	TextColor(8);
	cout << "Return Menu of Semester";
	gotoXY(42, 20);
	TextColor(9);
	cout << "Return Menu";
	TextColor(7);
	int x = 42, y = 4;
	int key = inputKey();
	int a = 20, b = 4;
	gotoXY(x, y);
	while (key != 13)
	{
		MoveMouse(key, x, y, a, b);
		gotoXY(x, y);
		key = inputKey();
	}
	if (y == 4)
	{
		OperationCourse(nameyear, namesemester, username);
	}
	//lecturer
	else if (y == 8)
	{
		clrscr();
		gotoXY(30, 0);
		TextColor(11);
		cout << "List of Lecturer in " << nameyear << " ( " << namesemester << " )";
		TextColor(7);
		CourseList colst;
		loadCourse(namecourse, colst);
		int n = LengthofCourselist(colst);
		string* lecturename = new string[n];
		Course* cur = colst.pHead;
		for (int i = 0; i < n; i++)
		{
			lecturename[i] = cur->LectureName;
			cur = cur->pNext;
		}
		int s = 0;
		gotoXY(42, 2);
		cout << lecturename[0] << endl;
		for (int i = 1; i < n; i++)
		{
			for (int j = 0; j < i && check; j++)
			{
				if (lecturename[i] == lecturename[j])
				{
					check = false;
				}
			}
			if (check) {
				gotoXY(42, 4 + s);
				cout << lecturename[i] << endl;
				s += 2;
			}
		}
		cout << "If you want to go back , Please enter esc .";
		key = inputKey();
		while (key != 27)
		{
			key = inputKey();
		}
		if (key == 27) MenuCourse(nameyear, namesemester, username);
	}
	//scoreboard
	else if (y == 12)
	{
		clrscr();
		CourseList colst;
		loadCourse(namecourse, colst);
		int n = LengthofCourselist(colst);
		Course* co = colst.pHead;
		string* c = new string[n];
		string* cla = new string[n];
		gotoXY(20, 0);
		TextColor(1);
		cout << "Please choose the Course ID and ClassName of ScoreBoard";
		TextColor(7);
		for (int i = 0; i < n; i++)
		{
			gotoXY(42, 4 * (1 + i));
			cout << co->ID << " ( " << co->Class << " ) ";
			c[i] = co->ID;
			cla[i] = co->Class;
			co = co->pNext;
		}
		RemoveCourse(colst);
		int i = 0;
		int x = 42, y = 4 * (i + 1);
		int a = 4 * n; b = 4;
		int key = inputKey();
		gotoXY(x, y);
		while (key != 13)
		{
			if (key == key_Down && y < 4 * n)
			{
				i++;
				y = 4 * (i + 1);
			}
			if (key == key_Up && y > 4)
			{
				i--;
				y = 4 * (i + 1);
			}
			gotoXY(x, y);
			key = inputKey();
		}
		for (int j = 0; j < n; j++)
		{
			if (j == i)
			{
				id_course = c[j];
				delete[]c;
				classname = cla[j];
				delete[]cla;
				string namefile = id_course + "_" + classname;
				clrscr();
				gotoXY(42, 4);
				cout << "View ScoreBoard";
				gotoXY(42, 8);
				cout << "Export ScoreBoard";
				int x = 42, y = 4;
				int key = inputKey();
				int a = 8, b = 4;
				gotoXY(x, y);
				while (key != 13)
				{
					MoveMouse(key, x, y, a, b);
					gotoXY(x, y);
					key = inputKey();
				}
				if (y == 4) {
					clrscr();
					ScoreBoardList sclst;
					loadScoreboard(namefile, sclst);
					scoreboard* score = sclst.pHead;
					StudentList slst;
					loadStudent(namefile, slst);
					student* stu = slst.pHead;
					TextColor(11);
					cout << "No";
					gotoXY(4, 0);
					cout << "Student ID";
					gotoXY(20, 0);
					cout << "Last Name";
					gotoXY(35, 0);
					cout << "First Name";
					gotoXY(50, 0);
					cout << "Midterm";
					gotoXY(60, 0);
					cout << "Final";
					gotoXY(70, 0);
					cout << "Bonus";
					gotoXY(80, 0);
					cout << "Average";
					TextColor(7);
					int i = 0;
					while (score != nullptr && stu != nullptr)
					{
						gotoXY(0, 1 + i);
						cout << score->No;
						gotoXY(4, 1 + i);
						cout << score->ID;
						gotoXY(20, 1 + i);
						cout << stu->Lastname;
						gotoXY(35, 1 + i);
						cout << stu->Firstname;
						gotoXY(50, 1 + i);
						cout << score->mid;
						gotoXY(60, 1 + i);
						cout << score->Final;
						gotoXY(70, 1 + i);
						cout << score->bonus;
						gotoXY(80, 1 + i);
						cout << score->aveg << endl;
						stu = stu->pNext;
						score = score->pNext;
						i++;
					}
					RemoveStudent(slst);
					RemoveScoreboard(sclst);
					cout << "If you want to go back , Please enter esc .\n";
					key = inputKey();
					while (key != 27)
					{
						key = inputKey();
					}
					if (key == 27) MenuCourse(nameyear, namesemester, username);
				}
				else
				{
					clrscr();
					exportScoreboard(id_course, classname);
					cout << "If you want to go back , Please enter esc .\n";
					key = inputKey();
					while (key != 27)
					{
						key = inputKey();
					}
					if (key == 27) MenuCourse(nameyear, namesemester, username);
				}
			}
		}
	}
	else if (y == 16)
	{
		MenuSemester(nameyear, username);
	}
	else
	{
		Menu(username);
	}
}

void OperationCourse(string &nameyear, string &namesemester, string &username)
{
	clrscr();
	string namecourse = nameyear + "_" + namesemester;
	string id_course, classname, id_student;
	gotoXY(42, 4);
	cout << "Import course";
	gotoXY(42, 8);
	cout << "Add a course";
	gotoXY(42, 12);
	cout << "Edit a course";
	gotoXY(42, 16);
	cout << "Remove a course";
	gotoXY(42, 20);
	cout << "Remove a specific student from a course";
	gotoXY(42, 24);
	cout << "Add a specific student to a course";
	gotoXY(42, 28);
	cout << "View list of a courses";
	gotoXY(42, 32);
	cout << "View list of student from a course";
	gotoXY(42, 36);
	TextColor(9);
	cout << "Go back";
	TextColor(7);
	int x = 42, y = 4;
	int a = 36, b = 4;
	int key = inputKey();
	gotoXY(x, y);
	while (key != 13)
	{
		MoveMouse(key, x, y, a, b);
		gotoXY(x, y);
		key = inputKey();
	}
	//import course
	if (y == 4)
	{
		CourseList colst;
		clrscr();
		importCourses(nameyear, namesemester);
		loadCourse(namecourse, colst);
		Course* cur = colst.pHead;
		while (cur != nullptr)
		{
			//make classlist of course
			StudentList slst;
			loadStudent(cur->Class, slst);
			int n = LengthofStudenlist(slst);
			string classname = cur->ID + "_" + cur->Class;
			student* temp = slst.pHead;
			while (temp != nullptr) {
				temp->classname = classname;
				AccountStudentList aclst;
				loadAccountStudent(aclst);
				AccountStudent* now = aclst.pHead;
				while (now != nullptr)
				{
					if (temp->ID == now->ID) break;
					now = now->pNext;
				}
				if (now == nullptr) {
					AddAccountStudent(temp->ID, temp->DoB);
				}
				RemoveAccountStudent(aclst);
				temp = temp->pNext;
			}
			SaveStudent(classname, n, slst);
			RemoveStudent(slst);
			cur = cur->pNext;
		}
		cout << "If you want to go back , Please enter esc." << endl;
		key = inputKey();
		while (key != 27)
		{
			key = inputKey();
		}
		if (key == 27) OperationCourse(nameyear, namesemester, username);
	}
	//add course
	else if (y == 8)
	{
		clrscr();
		CourseList colst;
		loadCourse(namecourse, colst);
		int n = LengthofCourselist(colst);
		Course* cur = new Course;
		cout << "Please enter the Id of course you want to add : ";
		getline(cin, cur->ID, '\n');
		cout << "Please enter the Name of course you want to add : ";
		getline(cin, cur->Name, '\n');
		cout << "Please enter the Class of course you want to add : ";
		getline(cin, cur->Class, '\n');
		cout << "Please enter the Lecture Account of course you want to add : ";
		getline(cin, cur->LecturerAcc, '\n');
		cout << "Please enter the Lecture Name of course you want to add : ";
		getline(cin, cur->LectureName, '\n');
		cout << "Please enter the Start Date of course you want to add (dd/mm/yy) : ";
		getline(cin, cur->StartDate, '\n');
		cout << "Please enter the End Date of course you want to add (dd/mm/yy) : ";
		getline(cin, cur->EndDate, '\n');
		cout << "Please enter the Day of Week of course you want to add : ";
		getline(cin, cur->DayofWeek, '\n');
		cout << "Please enter the Start Hour of course you want to add (hh:mm) : ";
		getline(cin, cur->StartHour, '\n');
		cout << "Please enter the End Hour of course you want to add (hh:mm): ";
		getline(cin, cur->EndHour, '\n');
		cout << "Please enter the Room of course you want to add : ";
		getline(cin, cur->Room, '\n');
		cur->pNext = nullptr;
		//creat new class
		StudentList slst;
		loadStudent(cur->Class, slst);
		int m = LengthofStudenlist(slst);
		string classname = cur->ID + "_" + cur->Class;
		student* stu = slst.pHead;
		while (stu != nullptr)
		{
			stu->classname = classname;
			stu = stu->pNext;
		}
		SaveStudent(classname, m, slst);
		RemoveStudent(slst);
		if (CreatNewScoreBoard(classname, m))cout << "Creat scoreboard of new class completely.\n";
		//update and check lecturer account
		AccountLecturerList leclst;
		loadAccountLecturer(leclst);
		AccountLecturer* lec = leclst.pHead;
		while (lec != nullptr)
		{
			if (cur->LecturerAcc == lec->lecturer_account) break;
			lec = lec->pNext;
		}
		if (lec == nullptr)
		{
			AddAccountLeturer(cur->LecturerAcc, cur->LecturerAcc);
		}
		RemoveAccountLecturer(leclst);
		if (cur == NULL)
			return;
		if (colst.pHead == NULL || colst.pTail == NULL)
		{
			colst.pHead = colst.pTail = cur;
		}
		else
		{
			colst.pTail->pNext = cur;
			colst.pTail = cur;
		}
		n++;
		if (SaveCourse(namecourse, n, colst)) cout << "Add a new course and save completely.\n";
		RemoveCourse(colst);
		cout << "If you want to go back , Please enter esc." << endl;
		key = inputKey();
		while (key != 27)
		{
			key = inputKey();
		}
		if (key == 27) OperationCourse(nameyear, namesemester, username);
	}
	//edit course
	else if (y == 12)
	{
		clrscr();
		gotoXY(20, 0);
		cout << "Please choose the Id and classname of course you want to edit : ";
		CourseList colst;
		loadCourse(namecourse, colst);
		Course* cur = colst.pHead;
		int n = LengthofCourselist(colst);
		string* s = new string[n];
		string*cla = new string[n];
		for (int i = 0; i < n; i++)
		{
			gotoXY(42, 4 * (i + 1));
			cout << cur->ID << " ( " << cur->Class << " )";
			s[i] = cur->ID;
			cla[i] = cur->Class;
			cur = cur->pNext;
		}
		int i = 0;
		int x = 42, y = 4 * (i + 1);
		int key = inputKey();
		gotoXY(x, y);
		while (key != 13)
		{
			if (key == key_Down && y < 4 * n)
			{
				i++;
				y = 4 * (i + 1);
			}
			if (key == key_Up && y > 4)
			{
				i--;
				y = 4 * (i + 1);
			}
			gotoXY(x, y);
			key = inputKey();
		}
		for (int j = 0; j < n; j++)
		{
			if (j == i)
			{
				id_course = s[j];
				delete[]s;
				classname = cla[j];
				delete[]cla;
				clrscr();
				cur = colst.pHead;
				while (cur != nullptr)
				{
					if (cur->ID == id_course && cur->Class == classname) break;
					cur = cur->pNext;
				}
				cout << "Which data do you want to edit : ";
				gotoXY(11, 2);
				cout << "Course ID ";
				gotoXY(11, 4);
				cout << "Name of course ";
				gotoXY(11, 6);
				cout << "Classname ";
				gotoXY(11, 8);
				cout << "Lecture Account";
				gotoXY(11, 10);
				cout << "Lecture Name";
				gotoXY(11, 12);
				cout << "Start date of course ";
				gotoXY(11, 14);
				cout << "End date of course ";
				gotoXY(11, 16);
				cout << "Day of week ";
				gotoXY(11, 18);
				cout << "Start hour of course ";
				gotoXY(11, 20);
				cout << "End hour of course ";
				gotoXY(11, 22);
				cout << "Room ";
				int x = 11, y = 2;
				int key = inputKey();
				gotoXY(x, y);
				while (key != 13)
				{
					if (key == key_Down && y < 22)
					{
						y += 2;
					}
					if (key == key_Up && y > 2)
					{
						y -= 2;
					}
					gotoXY(x, y);
					key = inputKey();
				}
				if (y == 2)
				{
					gotoXY(0, 23);
					cout << "Please enter new Id of this course : \n";
					getline(cin, cur->ID, '\n');
					string oldfile = id_course + "_" + cur->Class + ".txt";
					string newfile = cur->ID + "_" + cur->Class + ".txt";
					const char* old_file = oldfile.c_str();
					const char* new_file = newfile.c_str();
					int re = rename(old_file, new_file);
					string oldf = id_course + "_" + cur->Class + "_ScoreBoard.txt";
					string newf = cur->ID + "_" + cur->Class + "_ScoreBoard.txt";
					const char* old_f = oldf.c_str();
					const char* new_f = newf.c_str();
					int res = rename(old_f, new_f);
					if (re == 0 && res == 0) cout << "Edit ID of course and save completely.\n";
				}
				else if (y == 4)
				{
					gotoXY(0, 23);
					cout << "Please enter new name of this course : ";
					getline(cin, cur->Name, '\n');
				}
				else if (y == 6)
				{
					gotoXY(0, 23);
					cout << "Please enter new classname of this course : ";
					getline(cin, cur->Class, '\n');
					string oldfile = cur->ID + "_" + classname + ".txt";
					string newfile = cur->ID + "_" + cur->Class + ".txt";
					const char* old_file = oldfile.c_str();
					const char* new_file = newfile.c_str();
					int re = rename(old_file, new_file);
					//Update classname
					string namefile = id_course + "_" + cur->Class;
					StudentList slst;
					loadStudent(namefile, slst);
					student* stu = slst.pHead;
					while (stu != nullptr)
					{
						stu->classname = namefile;
						stu = stu->pNext;
					}
					SaveStudent(namefile, LengthofStudenlist(slst), slst);
					RemoveStudent(slst);
					//update scoreboard
					string oldf = cur->ID + "_" + classname + "_ScoreBoard.txt";
					string newf = cur->ID + "_" + cur->Class + "_ScoreBoard.txt";
					const char* old_f = oldf.c_str();
					const char* new_f = newf.c_str();
					int res = rename(old_f, new_f);
					if (re == 0 && res == 0) cout << "Edit classname of course and save completely.\n";
				}
				else if (y == 8)
				{
					gotoXY(0, 23);
					cout << "Please enter new Lecture Account of this course :";
					getline(cin, cur->LecturerAcc, '\n');
					//Update Account Lecture
				}
				else if (y == 10)
				{
					gotoXY(0, 23);
					cout << "Please enter new Lecture Name of this course : ";
					getline(cin, cur->LectureName, '\n');
				}
				else if (y == 12)
				{
					gotoXY(0, 23);
					cout << "Please enter new start date of this course (dd/mm/yy): ";
					getline(cin, cur->StartDate, '\n');
				}
				else if (y == 14)
				{
					gotoXY(0, 23);
					cout << "Please enter new end date of this course (dd/mm/yy): ";
					getline(cin, cur->EndDate, '\n');
				}
				else if (y == 16)
				{
					gotoXY(0, 23);
					cout << "Please enter new day of week of this course : ";
					getline(cin, cur->DayofWeek, '\n');
				}
				else if (y == 18)
				{
					gotoXY(0, 23);
					cout << "Please enter new start hour of this course (hour:minute): ";
					getline(cin, cur->StartHour, '\n');
				}
				else if (y == 20)
				{
					gotoXY(0, 23);
					cout << "Please enter new end hour of this course (hour:minute): ";
					getline(cin, cur->EndHour, '\n');
				}
				else
				{
					gotoXY(0, 23);
					cout << "Please enter new room of this course (hour:minute): ";
					getline(cin, cur->Room, '\n');
				}
				if (SaveCourse(namecourse, n, colst)) cout << "Edit a course and save completely.\n";
				RemoveCourse(colst);
				cout << "If you want to go back , Please enter esc." << endl;
				key = inputKey();
				while (key != 27)
				{
					key = inputKey();
				}
				if (key == 27) OperationCourse(nameyear, namesemester, username);
			}
		}
	}
	//remove course
	else if (y == 16)
	{
		clrscr();
		gotoXY(20, 0);
		cout << "Please choose the Id of course you want to remove : ";
		CourseList colst;
		loadCourse(namecourse, colst);
		Course* cur = colst.pHead;
		int n = LengthofCourselist(colst);
		string* s = new string[n];
		string* cla = new string[n];
		for (int i = 0; i < n; i++)
		{
			gotoXY(42, 4 * (i + 1));
			cout << cur->ID << " ( " << cur->Class << " )";
			s[i] = cur->ID;
			cla[i] = cur->Class;
			cur = cur->pNext;
		}
		int i = 0;
		int x = 42, y = 4 * (i + 1);
		int key = inputKey();
		gotoXY(x, y);
		while (key != 13)
		{
			if (key == key_Down && y < 4 * n)
			{
				i++;
				y = 4 * (i + 1);
			}
			if (key == key_Up && y > 4)
			{
				i--;
				y = 4 * (i + 1);
			}
			gotoXY(x, y);
			key = inputKey();
		}
		for (int j = 0; j < n; j++)
		{
			if (j == i)
			{
				id_course = s[j];
				delete[]s;
				classname = cla[j];
				delete[]cla;
				clrscr();
				cur = colst.pHead;
				if (cur->ID == id_course && cur->Class == classname)
				{
					colst.pHead = colst.pHead->pNext;
					delete cur;
				}
				else
				{
					while (cur->pNext != nullptr)
					{
						if (cur->pNext->ID == id_course && cur->pNext->Class == classname)
						{
							Course* temp = cur->pNext;
							cur->pNext = temp->pNext;
							delete temp;
							break;
						}
						cur = cur->pNext;
					}
				}
				n--;
				if (SaveCourse(namecourse, n, colst)) cout << "Remove course and save completely.\n";
				RemoveCourse(colst);
				cout << "If you want to go back , Please enter esc." << endl;
				key = inputKey();
				while (key != 27)
				{
					key = inputKey();
				}
				if (key == 27) OperationCourse(nameyear, namesemester, username);
			}
		}
	}
	//remove student from course
	else if (y == 20)
	{
		clrscr();
		cout << "   Please choose the Id and Classname of Course you want remove student from it :";
		CourseList colst;
		loadCourse(namecourse, colst);
		Course* temp = colst.pHead;
		int n = LengthofCourselist(colst);
		string* s = new string[n];
		string* c = new string[n];
		for (int i = 0; i < n; i++)
		{
			gotoXY(42, 4 * (i + 1));
			cout << temp->ID << " ( " << temp->Class << " )";
			s[i] = temp->ID;
			c[i] = temp->Class;
			temp = temp->pNext;
		}
		RemoveCourse(colst);
		int i = 0;
		int x = 42, y = 4 * (i + 1);
		int key = inputKey();
		gotoXY(x, y);
		while (key != 13)
		{
			if (key == key_Down && y < 4 * n)
			{
				i++;
				y = 4 * (i + 1);
			}
			if (key == key_Up && y > 4)
			{
				i--;
				y = 4 * (i + 1);
			}
			gotoXY(x, y);
			key = inputKey();
		}
		for (int j = 0; j < n; j++)
		{
			if (j == i)
			{
				id_course = s[j];
				delete[]s;
				classname = c[j];
				delete[]c;
				string namefile = id_course + "_" + classname;
				clrscr();
				StudentList slst;
				loadStudent(namefile, slst); //load student with your choice
				int lengthofstudent = LengthofStudenlist(slst);
				student* cur = slst.pHead;
				string* stu = new string[lengthofstudent];
				cout << "   Please choose the ID of student you want to remove : ";
				for (int i = 0; i < lengthofstudent; i++)
				{
					gotoXY(42, 2 * (i + 1));
					cout << cur->ID;
					stu[i] = cur->ID;
					cur = cur->pNext;
				}
				int m = 0;
				int x = 42, y = 2 * (m + 1);
				key = inputKey();
				gotoXY(x, y);
				while (key != 13)
				{
					if (key == key_Down && y < 2 * lengthofstudent)
					{
						m++;
						y = 2 * (m + 1);
					}
					if (key == key_Up && y > 2)
					{
						m--;
						y = 2 * (m + 1);
					}
					gotoXY(x, y);
					key = inputKey();
				}
				for (int k = 0; k < lengthofstudent; k++)
				{
					if (k == m)
					{
						id_student = stu[k];
						delete[]stu;
						cur = slst.pHead;
						if (cur->ID == id_student)
						{
							slst.pHead = slst.pHead->pNext;
							delete cur;
						}
						else
						{
							while (cur->pNext != nullptr)
							{
								if (cur->pNext->ID == id_student)
								{
									student* tmp = cur->pNext;
									cur->pNext = tmp->pNext;
									delete tmp;
									break;
								}
								cur = cur->pNext;
							}
						}
						clrscr();
						lengthofstudent--;
						if (SaveStudent(namefile, lengthofstudent, slst)) cout << "Remove student from a course and save completely.\n";
						RemoveStudent(slst);
						//update scoreboard
						ScoreBoardList sclst;
						loadScoreboard(namefile, sclst);
						int l = LengthofScoreBoardlist(sclst);
						scoreboard* score = sclst.pHead;
						if (score->ID == id_student)
						{
							sclst.pHead = sclst.pHead->pNext;
							delete score;
						}
						else
						{
							while (score != nullptr)
							{
								if (score->pNext->ID == id_student)
								{
									scoreboard* t = score->pNext;
									score->pNext = t->pNext;
									delete t;
									break;
								}
								score = score->pNext;
							}
						}
						l--;
						if (SaveScoreboard(namefile, l, sclst)) cout << "Update ScoreBoard completely.\n";
						RemoveScoreboard(sclst);
						cout << "If you want to go back , Please enter esc." << endl;
						key = inputKey();
						while (key != 27)
						{
							key = inputKey();
						}
						if (key == 27) OperationCourse(nameyear, namesemester, username);
					}
				}
			}
		}
	}
	//add a student to course
	else if (y == 24)
	{
		clrscr();
		cout << "   Please choose the Id and Classname of Course you want add a student :";
		CourseList colst;
		loadCourse(namecourse, colst);
		Course* cur = colst.pHead;
		int n = LengthofCourselist(colst);
		string* s = new string[n];
		string* c = new string[n];
		for (int i = 0; i < n; i++)
		{
			gotoXY(42, 4 * (i + 1));
			cout << cur->ID << " ( " << cur->Class << " )";
			s[i] = cur->ID;
			c[i] = cur->Class;
			cur = cur->pNext;
		}
		RemoveCourse(colst);
		int i = 0;
		int x = 42, y = 4 * (i + 1);
		int key = inputKey();
		gotoXY(x, y);
		while (key != 13)
		{
			if (key == key_Down && y < 4 * n)
			{
				i++;
				y = 4 * (i + 1);
			}
			if (key == key_Up && y > 4)
			{
				i--;
				y = 4 * (i + 1);
			}
			gotoXY(x, y);
			key = inputKey();
		}
		for (int j = 0; j < n; j++)
		{
			if (j == i)
			{
				id_course = s[j];
				delete[]s;
				classname = c[j];
				delete[]c;
				string namefile = id_course + "_" + classname;
				clrscr();
				StudentList slst;
				loadStudent(namefile, slst);
				int m = LengthofStudenlist(slst);
				student* temp = new student;
				temp->classname = namefile;
				cout << "Please enter the id of student you want to add : ";
				getline(cin, temp->ID, '\n');
				cout << "Please enter the last name of student you want to add : ";
				getline(cin, temp->Lastname, '\n');
				cout << "Please enter the first name of student you want to add : ";
				getline(cin, temp->Firstname, '\n');
				cout << "Please enter the gender of student you want to add : ";
				getline(cin, temp->Gender, '\n');
				cout << "Please enter the day of birth of student you want to add (dd/mm/yy): ";
				getline(cin, temp->DoB, '\n');
				temp->pNext = nullptr;
				if (slst.pHead == NULL || slst.pTail == NULL)
				{
					slst.pHead = slst.pTail = temp;
				}
				else
				{
					slst.pTail->pNext = temp;
					slst.pTail = temp;
				}
				m++;
				//update and check acount studentlist
				AccountStudentList aclst;
				loadAccountStudent(aclst);
				AccountStudent* now = aclst.pHead;
				while (now != nullptr)
				{
					if (temp->ID == now->ID) break;
					now = now->pNext;
				}
				if (now == nullptr) {
					AddAccountStudent(temp->ID, temp->DoB);
				}
				RemoveAccountStudent(aclst);
				//Update Scoreboard
				ScoreBoardList sclst;
				loadScoreboard(namefile, sclst);
				int l = LengthofScoreBoardlist(sclst);
				scoreboard* curs = new scoreboard;
				curs->ID = temp->ID;
				curs->mid = "0";
				curs->Final = "0";
				curs->bonus = "0";
				curs->aveg = "0";
				curs->pNext = nullptr;
				if (sclst.pHead == nullptr || sclst.pTail == nullptr)
				{
					sclst.pHead = sclst.pTail = curs;
				}
				else
				{
					sclst.pTail->pNext = curs;
					sclst.pTail = curs;
				}
				SaveScoreboard(namefile, l + 1, sclst);
				RemoveScoreboard(sclst);
				if (SaveStudent(namefile, m, slst)) cout << "Add a student to class " << classname << " of " << id_course << " completely.\n";
				RemoveStudent(slst);
				cout << "If you want to go back , Please enter esc." << endl;
				key = inputKey();
				while (key != 27)
				{
					key = inputKey();
				}
				if (key == 27) OperationCourse(nameyear, namesemester, username);
			}
		}
	}
	//view course
	else if (y == 28)
	{
		clrscr();
		TextColor(11);
		cout << "No";
		gotoXY(4, 0);
		cout << "Course ID";
		gotoXY(30, 0);
		cout << "Course Name";
		gotoXY(65, 0);
		cout << "Class";
		gotoXY(73, 0);
		cout << "Lecture Account";
		gotoXY(91, 0);
		cout << "Start Date";
		gotoXY(104, 0);
		cout << "End Date";
		gotoXY(117, 0);
		cout << "Day of Week";
		gotoXY(131, 0);
		cout << "Start Hour";
		gotoXY(144, 0);
		cout << "End Hour";
		gotoXY(156, 0);
		cout << "Room";
		TextColor(7);
		int i = 0;
		CourseList colst;
		loadCourse(namecourse, colst);
		Course* now = colst.pHead;
		while (now != nullptr)
		{
			gotoXY(0, 1 + i);
			cout << now->No;
			gotoXY(4, 1 + i);
			cout << now->ID;
			gotoXY(15, 1 + i);
			cout << now->Name;
			gotoXY(65, 1 + i);
			cout << now->Class;
			gotoXY(73, 1 + i);
			cout << now->LecturerAcc;
			gotoXY(91, 1 + i);
			cout << now->StartDate;
			gotoXY(104, 1 + i);
			cout << now->EndDate;
			gotoXY(117, 1 + i);
			cout << now->DayofWeek;
			gotoXY(131, 1 + i);
			cout << now->StartHour;
			gotoXY(144, 1 + i);
			cout << now->EndHour;
			gotoXY(156, 1 + i);
			cout << now->Room << endl;
			i++;
			now = now->pNext;
		}
		RemoveCourse(colst);
		cout << "If you want to go back , Please enter esc." << endl;
		key = inputKey();
		while (key != 27)
		{
			key = inputKey();
		}
		if (key == 27) OperationCourse(nameyear, namesemester, username);
	}
	//View student
	else if (y == 32)
	{
		clrscr();
		CourseList colst;
		loadCourse(namecourse, colst);
		Course* temp = colst.pHead;
		int n = LengthofCourselist(colst);
		string* s = new string[n];
		string* c = new string[n];
		for (int i = 0; i < n; i++)
		{
			gotoXY(42, 4 * (i + 1));
			cout << temp->ID << " ( " << temp->Class << " )";
			s[i] = temp->ID;
			c[i] = temp->Class;
			temp = temp->pNext;
		}
		RemoveCourse(colst);
		int i = 0;
		int x = 42, y = 4 * (i + 1);
		int key = inputKey();
		gotoXY(x, y);
		while (key != 13)
		{
			if (key == key_Down && y < 4 * n)
			{
				i++;
				y = 4 * (i + 1);
			}
			if (key == key_Up && y > 4)
			{
				i--;
				y = 4 * (i + 1);
			}
			gotoXY(x, y);
			key = inputKey();
		}
		for (int j = 0; j < n; j++)
		{
			if (j == i)
			{
				id_course = s[j];
				delete[]s;
				classname = c[j];
				delete[]c;
				string namefile = id_course + "_" + classname;
				clrscr();
				StudentList slst;
				loadStudent(namefile, slst);
				student* curs = slst.pHead;
				TextColor(9);
				cout << "No";
				gotoXY(8, 0);
				cout << "Id";
				gotoXY(20, 0);
				cout << "Last Name";
				gotoXY(35, 0);
				cout << "First Name";
				gotoXY(50, 0);
				cout << "Gender";
				gotoXY(60, 0);
				cout << "Date of Birth" << endl;
				TextColor(7);
				int i = 0;
				while (curs != nullptr)
				{
					cout << curs->No;
					gotoXY(5, 1 + i);
					cout << curs->ID;
					gotoXY(20, 1 + i);
					cout << curs->Lastname;
					gotoXY(35, 1 + i);
					cout << curs->Firstname;
					gotoXY(50, 1 + i);
					cout << curs->Gender;
					gotoXY(60, 1 + i);
					cout << curs->DoB.substr(0, 2) << "/" << curs->DoB.substr(2, 2) << "/" << curs->DoB.substr(4, 4) << endl;
					curs = curs->pNext;
					i++;
				}
				RemoveStudent(slst);
				cout << "If you want to go back , Please enter esc." << endl;
				key = inputKey();
				while (key != 27)
				{
					key = inputKey();
				}
				if (key == 27) OperationCourse(nameyear, namesemester, username);
			}
		}
	}
	else
	{
		MenuCourse(nameyear, namesemester, username);
	}
}
//
void loadYear(string &namefile, YearList &ylst)
{
	ifstream fin;
	fin.open(namefile + ".txt");
	string name;
	getline(fin, name, '\n');
	while (name != "0")
	{
		year* cur = new year;
		cur->name = name;
		cur->pNext = nullptr;
		if (cur == NULL)
			return;
		if (ylst.pHead == NULL || ylst.pTail == NULL)
		{
			ylst.pHead = ylst.pTail = cur;
		}
		else
		{
			ylst.pTail->pNext = cur;
			ylst.pTail = cur;
		}
		getline(fin, name, '\n');
	}
	fin.close();
}

void loadSemester(string &namefile, SemesterList &selst)
{
	ifstream fin;
	fin.open(namefile + ".txt");
	string name;
	getline(fin, name, '\n');
	while (name != "0")
	{
		Semester* cur = new Semester;
		cur->name = name;
		cur->pNext = nullptr;
		if (cur == NULL)
			return;
		if (selst.pHead == NULL || selst.pTail == NULL)
		{
			selst.pHead = selst.pTail = cur;
		}
		else
		{
			selst.pTail->pNext = cur;
			selst.pTail = cur;
		}
		getline(fin, name, '\n');
	}
	fin.close();
}

void loadClass(string &namefile, ClassList &clst)
{
	ifstream fin;
	fin.open(namefile + ".txt");
	string name;
	getline(fin, name, '\n');
	while (name != "0")
	{
		Classes* cur = new Classes;
		cur->name = name;
		cur->pNext = nullptr;
		if (cur == NULL)
			return;
		if (clst.pHead == NULL || clst.pTail == NULL)
		{
			clst.pHead = clst.pTail = cur;
		}
		else
		{
			clst.pTail->pNext = cur;
			clst.pTail = cur;
		}
		getline(fin, name, '\n');
	}
	fin.close();
}

void loadStudent(string &namefile, StudentList &slst)
{
	int n;
	ifstream fin;
	fin.open(namefile + ".txt");
	fin >> n;
	fin.ignore(1000, '\n');
	for (int i = 0; i < n; i++)
	{
		student* cur = new student;
		getline(fin, cur->No, ',');
		getline(fin, cur->ID, ',');
		getline(fin, cur->classname, ',');
		getline(fin, cur->Lastname, ',');
		getline(fin, cur->Firstname, ',');
		getline(fin, cur->Gender, ',');
		getline(fin, cur->DoB, '\n');
		cur->pNext = NULL;
		if (cur == NULL)
			return;
		if (slst.pHead == NULL || slst.pTail == NULL)
		{
			slst.pHead = slst.pTail = cur;
		}
		else
		{
			slst.pTail->pNext = cur;
			slst.pTail = cur;
		}
	}
	fin.close();
}

void loadAccountStudent(AccountStudentList &acslst)
{
	ifstream fin;
	fin.open("login_student.txt");
	while (!fin.eof())
	{
		AccountStudent* cur = new AccountStudent;
		getline(fin, cur->ID, '\n');
		getline(fin, cur->DoB, '\n');
		if (fin.eof()) break;
		cur->pNext = NULL;
		if (cur == NULL)
			return;
		if (acslst.pHead == NULL && acslst.pTail == NULL)
		{
			acslst.pHead = acslst.pTail = cur;
		}
		else
		{
			acslst.pTail->pNext = cur;
			acslst.pTail = cur;
		}
	}
}

void loadAccountLecturer(AccountLecturerList &lecslst)
{
	ifstream fin;
	fin.open("login_lecturer.txt");
	while (!fin.eof())
	{
		AccountLecturer* cur = new AccountLecturer;
		getline(fin, cur->lecturer_account, '\n');
		getline(fin, cur->password, '\n');
		if (fin.eof()) break;
		cur->pNext = NULL;
		if (cur == NULL)
			return;
		if (lecslst.pHead == NULL || lecslst.pTail == NULL)
		{
			lecslst.pHead = lecslst.pTail = cur;
		}
		else
		{
			lecslst.pTail->pNext = cur;
			lecslst.pTail = cur;
		}
	}
}

void loadScoreboard(string &namefile, ScoreBoardList &sclst) {
	int n;
	ifstream fin;
	fin.open(namefile + "_Scoreboard.txt");
	fin >> n;
	fin.ignore(1000, '\n');
	for (int i = 0; i < n; i++)
	{
		scoreboard* cur = new scoreboard;
		getline(fin, cur->No, ',');
		getline(fin, cur->ID, ',');
		getline(fin, cur->mid, ',');
		getline(fin, cur->Final, ',');
		getline(fin, cur->bonus, ',');
		getline(fin, cur->aveg, '\n');
		cur->pNext = NULL;
		if (cur == NULL)
			return;
		if (sclst.pHead == NULL && sclst.pTail == NULL)
		{
			sclst.pHead = sclst.pTail = cur;
		}
		else
		{
			sclst.pTail->pNext = cur;
			sclst.pTail = cur;
		}
	}
	fin.close();
}

void loadCourse(string &namefile, CourseList &colst) {
	int n;
	ifstream fin;
	fin.open(namefile + ".txt");
	fin >> n;
	fin.ignore(1000, '\n');
	for (int i = 0; i < n; i++)
	{
		Course* cur = new Course;
		getline(fin, cur->No, ',');
		getline(fin, cur->ID, ',');
		getline(fin, cur->Name, ',');
		getline(fin, cur->Class, ',');
		getline(fin, cur->LecturerAcc, ',');
		getline(fin, cur->LectureName, ',');
		getline(fin, cur->StartDate, ',');
		getline(fin, cur->EndDate, ',');
		getline(fin, cur->DayofWeek, ',');
		getline(fin, cur->StartHour, ',');
		getline(fin, cur->EndHour, ',');
		getline(fin, cur->Room, '\n');
		cur->pNext = NULL;
		if (cur == NULL)
			return;
		if (colst.pHead == NULL && colst.pTail == NULL)
		{
			colst.pHead = colst.pTail = cur;
		}
		else
		{
			colst.pTail->pNext = cur;
			colst.pTail = cur;
		}
	}
	fin.close();
}

bool SaveStudent(string &namefile, int n, StudentList &slst)
{
	ofstream fout;
	fout.open(namefile + ".txt");
	if (!fout.is_open()) return false;
	fout << n << endl;
	student* cur = slst.pHead;
	for (int i = 1; i <= n; i++)
	{
		fout << i << "," << cur->ID << "," << cur->classname << "," << cur->Lastname << "," << cur->Firstname << "," << cur->Gender << "," << cur->DoB << endl;
		cur = cur->pNext;
	}
	fout.close();
	return true;
}

bool SaveClass(string &namefile, ClassList &clst)
{
	ofstream fout;
	fout.open(namefile + ".txt");
	if (!fout.is_open()) return false;
	Classes* cur = clst.pHead;
	while (cur != nullptr)
	{
		fout << cur->name << endl;
		cur = cur->pNext;
	}
	fout << "0";
	fout.close();
	return true;
}

bool SaveYear(string &namefile, YearList &ylst)
{
	ofstream fout;
	fout.open(namefile + ".txt");
	if (!fout.is_open()) return false;
	year* cur = ylst.pHead;
	while (cur != nullptr)
	{
		fout << cur->name << endl;
		cur = cur->pNext;
	}
	fout << "0";
	fout.close();
	return true;
}

bool SaveSemester(string &namefile, SemesterList &selst)
{
	ofstream fout;
	fout.open(namefile + ".txt");
	if (!fout.is_open()) return false;
	Semester* cur = selst.pHead;
	while (cur != nullptr)
	{
		fout << cur->name << endl;
		cur = cur->pNext;
	}
	fout << "0";
	fout.close();
	return true;
}

bool SaveScoreboard(string &namefile, int n, ScoreBoardList &sclst)
{
	ofstream fout;
	fout.open(namefile + "_Scoreboard.txt");
	fout << n << endl;
	if (!fout.is_open()) return false;
	scoreboard* cur = sclst.pHead;
	for (int i = 1; i <= n; i++)
	{
		fout << i << "," << cur->ID << "," << cur->mid << "," << cur->Final << "," << cur->bonus << "," << cur->aveg << endl;
		cur = cur->pNext;
	}
	fout.close();
	return true;
}

bool SaveCourse(string &namefile, int n, CourseList &colst)
{
	ofstream fout;
	fout.open(namefile + ".txt");
	if (!fout.is_open()) return false;
	fout << n << endl;
	Course* cur = colst.pHead;
	for (int i = 1; i <= n; i++)
	{
		fout << i << "," << cur->ID << "," << cur->Name << "," << cur->Class << "," << cur->LecturerAcc << "," << cur->LectureName << ","
			<< cur->StartDate << "," << cur->EndDate << "," << cur->DayofWeek << "," << cur->StartHour << "," << cur->EndHour << ","
			<< cur->Room << endl;
		cur = cur->pNext;
	}
	fout.close();
	return true;
}

bool SaveAccountStudent(AccountStudentList &aclst)
{
	ofstream fout;
	fout.open("login_student.txt");
	if (!fout.is_open()) return false;
	AccountStudent* cur = aclst.pHead;
	while (cur != nullptr)
	{
		fout << cur->ID << endl;
		fout << cur->DoB << endl;
		cur = cur->pNext;
	}
	fout.close();
	return true;
}

void RemoveStudent(StudentList &slst)
{
	student* cur = slst.pHead;
	while (cur != NULL)
	{
		slst.pHead = slst.pHead->pNext;
		delete cur;
		cur = slst.pHead;
	}
}

void RemoveAccountStudent(AccountStudentList &acslst)
{
	AccountStudent* cur = acslst.pHead;
	while (cur != NULL)
	{
		acslst.pHead = acslst.pHead->pNext;
		delete cur;
		cur = acslst.pHead;
	}
}

void RemoveAccountLecturer(AccountLecturerList &lecslst)
{
	AccountLecturer* cur = lecslst.pHead;
	while (cur != NULL)
	{
		lecslst.pHead = lecslst.pHead->pNext;
		delete cur;
		cur = lecslst.pHead;
	}
}

void RemoveClass(ClassList &clst)
{
	Classes* cur = clst.pHead;
	while (cur != NULL)
	{
		clst.pHead = clst.pHead->pNext;
		delete cur;
		cur = clst.pHead;
	}
}

void RemoveYear(YearList &ylst)
{
	year* cur = ylst.pHead;
	while (cur != NULL)
	{
		ylst.pHead = ylst.pHead->pNext;
		delete cur;
		cur = ylst.pHead;
	}
}

void RemoveSemester(SemesterList &selst)
{
	Semester* cur = selst.pHead;
	while (cur != NULL)
	{
		selst.pHead = selst.pHead->pNext;
		delete cur;
		cur = selst.pHead;
	}
}

void RemoveCourse(CourseList &colst)
{
	Course* cur = colst.pHead;
	while (cur != NULL)
	{
		colst.pHead = colst.pHead->pNext;
		delete cur;
		cur = colst.pHead;
	}
}

void RemoveScoreboard(ScoreBoardList &sclst)
{
	scoreboard* cur = sclst.pHead;
	while (cur != NULL)
	{
		sclst.pHead = sclst.pHead->pNext;
		delete cur;
		cur = sclst.pHead;
	}
}

bool AddAccountStudent(string &id, string &dob)
{
	ofstream fout;
	fout.open("login_student.txt", ios::app);
	if (!fout.is_open()) return false;
	fout << id << endl;
	fout << dob << endl;
	fout.close();
	return true;
}

bool AddAccountLeturer(string &account, string &password)
{
	ofstream fout;
	fout.open("login_lecturer.txt", ios::app);
	if (!fout.is_open()) return false;
	fout << account << endl;
	fout << password << endl;
	fout.close();
	return true;
}

bool CreatNewScoreBoard(string &namefile, int n)
{
	StudentList slst;
	loadStudent(namefile, slst);
	student*cur = slst.pHead;
	ofstream fout;
	fout.open(namefile + "_Scoreboard.txt");
	fout << n << endl;
	if (!fout.is_open()) return false;
	for (int i = 0; i < n; i++)
	{
		fout << i + 1 << "," << cur->ID << ",0,0,0,0" << endl;//creat initial grade of mid,final,bonus,average = 0
		cur = cur->pNext;
	}
	fout.close();
	return true;
}

string CalculateAverage(string &mid, string &final, string &bonus, string &average)
{
	int n;
	double m, f, b, a;
	ofstream fout;
	fout.open("CalculateAverage.txt");
	if (!fout.is_open()) cout << "Can open file to save calculate average.";
	else {
		fout << "1" << endl;
		fout << mid << endl;
		fout << final << endl;
		fout << bonus << endl;
		fout << average << endl;
	}
	fout.close();
	ifstream fin;
	fin.open("CalculateAverage.txt");
	if (!fin.is_open()) cout << "Can open file to load calculate average.";
	else {
		fin >> n;
		for (int i = 0; i < n; i++)
		{
			fin >> m;
			fin >> f;
			fin >> b;
			fin >> a;
		}
	}
	fin.close();
	a = m * (0.3) + f * (0.5) + b * (0.2);
	ofstream fout1;
	fout1.open("CalculateAverage.txt");
	if (!fout1.is_open()) cout << "Can open file to save calculate average.";
	else {
		fout1 << "1" << endl;
		fout1 << m << endl;
		fout1 << f << endl;
		fout1 << b << endl;
		fout1 << setprecision(2) << a << endl;
	}
	fout1.close();
	ifstream fin1;
	fin1.open("CalculateAverage.txt");
	if (!fin1.is_open()) cout << "Can open file to load calculate average.";
	else {
		fin1 >> n;
		fin1.ignore(1000, '\n');
		for (int i = 0; i < n; i++)
		{
			getline(fin1, mid, '\n');
			getline(fin1, final, '\n');
			getline(fin1, bonus, '\n');
			getline(fin1, average, '\n');
		}
	}
	fin1.close();
	return average;
}

void UpdateClassofCourse(string &ID, string &newID, string &Lastname, string &Firstname, string &Gender, string &DoB, string &classname)
{
	string name = "ListofYear", namefile, nameclass;
	YearList ylst;
	loadYear(name, ylst);
	year* cur = ylst.pHead;
	while (cur != nullptr)
	{
		SemesterList selst;
		loadSemester(cur->name, selst);
		Semester* se = selst.pHead;
		while (se != nullptr)
		{
			namefile = cur->name + "_" + se->name;
			CourseList colst;
			loadCourse(namefile, colst);
			int l = LengthofCourselist(colst);
			Course* co = colst.pHead;
			if (l == 0) {
				se = se->pNext;
			}
			else {
				while (co != nullptr)
				{
					if (co->Class == classname)
					{
						nameclass = co->ID + "_" + classname;
						StudentList slst;
						ScoreBoardList sclst;
						loadStudent(nameclass, slst);
						int n = LengthofStudenlist(slst);
						loadScoreboard(nameclass, sclst);
						student* stu = slst.pHead;
						scoreboard* score = sclst.pHead;
						while (stu != nullptr&&score != nullptr)
						{
							if (stu->ID == ID && score->ID == ID)
							{
								stu->ID = newID;
								score->ID = newID;
								stu->DoB = DoB;
								stu->Firstname = Firstname;
								stu->Lastname = Lastname;
								stu->Gender = Gender;
							}
							stu = stu->pNext;
							score = score->pNext;
						}
						if (SaveStudent(nameclass, n, slst)) cout << "Update student in class " << classname << " of " << co->ID << " completely.\n";
						if (SaveScoreboard(nameclass, n, sclst)) cout << "Update scoreboard completely.\n";
						RemoveStudent(slst);
						RemoveScoreboard(sclst);
					}
					co = co->pNext;
				}
				se = se->pNext;
			}
		}
		cur = cur->pNext;
	}
}

void AddStudenttoClassofCourse(string &ID, string &Lastname, string &Firstname, string &Gender, string &DoB, string &classname)
{
	string name = "ListofYear", namefile, nameclass;
	YearList ylst;
	loadYear(name, ylst);
	year* cur = ylst.pHead;
	while (cur != nullptr)
	{
		SemesterList selst;
		loadSemester(cur->name, selst);
		Semester* se = selst.pHead;
		while (se != nullptr)
		{
			namefile = cur->name + "_" + se->name;
			CourseList colst;
			loadCourse(namefile, colst);
			int l = LengthofCourselist(colst);
			Course* co = colst.pHead;
			if (l == 0) {
				se = se->pNext;
			}
			else {
				while (co != nullptr)
				{
					if (co->Class == classname)
					{
						nameclass = co->ID + "_" + classname;
						StudentList slst;
						loadStudent(nameclass, slst);
						int n = LengthofStudenlist(slst);
						student* temp = new student;
						temp->classname = nameclass;
						temp->ID = ID;
						temp->Lastname = Lastname;
						temp->Firstname = Firstname;
						temp->Gender = Gender;
						temp->DoB = DoB;
						temp->pNext = nullptr;
						if (temp == NULL)
							return;
						if (slst.pHead == NULL || slst.pTail == NULL)
						{
							slst.pHead = slst.pTail = temp;
						}
						else
						{
							slst.pTail->pNext = temp;
							slst.pTail = temp;
						}
						ScoreBoardList sclst;
						loadScoreboard(nameclass, sclst);
						scoreboard* curs = new scoreboard;
						curs->ID = temp->ID;
						curs->mid = "0";
						curs->Final = "0";
						curs->bonus = "0";
						curs->aveg = "0";
						curs->pNext = nullptr;
						if (sclst.pHead == nullptr || sclst.pTail == nullptr)
						{
							sclst.pHead = sclst.pTail = curs;
						}
						else
						{
							sclst.pTail->pNext = curs;
							sclst.pTail = curs;
						}
						n++;
						if (SaveStudent(nameclass, n, slst)) cout << "Add student in class " << classname << " of " << co->ID << " completely.\n";
						if (SaveScoreboard(nameclass, n, sclst)) cout << "Update scoreboard " << classname << " of " << co->ID << " completely.\n";
						RemoveStudent(slst);
						RemoveScoreboard(sclst);
					}
					co = co->pNext;
				}
				se = se->pNext;
			}
		}
		cur = cur->pNext;
	}
}

void RemoveStudentInClassofCourse(string &ID, string &classname)
{
	string name = "ListofYear", namefile, nameclass;
	YearList ylst;
	loadYear(name, ylst);
	year* cur = ylst.pHead;
	while (cur != nullptr)
	{
		SemesterList selst;
		loadSemester(cur->name, selst);
		Semester* se = selst.pHead;
		while (se != nullptr)
		{
			namefile = cur->name + "_" + se->name;
			CourseList colst;
			loadCourse(namefile, colst);
			int l = LengthofCourselist(colst);
			Course* co = colst.pHead;
			if (l == 0) {
				se = se->pNext;
			}
			else {
				while (co != nullptr)
				{
					if (co->Class == classname)
					{
						nameclass = co->ID + "_" + classname;
						StudentList slst;
						loadStudent(nameclass, slst);
						int n = LengthofStudenlist(slst);
						student* stu = slst.pHead;
						if (stu->ID == ID)
						{
							slst.pHead = slst.pHead->pNext;
							delete stu;
						}
						else
						{
							while (stu->pNext != nullptr)
							{
								if (stu->pNext->ID == ID)
								{
									student* tmp = stu->pNext;
									stu->pNext = tmp->pNext;
									delete tmp;
									break;
								}
								stu = stu->pNext;
							}
						}
						//update scoreboard
						ScoreBoardList sclst;
						loadScoreboard(nameclass, sclst);
						int l = LengthofScoreBoardlist(sclst);
						scoreboard* score = sclst.pHead;
						if (score->ID == ID)
						{
							sclst.pHead = sclst.pHead->pNext;
							delete score;
						}
						else
						{
							while (score != nullptr)
							{
								if (score->pNext->ID == ID)
								{
									scoreboard* t = score->pNext;
									score->pNext = t->pNext;
									delete t;
									break;
								}
								score = score->pNext;
							}
						}
						n--;
						if (SaveStudent(nameclass, n, slst)) cout << "Remove student in class " << classname << " of " << co->ID << " completely.\n";
						if (SaveScoreboard(nameclass, n, sclst)) cout << "Update scoreboard " << classname << " of " << co->ID << " completely.\n";
						RemoveStudent(slst);
						RemoveScoreboard(sclst);
					}
					co = co->pNext;
				}
				se = se->pNext;
			}
		}
		cur = cur->pNext;
	}
}

void ChangeStudentInClassofCourse(string &ID, string &Lastname, string &Firstname, string &Gender, string &DoB, string &classname1, string &classname2)
{
	string name = "ListofYear", namefile, nameclass;
	YearList ylst;
	loadYear(name, ylst);
	year* cur = ylst.pHead;
	while (cur != nullptr)
	{
		SemesterList selst;
		loadSemester(cur->name, selst);
		Semester* se = selst.pHead;
		while (se != nullptr)
		{
			namefile = cur->name + "_" + se->name;
			CourseList colst;
			loadCourse(namefile, colst);
			int l = LengthofCourselist(colst);
			Course* co = colst.pHead;
			if (l == 0) {
				se = se->pNext;
			}
			else {
				while (co != nullptr)
				{
					if (co->Class == classname1)
					{
						nameclass = co->ID + "_" + classname1;
						StudentList slst;
						loadStudent(nameclass, slst);
						int n = LengthofStudenlist(slst);
						student* stu = slst.pHead;
						if (stu->ID == ID)
						{
							slst.pHead = slst.pHead->pNext;
							delete stu;
						}
						else
						{
							while (stu->pNext != nullptr)
							{
								if (stu->pNext->ID == ID)
								{
									student* tmp = stu->pNext;
									stu->pNext = tmp->pNext;
									delete tmp;
									break;
								}
								stu = stu->pNext;
							}
						}
						//update scoreboard
						ScoreBoardList sclst;
						loadScoreboard(nameclass, sclst);
						scoreboard* score = sclst.pHead;
						if (score->ID == ID)
						{
							sclst.pHead = sclst.pHead->pNext;
							delete score;
						}
						else
						{
							while (score != nullptr)
							{
								if (score->pNext->ID == ID)
								{
									scoreboard* t = score->pNext;
									score->pNext = t->pNext;
									delete t;
									break;
								}
								score = score->pNext;
							}
						}
						n--;
						SaveStudent(nameclass, n, slst);
						SaveScoreboard(nameclass, n, sclst);
						RemoveStudent(slst);
						RemoveScoreboard(sclst);
					}
					if (co->Class == classname2)
					{
						nameclass = co->ID + "_" + classname2;
						StudentList slst;
						loadStudent(nameclass, slst);
						int n = LengthofStudenlist(slst);
						student* temp = new student;
						temp->classname = nameclass;
						temp->ID = ID;
						temp->Lastname = Lastname;
						temp->Firstname = Firstname;
						temp->Gender = Gender;
						temp->DoB = DoB;
						temp->pNext = nullptr;
						if (temp == NULL)
							return;
						if (slst.pHead == NULL || slst.pTail == NULL)
						{
							slst.pHead = slst.pTail = temp;
						}
						else
						{
							slst.pTail->pNext = temp;
							slst.pTail = temp;
						}
						ScoreBoardList sclst;
						loadScoreboard(nameclass, sclst);
						scoreboard* curs = new scoreboard;
						curs->ID = temp->ID;
						curs->mid = "0";
						curs->Final = "0";
						curs->bonus = "0";
						curs->aveg = "0";
						curs->pNext = nullptr;
						if (sclst.pHead == nullptr || sclst.pTail == nullptr)
						{
							sclst.pHead = sclst.pTail = curs;
						}
						else
						{
							sclst.pTail->pNext = curs;
							sclst.pTail = curs;
						}
						n++;
						if (SaveStudent(nameclass, n, slst)) cout << "Change student in class " << classname1 << " to " << classname2 << " of " << co->ID << " completely.\n";
						if (SaveScoreboard(nameclass, n, sclst)) cout << "Update scoreboard of change student from " << classname1 << " to " << classname2 << " of " << co->ID << "completely.\n";
						RemoveStudent(slst);
						RemoveScoreboard(sclst);
					}
					co = co->pNext;
				}
				se = se->pNext;
			}
		}
		cur = cur->pNext;
	}
}