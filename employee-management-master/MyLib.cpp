#pragma once
#include "MyLib.h"
#include <locale>


wstring  MyLib::Chuoi::vietHoa(wstring s)
{
	wstring a1 = L"aáàảạãăắằẳặẵâấầẩậẫbcdđeéèẻẹẽêếềểệễghiíìỉịĩklmnoóòỏọõôốồổộỗơớờởợỡpqrstuúùủụũưứừửữựvxyýỳỷỹỵwzjf";
	wstring a2 = L"AÁÀẢẠÃĂẮẰẲẶẴÂẤẦẨẬẪBCDĐEÉÈẺẸẼÊẾỀỂỆỄGHIÍÌỈỊĨKLMNOÓÒỎỌÕÔỐỒỔỘỖƠỚỜỞỢỠPQRSTUÚÙỦỤŨƯỨỪỬỮỰVXYÝỲỶỸỴWZJF";

	wstring result;

	//locale loc;
	bool daChuyen;
	for (unsigned int i = 0; i < s.length(); ++i)
	{
		daChuyen = false;
		for (int j = 0; j < a1.length(); j++)
			if (a1.at(j) == s.at(i)) {
				result += a2.at(j);
				daChuyen = true;
				break;
			}
		if (daChuyen == false)
			result += s.at(i);

		//result += toupper(s.at(i), loc);
	}

	return result;
}

wstring  MyLib::Chuoi::vietThuong(wstring s)
{

	wstring a1 = L"aáàảạãăắằẳặẵâấầẩậẫbcdđeéèẻẹẽêếềểệễghiíìỉịĩklmnoóòỏọõôốồổộỗơớờởợỡpqrstuúùủụũưứừửữựvxyýỳỷỹỵwzjf";
	wstring a2 = L"AÁÀẢẠÃĂẮẰẲẶẴÂẤẦẨẬẪBCDĐEÉÈẺẸẼÊẾỀỂỆỄGHIÍÌỈỊĨKLMNOÓÒỎỌÕÔỐỒỔỘỖƠỚỜỞỢỠPQRSTUÚÙỦỤŨƯỨỪỬỮỰVXYÝỲỶỸỴWZJF";

	wstring result;

	locale loc;
	bool daChuyen;
	for (unsigned int i = 0; i < s.length(); ++i)
	{
		daChuyen = false;
		for (int j = 0; j < a1.length(); j++)
			if (a2.at(j) == s.at(i)) {
				result += a1.at(j);
				daChuyen = true;
				break;
			}
		if (daChuyen == false)
			result += s.at(i);

		//result += toupper(s.at(i), loc);
	}

	return result;
}


wstring MyLib::Chuoi::boDau(wstring s) {


	wstring temp, charx;
	for (unsigned int i = 0; i < s.length(); ++i)
	{
		charx = s.at(i);

		if (this->kiemTrachuaChuoi(charx.c_str(), L"aáàảạãăắằẳặẵâấầẩậẫ") > 0)
			temp += 'a';
		else if (this->kiemTrachuaChuoi(charx.c_str(), L"AÁÀẢẠÃĂẮẰẲẶẴÂẤẦẨẬẪ") > 0)
			temp += 'A';
		else if (this->kiemTrachuaChuoi(charx.c_str(), L"dđ") > 0)
			temp += 'd';
		else if (this->kiemTrachuaChuoi(charx.c_str(), L"DĐ") > 0)
			temp += 'D';
		else if (this->kiemTrachuaChuoi(charx.c_str(), L"eéèẻẹẽêếềểệễ") > 0)
			temp += 'e';
		else if (this->kiemTrachuaChuoi(charx.c_str(), L"EÉÈẺẸẼÊẾỀỂỆỄ") > 0)
			temp += 'E';
		else if (this->kiemTrachuaChuoi(charx.c_str(), L"iíìỉịĩ") > 0)
			temp += 'i';
		else if (this->kiemTrachuaChuoi(charx.c_str(), L"IÍÌỈỊĨ") > 0)
			temp += 'I';
		else if (this->kiemTrachuaChuoi(charx.c_str(), L"yýỳỷỹỵ") > 0)
			temp += 'y';
		else if (this->kiemTrachuaChuoi(charx.c_str(), L"YÝỲỶỸỴ") > 0)
			temp += 'Y';
		else if (this->kiemTrachuaChuoi(charx.c_str(), L"oóòỏọõôốồổộỗơớờởợỡ") > 0)
			temp += 'o';
		else if (this->kiemTrachuaChuoi(charx.c_str(), L"OÓÒỎỌÕÔỐỒỔỘỖƠỚỜỞỢỠ") > 0)
			temp += 'O';
		else if (this->kiemTrachuaChuoi(charx.c_str(), L"uúùủụũưứừửữự") > 0)
			temp += 'u';
		else if (this->kiemTrachuaChuoi(charx.c_str(), L"UÚÙỦỤŨƯỨỪỬỮỰ") > 0)
			temp += 'U';
		else
			temp += charx;
	}

	return temp;
}

