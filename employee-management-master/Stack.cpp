#pragma once
#include "Stack.h"

Stack::Stack()
{
	this->top = NULL;
}

Stack::~Stack()
{

	Node *p;
	while (top != NULL) {
		p = top;
		top = top->link;
		delete p;

	}
	top = NULL;
}

void Stack::push(NhanVien nv)
{
	Node * p = new Node();
	p->data = nv;
	p->link = this->top;
	this->top = p;
}

NhanVien Stack::pop()
{
	Node *p = this->top;
	NhanVien *nv = &p->data;
	this->top = this->top->link;
	delete p;
	return *nv;
}

NhanVien Stack::peek()
{
	return this->top->data;
}

bool Stack::isEmpty()
{
	return this->top == NULL;
}

wstring Stack::toSaveFile()
{
	Stack *temp = new Stack();
	wstringstream  os;// string stream cung cấp một buffer để chứa dữ liệu. 
					// Tuy nhiên, string stream không kết nối đến các Input/Output channel (như keyboard, monitor, file,…).
	Node*p = this->top;

	while (p != NULL) {
		temp->push(p->data);
		p = p->link;
	}

	p = temp->top;
	while (p != NULL) {
		os << p->data.toLuuFile();
		p = p->link;
	}
	return os.str(); // returns a string object with a copy of the current contents of the stream.
}

wstring Stack::toString()
{
	Stack *temp = new Stack();
	Node*p = this->top;

	while (p != NULL) {
		temp->push(p->data);
		p = p->link;
	}
	wstringstream os;
	if (this->isEmpty() == false)
	{
		os << L"\n\t\t\t\t\t      ** DANH SÁCH NHÂN VIÊN **"
			<< L"\n\t┌────────────────────────┬────────────────────────┬────────────────────────┬────────────────────────┐"
			<< L"\n\t│" << setw(20) << L"Họ và tên   " << setw(5) << L"│" << setw(20) << L"Chức vụ  " << setw(5) << L"│" << setw(20) << L"Ngày sinh  " << setw(5) << L"│" << setw(20) << L"Hệ số lương  " << setw(5) << L"│"
			<< L"\n\t├────────────────────────┼────────────────────────┼────────────────────────┼────────────────────────┤";
		p = temp->top;
		while (p != NULL) {

			os << p->data.toString();
			if (p->link != NULL)
				os << L"\n\t├────────────────────────┼────────────────────────┼────────────────────────┼────────────────────────┤";
			p = p->link;
		}
		os << L"\n\t└────────────────────────┴────────────────────────┴────────────────────────┴────────────────────────┘";

	}
	return os.str();

}


wstring Stack::toStringSearch()
{
	Stack *temp = new Stack();
	Node*p = this->top;

	while (p != NULL) {
		temp->push(p->data);
		p = p->link;
	}
	wstringstream os;
	if (this->isEmpty() == false)
	{
		os << L"\n\t\t\t\t\t      ** DANH SÁCH NHÂN VIÊN **"
			<< L"\n\t┌─────────┬────────────────────────┬────────────────────────┬────────────────────────┬────────────────────────┐"
			<< L"\n\t│" << setw(8) << L"STT  " << setw(2) << L"│" << setw(20) << L"Họ và tên   " << setw(5) << L"│" << setw(20) << L"Chức vụ  " << setw(5) << L"│" << setw(20) << L"Ngày sinh  " << setw(5) << L"│" << setw(20) << L"Hệ số lương  " << setw(5) << L"│"
			<< L"\n\t├─────────┼────────────────────────┼────────────────────────┼────────────────────────┼────────────────────────┤";
		p = temp->top;
		int viTri = 1;
		while (p != NULL) {
			if (p->data.getViTri() == 0)
				p->data.setViTri(viTri);
			os << p->data.toStringSearch();
			p = p->link;
			viTri++;
		}
		os << L"\n\t└─────────┴────────────────────────┴────────────────────────┴────────────────────────┴────────────────────────┘";

	}
	return os.str();

}

