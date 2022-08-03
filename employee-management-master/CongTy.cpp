#pragma once
#include "CongTy.h"

void choNhap(void) {
	wcout << L"\n\n\t\t\tNhấn phím bất kì để trở về: ";
	char c = _getch();
}

CongTy::CongTy(string ten)
{
	this->ten = ten;
	this->danhSachNhanVien = new Stack();
	this->chucVu = new vector<wstring>();
	this->tieuChiSapXepCuoi = 0;
	this->chieuXapXepCuoi = 0;
	this->maNhanVienCuoi = 0;

}

CongTy::~CongTy()
{
	this->ten = "";
	this->danhSachNhanVien->~Stack();
	this->tieuChiSapXepCuoi = 0;
	this->chieuXapXepCuoi = 0;
	this->maNhanVienCuoi = 0;
}

void CongTy::docFile(const char* path)
{

	locale loc(locale(), new codecvt_utf8<wchar_t>);  // UTF-8
	wifstream fin(path);
	if (!fin) {
		wcout << L"\n\t\t\tKhông thể đọc file " << path << "\n";
	}
	else {

		if (this->danhSachNhanVien->isEmpty() == false)
			this->danhSachNhanVien->~Stack();



		fin.imbue(loc);// đọc file không bị lỗi font trong console
		NhanVien * nv = new NhanVien();
		MyLib::Chuoi *chuoi = new MyLib::Chuoi();
		wstring ma, ten, chucVu, ngay, mangChucVu, tam, heSo;
		int maNVC = 0;

		vector<wstring> *ngayArr = new vector<wstring>();
		if (fin.good())
			getline(fin, mangChucVu);
		if (this->chucVu->size() == 0) // khi chức vụ chưa có tên chức vụ nào cả
			this->chucVu = chuoi->tach(mangChucVu, ',');
		else { // khi chức vụ có tên một số chức vụ trong file đọc
			vector<wstring> *tam = chuoi->tach(mangChucVu, ',');
			bool daCo = false;
			for (int i = 0; i < tam->size(); i++) {
				daCo = false;
				for (int j = 0; j < this->chucVu->size(); j++)
					if (tam->data()[i] == this->chucVu->data()[j])
						daCo = true;
				if (daCo == false)
					this->chucVu->push_back(tam->data()[i]);
			}

		}

		while (!fin.eof())
		{
			getline(fin, ma);
			getline(fin, ten);
			getline(fin, chucVu);
			getline(fin, ngay);
			getline(fin, heSo);
			if (ma.length() == 0 || ten.length() == 0 || chucVu.length() == 0 || ngay.length() == 0 || heSo.length() == 0)
				break;
			ngayArr = chuoi->tach(ngay, '/');
			//nv = new NhanVien(stoi(ma), ten, chucVu, new Ngay(stoi(ngayArr->data()[0]), stoi(ngayArr->data()[1]), stoi(ngayArr->data()[2])), stof(heSo));
			maNVC = maNVC < chuoi->chuyenStringSangSoNguyen(ma) ? chuoi->chuyenStringSangSoNguyen(ma) : maNVC;//???
			this->danhSachNhanVien->push(*new NhanVien(chuoi->chuyenStringSangSoNguyen(ma), chuoi->vietHoaKiTuDau(ten), chucVu, new Ngay(chuoi->chuyenStringSangSoNguyen(ngayArr->data()[0]), chuoi->chuyenStringSangSoNguyen(ngayArr->data()[1]), chuoi->chuyenStringSangSoNguyen(ngayArr->data()[2])), chuoi->chuyenStringSangSoThuc(heSo)));
			ma = L""; ten = L""; chucVu = L""; ngay = L""; heSo = L"";

		}
		this->maNhanVienCuoi = maNVC;
		fin.close();
		wcout << L"\n\n\t\t\tĐọc file thành công!\n";
		this->hienThi();
	}
	choNhap();

}

void CongTy::luuFile(const char * path)
{
	if (this->danhSachNhanVien->isEmpty() == false) {
		locale loc(locale(), new codecvt_utf8<wchar_t>);  // UTF-8
		wofstream fout(path);
		if (!fout) {
			wcout << L"\n\t\t\tKhông thể tạo file " << path << "\n";
		}
		else {
			fout.imbue(loc);
			for (int i = 0; i < this->chucVu->size() - 1; i++)
				fout << this->chucVu->data()[i].c_str() << ",";// bỏ c_str dc ko
			fout << this->chucVu->data()[this->chucVu->size() - 1].c_str(); // bỏ c_str dc ko
			fout << this->danhSachNhanVien->toSaveFile();
			fout.close();
			wcout << L"\n\t\t\tLưu file thành công!\n";
		}
	}
	else {
		wcout << L"\n\t\t\tDanh sách nhân viên rỗng\n";
		choNhap();
	}
}

