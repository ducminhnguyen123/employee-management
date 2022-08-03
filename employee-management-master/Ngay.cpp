#include "Ngay.h"

Ngay::Ngay() {
	this->ngay = 0;
	this->thang = 0;
	this->nam = 0;
}

Ngay::Ngay(int ngay = 0, int thang = 0, int nam = 0)
{
	this->ngay = ngay;
	this->thang = thang;
	this->nam = nam;
}

Ngay::Ngay(wstring ngay)
{
	this->ngay = this->thang = this->nam = 0;
	int dem = 0;
	for (int i = 0; i < ngay.size(); i++)
		if (ngay[i] == '/')
			switch (dem)
			{
			case 0:
				for (int j = i - 1; j >= 0; j--)
					this->ngay += (j == 1 ? 1 : (j == 0 && ngay[j + 1] == '/') ? 1 : 2)*(ngay[j] - '0');// sao lại là 10 ở phần này
				dem++;
				break;
			case 1:
				for (int j = i - 1; ngay[j] != '/'; j--)
					this->thang += (j == 4 ? 1 : (j == 3 && ngay[j + 1] == '/') ? 1 : (j == 2 && ngay[j + 1] == '/') ? 1 : 10)*(ngay[j] - '0');

				int tam = 1000;
				for (int j = i + 1; j <= i + 4; j++) {
					this->nam += (ngay[j] - '0') * tam;
					tam /= 10;
				}
				return;

			}

}

bool Ngay::operator==(Ngay b)
{
	return this->ngay == b.ngay && this->thang == b.thang && this->nam == b.nam;
}

bool Ngay::operator!=(Ngay b)
{
	return this->ngay != b.ngay || this->thang != b.thang || this->nam != b.nam;
}




int Ngay::soSanh(Ngay * a, Ngay * b)
{
	if (a == b)return 0;
	else {
		int kq;
		a->nam > b->nam ? kq = -1 : a->nam < b->nam ? kq = 1 : kq = 0;
		if (kq != 0)return kq;
		a->thang > b->thang ? kq = -1 : a->thang < b->thang ? kq = 1 : kq = 0;
		if (kq != 0)return kq;
		a->ngay > b->ngay ? kq = -1 : a->ngay < b->ngay ? kq = 1 : kq = 0;
		if (kq != 0)return kq;
	}
	return 0;
}

bool Ngay::timNgay(Ngay * a, Ngay * b)
{
	int dem = 0, dem2 = 0;
	a->nam != 0 ? dem++ : dem += 0;
	a->thang != 0 ? dem++ : dem += 0;
	a->ngay != 0 ? dem++ : dem += 0;


	if (a->nam != 0 && a->nam == b->nam)
		dem2++;
	if (a->thang != 0 && a->thang == b->thang)
		dem2++;
	if (a->ngay != 0 && a->ngay == b->ngay)
		dem2++;
	if (dem == dem2 && dem > 0)
		return true;
	return false;
}







void Ngay::nhapNgay()
{
	MyLib::Chuoi chuoi;
	fflush(stdin);
	wstring ngay, thang, nam;
	while (true) {
		wcout << L"\n\t\t\tNhập ngày: ";
		getline(wcin, ngay);
		wcout << L"\t\t\tNhập tháng: ";
		getline(wcin, thang);
		wcout << L"\t\t\tNhập năm: ";
		getline(wcin, nam);

		if (chuoi.kiemTraNhapSoNguyen(ngay) == true && chuoi.kiemTraNhapSoNguyen(thang) == true && chuoi.kiemTraNhapSoNguyen(nam) == true)
			if (this->kiemTraNhap(chuoi.chuyenStringSangSoNguyen(thang), chuoi.chuyenStringSangSoNguyen(ngay), chuoi.chuyenStringSangSoNguyen(nam)) == 0) {
				this->ngay = chuoi.chuyenStringSangSoNguyen(ngay);
				this->thang = chuoi.chuyenStringSangSoNguyen(thang);
				this->nam = chuoi.chuyenStringSangSoNguyen(nam);
				break;
			}
		wcout << L"\n\t\t\tDữ liệu không hợp lệ, vui lòng thử lại!";
	}


}

int  Ngay::kiemTraNhap(int month, int day, int year)
{
	time_t theTime = time(NULL);
	struct tm *aTime = localtime(&theTime);

	int status = 0;

	if ((month == 1 || month == 3 || month == 5 || month == 7 ||
		month == 8 || month == 10 || month == 12) && (day > 31 || day < 1))
	{
		status = 3;
	}
	else if ((month == 4 || month == 6 || month == 9 || month == 11) && (day > 30 || day < 1))
	{
		status = 4;
	}
	else if ((month == 2) && (year % 4 == 0) && (day > 29 || day < 1))
	{
		status = 5;
	}
	else if ((month == 2) && (year % 4 != 0) && (day > 28 || day < 1))
	{
		status = 6;
	}
	else if ((year < aTime->tm_year + 1850) || (year > aTime->tm_year + 1900))
	{
		status = 1;
	}
	if ((month < 1) || (month > 12))
	{
		status = 2;
	}
	return status;
};

int Ngay::getNgay()
{
	return this->ngay;
}

int Ngay::getThang()
{
	return this->thang;
}

int Ngay::getNam()
{
	return this->nam;
}

wstring Ngay::toString()
{
	wostringstream os;
	os << this->ngay << L"/" << this->thang << L"/" << this->nam;
	return os.str();
}