int Stack::size() {
	if (this->isEmpty() == true)return 0;
	Node*p = new Node();
	p = this->top;
	int count = 0;
	while (p != NULL) {
		p = p->link;
		count++;
	}
	return count;
}
void Stack::sort(vector<wstring> *chucVu, int index, int direction)
{
	Stack *temp = new Stack();
	MyLib::Chuoi *string = new MyLib::Chuoi;
	vector<wstring> *arr1;
	vector<wstring> *arr2;
	Node*p = new Node(), *q = new Node();
	NhanVien *t = new NhanVien();
	p = this->top;
	int hoanDoi = 0;
	while (p->link != NULL) {
		q = p->link;
		while (q != NULL) {
			hoanDoi = 0;
			switch (index)
			{
			case 1:
			{
				NhanVien x;
				int ss;
				ss = x.soSanhTen(q->data.getHoTen(), p->data.getHoTen());
				if ((ss < 0 && direction == 2) || (ss > 0 && direction == 1))
					hoanDoi++;
			}
			break;
			case 2:
			{
				int cv1 = -1, cv2 = -1;
				for (int i = 0; i < chucVu->size(); i++) {
					if (cv1 != -1 && cv2 != -1)break;
					if (q->data.getChucVu() == chucVu->data()[i])
						cv1 = i;
					if (p->data.getChucVu() == chucVu->data()[i])
						cv2 = i;
				}
				if (direction == 1 && cv1 < cv2)
					hoanDoi++;
				else if (direction == 2 && cv1 > cv2)
					hoanDoi++;

			}
			break;
			case 3:
			{
				Ngay x;
				int ss;
				ss = x.soSanh(q->data.getNgaySinh(), p->data.getNgaySinh());
				if ((ss < 0 && direction == 2) || (ss > 0 && direction == 1))
					hoanDoi++;
			}
			break;
			case 4:
			{
				if ((direction == 2 && q->data.getHeSoLuong() < p->data.getHeSoLuong())
					|| (direction == 1 && q->data.getHeSoLuong() > p->data.getHeSoLuong()))
					hoanDoi++;
				break;
			}

			default:
				break;
			}


			if (hoanDoi == 1) {
				*t = q->data;
				q->data = p->data;
				p->data = *t;
			}

			q = q->link;
		}
		p = p->link;
	}


}