void CongTy::xuatFile(const char* path)
{
	system("cls");
	if (this->danhSachNhanVien->isEmpty() == false) {
		locale loc(locale(), new codecvt_utf8<wchar_t>);  // UTF-8
		wofstream fout(path);
		if (!fout) {
			wcout << L"\n\t\t\tKhông thể tạo file " << path << "\n";
		}
		else {
			fout.imbue(loc);
			fout << this->danhSachNhanVien->toStringSearch();
			fout.close();
			wcout << L"\n\t\t\tXuất file thành công!\n";
			this->hienThi();
		}
	}
	else
		wcout << L"\n\t\t\tDanh sách nhân viên rỗng\n";
	choNhap();
}

void CongTy::hienThi()
{
	this->danhSachNhanVien->isEmpty() == false ? wcout << this->danhSachNhanVien->toStringSearch() : wcout << L"\n\t\tDanh sách nhân viên rỗng\n";
}

void CongTy::sapXep()
{

	system("cls");
	if (this->danhSachNhanVien->isEmpty() == false) {
		vector<wstring> menu = { L"Theo họ và tên", L"Theo chức vụ", L"theo ngày sinh",L"Theo hệ số lương",L"Quay về menu chính" };
		int pointer = 0;
		Menu *m = new Menu();

		while (true)
		{
			fflush(stdin);
			system("cls");

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			wcout << L"\n\t\t\t\tChọn tiêu chí sắp xếp\n";

			for (int i = 0; i < menu.size(); ++i)
			{

				if (i == pointer) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 125);
					wcout << L"\n\t\t\t\t╔════════════════════════════════════════════╗";
					wcout << L"\n\t\t\t\t║" << right << setw(10) << L">>  " << left << setw(34) << menu[i] << right << setw(0) << L'║';
					wcout << L"\n\t\t\t\t╚════════════════════════════════════════════╝";

				}
				else {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					wcout << L"\n\t\t\t\t╔════════════════════════════════════════════╗";
					wcout << L"\n\t\t\t\t║" << right << setw(10) << L"  " << left << setw(34) << menu[i] << right << setw(0) << L'║';
					wcout << L"\n\t\t\t\t╚════════════════════════════════════════════╝";

				}
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

			}

			int x;
			bool thoat = false;



			if (_kbhit) {
				x = m->diChuyenPhim();
				switch (x)
				{
				case 1:
				case 3: {
					pointer += 1;
					if (pointer == 5)
						pointer = 0;
					thoat = true;
					break; }
				case 2:
				case 4: {
					pointer -= 1;
					if (pointer == -1)
						pointer = 4;
					thoat = true;
					break; }
				case 5: {

					switch (pointer)
					{
					case 4:
						return; // quay về menu
					default:
					{
						vector<wstring> menuChon;
						switch (pointer)
						{
						case 0:
							menuChon = { L"Theo chiều xuôi", L"Theo chiều ngược",L"Trở về" };
							break;
						case 3:
							menuChon = { L"Tăng dần", L"Giảm dần",L"Trở về" };
							break;
						default:
							menuChon = { L"Lớn dần", L"Nhỏ dần",L"Trở về" };
							break;
						}


						int viTriChon = 0;
						bool troVe = false;
						Menu *menu = new Menu();
						while (true)
						{
							system("cls");

							this->hienThi();

							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							wcout << L"\n\n\t\t\t\tChọn chiều sắp xếp?\n\n";
							for (int i = 0; i < menuChon.size(); ++i)
							{
								if (i == viTriChon)
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 125);
								else
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

								wcout << L"\n\t\t\t\t╔════════════════════════════╗";
								wcout << L"\n\t\t\t\t║" << right << setw(5) << L" " << left << setw(17) << menuChon[i] << right << setw(7) << L'║';
								wcout << L"\n\t\t\t\t╚════════════════════════════╝";

								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

							}

							int nhanPhim;
							if (_kbhit) {
								nhanPhim = menu->diChuyenPhim();
								switch (nhanPhim) {
								case 1:
								case 3: {
									viTriChon += 1;
									if (viTriChon == 3)
										viTriChon = 0;
									break; }
								case 2:
								case 4: {
									viTriChon -= 1;
									if (viTriChon == -1)
										viTriChon = 2;
									break; }
								case 5: {
									switch (viTriChon)
									{
									case 2: {
										troVe = true;
										break;
									}
									default:
										this->danhSachNhanVien->sort(this->chucVu, pointer + 1, viTriChon + 1);
										this->tieuChiSapXepCuoi = pointer + 1;
										this->chieuXapXepCuoi = viTriChon + 1;
										break;
									}
									break; }
								default:
									break;
								}
							}

							if (troVe == true)
								break;

						}



					}

					}

					break;
				}

				default:
					break;
				}

			}

		}
	}
	else {
		wcout << L"\n\t\t\tDanh sách nhân viên rỗng, hãy đọc file hoặc thêm mới nhân viên trước!";
		choNhap();
	}


}

