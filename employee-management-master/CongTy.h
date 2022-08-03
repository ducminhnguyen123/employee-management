
#pragma once
#include <locale>
#include <string>
#include <fstream>
#include <codecvt>
#include <windows.h>
#include <conio.h> 
#include "NhanVien.h"
#include "Stack.h"
#include "MyLib.h"

class CongTy
{
public:
	CongTy(string ten = "");
	~CongTy();
	void docFile(const char* path);
	void luuFile(const char* path);
	void xuatFile(const char* path);
	void hienThi();
	void sapXep();
	void themNhanVien();
	void xoaNhanVien();
	void timKiem(int xoa);
	void menuChucNang(const char* path, const char* pathXuat);

	void quanLyChucVu();
	void themChucVu();
	void xoaChucVu();
	void suaChucVu();
	void suaViTriChucVu(int viTri,bool them);
private:
	string ten;
	Stack *danhSachNhanVien;
	vector<wstring> *chucVu;
	int tieuChiSapXepCuoi;
	int chieuXapXepCuoi;
	int maNhanVienCuoi;

};
