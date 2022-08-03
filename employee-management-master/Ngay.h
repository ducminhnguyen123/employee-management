#pragma once
#include <iostream>
#include <string>
#include<sstream>
#include <ctime>
#include "MyLib.h"
using namespace std;

class Ngay
{

public:
	Ngay();
	Ngay(int, int, int);
	Ngay(wstring ngay);
	bool operator==(Ngay b);
	bool operator!=(Ngay b);
	int soSanh(Ngay *a, Ngay *b);
	bool timNgay(Ngay *a, Ngay *b);
	void nhapNgay();
	wstring toString();
	int kiemTraNhap(int month, int day, int year);


	int getNgay();
	int getThang();
	int getNam();
	~Ngay() {};
private:
	int ngay, thang, nam;
};