void CongTy::themNhanVien()
{
	if (this->chucVu->size() > 0) {
		NhanVien *nv = new NhanVien();
		if (nv->nhapThongTin(this->maNhanVienCuoi + 1, this->chucVu) == true) {
			this->danhSachNhanVien->insertNode(*nv, this->chucVu, this->tieuChiSapXepCuoi, this->chieuXapXepCuoi);
			/*this->danhSachNhanVien->push(*nv);
			this->danhSachNhanVien->sort(this->chucVu, this->tieuChiSapXepCuoi, this->chieuXapXepCuoi);*/
			this->maNhanVienCuoi = nv->getMa();
			wcout << L"\n\n\t\t\tThêm nhân viên thành công! ";
			system("cls");
			this->hienThi();
			choNhap();
		}
	}
	else {
		wcout << L"\n\n\t\t\tVui lòng đọc file hoặc thêm chức vụ trước! ";
		choNhap();
	}


}

void CongTy::xoaNhanVien()
{
	this->timKiem(0);//0 là xóa
}

void CongTy::timKiem(int xoa)
{

	system("cls");
	if (this->danhSachNhanVien->isEmpty() == false) {
		vector<wstring> menu = { L"Theo họ và tên", L"Theo chức vụ", L"theo ngày sinh",L"Theo hệ số lương",L"Quay về menu chính" };
		int pointer = 0;
		Menu *m = new Menu();
		while (true)
		{
			fflush(stdin);
			system("cls");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			if (xoa == 0)
				wcout << L"\n\t\t\t\tChọn tiêu chí xóa nhân viên\n";
			else
				wcout << L"\n\t\t\t\tChọn tiêu chí tìm kiếm\n";
			for (int i = 0; i < menu.size(); ++i)
			{
				if (i == pointer) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 125);
					wcout << L"\n\t\t\t\t╔════════════════════════════════════════════╗";
					wcout << L"\n\t\t\t\t║" << right << setw(10) << L">>  " << left << setw(34) << menu[i] << right << setw(0) << L'║';
					wcout << L"\n\t\t\t\t╚════════════════════════════════════════════╝";

				}
				else {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					wcout << L"\n\t\t\t\t╔════════════════════════════════════════════╗";
					wcout << L"\n\t\t\t\t║" << right << setw(10) << L"  " << left << setw(34) << menu[i] << right << setw(0) << L'║';
					wcout << L"\n\t\t\t\t╚════════════════════════════════════════════╝";

				}
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}

			int x;
			bool thoat = false;



			if (_kbhit) {
				x = m->diChuyenPhim();
				switch (x)
				{
				case 1:
				case 3: {
					pointer += 1;
					if (pointer == 5)
						pointer = 0;
					thoat = true;
					break; }
				case 2:
				case 4: {
					pointer -= 1;
					if (pointer == -1)
						pointer = 4;
					thoat = true;
					break; }
				case 5: {

					switch (pointer)
					{
					case 4:
						return;
					default:
					{
						vector<wstring> menuLuu;
						switch (pointer)
						{
							/*case 3:
								menuLuu = { L"Nhập hệ số lương",L"Trở về" };
								break;*/
						default:
							menuLuu = { L"Nhập từ khóa",L"Trở về" };
							break;
						}

						int viTriLuu = 0;
						bool troVe = false, daTim = false, daXoaDanhSach = false;
						Stack *tam = new Stack();
						Menu *m = new Menu();
						while (true)
						{
							system("cls");
							if (this->danhSachNhanVien->isEmpty() == true) {
								this->hienThi();
								choNhap();
								break;
							}
							if ((tam->isEmpty() == true && daTim == false) || daXoaDanhSach == true) {
								daXoaDanhSach = false;
								wcout << this->danhSachNhanVien->toStringSearch();
							}
							else if (tam->isEmpty() == false && daTim == true)
								wcout << tam->toStringSearch();
							else if (tam->isEmpty() == true && daTim == true)
								wcout << L"\n\t\t\t\tKHÔNG TÌM THẤY DỮ LIỆU LIÊN QUAN ĐẾN TỪ KHÓA";


							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							if (xoa == 0 && tam->isEmpty() == false) {
								wcout << L"\n\n\t\t\t\tBẠN CÓ CHẮC CHẮN MUỐN XÓA TOÀN BỘ NHÂN VIÊN ĐÃ TÌM THẤY Ở TRÊN?\n\n";
								menuLuu = { L"CÓ",L"KHÔNG" };
							}
							else
								wcout << L"\n\n\t\t\t\t      Tìm tất cả nhân viên liên quan đến từ khóa\n\n";



							for (int i = 0; i < menuLuu.size(); ++i)
							{
								if (i == 0)
									wcout << "\n\t\t\t\t";
								else
									wcout << "\t\t";
								if (viTriLuu == i)
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 125);
								else
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
								wcout << L"╔═══════════════════╗";
							}
							for (int i = 0; i < menuLuu.size(); ++i)
							{
								if (i == 0)
									wcout << "\n\t\t\t\t";
								else
									wcout << "\t\t";
								if (viTriLuu == i)
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 125);
								else
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
								wcout << L"║" << right << setw(3) << L" " << left << setw(12) << menuLuu[i] << right << setw(5) << L'║';
							}
							for (int i = 0; i < menuLuu.size(); ++i)
							{
								if (i == 0)
									wcout << "\n\t\t\t\t";
								else
									wcout << "\t\t";
								if (viTriLuu == i)
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 125);
								else
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
								wcout << L"╚═══════════════════╝";

							}
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							//for (int i = 0; i < menuLuu.size(); ++i)
							//{
							//	//wcout << L'\t';
							//	if (i == viTriLuu)
							//		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 125);
							//	else
							//		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							//	wcout << L"\n\t\t\t\t╔════════════════════════════╗";
							//	wcout << L"\n\t\t\t\t║" << right << setw(5) << L" " << left << setw(17) << menuLuu[i] << right << setw(7) << L'║';
							//	wcout << L"\n\t\t\t\t╚════════════════════════════╝";
							//	/*	wcout << left << setw(7) << menuLuu[i]<<setw(5);*/
							//	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							//}
							int luu;
							if (_kbhit) {
								luu = m->diChuyenPhim();
								switch (luu) {
								case 1:
								case 3: {
									viTriLuu += 1;
									if (viTriLuu == 2)
										viTriLuu = 0;
									break; }
								case 2:
								case 4: {
									viTriLuu -= 1;
									if (viTriLuu == -1)
										viTriLuu = 1;
									break; }
								case 5: {
									switch (viTriLuu)
									{
									case 1: {
										if (daXoaDanhSach == false)
											troVe = true;
										break;
									}
									default:
										if (xoa == 0 && tam->isEmpty() == false) {
											this->danhSachNhanVien->deleteSearch(tam);
											daXoaDanhSach = true;
											system("cls");
											wcout << L"\n\t\t\t\tXÓA DANH SÁCH ĐÃ TÌM THÀNH CÔNG!";
											//Sleep(2000);
											daTim = false;
										}
										else {
											if (tam->isEmpty() == false)
												tam->~Stack();
											this->danhSachNhanVien->search(tam, this->chucVu, pointer + 1);
											daTim = true;
										}
										break;
									}

									if (daXoaDanhSach == true)
										choNhap();
									switch (pointer)
									{
									case 3:
										menuLuu = { L"Nhập từ khóa",L"Trở về" };
										break;
									default:
										menuLuu = { L"Nhập từ khóa",L"Trở về" };
										break;
									}
									//choNhap();
									break; }




								default:
									break;
								}
							}

							if (troVe == true)
								break;

						}



					}


					}

					break;
				}

				default:
					break;
				}

			}


		}
	}
	else {
		wcout << L"\n\t\t\tDanh sách nhân viên rỗng, hãy đọc file hoặc thêm mới nhân viên trước!";
		choNhap();

	}
}


