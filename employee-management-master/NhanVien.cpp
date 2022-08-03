#pragma once
#include "NhanVien.h"


NhanVien::NhanVien()
{
	this->viTri = 0;
	this->ma = 0;
	this->hoTen = L"";
	this->chucVu = L"";
	this->ngaySinh = NULL;
	this->heSoLuong = 0;
}

NhanVien::NhanVien(int ma, wstring hoTen, wstring chucVu, Ngay* ngaySinh, float heSoLuong)
{
	this->viTri = 0;
	this->ma = ma;
	this->hoTen = hoTen;
	this->chucVu = chucVu;
	this->ngaySinh = ngaySinh;
	this->heSoLuong = heSoLuong;
}
//}

bool NhanVien::nhapThongTin(int ma, vector<wstring> *chucVuArr)
{
	NhanVien *tam = new NhanVien;
	MyLib::Chuoi *chuoi = new MyLib::Chuoi();
	if (chucVuArr->size() > 0) {
		system("cls");
		tam->ma = ma;
		wcout << L"\n\t\t\t  * Nhập thông tin nhân viên:* ";
		wcout << L"\n\t\t\t----------------------------------------";
		while (true)
		{
			wcout << L"\n\t\t\t Họ và tên: ";
			//wcin.ignore();
			getline(wcin, tam->hoTen);
			if (tam->hoTen.size() > 0) {
				if (chuoi->kiemTraNhapTen(tam->hoTen) == true) {
					tam->hoTen = chuoi->vietHoaKiTuDau(tam->hoTen);
					break;
				}
			}
			else
				wcout << L"\n\t\t\tTên không được để trống!";
		}
		wcout << L"\n\t\t\t----------------------------------------";



		Menu *m = new Menu();
		int viTriChon = 0;
		bool thoat = false;
		while (true)
		{

			system("cls");
			wcout << L"\n\t\t\t  * Nhập thông tin nhân viên:* ";
			wcout << L"\n\t\t\t----------------------------------------";
			wcout << L"\n\t\t\t Họ và tên: " << tam->hoTen;
			wcout << L"\n\t\t\t----------------------------------------";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			wcout << L"\n\t\t\tChọn chức vụ( nhấn enter ở chức vụ bạn chọn)\n";
			for (int i = 0; i < chucVuArr->size(); ++i)
			{
				if (viTriChon == i) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 125);
					wcout << L"\n\t\t\t" << right << setw(5) << L"=> " << left << setw(25) << chucVuArr->data()[i];
				}
				else {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					wcout << L"\n\t\t\t" << right << setw(5) << L"   " << left << setw(25) << chucVuArr->data()[i];
				}
			}

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

			int diChuyenPhim;
			if (_kbhit) {
				diChuyenPhim = m->diChuyenPhim();
				switch (diChuyenPhim) {
				case 1:
				case 3: {
					viTriChon += 1;
					if (viTriChon == chucVuArr->size())
						viTriChon = 0;
					break; }
				case 2:
				case 4: {
					viTriChon -= 1;
					if (viTriChon == -1)
						viTriChon = chucVuArr->size() - 1;
					break; }
				case 5:
					if (viTriChon >= 0 && viTriChon <= chucVuArr->size()) {
						tam->chucVu = chucVuArr->data()[viTriChon];
						thoat = true;
					}
					break;

				default:
					break;
				}
			}

			if (thoat == true)
				break;

		}


		//wcout << L"\n\t\t\t-Chọn chức vụ: ";
		//for (int i = 0; i < chucVuArr->size(); i++)
		//	wcout << "\n\t\t\t" << (i + 1) << " : " << chucVuArr->data()[i].c_str();
		//wstring cv;
		//int soNguyen;
		//while (true) {
		//	wcout << L"\n\t\t\t=> Vui lòng nhập số tương ứng: ";
		//	wcin >> cv;
		//	//if (chuoi->kiemTraNhapSoNguyen(cv) == true)
		//	soNguyen = chuoi->chuyenStringSangSoNguyen(cv);
		//	if (soNguyen >= 1 && soNguyen <= chucVuArr->size()) {
		//		tam->chucVu = chucVuArr->data()[soNguyen - 1];
		//		break;
		//	}
		//	wcout << L"\n\t\t\tVui lòng nhập số theo yêu cầu!";
		//}

		system("cls");
		wcout << L"\n\t\t\t  * Nhập thông tin nhân viên:* ";
		wcout << L"\n\t\t\t----------------------------------------";
		wcout << L"\n\t\t\t Họ và tên: " << tam->hoTen;
		wcout << L"\n\t\t\t----------------------------------------";
		wcout << L"\n\t\t\t Chức vụ: " << tam->chucVu;
		wcout << L"\n\t\t\t----------------------------------------";
		wcout << L"\n\t\t\t Ngày sinh: \n";
		tam->ngaySinh = new Ngay();
		tam->ngaySinh->nhapNgay();

		system("cls");
		wcout << L"\n\t\t\t  * Nhập thông tin nhân viên:* ";
		wcout << L"\n\t\t\t----------------------------------------";
		wcout << L"\n\t\t\t Họ và tên: " << tam->hoTen;
		wcout << L"\n\t\t\t----------------------------------------";
		wcout << L"\n\t\t\t Chức vụ: " << tam->chucVu;
		wcout << L"\n\t\t\t----------------------------------------";
		wcout << L"\n\t\t\t Ngày sinh: " << tam->ngaySinh->toString();
		wcout << L"\n\t\t\t----------------------------------------";



		wstring hs;
		float soThuc;
		while (true)
		{
			wcout << L"\n\t\t\t Hệ số lương: ";
			getline(wcin, hs);
			soThuc = chuoi->chuyenStringSangSoThuc(hs);
			if (soThuc > 0 && soThuc <= 10) {
				tam->heSoLuong = soThuc;
				break;
			}
			/*wcin >> tam->heSoLuong;*/
			/*if (tam->heSoLuong > 0 && tam->heSoLuong <= 10)
				break;
			else*/
			wcout << L"\t\t\tDữ liệu không hợp lệ, vui lòng thử lại!";
		}

	}


	vector<wstring> menuLuu = { L"CÓ", L"KHÔNG" };
	int viTriLuu = 0;
	while (true)
	{
		system("cls");
		wcout << tam->thongTin();
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		wcout << L"\n\n\t\t\t\tbạn có muốn lưu thông tin nhân viên trên?\n";
		//for (int i = 0; i < menuLuu.size(); ++i)
		//{
		//	//wcout << L'\t';
		//	if (i == viTriLuu)
		//		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 125);
		//	else
		//		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

		//	wcout << L"\n\t\t\t\t╔═══════════════╗";
		//	wcout << L"\n\t\t\t\t║" << right << setw(5) << L" " << left << setw(10) << menuLuu[i] << right << setw(0) << L'║';
		//	wcout << L"\n\t\t\t\t╚═══════════════╝";

		//	/*	wcout << left << setw(7) << menuLuu[i]<<setw(5);*/
		//	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

		//}

		for (int i = 0; i < menuLuu.size(); ++i)
		{
			if (i == 0)
				wcout << "\n\t\t\t\t";
			else
				wcout << "\t";
			if (viTriLuu == i)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 125);
			else
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			wcout << L"╔═══════════════╗";
		}
		for (int i = 0; i < menuLuu.size(); ++i)
		{
			if (i == 0)
				wcout << "\n\t\t\t\t";
			else
				wcout << "\t";
			if (viTriLuu == i)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 125);
			else
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			wcout << L"║" << right << setw(5) << L" " << left << setw(10) << menuLuu[i] << right << setw(0) << L'║';
		}
		for (int i = 0; i < menuLuu.size(); ++i)
		{
			if (i == 0)
				wcout << "\n\t\t\t\t";
			else
				wcout << "\t";
			if (viTriLuu == i)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 125);
			else
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			wcout << L"╚═══════════════╝";

		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		int luu;
		Menu me;
		if (_kbhit) {
			luu = me.diChuyenPhim();
			switch (luu) {
			case 1:
			case 3: {
				viTriLuu += 1;
				if (viTriLuu == menuLuu.size())
					viTriLuu = 0;
				break; }
			case 2:
			case 4: {
				viTriLuu -= 1;
				if (viTriLuu == -1)
					viTriLuu = menuLuu.size()-1;
				break; }
			case 5:
				switch (viTriLuu) {
				case 0: {
					this->ma = tam->ma;
					this->hoTen = tam->hoTen;
					this->chucVu = tam->chucVu;
					this->ngaySinh = tam->ngaySinh;
					this->heSoLuong = tam->heSoLuong;
					return true;
				}
				case 1:
					wcout << endl;
					return false;
				}


			default:
				break;
			}

		}

	}



}

