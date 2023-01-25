#ifndef Course_H
#define Course_H
#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <conio.h>
#include <fstream>
#define SPACE 10
using namespace std;

class CourseNode
{
	string Name, Type;
	int cid;
	double Cost;

	CourseNode * right;
	CourseNode * left;
	public:
		CourseNode()
		{
			cid = 0;
			right = left = NULL;
		}

	void setcid(int cid)
	{
		this->cid = cid;
	}

	int getcid()
	{
		return cid;
	}

	void setName(string Name)
	{
		this->Name = Name;
	}

	string getName()
	{
		return Name;
	}

	void setType(string Type)
	{
		this->Type = Type;
	}

	string getType()
	{
		return Type;
	}

	void setCost(double Cost)
	{
		this->Cost = Cost;
	}

	double getCost()
	{
		return Cost;
	}

	void setright(CourseNode *right)
	{
		this->right = right;
	}

	CourseNode* getright()
	{
		return right;
	}

	void setleft(CourseNode *left)
	{
		this->left = left;
	}

	CourseNode* getleft()
	{
		return left;
	}
};

class Courses
{
	CourseNode * Root;
	CourseNode * NN;
	CourseNode * Current;
	CourseNode * LastCurrent;
	public:
		Courses()
		{
			Root = Current = LastCurrent = NN = NULL;
		}~Courses()
		{
			delete Root, Current, LastCurrent, NN;
		}

	void SetRoot(CourseNode *Root)
	{
		this->Root = Root;
	}

	CourseNode* GetRoot()
	{
		return Root;
	}

	void AddCourses()
	{
		fstream file;
		int size, val;
		cout << "How Many Courses You Want In the Tress:  ";
		cin >> size;
		for (int j = 1; j <= size; j++)
		{
			cout << "\n*****Enter Course#" << j << " Details*****\n";

			file.open("Courses.txt", ios::out | ios::app);

			int i;
			cout << "\nEnter The Course ID   :   ";
			cin >> i;
			file << endl << setw(20) << i;
			string n;
			cout << "\nEnter The Course Name :   ";
			cin >> n;
			file << setw(20) << n;
			string t;
			cout << "\nEnter The Course Type :   ";
			cin >> t;
			file << setw(20) << t;
			double c;
			cout << "\nEnter The Course Cost :   ";
			cin >> c;
			file << setw(20) << c;
			Add(i, n, t, c);
			file.close();
			system("cls");
		}
	}

	void Add(int i, string n, string t, double c)
	{
		NN = new CourseNode;
		NN->setcid(i);
		NN->setName(n);
		NN->setType(t);
		NN->setCost(c);
		NN->setleft(NULL);
		NN->setright(NULL);

		if (Root == NULL)
		{
			Root = NN;
		}
		else
		{
			Current = Root;
			while (Current != NULL)
			{
				LastCurrent = Current;
				if (i < Current->getcid())
				{
					Current = Current->getleft();
				}
				else
				{
					Current = Current->getright();
				}
			}

			if (LastCurrent->getcid() < i)
			{
				LastCurrent->setright(NN);
			}
			else
			{
				LastCurrent->setleft(NN);
			}
		}
	}

	CourseNode* Search()
	{
		int search;
		cout << "\nEnter Course ID:  ";
		cin >> search;
		Current = Root;
		LastCurrent = NULL;
		while (Current != NULL && Current->getcid() != search)
		{
			LastCurrent = Current;
			if (search < Current->getcid())
			{
				Current = Current->getleft();
			}
			else
			{
				Current = Current->getright();
			}
		}

		if (Current != NULL)
		{
			cout << "\n\t\t\t\t__________________________________________________" <<
				"\n\t\t\t\t|                 RECORD FOUND                   |" <<
				"\n\t\t\t\t|________________________________________________|" <<
				"\n\t\t\t\t|                     |                          |" <<
				"\n\t\t\t\t|       NAME          |           " << left << setw(15) << Current->getName() << "|" <<
				"\n\t\t\t\t|       TYPE          |           " << left << setw(15) << Current->getType() << "|" <<
				"\n\t\t\t\t|       COST          |           " << left << setw(15) << Current->getCost() << "|" <<
				"\n\t\t\t\t|_____________________|__________________________|";
		}
		else
		{
			cout << "\n*****Course Not Found*****\n";
		}

		getch();
		system("cls");
		return Current;
	}