void CongTy::themChucVu() {
	system("cls");
	MyLib::Chuoi *chuoi = new MyLib::Chuoi();
	wstring tenCV;
	wcout << L"\n\n\t\t\t* Thêm chức vụ *\n";
	wcout << L"\n\t\t\t----------------------------------------";
	bool daCo;
	while (true)
	{
		daCo = false;
		wcout << L"\n\t\t\tNhập tên chức vụ: ";
		getline(wcin, tenCV);
		if (tenCV.size() > 0) {
			if (chuoi->kiemTraNhapChucVu(tenCV) == true) {
				tenCV = chuoi->boKhoangTrang(chuoi->vietHoaKiTuDau(tenCV));
				for (int i = 0; i < this->chucVu->size(); i++)
					if (chuoi->soSanhChuoi(chucVu->data()[i].c_str(), tenCV.c_str()) == 0) {
						daCo = true;
						break;
					}
				if (daCo == false)
					break;
				else
					wcout << L"\n\t\t\tChức vụ " << tenCV << L" đã tồn tại, vui lòng nhập tên khác!";

			}
		}
		else
			wcout << L"\n\t\t\tTên không được để trống!";
	}
	if (this->chucVu->size() == 0) {
		this->chucVu->insert(chucVu->begin(), tenCV);
		wcout << L"\n\n\t\t\tThêm thành công!";
	}
	else {
		this->chucVu->insert(chucVu->begin(), tenCV);
		this->suaViTriChucVu(0, true);
		wcout << L"\n\t\t\tThêm thành công!";

		//for (int i = 0; i < this->chucVu->size(); i++)
		//	wcout << "\n\t\t\t" << (i + 1) << " : " << this->chucVu->data()[i].c_str();
		//wcout << "\n\t\t\t" << this->chucVu->size() + 1 << " : ";
		//wstring cv;
		//int soNguyen;
		//while (true) {
		//	wcout << L"\n\t\t\t=> Vui lòng nhập số tương ứng: ";
		//	wcin >> cv;
		//	//if (chuoi->kiemTraNhapSoNguyen(cv) == true)
		//	soNguyen = chuoi->chuyenStringSangSoNguyen(cv);
		//	if (soNguyen >= 1 && soNguyen <= chucVu->size() + 1) {
		//		this->chucVu->insert(chucVu->begin() + (soNguyen - 1), tenCV);
		//		wcout << L"\n\t\t\tThêm thành công!";
		//		break;
		//	}
		//	wcout << L"\n\t\t\tVui lòng nhập số theo yêu cầu!";
		//}
	}
	choNhap();

}

