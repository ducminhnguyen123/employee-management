#pragma once
#include <stdio.h>
#include <vector>
#include <sstream>
#include<iostream>
using namespace std;

namespace MyLib
{
	class Chuoi
	{
	public:
		int soSanhChuoi(const wchar_t *X, const wchar_t *Y);
		int kiemTrachuaChuoi(const wchar_t *X, const wchar_t *Y);// done???
		vector<wstring> *tach(wstring s, char delim, int rep = 0); //done
		wstring vietHoa(wstring s); //done
		wstring vietThuong(wstring s); //done
		wstring boDau(wstring s); // done ???
		int timKiemChuoiCon(wstring chuoiCha, wstring chuoiCon);
		wstring boKhoangTrang(wstring a); //done
		bool kiemTraNhapTen(wstring ten); //done
		bool kiemTraNhapChucVu(wstring chucVu); //done
		wstring vietHoaKiTuDau(wstring ten); //done
		bool kiemTraNhapSoNguyen(wstring so); 
		bool kiemTraNhapSoThuc(wstring so);
		int chuyenStringSangSoNguyen(wstring so);
		float chuyenStringSangSoThuc(wstring so);



	};




}

//// Implement strcmp function in C
//int main()
//{
//	char *X = "Techie";
//	char *Y = "Tech";
//
//	int ret = strcmp(X, Y);
//
//	if (ret > 0)
//		printf("%s", "X is greater than Y");
//	else if (ret < 0)
//		printf("%s", "X is less than Y");
//	else
//		printf("%s", "X is equal to Y");
//
//	return 0;
//}