int MyLib::Chuoi::timKiemChuoiCon(wstring chuoiCha, wstring  chuoiCon)
{
	chuoiCha = this->boKhoangTrang(this->vietHoa(chuoiCha));
	chuoiCon = this->boKhoangTrang(this->vietHoa(chuoiCon));
	int e = 0, viTri = -1, dem = -1;

	for (unsigned int i = 0; i < chuoiCha.length(); ++i)
	{
		if (chuoiCha.at(i) == chuoiCon.at(e)) {
			if (dem != -1 && dem != i - 1)return -1;
			if (e == 0) {
				viTri = i;
				dem = i;
			}
			else
				dem++;
			e++;
			if (e == chuoiCon.size()) {
				if (dem == i)return viTri;
				return -1;
			}
		}
		else
			if (dem > -1 && (chuoiCha.size() - (i + 1)) >= chuoiCon.size()) {
				e = 0;
				viTri = -1;
				dem = -1;
			}
	}
	return -1;

	/*int e = 0, indx = -1;
	for (int i = 0; i < chuoiCha.size(); i++) {
		if (chuoiCha.at(i) == chuoiCon.at(e)) {
			if (e == 0)
				indx = i;
			e++;
			if (e == chuoiCon.size()) {
				return indx;
			}
			else {
				e = 0;
			}
		}
	}
	return -1;*/
}

wstring MyLib::Chuoi::boKhoangTrang(wstring a)
{
	if (a.size() == 0 || this->kiemTrachuaChuoi(a.c_str(), L" \t\n") == a.size())
		return L"";
	int dau = 0, cuoi = 0;
	if ((a.at(dau) != ' ' && a.at(dau) == '\t' && a.at(dau) == '\n') && (a.at(cuoi) != ' ' && a.at(cuoi) == '\t' && a.at(cuoi) == '\n'))
		return a;

	while ((a.at(dau) == ' ' || a.at(dau) == '\t' || a.at(dau) == '\n'))
		dau++;

	for (int i = dau; i < a.size(); i++)
		if (a.at(i) == '\t' || a.at(i) == '\n') {
			a.erase(a.begin() + i, a.begin() + i + 1);
			i--;
		}

	for (int i = dau; i < a.size() - 1; i++)
		if (a.at(i) == ' ' && a.at(i + 1) == ' ') {
			a.erase(a.begin() + i, a.begin() + i + 1);
			i--;
		}
	cuoi = a.size() - 1;
	while (a.at(cuoi) == ' ' || a.at(cuoi) == '\t' || a.at(cuoi) == '\n')
		cuoi--;
	wstring temp = L"";
	for (int i = dau; i <= cuoi; i++)
		temp += a.at(i);
	return temp;
}


int MyLib::Chuoi::soSanhChuoi(const wchar_t * X, const wchar_t * Y)
{

	wstring x = this->boKhoangTrang(this->boDau(this->vietHoa(X)));
	wstring y = this->boKhoangTrang(this->boDau(this->vietHoa(Y)));
	X = x.c_str();
	Y = y.c_str();

	while (*X)
	{
		//Nếu kí tự khác hoặc kí tự thứ 2 kết thúc  của chuỗi chuỗi đã tạo
		if (*X != *Y)
			break;

		// chuYển tới cặp kí tự khác nhau
		X++;
		Y++;
	}

	// trả về ASCII khác sau khi chuYển từ char* sang unsigned char*
	return *(const unsigned char*)X - *(const unsigned char*)Y;
}