void CongTy::xoaChucVu() {
	system("cls");
	if (this->chucVu->size() > 0) {

		MyLib::Chuoi *chuoi = new MyLib::Chuoi();

		int viTriChon = 0;
		Menu *m = new Menu();
		vector<wstring> menu;
		for (int i = 0; i < this->chucVu->size(); i++)
			menu.push_back(this->chucVu->data()[i]);
		menu.push_back(L"Trở về");
		bool troVe = false;
		while (true)
		{

			system("cls");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			wcout << L"\n\n\t\t\tChọn chức vụ bạn muốn xóa\n\n";

			for (int i = 0; i < menu.size(); ++i)
			{
				if (viTriChon == i) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 125);
					wcout << L"\n\t\t\t\t" << right << setw(5) << L"=> " << left << setw(25) << menu.data()[i];
				}
				else {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					wcout << L"\n\t\t\t\t" << right << setw(5) << L"   " << left << setw(25) << menu.data()[i];
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
					if (viTriChon == menu.size())
						viTriChon = 0;
					break; }
				case 2:
				case 4: {
					viTriChon -= 1;
					if (viTriChon == -1)
						viTriChon = menu.size() - 1;
					break; }
				case 5:
				{
					if (viTriChon == menu.size() - 1) {
						troVe = true;
						break;
					}
					system("cls");
					if (this->danhSachNhanVien->CheckExitChucVu(chucVu->data()[viTriChon]) == true) {
						this->chucVu->erase(this->chucVu->begin() + viTriChon, this->chucVu->begin() + viTriChon + 1);
						menu.erase(menu.begin() + viTriChon, menu.begin() + viTriChon + 1);
						wcout << L"\n\t\t\t Xóa chức vụ thành công!";
					}
					else
						wcout << L"\n\t\t\t Chức vụ đã được sử dụng, không thể xóa!";
					choNhap();
					break;
				}


				default:
					break;
				}
			}

			if (troVe == true) {
				menu.clear();
				break;
			}
		}
	}
	else {
		wcout << L"\n\n\t\t\tVui lòng đọc file hoặc thêm chức vụ trước! ";
		choNhap();
	}
}

