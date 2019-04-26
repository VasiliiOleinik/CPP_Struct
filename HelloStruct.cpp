// HelloStruct.cpp:
//

#include "stdafx.h"
#include <iostream>
using std::cout;

#include <Windows.h>

// Structure declarations
// C 		C ++
// struct 	TAG_IMA_NEW_TYPE {
// type1 	name1 field;
// type2	 name2;
// ... 		...
// typeN 	namePolyN;
//};

struct TPoint
{
	double x; // fields
	double y;

	// Encapsulation
	// function == method
	void Set(double xx, double yy)
	{
		x = xx;
		y = yy;
	}
	void Show(char *s, bool nl = true);
};

void init();
double rnd(double a = -12., double b = 24.);
int FileLength(char *FName);
void FileSort(char *FName);

int _tmain(int argc, _TCHAR *argv[])
{
	init();

	// Declaration of a variable - structure
	TPoint a;

	// Variable declaration - initialized structures
	TPoint b = {1., 2.};

	// Declaration of a variable - a pointer to the structure
	TPoint *p;
	TPoint *p1 = &a;

	TPoint c;

	// Create dynamic structure
	p = new TPoint;
	p->x = 123;
	p->y = 321;
	cout << "Dynamic point: " << p->x << "; " << p->y << "\n";

	// Access to structure fields
	// 1) Operation point. variable structure
	// 2) Arrow operation -> pointer to structure
	a.x = 12;
	a.y = 23;
	cout << "point a: " << p1->x << "; " << p1->y << "\n";
	cout << "point b: " << b.x << "; " << b.y << "\n";

	c = a;
	cout << "point c: " << c.x << "; " << c.y << "\n";

	// Now using methods
	a.Set(-1., -2.);
	b.Set(10., 11.);
	p->Set(-100., 100.);

	a.Show("Point A: ");
	b.Show("POint B: ");
	p->Show("Dynamic point: ");

	delete p;
	// p = 0;

	cout << "\n\nStructure size: " << sizeof(TPoint) << "\n\n";

	// Arrays of structures
	// type Name [Size];
	// type Name [Size1] [Size2] [Size3];
	const int N = 5;
	// TPoint arr[N] = { {1., 1.}, {2., 1.}, {2., 5.} };
	TPoint *arr = new TPoint[N];

	for (int i = 0; i < N; i++)
	{
		arr[i].Set(rnd(), rnd());
		arr[i].Show("C������������: ");
	} // for i

	// Write structures to file - concept of databases
	FILE *f = fopen("points.dat", "wb");
	// Buffer, 1st item size, Number of elements, file
	// fwrite (arr, sizeof (TPoint), N, f); // Write the entire array

	// Record on the 1st structure
	for (int i = 0; i < N; i++)
	{
		// Buffer, 1st item size, Number of elements, file
		fwrite(&arr[i], sizeof(TPoint), 1, f);
		arr[i].Show("Registered: ");
	} // for i
	fclose(f);
	delete[] arr;

	f = fopen("points.dat", "rb");
	int n;
	// Move the file pointer
	// File Offset Reference Point
	fseek(f, 0, SEEK_END); // SEEK_SET SEEK_CUR SEEK_END

	n = ftell(f);		  // Position of the file pointer in bytes rel. file start
	n / = sizeof(TPoint); // File size in records
	fseek(f, 0, SEEK_SET);

	cout << "---------------------------\n";
	// Reading from file by 1st structure
	p = new TPoint;
	for (int i = 0; i < n; i++)
	{
		// Buffer, 1st item size, Number of elements, file
		fread(p, sizeof(TPoint), 1, f);
		p->Show("���������: ");
	} // for i
	fclose(f);

	FileSort("points.dat");

	cout << "---------------------------\n";
	f = fopen("points.dat", "rb");
	for (int i = 0; i < n; i++)
	{
		// Buffer, 1st item size, Number of elements, file
		fread(p, sizeof(TPoint), 1, f);
		p->Show("Read:");
	} // for i
	fclose(f);

	delete p;
	return 0;
} // _tmain

// Preparing the application for work
void init()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	srand(GetTickCount());
} // init

// Define method outside structure declaration
void TPoint::Show(char *s, bool nl)
{
	cout << s;
	cout << x << "; " << y;
	if (nl)
		cout << "\n";
} // Show

double rnd(double a, double b)
{
	return a + (b - a) * rand() / (RAND_MAX + 1);
} // rnd

void FileSort(char *FName)
{
	FILE *f = fopen("points.dat", "r+b");
	TPoint *j1 = new TPoint;
	TPoint *p = new TPoint;
	int n = FileLength(FName);

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n - i - 1; j++)
		{
			fseek(f, j * sizeof(TPoint), SEEK_SET);
			fread(p, sizeof(TPoint), 1, f);
			fread(j1, sizeof(TPoint), 1, f);
			if (p->x > j1->x)
			{
				fseek(f, j * sizeof(TPoint), SEEK_SET);
				fwrite(j1, sizeof(TPoint), 1, f);
				fwrite(p, sizeof(TPoint), 1, f);
			} // if
		}	 // for j
	}		  // for i
	fclose(f);

	delete p;
	delete j1;
}

int FileLength(char *FName)
{
	FILE *f = fopen("points.dat", "rb");
	fseek(f, 0, SEEK_END); // SEEK_SET     SEEK_CUR    SEEK_END

	int n = ftell(f);	 // Position of the file pointer in bytes rel. file start
	n / = sizeof(TPoint); // File size in records
	fseek(f, 0, SEEK_SET);
	return n;
} // FileLength