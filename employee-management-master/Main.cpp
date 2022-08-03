#pragma once
#include "windows.h"
#include <io.h>
#include <fcntl.h>"
#include "CongTy.h"
#include "MyLib.h"


int main() {
	_setmode(_fileno(stdout), _O_WTEXT); //needed for output
	_setmode(_fileno(stdin), _O_WTEXT); //needed for input

	CongTy *ct = new CongTy;
	const char* path = "F://CTDL và giải thuật//btl_CTDL//btl_CTDL//data.txt";
	const char* pathXuat = "F://CTDL và giải thuật//btl_CTDL//btl_CTDLxuat.txt";
	ct->menuChucNang(path, pathXuat);

	//MyLib::Chuoi chuoi;
	//wstring s;
	//getline(wcin, s);
	//wcout << chuoi.boKhoangTrang(s);


	//MyLib::Chuoi *chuoi = new MyLib::Chuoi();
	//wcout << chuoi->tach(L"h,,du", L',');
	//wcout<<chuoi.boKhoangTrang(L"    ")<<endl;
	//wcout << chuoi.boKhoangTrang(L"k ") << endl;
	//wcout << chuoi.boKhoangTrang(L" \t\n") << endl;
	//wcout << chuoi.soSanhChuoi(L"Khải", L"Xuân");


	//
	//Stack *temp = new Stack(),*chinh= new Stack();
	//NhanVien *nv = new NhanVien(1, L"Lê Tuấn khôi", L"nhân viên", new Ngay(L"09/03/1998"), (float)5.6);
	//NhanVien *nv2 = new NhanVien(2, L"Lê Tuấn khải", L"nhân viên", new Ngay(L"09/03/1998"), (float)5.6);
	//temp->push(*nv);
	//chinh->push(*nv2);
	//chinh->push(*nv);
	//chinh->deleteSearch(temp);
	//wcout << chinh->toString();

	//MyLib::Chuoi *chuoi = new MyLib::Chuoi();
	/*vector<wstring> chucVuArr;
	NhanVien *nv = new NhanVien;
	nv->nhapThongTin(1,chucVuArr);*/
	/*wstring kiTu = L"aáàảạãăắằẳặẵâấầẩậẫbcdđeéèẻẹẽêếềểệễghiíìỉịĩklmnoóòỏọõôốồổộỗơớờởợỡpqrstuúùủụũưứừửữvxyAÁÀẢẠÃĂẮẰẲẶẴÂẤẦẨẬẪBCDĐEÉÈẺẸẼÊẾỀỂỆỄGHIÍÌỈỊĨKLMNOÓÒỎỌÕÔỐỒỔỘỖƠỚỜỞỢỠPQRSTUÚÙỦỤŨƯỨỪỬỮVXY";
	MyLib::Chuoi *chuoi = new MyLib::Chuoi;
	int chua = chuoi->kiemTrachuaChuoi(L"khải", kiTu.c_str());
	wcout << L"chuỗi chứa " << chua;*/

	//wstring s(L"1/1/1998");

	//MyLib::TachChuoi *tc = new MyLib::TachChuoi;
	//vector<wstring> flds = tc->tach(s, '/');
	//for (int k = 0; k < flds.size(); k++)
	//	wcout << k << " => " << flds[k] << endl;



	//Ngay * n = new Ngay(L"1/11/1998");
	//ct->hienThi();
	/*NhanVien *nv = new NhanVien(1, L"Lê Tuấn khải", L"nhân viên", new Ngay(L"09/03/1998"), (float)5.6);
	NhanVien *nv2 = new NhanVien(2, L"Lê Tuấn khải", L"nhân viên", new Ngay(L"09/03/1998"), (float)5.6);
	ct->themNhanVien(nv);
	ct->themNhanVien(nv2);
	ct->hienThi();
	ct->luuFile(path);*/
	/*ct->docFile(path);
	ct->sapXep();*/




	/*MyLib::Chuoi * string = new MyLib::Chuoi;
	int kq = string->soSanhChuoi(L"Ẫ", L"ẫ");
	*/


	/*
	Stack *st = new Stack;
	NhanVien nv("0001",L"khải",L"nhân viên",Ngay("09/03/1998"),(float)5.6);
	NhanVien nv1("0002", L"khải", L"nhân viên", Ngay("09/03/1998"), (float)5.6);
	NhanVien nv2("0003", L"khải", L"nhân viên", Ngay("09/03/1998"), (float)5.6);
	st->push(nv);
	st->push(nv1);
	st->push(nv2);
	while(st->isEmpty()==false)
	wcout<<st->pop().toString().str();
	*/


	system("pause");
	return 0;
}