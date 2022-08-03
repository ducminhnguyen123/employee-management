#pragma once
#include <locale>
#include <fstream>
#include <codecvt>
#include<fstream>
#include<iomanip>
#include <windows.h>
#include<conio.h>
#include "MyLib.h"
#include "Ngay.h"
#include "Menu.h"


class NhanVien
{
public:
	NhanVien();
	NhanVien(int ma, wstring hoTen, wstring chucVu, Ngay* ngaySinh, float heSoLuong);
	bool nhapThongTin(int ma, vector<wstring> *chucVu);
	wstring toString();
	wstring toStringSearch();
	wstring toLuuFile();
	int soSanhTen(wstring hoTenA, wstring hoTenB);
	wstring thongTin();
	bool operator!=(NhanVien *a);

	int getViTri();
	int getMa();
	wstring getHoTen();
	Ngay *getNgaySinh();
	float getHeSoLuong();
	wstring getChucVu();

	void setViTri(int viTri);
	void setMa(int ma);
	void setHoTen(wstring hoTen);
	void setChucVu(wstring chucVu);
	void setNgaySinh(Ngay * ngaySinh);
	void setHeSoLuong(float heSoLuong);
	~NhanVien();
private:
	int viTri;
	int ma;
	wstring hoTen;
	wstring chucVu;
	Ngay *ngaySinh;
	float heSoLuong;

};