int MyLib::Chuoi::kiemTrachuaChuoi(const wchar_t * X, const wchar_t * Y)
{
	const wchar_t * yTam;
	int count = 0;
	while (*X)
	{
		yTam = Y;
		wchar_t x = *X;
		while (*yTam) {
			wchar_t y = *yTam;
			if (x == y) {
				count++;
				break;
			}
			yTam++;
		}

		// chuyển tới cặp kí tự khác nhau
		X++;

	}

	return count;
}

vector<wstring> *MyLib::Chuoi::tach(wstring chuoiCanTach, char kiTuTach, int rep)//rep == 1 thi van tach phan tu rong
{
	vector<wstring> *mangTach = new vector<wstring>();
	if (!mangTach->empty()) mangTach->clear();  //làm rỗng vector
	wstring chuaChuoi = chuoiCanTach;
	wstring tuTach = L"";
	int i = 0;
	while (i < chuaChuoi.length()) {
		if (chuaChuoi[i] != kiTuTach)
			tuTach += chuaChuoi[i];
		else if (rep == 1) {
			mangTach->push_back(tuTach);
			tuTach = L"";
		}
		else if (tuTach.length() > 0) {
			mangTach->push_back(tuTach);
			tuTach = L"";
		}
		i++;
	}
	if (!tuTach.empty())
		mangTach->push_back(tuTach);
	return mangTach;
}

bool MyLib::Chuoi::kiemTraNhapTen(wstring ten) {

	ten = this->boKhoangTrang(ten);
	if (ten.size() == 0)
	{
		wcout << L"\n\t\t\tTên không được trống!";
		return false;
	}
	wstring kiTu = L"aáàảạãăắằẳặẵâấầẩậẫbcdđeéèẻẹẽêếềểệễghiíìỉịĩklmnoóòỏọõôốồổộỗơớờởợỡpqrstuúùủụũưứừửữựvxyýỳỷỹỵwzjfAÁÀẢẠÃĂẮẰẲẶẴÂẤẦẨẬẪBCDĐEÉÈẺẸẼÊẾỀỂỆỄGHIÍÌỈỊĨKLMNOÓÒỎỌÕÔỐỒỔỘỖƠỚỜỞỢỠPQRSTUÚÙỦỤŨƯỨỪỬỮỰVXYÝỲỶỸỴWZJF";
	vector<wstring>* tenArr = this->tach(ten, ' ');
	if (tenArr->size() < 2) {
		wcout << L"\n\t\t\tVui lòng nhập họ và tên ít nhất 2 từ (vd Lê Khải)!";
		return false;
	}
	for (int i = 0; i < tenArr->size(); i++)
		if (this->kiemTrachuaChuoi(tenArr->data()[i].c_str(), kiTu.c_str()) != tenArr->data()[i].size()) {
			wcout << L"\n\t\t\tTên không được chứa số và kí từ đặc biệt!";
			return false;
		}
	return true;
}


bool MyLib::Chuoi::kiemTraNhapChucVu(wstring chucVu) {

	chucVu = this->boKhoangTrang(chucVu);
	if (chucVu.size() == 0)
	{
		wcout << L"\n\t\t\tTên không được trống!";
		return false;
	}
	wstring kiTu = L"aáàảạãăắằẳặẵâấầẩậẫbcdđeéèẻẹẽêếềểệễghiíìỉịĩklmnoóòỏọõôốồổộỗơớờởợỡpqrstuúùủụũưứừửữựvxyýỳỷỹỵwzjfAÁÀẢẠÃĂẮẰẲẶẴÂẤẦẨẬẪBCDĐEÉÈẺẸẼÊẾỀỂỆỄGHIÍÌỈỊĨKLMNOÓÒỎỌÕÔỐỒỔỘỖƠỚỜỞỢỠPQRSTUÚÙỦỤŨƯỨỪỬỮỰVXYÝỲỶỸỴWZJF";
	vector<wstring>* chucVuArr = this->tach(chucVu, ' ');
	for (int i = 0; i < chucVuArr->size(); i++)
		if (this->kiemTrachuaChuoi(chucVuArr->data()[i].c_str(), kiTu.c_str()) != chucVuArr->data()[i].size()) {
			wcout << L"\n\t\t\tTên không được chứa số và kí từ đặc biệt!";
			return false;
		}
	return true;
}