wstring NhanVien::toString()
{
	wstringstream  os;
	os << L"\n\t│" << setw(20) << this->hoTen << setw(5) << L"│" << setw(20) << this->chucVu << setw(5) << L"│" << setw(18) << this->ngaySinh->toString() << setw(7) << L"│" << setw(15) << this->heSoLuong << setw(10) << L"│";
	return os.str();
}


wstring NhanVien::toStringSearch()
{
	wstringstream  os;
	os << L"\n\t│" << setw(5) << this->viTri << setw(5) << L"│" << setw(20) << this->hoTen << setw(5) << L"│" << setw(20) << this->chucVu << setw(5) << L"│" << setw(18) << this->ngaySinh->toString() << setw(7) << L"│" << setw(15) << this->heSoLuong << setw(10) << L"│";
	return os.str();
}

wstring NhanVien::toLuuFile()
{

	wstringstream  os;
	os << L"\n" << this->ma << L"\n" << this->hoTen << L"\n" << this->chucVu << L"\n" << this->ngaySinh->toString() << L"\n" << this->heSoLuong;
	return os.str();

}

int NhanVien::soSanhTen(wstring hoTenA, wstring hoTenB)
{
	if (hoTenA == hoTenB)return 0;
	else {
		MyLib::Chuoi *chuoi = new MyLib::Chuoi();
		vector<wstring> *ar = chuoi->tach(hoTenA, ' '), *br = chuoi->tach(hoTenB, ' ');
		const wchar_t* tenA = ar->data()[ar->size() - 1].c_str()
			, *hoA = ar->data()[0].c_str()
			, *tenB = br->data()[br->size() - 1].c_str()
			, *hoB = br->data()[0].c_str()
			, *tenDemA = L"", *tenDemB = L"";
		for (int i = 1; i < ar->size() - 1; i++)
			tenDemA += *ar->data()[i].c_str();
		for (int i = 1; i < br->size() - 1; i++)
			tenDemB += *br->data()[i].c_str();// data()[i] là gì 



		int kq;
		chuoi->soSanhChuoi(tenA, tenB) > 0 ?
			kq = 1 : chuoi->soSanhChuoi(tenA, tenB) < 0 ?
			kq = -1 : kq = 0;
		if (kq != 0)return kq;
		chuoi->soSanhChuoi(tenDemA, tenDemB) > 0 ?
			kq = 1 : chuoi->soSanhChuoi(tenDemA, tenDemB) < 0 ?
			kq = -1 : kq = 0;
		if (kq != 0)return kq;
		chuoi->soSanhChuoi(hoA, hoB) > 0 ?
			kq = 1 : chuoi->soSanhChuoi(hoA, hoB) < 0 ?
			kq = -1 : kq = 0;
		if (kq != 0)return kq;

	}
	return 0;
}