void CongTy::suaChucVu() {


	system("cls");
	if (this->chucVu->size() > 0) {

		MyLib::Chuoi *chuoi = new MyLib::Chuoi();

		int viTriChon = 0, viTriChucVuChon = -1;
		Menu *m = new Menu();
		vector<wstring> menu;
		int chonSua = -1;
		bool daChonCV = false, troVe = false;

		while (true)
		{

			system("cls");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			if (daChonCV == false && viTriChucVuChon == -1)
			{
				wcout << L"\n\t\t\t\tChọn chức vụ muốn sửa?\n\n";
				if (menu.size() > 0)
					menu.clear();
				for (int i = 0; i < this->chucVu->size(); i++)
					menu.push_back(this->chucVu->data()[i]);
				menu.push_back(L"Trở về");

			}
			else {
				wcout << L"\n\t\t\t\tBạn muốn sửa chức vụ " << this->chucVu->data()[viTriChucVuChon] << "?\n\n";
				menu = { L"Sửa tên",L"Sửa vị trí",L"Trở về" };
			}
			for (int i = 0; i < menu.size(); ++i)
			{
				if (viTriChon == i) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 125);
					wcout << L"\n\t\t\t\t" << right << setw(5) << L"=> " << left << setw(25) << menu.data()[i];
				}
				else {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					wcout << L"\n\t\t\t\t" << right << setw(5) << L"   " << left << setw(25) << menu.data()[i];
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
					if (viTriChon == menu.size())
						viTriChon = 0;
					break; }
				case 2:
				case 4: {
					viTriChon -= 1;
					if (viTriChon == -1)
						viTriChon = menu.size() - 1;
					break; }
				case 5:

					if (viTriChon == menu.size() - 1) {
						troVe = true;
						break;
					}
					if (viTriChon != menu.size() - 1 && daChonCV == false) {
						viTriChucVuChon = viTriChon;
						viTriChon = 0;
						daChonCV = true;
					}
					else
						switch (viTriChon)
						{
						case 0:
						{
							system("cls");
							bool daCo;
							wstring tenCV;
							wcout << L"\n\t\t\tTên ban đầu: " << chucVu->data()[viTriChucVuChon];
							while (true)
							{
								daCo = false;
								wcout << L"\n\t\t\tNhập tên mới: ";
								getline(wcin, tenCV);
								if (tenCV.size() > 0) {
									if (chuoi->kiemTraNhapChucVu(tenCV) == true) {
										tenCV = chuoi->vietHoaKiTuDau(tenCV);
										for (int i = 0; i < this->chucVu->size(); i++)
											if (chuoi->soSanhChuoi(chucVu->data()[i].c_str(), tenCV.c_str()) == 0 && i != viTriChucVuChon) {
												daCo = true;
												break;
											}
										if (daCo == false) {
											if (this->danhSachNhanVien->CheckExitChucVu(chucVu->data()[viTriChucVuChon]) == false)
												this->danhSachNhanVien->editDataChucVu(chucVu->data()[viTriChucVuChon], tenCV);
											this->chucVu->data()[viTriChucVuChon] = tenCV;
											menu.data()[viTriChucVuChon] = tenCV;

											wcout << L"\n\t\t\tSửa tên thành công!";
											daChonCV = false;
											viTriChucVuChon = -1;
											choNhap();
											break;
										}
										else
											wcout << L"\n\t\t\tChức vụ " << tenCV << L" đã tồn tại, vui lòng nhập tên khác!";
									}
								}
								else
									wcout << L"\n\t\t\tTên không được để trống!";
							}
						}
						break;
						case 1:
							this->suaViTriChucVu(viTriChucVuChon, false);
							daChonCV = false;
							viTriChucVuChon = -1;
							break;
						default:
							break;
						}


				default:
					break;
				}
			}


			if (troVe == true)
				break;
		}
	}
	else {
		wcout << L"\n\n\t\t\tVui lòng đọc file hoặc thêm chức vụ trước! ";
		choNhap();
	}

}


