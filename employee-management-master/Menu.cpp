#pragma once
#include "Menu.h"

Menu::Menu()
{
}

int Menu::diChuyenPhim()
 {
	char c = _getch();
	if ((int)c == -32) c = _getch();//???
	switch ((int)c) {
	case 80:
		return 1; //cout << "Xuong";
	case 72:
		return 2; //cout << "Len";
	case 77:
		return 3; //cout << "Phai";       
	case 75:
		return 4; //cout << "Trai";
	case 27:
		return 8; //Nut ESC thoat
	case 13:
		return 5; //Nut Enter
	default:
		return 0; //cout << "Sai";
	}
	//return 0;
}


Menu::~Menu()
{
}
