#ifndef STACK_H
#endif 
#define STACK_H

#pragma once
#include "NhanVien.h"

//#include "MyLib.h"


struct Node
{
	NhanVien data;
	Node *link;
};


class Stack {
public:
	Stack();
	~Stack();
	void push(NhanVien nv);
	NhanVien pop();
	NhanVien peek();
	bool isEmpty();
	int size();
	wstring toSaveFile();
	wstring toString();
	wstring toStringSearch();
	void sort(vector<wstring> *chucVu, int index, int direction);
	void search(Stack *temp, vector<wstring> *chucVu, int index);
	void deleteSearch(Stack *temp);
	void deleteNode(Stack *a, int position);
	void insertNode(NhanVien nv, vector<wstring>* chucVu, int index, int direction);
	bool CheckExitChucVu(wstring chucVu);
	void editDataChucVu(wstring chucVuTruoc, wstring chucVuSau);

private:
	Node *top;
};