wstring NhanVien::thongTin()
{
	wstringstream  os;
	os << L"\n\t\t\t\t\t* Thông tin nhân viên:* "
		<< L"\n\t\t\t\t----------------------------------------"
		<< L"\n\t\t\t\t Họ và tên: " << this->hoTen
		<< L"\n\t\t\t\t----------------------------------------"
		<< L"\n\t\t\t\t Chức vụ: " << this->chucVu
		<< L"\n\t\t\t\t----------------------------------------"
		<< L"\n\t\t\t\t Ngày sinh: " << this->ngaySinh->toString()
		<< L"\n\t\t\t\t----------------------------------------"
		<< L"\n\t\t\t\t Hệ số lương: " << this->heSoLuong
		<< L"\n\t\t\t\t----------------------------------------";
	return os.str();
}

bool NhanVien::operator!=(NhanVien * a)
{
	return this->ma != a->ma;
}

int NhanVien::getViTri()
{
	return this->viTri;
}

int NhanVien::getMa()
{
	return this->ma;
}

wstring NhanVien::getHoTen()
{
	return this->hoTen;
}

Ngay* NhanVien::getNgaySinh()
{
	return this->ngaySinh;
}

float NhanVien::getHeSoLuong()
{
	return this->heSoLuong;
}

wstring NhanVien::getChucVu()
{
	return this->chucVu;
}

void NhanVien::setViTri(int viTri)
{
	this->viTri = viTri;
}

void NhanVien::setMa(int ma) { this->ma = ma; }

void NhanVien::setHoTen(wstring hoTen) { this->hoTen = hoTen; }

void NhanVien::setChucVu(wstring chucVu) { this->chucVu = chucVu; }

void NhanVien::setNgaySinh(Ngay * ngaySinh) { this->ngaySinh = ngaySinh; }

void NhanVien::setHeSoLuong(float heSoLuong) { this->heSoLuong = heSoLuong; }


NhanVien::~NhanVien()
{
}