	void Update()
	{
		Search();
		char choice;
		if (Current != NULL)
		{
			int id;
			string name, type;
			double cost;
			do { 	cout << "\n\t\t\t\t\t________________________________" <<
					"\n\t\t\t\t\t|                              |" <<
					"\n\t\t\t\t\t|        UPDATE SYSTEM         |" <<
					"\n\t\t\t\t\t|______________________________|" <<
					"\n\t\t\t\t\t|                              |" <<
					"\n\t\t\t\t\t|[1]  UPDATE NAME             |" <<
					"\n\t\t\t\t\t|                              |" <<
					"\n\t\t\t\t\t|[2]  UPDATE TYPE             |" <<
					"\n\t\t\t\t\t|                              |" <<
					"\n\t\t\t\t\t|[3]  UPDATE COST             |" <<
					"\n\t\t\t\t\t|                              |" <<
					"\n\t\t\t\t\t|[4]  EXIT TO MAIN            |" <<
					"\n\t\t\t\t\t|______________________________|" <<
					"\n\nENTER YOUR CHOICE.\n";
				cin >> choice;
				system("cls");
				switch (choice)
				{
					case '1':
						cout << "\nEnter New Name = ";
						cin >> name;
						Current->setName(name);
						break;
					case '2':
						cout << "\nEnter New TYPE = ";
						cin >> type;
						Current->setType(type);
						break;
					case '3':
						cout << "\nEnter New COST = ";
						cin >> cost;
						Current->setCost(cost);
						break;
				}

				system("cls");
			} while (choice != '4');
			SaveFile(Root);
			UpdateFile();
		}
	}

	CourseNode* Delete()
	{
		Search();
		CourseNode *temp = NULL;
		if (Current != NULL)
		{
			if (Current->getleft() == NULL || Current->getright() == NULL)
			{
				if (Current->getleft() == NULL)
				{
					temp = Current->getright();
				}
				else
				{
					temp = Current->getleft();
				}

				if (LastCurrent == NULL)
				{
					SaveFile(Root);
					UpdateFile();
					return temp;
				}

				if (LastCurrent->getleft() == Current)
				{
					LastCurrent->setleft(temp);
				}
				else
				{
					LastCurrent->setright(temp);
				}

				free(Current);
			}
			else
			{
				CourseNode *P = NULL;
				temp = Current->getright();
				while (temp->getleft() != NULL)
				{
					P = temp;
					temp = temp->getleft();
				}

				if (P != NULL)
				{
					P->setleft(temp->getright());
				}
				else
				{
					Current->setright(temp->getright());
				}

				Current->setcid(temp->getcid());
				Current->setName(temp->getName());
				Current->setType(temp->getType());
				Current->setCost(temp->getCost());
				free(temp);
			}
		}

		SaveFile(Root);
		UpdateFile();
		return Root;
	}

	void DisplayAll()
	{
		fstream file;
		file.open("Courses.txt", ios:: in);

		if (!file)
		{
			cout << "\n******No File Created ******\n";
		}
		else
		{
			string view;

			cout << "\n\t___________________________________________________________________________" << "\n\n";
			cout << "\t" << setw(10) << "ID" << setw(18) << "NAME" << setw(19) << "TYPE" << setw(19) << "COST";
			cout << "\n\t___________________________________________________________________________";
			getline(file, view);	//to ignore the first blank line in file
			while (!file.eof())
			{
				getline(file, view);
				cout << "\n\n" << view;
			}

			file.close();
		}

		getch();
		system("cls");
	}