void  Stack::search(Stack *temp, vector<wstring>* chucVu, int index)
{
	system("cls");
	wstring tuKhoa = L"";
	Ngay *ngayTim = new Ngay();
	MyLib::Chuoi *chuoi = new MyLib::Chuoi();
	float hsl = 0;
	int moc = -1;
	switch (index)
	{
	case 1:
	{
		wstring kiTu = L" \t\n";

		///wcin.ignore();
		while (true) {
			wcout << L"\n\t\t\tNhập từ khóa: ";
			getline(wcin, tuKhoa);
			if (tuKhoa.size() > 0)
				if (chuoi->kiemTrachuaChuoi(tuKhoa.c_str(), kiTu.c_str()) < tuKhoa.size())
					if (chuoi->boKhoangTrang(tuKhoa).size() > 0) {
						tuKhoa = chuoi->boKhoangTrang(tuKhoa);
						break;
					}
			wcout << L"\n\t\t\tTừ khóa trống, vui lòng kiểm tra lại!";
		}
	}
	break;
	case 2: {


		Menu *m = new Menu();
		int viTriChon = 0;
		bool thoat = false;
		while (true)
		{
			system("cls");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			wcout << L"\n\t\t\tChọn chức vụ( nhấn enter ở chức vụ bạn chọn?)\n";
			for (int i = 0; i < chucVu->size(); ++i)
			{
				if (viTriChon == i) {
					int color_code = 0 * 16 + 6;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_code);
					wcout << L"\n\t\t\t"<< right << setw(5) << L"=> " << left << setw(25) << chucVu->data()[i];
				}
				else {
					int color_code = 0 * 16 + 6;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_code);
					wcout << L"\n\t\t\t" << right << setw(5) << L"   " << left << setw(25) << chucVu->data()[i];
				}
			}
			//int color_code = 0 * 16 + 12;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

			int diChuyenPhim;
			if (_kbhit) { // Checks the console for keyboard input.
				diChuyenPhim = m->diChuyenPhim();
				switch (diChuyenPhim) {
				case 1:
				case 3: {
					viTriChon += 1;
					if (viTriChon == chucVu->size())
						viTriChon = 0;
					break; }
				case 2:
				case 4: {
					viTriChon -= 1;
					if (viTriChon == -1)
						viTriChon = chucVu->size() - 1;
					break; }
				case 5:
					if (viTriChon >= 0 && viTriChon <= chucVu->size()) {
						tuKhoa = chucVu->data()[viTriChon];
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

		//for (int i = 0; i < chucVu->size(); i++)
		//	wcout << "\n\t\t\t" << (i + 1) << " : " << chucVu->data()[i].c_str();
		//wcout << L"\n\n\t\t\t=> Vui lòng nhập số tương  ứng: ";
		//int soNguyen;
		//wstring cv;
		//while (true) {
		//	wcin >> cv;
		//	soNguyen = chuoi->chuyenStringSangSoNguyen(cv);
		//	if (soNguyen >= 1 && soNguyen <= chucVu->size()) {
		//		tuKhoa = chucVu->data()[soNguyen - 1];
		//		break;
		//	}
		//	wcout << L"\n\t\t\tVui lòng nhập số theo yêu cầu!";
		//}
	}
			break;
	case 3: {
		int ng = 0, t = 0, n = 0;
		fflush(stdin);
		wcout << L"\n\t\tNhập 0 nếu không muốn nhập mục đó\n";
		wstring ngay, thang, nam;
		while (true) {
			wcout << L"\n\t\t\tNhập ngày: ";
			getline(wcin, ngay);
			//wcin >> ngay;
			wcout << L"\t\t\tNhập tháng: ";
			getline(wcin, thang);
			//wcin >> thang;
			wcout << L"\t\t\tNhập năm: ";
			//wcin >> nam;
			getline(wcin, nam);
			if (chuoi->kiemTraNhapSoNguyen(ngay) == true && chuoi->kiemTraNhapSoNguyen(thang) == true && chuoi->kiemTraNhapSoNguyen(nam) == true) {
				if (ngay != L"0" || thang != L"0" || nam != L"0") {
					ngayTim = new Ngay(chuoi->chuyenStringSangSoNguyen(ngay), chuoi->chuyenStringSangSoNguyen(thang), chuoi->chuyenStringSangSoNguyen(nam));
					break;
				}
				else
					wcout << L"\n\t\t\tVui vòng nhập ít nhất một mục!";
			}
			else
				wcout << L"\n\t\t\tDữ liệu không hợp lệ, vui lòng thử lại!";
		}

		/*	while (true) {
				wcout << L"\n\t\t\tNhập ngày: ";
				wcin >> ng;
				wcout << L"\t\t\tNhập tháng: ";
				wcin >> t;
				wcout << L"\t\t\tNhập năm: ";
				wcin >> n;
				if (ng != 0 || t != 0 || n != 0) {
					ngayTim = new Ngay(ng, t, n);
					break;
				}
				else
					wcout << L"\n\t\t\tVui vòng nhập ít nhất một mục!";
			}*/


	}
			break;
	case 4:
	{

		wstring mocS, hslS;
		Menu *m = new Menu();
		vector<wstring> chon = { L"Lớn hơn mốc(vd > 5)",L"Bằng mốc(vd = 5)",L"Nhỏ hơn mốc(vd < 5)" };
		int viTriChon = 0;
		bool thoat = false;
		while (true)
		{

			system("cls");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			wcout << L"\n\t\t\t\tVui lòng chọn mốc giới hạn tìm kiếm\n\n";
			for (int i = 0; i < chon.size(); ++i)
			{
				if (viTriChon == i) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 125);
					wcout << L"\n\t\t\t\t" << right << setw(5) << L"=> " << left << setw(25) << chon.data()[i];
				}
				else {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					wcout << L"\n\t\t\t\t" << right << setw(5) << L"   " << left << setw(25) << chon.data()[i];
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
					if (viTriChon == chon.size())
						viTriChon = 0;
					break; }
				case 2:
				case 4: {
					viTriChon -= 1;
					if (viTriChon == -1)
						viTriChon = chon.size() - 1;
					break; }
				case 5:
					while (true) {
						wcout << L"\n\n\t\t\t=> Nhập hệ số lương: ";
						getline(wcin, hslS);
						hsl = chuoi->chuyenStringSangSoThuc(hslS);
						if (hsl > 0 && hsl <= 10) {
							moc = viTriChon;
							thoat = true;
							break;
						}
						else
							wcout << L"\n\t\t\tDữ liệu không hợp lệ, vui lòng thử lại!";
					}
					break;

				default:
					break;
				}
			}

			if (thoat == true)
				break;

		}




		/*for (int i = 0; i < chon.size(); i++)
			wcout << "\n\t\t\t" << (i + 1) << " : " << chon.data()[i].c_str();*/
			/*while (true) {
				wcout << L"\n\n\t\t\t=> Vui lòng nhập số tương  ứng: ";
				wcin >> mocS;
				moc = chuoi->chuyenStringSangSoNguyen(mocS);
				if (moc >= 1 && moc <= chon.size()) {
					while (true) {
						wcout << L"\n\n\t\t\t=> Nhập hệ số lương: ";
						wcin >> hslS;
						hsl = chuoi->chuyenStringSangSoNguyen(hslS);
						if (hsl > 0 && hsl <= 10)
							break;
					}
					break;
				}
			}*/



	}
	break;
	default:
		break;
	}

	Stack *daoNguoc = new Stack();
	Node*p = this->top;
	while (p != NULL) {
		daoNguoc->push(p->data);
		p = p->link;
	}


	p = daoNguoc->top;
	bool them;
	int viTri = 1;
	while (p != NULL) {

		them = false;

		switch (index)
		{
		case 1:
		{

			if (chuoi->timKiemChuoiCon(p->data.getHoTen(), tuKhoa) != -1)
				them = true;
		}
		break;
		case 2: {
			if (p->data.getChucVu() == tuKhoa)
				them = true;
		}
		break;
		case 3: {
			Ngay x;
			if (x.timNgay(ngayTim, p->data.getNgaySinh()) == true)
				them = true;
		}
				break;
		case 4:

			switch (moc)
			{
			case 0:
				if (p->data.getHeSoLuong() > hsl)
					them = true;
				break;
			case 1:
				if (p->data.getHeSoLuong() == hsl)
					them = true;
				break;
			case 2:
				if (p->data.getHeSoLuong() < hsl)
					them = true;
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}


		if (them == true) {
			p->data.setViTri(viTri);
			temp->push(p->data);
		}

		p = p->link;
		viTri++;
	}

}