wstring MyLib::Chuoi::vietHoaKiTuDau(wstring ten)
{
	vector<wstring>* tenArr = this->tach(this->boKhoangTrang(this->vietThuong(ten)), ' ');
	wstring a1 = L"aáàảạãăắằẳặẵâấầẩậẫbcdđeéèẻẹẽêếềểệễghiíìỉịĩklmnoóòỏọõôốồổộỗơớờởợỡpqrstuúùủụũưứừửữựvxyýỳỷỹỵwzjf";
	wstring a2 = L"AÁÀẢẠÃĂẮẰẲẶẴÂẤẦẨẬẪBCDĐEÉÈẺẸẼÊẾỀỂỆỄGHIÍÌỈỊĨKLMNOÓÒỎỌÕÔỐỒỔỘỖƠỚỜỞỢỠPQRSTUÚÙỦỤŨƯỨỪỬỮỰVXYÝỲỶỸỴWZJF";
	wstring ketQua, tam;
	int viTri = -1;
	bool daChuyen;
	for (int i = 0; i < tenArr->size(); i++) {
		viTri = -1;
		for (int h = 0; h < tenArr->data()[i].size(); h++) {
			tam = tenArr->data()[i].at(h);
			if (h == 0) {
				viTri = this->timKiemChuoiCon(a1, tam);
				if (viTri > -1)
					ketQua += a2.at(viTri);
			}
			else
				ketQua += tam;
		}
		if (i < tenArr->size() - 1)
			ketQua += ' ';
	}


	return ketQua;
}

bool MyLib::Chuoi::kiemTraNhapSoNguyen(wstring so)
{
	if (so.size() == 0) {
		return false;
	}
	so = this->boKhoangTrang(so);
	wstring kiTu = L"0123456789";
	if (this->kiemTrachuaChuoi(so.c_str(), kiTu.c_str()) != so.size())
		return false;
	return true;

}


bool MyLib::Chuoi::kiemTraNhapSoThuc(wstring so)
{
	if (so.size() == 0) {
		return false;
	}
	so = this->boKhoangTrang(so);
	wstring kiTu = L".0123456789";
	if (so.at(0) == L'.')
		return false;
	if (this->kiemTrachuaChuoi(so.c_str(), L".") > 1)
		return false;
	if (this->kiemTrachuaChuoi(so.c_str(), kiTu.c_str()) != so.size())
		return false;
	if (this->kiemTrachuaChuoi(so.c_str(), L".") > 1)
		return false;
	return true;

}




int  MyLib::Chuoi::chuyenStringSangSoNguyen(wstring so) {
	if (kiemTraNhapSoNguyen(so) == false) return NULL;
	const wchar_t * tam = so.c_str();
	int kq = 0;
	for (int i = 0; tam[i] != '\0'; ++i)
		kq = kq * 10 + tam[i] - '0';
	return kq;
}


float  MyLib::Chuoi::chuyenStringSangSoThuc(wstring so) {
	if (kiemTraNhapSoThuc(so) == false) return NULL;
	const wchar_t * tam = so.c_str();
	float kq = 0, thapPhan = 1;
	bool quaCham = false;
	for (int i = 0; tam[i] != '\0'; ++i) {
		if (tam[i] == '.')
			quaCham = true;
		else if (quaCham == true) {
			thapPhan *= 0.1;
			kq += thapPhan * (tam[i] - '0');
		}
		else
			kq = kq * 10 + tam[i] - '0';
	}
	return kq;
}







//SĂP XẾP