	void DisplayTree(CourseNode *r, int space)
	{
		if (r == NULL) return;
		space += SPACE;
		DisplayTree(r->getright(), space);
		cout << endl;
		for (int i = SPACE; i < space; i++) cout << " ";
		cout << r->getcid() << "\n";
		for (int i = SPACE; i < space; i++) cout << " ";
		cout << r->getName() << "\n";
		for (int i = SPACE; i < space; i++) cout << " ";
		cout << r->getType() << "\n";
		for (int i = SPACE; i < space; i++) cout << " ";
		cout << r->getCost() << "\n";
		DisplayTree(r->getleft(), space);
	}

	void SaveFile(CourseNode *A)
	{
		fstream file;
		if (A != NULL)
		{
			int id;
			string name, type;
			double cost;
			file.open("Courses1.txt", ios::out | ios::app);
			file << endl << setw(20) << A->getcid();
			file << setw(20) << A->getName();
			file << setw(20) << A->getType();
			file << setw(20) << A->getCost();
			file.close();
			SaveFile(A->getleft());
			SaveFile(A->getright());
		}
	}

	void UpdateFile()
	{
		DeleteFile();
		rename("Courses1.txt", "Courses.txt");
	}

	void UpdateTree()
	{
		fstream file;
		file.open("Courses.txt", ios:: in);
		if (file)
		{
			int id;
			string name, type;
			double cost;
			//getline(file, name);		//to ignore the first blank line in file
			while (!file.eof())
			{
				file >> id >> name >> type >> cost;
				Add(id, name, type, cost);
			}

			file.close();
		}
	}

	void DeleteFile()
	{
		remove("Courses.txt");
	}

	void DeleteTree()
	{
		if (Root == NULL) return;

		CourseNode * temp;
		Current = Root->getleft();
		while (Current != NULL)
		{
			temp = Current;
			Current = Current->getleft();
			delete temp;
		}

		Current = Root->getright();
		while (Current != NULL)
		{
			temp = Current;
			Current = Current->getright();
			delete temp;
		}

		Current = Root;
		delete Current;
		DeleteFile();
		Root = NULL;
	}

	void MENU()
	{
		char choice;
		do { 	cout << "======================================================"
			"==================================================================\n"
			"\n\n\t\t\t\t\t         M A I N   M E N U    \n\n\n"
			"=============================================================="
			"==========================================================\n\n\n"
			"\n     ________________________________  \t________________________________  \t________________________________"
			"\n     |                              |  \t|                              |  \t|                              |"
			"\n     | 1 ->     ADD COURSES         |  \t| 2 ->     DISPLAY ALL         |  \t| 3 ->    DISPLAY TREE         |"
			"\n     |______________________________|  \t|______________________________|  \t|______________________________|"
			"\n     ________________________________  \t________________________________  \t________________________________"
			"\n     |                              |  \t|                              |  \t|                              |"
			"\n     | 4 ->      SEARCH             |  \t| 5 ->        UPDATE           |  \t| 6 ->    DELETE COURSE        |"
			"\n     |______________________________|  \t|______________________________|  \t|______________________________|"
			"\n     ________________________________  \t________________________________  \t________________________________"
			"\n     |                              |  \t|                              |  \t|                              |"
			"\n     | 7 ->     DELETE ALL          |  \t| 8 ->      MAIN MENU          |  \t| 9 ->       E X I T           |"
			"\n     |______________________________|  \t|______________________________|  \t|______________________________|"
			"\n\n=============================================================="
			"==========================================================\n\n\n"
			"\n\t\t\t\t\t\t ENTER YOU CHOICE =  ";
			cin >> choice;
			system("cls");
			switch (choice)
			{
				case '1':
					AddCourses();
					break;

				case '2':
					DisplayAll();
					break;

				case '3':
					DisplayTree(GetRoot(), 5);
					getch();
					system("cls");
					break;

				case '4':
					Search();
					break;

				case '5':
					Update();
					break;

				case '6':
					SetRoot(Delete());
					break;

				case '7':
					DeleteTree();
					break;

				case '9':
					exit(0);
					break;

				default:
					system("cls");
			}
		} while (choice != '8');
	}
};


#endif