void CongTy::suaViTriChucVu(int viTri, bool them) {


	if (this->chucVu->size() > 0) {
		system("cls");
		int viTriChon = viTri;
		Menu *m = new Menu();
		vector<wstring> menu;
		vector<wstring> menuLuuSua;
		for (int i = 0; i < this->chucVu->size(); i++)
			menu.push_back(this->chucVu->data()[i]);
		bool daChonVT = false, troVe = false;

		while (true)
		{

			system("cls");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			if (daChonVT == false)
				wcout << L"\n\t\t\t\tDi chuyển đến vị trí bạn muốn, cấp giảm dần từ trên xuống\n\n";
			else {
				if (them == true) {
					wcout << L"\n\t\t\t\tBạn có chắc chắn muốn chọn vị trí này?\n\n";
					menu = { L"Có",L"Không" };
				}
				else {
					wcout << L"\n\t\t\t\tBạn có chắc chắn muốn thay đổi vị trí?\n\n";
					menu = { L"Có",L"Không",L"Trở về" };
				}
			}


			for (int i = 0; i < menu.size(); ++i)
			{
				if (viTriChon == i) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 125);
					wcout << L"\n\t\t\t\t" << right << setw(5) << L"=> " << left << setw(25) << menu.data()[i];
				}
				else {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					wcout << L"\n\t\t\t\t" << right << setw(5) << L"   " << left << setw(25) << menu.data()[i];
				}
			}

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

			int diChuyenPhim;
			if (_kbhit) {
				diChuyenPhim = m->diChuyenPhim();
				switch (diChuyenPhim) {
				case 1:
				case 3: {
					if (daChonVT == false)
						if (viTriChon == menu.size() - 1) {
							wstring t;
							for (int i = menu.size() - 1; i > 0; i--)
							{
								t = menu.data()[i];
								menu.data()[i] = menu.data()[i - 1];
								menu.data()[i - 1] = t;
							}
						}
						else {
							wstring t = menu.data()[viTriChon];
							menu.data()[viTriChon] = menu.data()[viTriChon + 1];
							menu.data()[viTriChon + 1] = t;
						}
					viTriChon += 1;
					if (viTriChon == menu.size())
						viTriChon = 0;

					break; }
				case 2:
				case 4: {
					if (daChonVT == false)
						if (viTriChon == 0) {
							wstring t;
							for (int i = 0; i < menu.size() - 1; i++)
							{
								t = menu.data()[i];
								menu.data()[i] = menu.data()[i + 1];
								menu.data()[i + 1] = t;
							}

						}
						else {
							wstring t = menu.data()[viTriChon];
							menu.data()[viTriChon] = menu.data()[viTriChon - 1];
							menu.data()[viTriChon - 1] = t;
						}

					viTriChon -= 1;
					if (viTriChon == -1)
						viTriChon = menu.size() - 1;
					break; }
				case 5: {
					if (daChonVT == false) {
						daChonVT = true;
						viTriChon = 0;
						menuLuuSua = menu;
						break;
					}
					switch (viTriChon)
					{
					case 0:
						*this->chucVu = menuLuuSua;
						menuLuuSua.clear();
						troVe = true;
						break;
					case 1:
						daChonVT = false;
						viTriChon = viTri;
						menu.clear();
						for (int i = 0; i < this->chucVu->size(); i++)
							menu.push_back(this->chucVu->data()[i]);
						break;
					default:

						troVe = true;
						break;
					}

				}
				default:
					break;
				}
			}

			if (troVe == true)
				break;
		}
	}
	else {
		wcout << L"\n\n\t\t\tVui lòng đọc file hoặc thêm chức vụ trước! ";
		choNhap();
	}


}

void CongTy::quanLyChucVu() {

	system("cls");
	MyLib::Chuoi *chuoi = new MyLib::Chuoi();
	Menu *menu = new Menu();
	vector<wstring> menuChon = { L"Xem danh sách",L"Thêm chức vụ",L"Xóa chức vụ",L"Sửa chức vụ",L"Trở về" };
	int viTriChon = 0;
	bool troVe = false;
	while (true)
	{
		system("cls");

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		wcout << L"\n\n\t\t\t\tChọn thao tác?\n\n";
		for (int i = 0; i < menuChon.size(); ++i)
		{
			if (i == viTriChon)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 125);
			else
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

			wcout << L"\n\t\t\t\t╔════════════════════════════╗";
			wcout << L"\n\t\t\t\t║" << right << setw(5) << L" " << left << setw(17) << menuChon[i] << right << setw(7) << L'║';
			wcout << L"\n\t\t\t\t╚════════════════════════════╝";

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

		}

		int nhanPhim;
		if (_kbhit) {
			nhanPhim = menu->diChuyenPhim();
			switch (nhanPhim) {
			case 1:
			case 3: {
				viTriChon += 1;
				if (viTriChon == menuChon.size())
					viTriChon = 0;
				break; }
			case 2:
			case 4: {
				viTriChon -= 1;
				if (viTriChon == -1)
					viTriChon = menuChon.size() - 1;
				break; }
			case 5: {
				switch (viTriChon)
				{
				case 0:
					system("cls");
					if (this->chucVu->size() > 0) {
						wcout << L"\n\n\t\t\tDanh sách chức vụ\n\n";
						for (int i = 0; i < this->chucVu->size(); i++)
							wcout << "\n\t\t\t" << i + 1 << L" - " << this->chucVu->data()[i];
					}
					else
						wcout << L"\n\n\t\t\tDanh sách chức vụ rỗng!\n\n";
					choNhap();
					break;
				case 1:
					this->themChucVu();
					break;
				case 2:
					this->xoaChucVu();
					break;
				case 3:
					this->suaChucVu();
					break;
				case 4:
					troVe = true;
					break;

				}
				break; }
			default:
				break;
			}
		}

		if (troVe == true)
			break;

	}

}