void Stack::deleteNode(Stack *a, int vt)
{

	if (a->top == NULL)
		return;

	struct Node* temp = a->top;


	//if (temp->data.getMa() == id)
	if (vt == a->size())
	{
		a->top = temp->link;
		free(temp);
		return;
	}
	//for (int i = 0; temp != NULL && temp->link->data.getMa() != id; i++)
	for (int i = a->size(); temp != NULL && i - 1 != vt; i--)
		temp = temp->link;

	if (temp == NULL || temp->link == NULL)
		return;

	struct Node *next = temp->link->link;

	free(temp->link);

	temp->link = next;
}



void Stack::insertNode(NhanVien nv, vector<wstring>* chucVu, int index, int direction)
{

	if (this->isEmpty() == true || (index == 0 && direction == 0)) {
		this->push(nv);
		return;
	}


	struct Node* p = this->top;
	bool ngung = false;
	switch (index)
	{
	case 1:
	{

		int ss;
		ss = nv.soSanhTen(nv.getHoTen(), p->data.getHoTen());
		if ((ss < 0 && direction == 2) || (ss > 0 && direction == 1))
			ngung = true;
	}
	break;
	case 2:
	{
		int cv1 = -1, cv2 = -1;
		for (int i = 0; i < chucVu->size(); i++) {
			if (cv1 != -1 && cv2 != -1)break;
			if (nv.getChucVu() == chucVu->data()[i])
				cv1 = i;
			if (p->data.getChucVu() == chucVu->data()[i])
				cv2 = i;
		}
		if ((direction == 1 && cv1 < cv2) || (direction == 2 && cv1 > cv2))
			ngung = true;

	}
	break;
	case 3:
	{
		Ngay x;
		int ss;
		ss = x.soSanh(nv.getNgaySinh(), p->data.getNgaySinh());
		if ((ss < 0 && direction == 2) || (ss > 0 && direction == 1))
			ngung = true;
	}
	break;
	case 4:
	{
		if ((direction == 2 && nv.getHeSoLuong() < p->data.getHeSoLuong())
			|| (direction == 1 && nv.getHeSoLuong() > p->data.getHeSoLuong()))
			ngung = true;
		break;
	}

	default:
		break;
	}
	if (ngung == true) {
		this->push(nv);
		return;
	}

	ngung = false;
	while (p->link != NULL) {
		switch (index)
		{
		case 1:
		{

			int ss;
			ss = nv.soSanhTen(nv.getHoTen(), p->link->data.getHoTen());
			if ((ss < 0 && direction == 2) || (ss > 0 && direction == 1))
				ngung = true;
		}
		break;
		case 2:
		{
			int cv1 = -1, cv2 = -1;
			for (int i = 0; i < chucVu->size(); i++) {
				if (cv1 != -1 && cv2 != -1)break;
				if (nv.getChucVu() == chucVu->data()[i])
					cv1 = i;
				if (p->link->data.getChucVu() == chucVu->data()[i])
					cv2 = i;
			}
			if ((direction == 1 && cv1 < cv2) || (direction == 2 && cv1 > cv2))
				ngung = true;

		}
		break;
		case 3:
		{
			Ngay x;
			int ss;
			ss = x.soSanh(nv.getNgaySinh(), p->link->data.getNgaySinh());
			if ((ss < 0 && direction == 2) || (ss > 0 && direction == 1))
				ngung = true;
		}
		break;
		case 4:
		{
			if ((direction == 2 && nv.getHeSoLuong() < p->link->data.getHeSoLuong())
				|| (direction == 1 && nv.getHeSoLuong() > p->link->data.getHeSoLuong()))
				ngung = true;
			break;
		}

		default:
			break;
		}
		if (ngung == true)
			break;
		p = p->link;
	}



	Node * x = new Node();
	x->data = nv;
	x->link = p->link;
	p->link = x;
}


void Stack::deleteSearch(Stack * temp)
{
	Node* p = temp->top;
	while (p != NULL) {
		this->deleteNode(this, p->data.getViTri());
		//this->deleteNode(this, p->data.getMa());
		p = p->link;
		//p->data.setViTri(p->data.getViTri() - 1);
	}
	temp->~Stack();
}

bool Stack::CheckExitChucVu(wstring chucVu) {
	if (this->isEmpty() == true)
		return true;
	Node*p = this->top;
	while (p != NULL) {
		if (p->data.getChucVu() == chucVu)
			return false;
		p = p->link;
	}
	return true;
}

void Stack::editDataChucVu(wstring chucVuTruoc, wstring chucVuSau) {
	if (this->isEmpty() == true)
		return;
	Node*p = this->top;
	while (p != NULL) {
		if (p->data.getChucVu() == chucVuTruoc)
			p->data.setChucVu(chucVuSau);
		p = p->link;
	}

}