void CongTy::menuChucNang(const char* path, const char* pathXuat)
{
	vector<wstring> menu = { L"ĐỌC DỮ LIỆU TỪ FILE", L"XEM DANH SÁCH NHÂN VIÊN", L"SẮP XẾP NHÂN VIÊN",L"THÊM NHÂN VIÊN",L"XÓA NHÂN VIÊN",L"TÌM KIẾM",L"XUẤT FILE",L"LƯU FILE",L"QUẢN LÝ CHỨC VỤ",L"THOÁT CHƯƠNG TRÌNH" };
	int pointer = 0;

	Menu *m = new Menu();

	while (true)
	{
		fflush(stdin);
		system("cls");

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		wcout << L"\n\t\t\t       ╔══════════════════════════════════════════════╗";
		wcout << L"\n\t\t\t       ║ >>>>>>>  HỆ THỐNG QUẢN LÝ NHÂN VIÊN  <<<<<<< ║";
		wcout << L"\n\t\t\t       ╚══════════════════════════════════════════════╝";
		for (int i = 0; i < menu.size(); ++i)
		{
			if (i == pointer)
			{

				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 125);
				wcout << L"\n\t\t\t\t╔════════════════════════════════════════════╗";
				wcout << L"\n\t\t\t\t║" << right << setw(10) << L">>  " << left << setw(34) << menu[i] << right << setw(0) << L'║';
				wcout << L"\n\t\t\t\t╚════════════════════════════════════════════╝";
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				wcout << L"\n\t\t\t\t╔════════════════════════════════════════════╗";
				wcout << L"\n\t\t\t\t║" << right << setw(10) << L"    " << left << setw(34) << menu[i] << right << setw(0) << L'║';
				wcout << L"\n\t\t\t\t╚════════════════════════════════════════════╝";
			}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

		}

		int x;
		bool thoat = false;


		if (_kbhit) {
			x = m->diChuyenPhim();
			switch (x)
			{
			case 1:
			case 3: {
				pointer += 1;
				if (pointer == menu.size())
					pointer = 0;
				thoat = true;
				break; }
			case 2:
			case 4: {
				pointer -= 1;
				if (pointer == -1)
					pointer = menu.size() - 1;
				thoat = true;
				break; }
			case 5: {
				switch (pointer) {
				case 0: {
					system("CLS");
					this->docFile(path);
					break; }
				case 1: {
					system("CLS");
					this->hienThi();
					choNhap();
					break; }
				case 2:
					this->sapXep();
					break;
				case 3: {
					system("CLS");
					this->themNhanVien();
					break;
				}
				case 4:
					this->xoaNhanVien();
					break;
				case 5:
					this->timKiem(1);//0 là xóa,1 là tìm kiếm
					break;
				case 6:
					this->xuatFile(pathXuat);
					break;
				case 7:
					system("CLS");
					this->luuFile(path);
					if (this->danhSachNhanVien->isEmpty() == false) {
						this->hienThi();
						choNhap();
					}
					break;
				case 8:
					this->quanLyChucVu();
					break;
				case 9:
					if (this->danhSachNhanVien->isEmpty() == false) {

						vector<wstring> menuLuu = { L"CÓ", L"KHÔNG" };
						int viTriLuu = 0;
						Menu *m = new Menu();
						while (true)
						{

							system("cls");
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							wcout << L"\n\t\t\t\t    BẠN CÓ MUỐN LƯU DANH SÁCH HIỆN TẠI KHÔNG?\n\n";

							for (int i = 0; i < menuLuu.size(); ++i)
							{
								if (i == 0)
									wcout << "\n\t\t\t\t";
								else
									wcout << "\t\t";
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
									wcout << "\t\t";
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
									wcout << "\t\t";
								if (viTriLuu == i)
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 125);
								else
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
								wcout << L"╚═══════════════╝";

							}
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

							int luu;
							if (_kbhit) {
								luu = m->diChuyenPhim();
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
										viTriLuu = menuLuu.size() - 1;
									break; }
								case 5:
									switch (viTriLuu) {
									case 0: {
										system("CLS");
										this->luuFile(path);
										return; }
									case 1:
										wcout << endl;
										return;
									}


								default:
									break;
								}

							}

						}



					}
					wcout << endl;
					return;

				default:
					break;
				}
				thoat = true;
				break;
			}

			default:
				break;
			}

		}

	}


}