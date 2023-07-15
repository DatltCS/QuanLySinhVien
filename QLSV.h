#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
#include<conio.h>
#include<Windows.h>
using namespace std;
/*
												-------------Boi vi la code chung nen ai code gi, viet code phai de lai info cho cac thanh vien trong team thac mac--------
												-------------Sua code cua thanh vien trong nhom nho de lai info va ngay cap nhat, vd: ' Update: Nguyen 30/12/2021 '-------
																							---Thank, cung chung tay nhau qua mon!!!---
																													Nguyen.
*/
struct HocVien
{
	int id;
	string firstName;
	string lastName;
	int birthDay[3];// nn/tt/nnnn
	string idClass;
	double point;

	HocVien* link;
};
struct Class
{
	string id;
	string name;
	string timeTable[3][7];
	int fee;
	int SLHV;
	HocVien* first;

	Class* link;
};
//-------code cua Nguyen----------//
//- Ham xu ly HocVien -//
void initHV(HocVien*& first)
{
	first = NULL;
}
HocVien* createHV()
{
	HocVien* p;
	p = new HocVien;
	p->id = NULL;
	p->firstName = "";
	p->lastName = "";
	for (int i = 0; i < 3; i++)
		p->birthDay[i] = NULL;
	p->point = NULL;
	p->idClass = "";
	p->link = NULL;
	return p;
}
void addFirstHV(HocVien*& First, HocVien*& add)
{
	if (First == NULL)
	{
		First = add;
	}
	else
	{
		add->link = First;
		First = add;
	}
}
void addLastHV(HocVien*& First, HocVien* add)
{
	
	if (First == NULL)
		First = add;
	else
	{
		HocVien* p = First;
		while (p->link != NULL)
		{
			p = p->link;
		}
		p->link = add;
	}
}
void tranferHV(HocVien*& a, HocVien*& b) //- Gan cac nut HV b cho HV a
{
	a->id = b->id;
	a->firstName = b->firstName;
	a->lastName = b->lastName;
	a->idClass = b->idClass;
	a->point = b->point;
	for (int i = 0; i < 3; i++)
		a->birthDay[i] = b->birthDay[i];
}
void swapHV(HocVien*& a, HocVien*& b) //- Hoan doi gia tri thanh phan hoc vien
{
	HocVien* c = createHV();
	tranferHV(c, a);
	tranferHV(a, b);
	tranferHV(b, c);
}
//- Ham xu ly Class -//
void initClass(Class*& first)
{
	first = NULL;
}
Class* createClass()
{
	Class* p;
	p = new Class;
	p->id = "";
	p->name = "";
	p->SLHV = 0;
	p->first = NULL;
	p->fee = NULL;
	p->link = NULL;
	return p;
}
void addFirstClass(Class*& First, Class*& add)
{
	if (First == NULL)
	{
		First = add;
	}
	else
	{
		add->link = First;
		First = add;
	}
}
void addLastClass(Class*& First, Class* add)
{
	Class* p = First;
	if (p == NULL)
		First = add;
	else
	{
		while (p->link != NULL)
		{
			p = p->link;
		}
		p->link = add;
	}
}
void tranferClass(Class*& a, Class*& b) //- Gan class b cho class a
{
	a->id = b->id;
	a->name = b->name;
	a->fee = b->fee;
	a->SLHV = b->SLHV;
	a->first = b->first;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 7; j++)
			a->timeTable[i][j] = b->timeTable[i][j];
}
void swapClass(Class*& a, Class*& b) //- Hoan doi cac gia tri thanh phan class
{
	Class* c = createClass();
	tranferClass(c, a);
	tranferClass(a, b);
	tranferClass(b, c);
}
//- doc file -//
void formatPoint(double& x)
{
	double t = int(x * 100);
	int valRound = int(x * 1000) % 10;
	if (valRound >= 5)
		t++;
	x = t / 100;
}
void inputClassFromFile(Class*& First, int &SL) //- Lua chon 1 -//
{
	SL = 0;
	ifstream readFile;
	readFile.open("lophoc.txt", ios::in);
	if (readFile.is_open())
	{
		while (readFile.eof() == false)
		{
			Class* p = createClass();

			getline(readFile, p->id, '#');
			getline(readFile, p->name, '#');
			readFile >> p->fee;
			readFile.ignore(1);
			for (int i = 0; i < 7; i++)
				for (int j = 0; j < 3; j++)
					getline(readFile, p->timeTable[j][i], '#');
			readFile.ignore(1);
			addFirstClass(First, p);
			SL++;
		}
		cout << "Doc File lophoc.txt thanh cong!!!" << endl;
	}
	else
		cout << "Khong mo duoc file lophoc.txt!!!" << endl;
	readFile.close();
}
void inputHVFromFile(HocVien*& DShv, int& SL, Class*& firstclass) //- Lua chon 1 -//
{
	ifstream readFile;
	readFile.open("hocvien.txt", ios::in);
	if (readFile.is_open())
	{
		while (readFile.eof() == false)
		{
			HocVien* p = createHV();
			getline(readFile, p->idClass, '#');
			readFile >> p->id;
			readFile.ignore(1);
			getline(readFile, p->firstName, '#');
			getline(readFile, p->lastName, '#');
			readFile >> p->birthDay[0];
			readFile.ignore(1);
			readFile >> p->birthDay[1];
			readFile.ignore(1);
			readFile >> p->birthDay[2];
			readFile.ignore(1);
			readFile >> p->point;
			readFile.ignore(1);
			formatPoint(p->point);
			addFirstHV(DShv, p);
			SL++;
			Class* t;
			t = firstclass;
			while (t!=NULL)
			{
				if (t->id == p->idClass)
				{
					HocVien* v = createHV();
					tranferHV(v, p);
					addFirstHV(t->first, v);
					t->SLHV++;
					break;
				}
				t = t->link;
			}
		}
		cout << "Doc File hocvien.txt thanh cong!!!" << endl;
	}
	else
		cout << "Mo file khong thanh cong!!!" << endl;
	readFile.close();
}
//-in ra console-//
void outputListClass(Class* first)
{
	if (first == NULL)
	{
		cout << "Class chua co du lieu!" << endl;
		return;
	}
	int i = 1;
	Class* p;
	p = first;
	cout << setw(12) << "STT" << setw(10) << "Ma Lop" << setw(25) << "Ten Lop" << setw(35) << "So Luong Hoc Vien" << setw(20) << "Hoc Phi" << endl;
	cout << "----------------------------------------------------------------------------------------------------------" << endl;
	while (p != NULL)
	{
		cout << setw(10) << i++ << "|" << setw(10) << p->id << setw(30) << p->name << setw(23) << p->SLHV << setw(28) << p->fee << endl;
		p = p->link;
	}
}
void outputListHV(HocVien* first)
{
	if (first == NULL)
	{
		cout << "Chua co danh sach!!!" << endl;
		return;
	}
	int i = 1;
	HocVien* p;
	p = first;
	cout << setw(12) << "STT" << setw(20) << "MSSV" << setw(20) << "Ho & ten dem" << setw(10) << "Ten" << setw(20) << "Ngay Sinh" << setw(11) << "Ma Lop" << setw(10) << "Diem" << endl;
	cout << "----------------------------------------------------------------------------------------------------------" << endl;
	while (p != NULL)
	{
		cout << setw(11) << i++ << "|" << setw(20) << p->id << setw(20) << p->firstName << setw(10) << p->lastName << setw(13) << p->birthDay[0] << "/" << setw(2) << p->birthDay[1] << "/" << setw(4) << p->birthDay[2] << setw(10) << p->idClass << setw(10) << p->point << endl;
		p = p->link;
	}
}

//-------------------------------------------------//Sap xep HV theo diem//----------------------------------//
//-sap xep- heapsort//
HocVien* getAddressHV(HocVien* first, int i) //- xuat dia chi tai vi tri i
{
	HocVien* p;
	p = first;
	for (int j = 0; j < i; j++)
		p = p->link;
	return p;
}
void shift(HocVien*& first, int i, int n)
{
	int j = 2 * i + 1;
	if (j >= n)
		return;
	if (j + 1 < n)
	{
		HocVien* a = getAddressHV(first, j);
		HocVien* b = getAddressHV(first, j + 1);
		if (a->point > b->point)
			j++;
	}
	HocVien* c = getAddressHV(first, i);
	HocVien* d = getAddressHV(first, j);
	if (c->point > d->point)
	{
		swapHV(c, d);
		shift(first, j, n);
	}
	else
		return;
}
void HeapSortHV(HocVien*& first, int SLHV)
{
	int i = SLHV / 2 - 1;
	while (i >= 0)
	{
		shift(first, i, SLHV);
		i--;
	}
	int n = SLHV - 1;
	while (n > 0)
	{
		HocVien* a = getAddressHV(first, n);
		swapHV(first, a);
		n--;
		if (n > 0)
		{
			i = (n + 1) / 2 - 1;
			shift(first, 0, n + 1);
		}
	}
}
void HeapSortPointHVofClass(Class*& dsLop)
{
	Class* pt = dsLop;
	while (pt != NULL)
	{
		HeapSortHV(pt->first, pt->SLHV);
		pt = pt->link;
	}
}
//-sap xep merge sort-//			//Update: Dat da check 5/1/2022
HocVien* mergePointHV(HocVien* a, HocVien* b)  
{
	HocVien* first;
	initHV(first);
	HocVien* p = a;
	HocVien* q = b;
	while (p != NULL && q != NULL)
	{
		if (p->point > q->point)
		{
			HocVien* t = createHV();
			tranferHV(t, p);
			p = p->link;
			addLastHV(first, t);
		}
		else
		{
			HocVien* t = createHV();
			tranferHV(t, q);
			q = q->link;
			addLastHV(first, t);
		}
	}
	while (p!=NULL)
	{
		HocVien* e = createHV();
		tranferHV(e, p);
		addLastHV(first, e);
		p = p->link;
	}
	while (q != NULL)
	{
		HocVien* e = createHV();
		tranferHV(e, q);
		addLastHV(first, e);
		q = q->link;
	}
	return first;
}
HocVien* mergeSortPointHV(HocVien* first, int SL)
{
	if (SL == 1)
		return first;
	HocVien* p = first;
	int mid = SL / 2;
	HocVien* first_1;
	initHV(first_1);
	HocVien* first_2;
	initHV(first_2);
	for (int i = 1; i <= mid; i++)
	{
		HocVien* t = createHV();
		tranferHV(t, p);
		addLastHV(first_1, t);
		p = p->link;
	}
	while (p != NULL)
	{
		HocVien* e = createHV();
		tranferHV(e, p);
		addLastHV(first_2, e);
		p = p->link;
	}
	first_1 = mergeSortPointHV(first_1, mid);
	first_2 = mergeSortPointHV(first_2, SL - mid);
	return mergePointHV(first_1, first_2);
}
void mergeSortPointHVofClass(Class*& dsLop)
{
	Class* p = dsLop;
	while (p != NULL)
	{
		p->first = mergeSortPointHV(p->first, p->SLHV);
		p = p->link;
	}
}
//- sap xep counting sort-//
int luythua(int x, int y) //luy thua cua so nguyen duong
{
	int t = y;
	if (t == 0)
		return 1;
	if (t < 0)
		t = t * -1;
	int KQ = 1;
	for (int i = 0; i < t; i++)
		KQ *= x;
	if (y < 0)
		return 1 / KQ;
	else
		return KQ;
}
HocVien* countingSortHV(HocVien* first)
{
	HocVien* p = first;
	HocVien** a = new HocVien*[1001];
	for (int i = 0; i <= 1000; i++)
	{
		initHV(a[i]);
	}
	while (p != NULL)
	{
		int x = int(p->point * 100);
		HocVien* t = createHV();
		tranferHV(t, p);
		addLastHV(a[x], t); 
		p = p->link;
	}
	HocVien* KQ;
	initHV(KQ);
	for (int i = 1000; i >= 0; i--)
	{
		if (a[i] != NULL)
			addLastHV(KQ, a[i]);
	}
	delete[]a;
	return KQ;
}
void countingSortHVofClass(Class*& dsLop)
{
	Class* p = dsLop;
	while (p != NULL)
	{
		p->first = countingSortHV(p->first);
		p = p->link;
	}
}
//-------------------------------------------------//Sap xep class//----------------------------------//
//- sap xep lop thu tu tang dan heapSort-//
Class* getAddressClass(Class* first, int i) //- xuat dia chi tai vi tri i
{
	Class* p;
	p = first;
	for (int j = 0; j < i; j++)
		p = p->link;
	return p;
}
void shiftIdClass(Class*& first, int i, int n)
{
	int j = 2 * i + 1;
	if (j >= n)
		return;
	if (j + 1 < n)
	{
		Class* a = getAddressClass(first, j);
		Class* b = getAddressClass(first, j + 1);
		if (a->id<b->id)
			j++;
	}
	Class* c = getAddressClass(first, i);
	Class* d = getAddressClass(first, j);
	if (c->id < d->id)
	{
		swapClass(c, d);
		shiftIdClass(first, j, n);
	}
	else
		return;
}
void HeapSortIdClass(Class*& first, int SL)
{
	int i = SL / 2 - 1;
	while (i >= 0)
	{
		shiftIdClass(first, i, SL);
		i--;
	}
	int n = SL - 1;
	while (n > 0)
	{
		Class* a = getAddressClass(first, n);
		swapClass(first, a);
		n--;
		if (n > 0)
		{
			i = (n + 1) / 2 - 1;
			shiftIdClass(first, 0, n + 1);
		}
	}
}
//- sap xep lop thu tu tang dan mergeSort-//
Class* mergeIdClass(Class* a, Class* b)
{
	Class* first;
	initClass(first);
	Class* p = a;
	Class* q = b;
	while (p != NULL && q != NULL)
	{
		if (p->id < q->id)
		{
			Class* t = createClass();
			tranferClass(t, p);
			p = p->link;
			addLastClass(first, t);
		}
		else
		{
			Class* t = createClass();
			tranferClass(t, q);
			q = q->link;
			addLastClass(first, t);
		}
	}
	while (p != NULL)
	{
		Class* e = createClass();
		tranferClass(e, p);
		addLastClass(first, e);
		p = p->link;
	}
	while (q != NULL)
	{
		Class* e = createClass();
		tranferClass(e, q);
		addLastClass(first, e);
		q = q->link;
	}
	return first;
}
Class* mergeSortIdClass(Class* first, int SL)
{
	if (SL == 1)
		return first;
	Class* p = first;
	int mid = SL / 2;
	Class* first_1;
	initClass(first_1);
	Class* first_2;
	initClass(first_2);
	for (int i = 1; i <= mid; i++)
	{
		Class* t = createClass();
		tranferClass(t, p);
		addLastClass(first_1, t);
		p = p->link;
	}
	while (p != NULL)
	{
		Class* e = createClass();
		tranferClass(e, p);
		addLastClass(first_2, e);
		p = p->link;
	}
	first_1 = mergeSortIdClass(first_1, mid);
	first_2 = mergeSortIdClass(first_2, SL - mid);
	return mergeIdClass(first_1, first_2);
}
//- sap xep lop thu tu tang dan countingSort-//
int maxlengthStr(Class* first)
{
	Class* p = first;
	int Max = (p->id).length();
	while (p != NULL)
	{
		int x = (p->id).length();
		if (Max < x)
			Max = x;
		p = p->link;
	}
	return Max;
}
int anhXaClass(string a, int Maxlength)
{
	int size = a.length();
	int i = 0, KQ = 0;
	while (i < size)
	{
		KQ += int(int(a[i]) * luythua(10, Maxlength - 1 - i));
		i++;
	}
	return KQ;
}
int anhXaMaxClass(Class* first)
{
	Class* p = first;
	int Maxlength = maxlengthStr(first);
	int Max = anhXaClass(p->id, Maxlength);
	while (p != NULL)
	{
		if (Max < anhXaClass(p->id, Maxlength))
			Max = anhXaClass(p->id, Maxlength);
		p = p->link;
	}
	return Max;
}
Class* CountingSortIdClass(Class* first)
{
	int MaxLengthStr = maxlengthStr(first);
	int MaxAnhXa = anhXaMaxClass(first);
	Class** c = new Class * [MaxAnhXa + 1];
	for (int i = 0; i <= MaxAnhXa; i++)
		initClass(c[i]);
	Class* p = first;
	while (p!=NULL)
	{
		int x = anhXaClass(p->id,MaxLengthStr);
		Class* t = createClass();
		tranferClass(t, p);
		addLastClass(c[x], t);
		p = p->link;
	}
	Class* KQ;
	initClass(KQ);
	for (int i = 0; i <=MaxAnhXa; i++)
	{
		if (c[i] != NULL)
			addLastClass(KQ, c[i]);
	}
	delete[]c;
	return KQ;
}
//-------------------------------------------------//Sap xep HV theo ten giam dan//----------------------------------// //Update: Linh da check 8/1/2022
//-------------heapSort----------------//
void shiftNameHV(HocVien*& first, int i, int n)
{
	int j = 2 * i + 1;
	if (j >= n)
		return;
	if (j + 1 < n)
	{
		HocVien* a = getAddressHV(first, j);
		HocVien* b = getAddressHV(first, j + 1);
		if (a->lastName > b->lastName)
			j++;
	}
	HocVien* c = getAddressHV(first, i);
	HocVien* d = getAddressHV(first, j);
	if (c->lastName > d->lastName)
	{
		swapHV(c, d);
		shiftNameHV(first, j, n);
	}
	else
		return;
}
void HeapSortNameHV(HocVien*& first, int SLHV)
{
	int i = SLHV / 2 - 1;
	while (i >= 0)
	{
		shiftNameHV(first, i, SLHV);
		i--;
	}
	int n = SLHV - 1;
	while (n > 0)
	{
		HocVien* a = getAddressHV(first, n);
		swapHV(first, a);
		n--;
		if (n > 0)
		{
			i = (n + 1) / 2 - 1;
			shiftNameHV(first, 0, n + 1);
		}
	}
}
//-------------mergeSort----------------//
HocVien* mergeNameHV(HocVien* a, HocVien* b)
{
	HocVien* first;
	initHV(first);
	HocVien* p = a;
	HocVien* q = b;
	while (p != NULL && q != NULL)
	{
		if (p->lastName > q->lastName)
		{
			HocVien* t = createHV();
			tranferHV(t, p);
			p = p->link;
			addLastHV(first, t);
		}
		else
		{
			HocVien* t = createHV();
			tranferHV(t, q);
			q = q->link;
			addLastHV(first, t);
		}
	}
	while (p != NULL)
	{
		HocVien* e = createHV();
		tranferHV(e, p);
		addLastHV(first, e);
		p = p->link;
	}
	while (q != NULL)
	{
		HocVien* e = createHV();
		tranferHV(e, q);
		addLastHV(first, e);
		q = q->link;
	}
	return first;
}
HocVien* mergeSortNameHV(HocVien* first, int SL)
{
	if (SL == 1)
		return first;
	HocVien* p = first;
	int mid = SL / 2;
	HocVien* first_1;
	initHV(first_1);
	HocVien* first_2;
	initHV(first_2);
	for (int i = 1; i <= mid; i++)
	{
		HocVien* t = createHV();
		tranferHV(t, p);
		addLastHV(first_1, t);
		p = p->link;
	}
	while (p != NULL)
	{
		HocVien* e = createHV();
		tranferHV(e, p);
		addLastHV(first_2, e);
		p = p->link;
	}
	first_1 = mergeSortNameHV(first_1, mid);
	first_2 = mergeSortNameHV(first_2, SL - mid);
	return mergeNameHV(first_1, first_2);
}
//-------------countingSort-------------//
int maxlengthStrHV(HocVien* first)
{
	HocVien* p = first;
	int Max = (p->lastName).length();
	while (p != NULL)
	{
		int x = (p->lastName).length();
		if (Max < x)
			Max = x;
		p = p->link;
	}
	return Max;
}
int anhXaNameHV(string a, int Maxlength)
{
	int size = a.length();
	int i = 0, KQ = 0;
	while (i < size)
	{
		KQ += int(int(a[i]) * luythua(10, Maxlength - 1 - i));
		i++;
	}
	return KQ;
}
int anhXaMaxNameHV(HocVien* first)
{
	HocVien* p = first;
	int Maxlength = maxlengthStrHV(first);
	int Max = anhXaNameHV(p->lastName, Maxlength);
	while (p != NULL)
	{
		if (Max < anhXaNameHV(p->lastName, Maxlength))
			Max = anhXaNameHV(p->lastName, Maxlength);
		p = p->link;
	}
	return Max;
}
HocVien* CountingSortNameHV(HocVien* first)
{
	int MaxLengthStr = maxlengthStrHV(first);
	int MaxAnhXa = anhXaMaxNameHV(first);
	HocVien** c = new HocVien * [MaxAnhXa + 1];
	for (int i = 0; i <= MaxAnhXa; i++)
		initHV(c[i]);
	HocVien* p = first;
	while (p != NULL)
	{
		int x = anhXaNameHV(p->lastName, MaxLengthStr);
		HocVien* t = createHV();
		tranferHV(t, p);
		addLastHV(c[x], t);
		p = p->link;
	}
	HocVien* KQ;
	initHV(KQ);
	for (int i = MaxAnhXa; i >= 0; i--)
	{
		if (c[i] != NULL)
			addLastHV(KQ, c[i]);
	}
	delete[]c;
	return KQ;
}

//-------------in ra HV be hon 5 va sap xep ten giam dan---------------// //- Lua chon 10 -//	//Update: Thuy da sua 12/1/2022
void outputHVbad(HocVien* first)
{
	if (first == NULL)
	{
		cout << "Chua co danh sach!" << endl;
		return;
	}
	int SL = 0;
	HocVien* KQ;
	initHV(KQ);
	HocVien* p = first;
	while (p != NULL)
	{
		if (p->point < 5)
		{
			HocVien* t = createHV();
			tranferHV(t, p);
			addFirstHV(KQ, t);
			SL++;
		}
		p = p->link;
	}
	KQ = mergeSortNameHV(KQ, SL);
	cout << setw(65) << "DANH SACH HOC VIEN KEM" << endl << endl;
	outputListHV(KQ);
}
//-------------ghi ra file hoc vien hon hoac bang 8 diem---------------//	//--Lua chon 11--// 
void outputHVgood(HocVien* first)
{
	if (first == NULL)
	{
		cout << "Chua co danh sach!" << endl;
		return;
	}
	int SL = 0;
	HocVien* KQ;
	initHV(KQ);
	HocVien* p = first;
	while (p != NULL)
	{
		if (p->point >= 8)
		{
			HocVien* t = createHV();
			tranferHV(t, p);
			addFirstHV(KQ, t);
			SL++;
		}
		p = p->link;
	}
	KQ = countingSortHV(KQ);
	cout << setw(65) << "DANH SACH HOC BONG" << endl << endl;
	outputListHV(KQ);
	char i;
	cout << "\nBan co muon ghi ra file khong? (y/n) ";
	cin >> i;
	if (i == 'y' || i == 'Y')
	{
		ofstream writeFile;
		writeFile.open("dshocbong.txt", ios::out);
		if (writeFile.is_open())
		{
			HocVien* k = KQ;
			while (k != NULL)
			{
				writeFile << k->idClass << '#' << k->id << '#' << k->firstName << '#' << k->lastName << '#' << k->birthDay[0] << '#' << k->birthDay[1] << '#' << k->birthDay[2] << '#' << k->point << endl;
				k = k->link;
			}
		}
		else
			cout << "Loi! Khong mo duoc file!!";
		writeFile.close();
	}
}

//-----Code cua Dat -------//  update: Nguyen da sua ngay 2/1/2022
//xuat hoc vien theo tung lop            --------- lua chon 5                       
void outputHocVienOfClass(Class* first)
{
	Class* p = first;
	while (p != NULL)
	{
		cout << "Ma lop: " << p->id << "\t" << "Ten Lop: " << p->name << "\t" << "So luong hoc vien: " << p->SLHV << endl;
		outputListHV(p->first);
		p = p->link;
		cout << endl;
	}
}
//-Xuat hoc vien cao diem nhat-//     //-- Lua chon 7 --//
double MaxPoint(HocVien* first)
{
	HocVien* p = first;
	double max = p->point;
	while (p != NULL)
	{
		if (max < p->point)
		{
			max = p->point;
		}
		p = p->link;
	}
	return max;
}
void outputHocVienMax(HocVien* first)
{
	HocVien* KQ;
	initHV(KQ);
	HocVien* p = first;
	double maxPoint = MaxPoint(first);
	while (p != NULL)
	{
		if (p->point == maxPoint)
		{
			HocVien* t = createHV();
			tranferHV(t, p);
			addFirstHV(KQ,t);
		}
		p = p->link;
	}
	outputListHV(KQ);
}
//-Xuat hoc vien hoc o lop hoc phi cao nhat-//          //-Lua chon 8--//
int MaxFee(Class* first)
{
	Class* p = first;
	int max = p->fee;
	while (p != NULL)
	{
		if (max < p->fee)
		{
			max = p->fee;
		}
		p = p->link;
	}
	return max;
}
void ouputMaxFeeHocVien(Class* firstClass)
{
	int maxFeeClass = MaxFee(firstClass);
	Class* p = firstClass;
	while (p != NULL)
	{
		if (p->fee == maxFeeClass)
		{
			cout << setw(35) << "Ten lop: " << p->name << "|| Hoc phi:" << p->fee << endl << endl;
			outputListHV(p->first);
		}
		p = p->link;
	}
}


//----Code of Thuy -------// Update: Nguyen da check 11/1/2022
void getNulchar(int& x)
{
	int KQ = 0;
	int i = 0;
	char t;
	do
	{
		t = _getch();
		if (t >= 48 && t <= 57)
		{
			cout << t;
			KQ = KQ * 10 + (int(t) - 48);
			i++;
		}
		if (t == 8 && i > 0)
		{
			KQ = KQ / 10;
			cout << "\b \b";
			i--;
		}
	} while (t != 13);
	x = KQ;
	cout << endl;
}
string formatLower(string a)
{
	string KQ = "";
	int size = a.length();
	for (int i = 0; i < size; i++)
		KQ += tolower(a[i]);
	return KQ;
}
void formatName(string& str)
{
	if (str == "")
		return;
	int size = str.length();
	int i = 0, j = size - 1;
	while (str[i] == ' ')
		i++;
	while (str[j] == ' ')
		j--;
	str = str.substr(i, j - i + 1);   // xoa space dau va cuoi
	size = str.length();
	bool flag = false;
	for (int i = 0; i < size; i++)
	{
		if (str[i] == ' ')
		{
			if (flag)                 
			{
				str.erase(i, 1);
				size--;
				i--;
			}
			
			flag = true;
		}
		else
			flag = false;           // xoa giua chi de lai 1 space
	}
	size = str.length();
	for (int i = 0; i < size; i++)  //format chu thuong het
		str[i] = (char)tolower(str[i]);
	str[0] = (char)towupper(str[0]);
	for (int i = 0; i < size; i++)  //format chu hoa dau tien va sau dau cach
		if (str[i] == ' ')
			str[i + 1] = (char)toupper(str[i + 1]);
}
bool checkMaLop(Class* first, string ma)
{
	if (first == NULL)
		return false;
	Class* p = first;
	while (p != NULL)
	{
		if (p->id == ma)
		{
			return true;
		}
		p = p->link;
	}
	return false;
}
bool checkNameClass(Class* first, string name)
{
	if (first == NULL)
		return false;
	Class* p = first;
	while (p != NULL)
	{
		if (p->name == name)
		{
			return true;
		}
		p = p->link;
	}
	return false;
}
bool checkMaHV(HocVien* first, int ma)
{
	if (first == NULL)
	{
		return false;
	}

	HocVien* p;
	p = first;
	while (p != NULL)
	{
		if (p->id == ma)
		{
			return true;
		}
		p = p->link;
	}
	return false;
}
bool checkNamNhuan(int year)
{
	if (year % 400 == 0)
		return true;
	if (year % 4 == 0 && year % 100 != 0)
		return true;
	return false;
}
bool checkBirthDay(int day, int month, int year)
{
	int thang=0;
	if (month > 12 || month <= 0 || year <= 0 || year>2022)
		return false;
	switch (month)
	{
	case 1:
		thang = 31;
	case 2:
		if (checkNamNhuan(year))
			thang = 29;
		else
			thang = 28;
	case 3:
		thang = 31;
	case 4:
		thang = 30;
	case 5:
		thang = 31;
	case 6:
		thang = 30;
	case 7:
		thang = 31;
	case 8:
		thang = 31;
	case 9:
		thang = 30;
	case 10:
		thang = 31;
	case 11:
		thang = 30;
	case 12:
		thang = 31;
	}
	if (day<0 || day>thang)
		return false;
	else
		return true;
}
void inputFromKeyboard(HocVien*& dsHV, int SLHV, Class*& dsLop)              //------lua chon 2
{
	HocVien* x = createHV();
	cout << "Nhap ho & ten dem: "; 
	getline(cin, x->firstName);
	formatName(x->firstName);
	cout << "Nhap ten: ";
	getline(cin, x->lastName);
	formatName(x->lastName);
	do
	{
		cout << "Nhap ma so sinh vien: ";
		getNulchar(x->id);
		if (checkMaHV(dsHV, x->id) == true)
			cout << "Ma so sinh vien da co. Vui long nhap lai\n";		
	} while (checkMaHV(dsHV, x->id) == true);
	do
	{
		cout << "Nhap ngay sinh : ";
		getNulchar(x->birthDay[0]);
		cout << "Nhap thang sinh : ";
		getNulchar(x->birthDay[1]);
		cout << "Nhap nam sinh:";
		getNulchar(x->birthDay[2]);
		if (checkBirthDay(x->birthDay[0], x->birthDay[1], x->birthDay[2]) == false)
			cout << "Dinh dang ngay thang nam sinh sai! Moi nhap lai!\n";
	} while (checkBirthDay(x->birthDay[0], x->birthDay[1], x->birthDay[2])==false);
	do
	{
		cout << "Nhap ma lop: ";
		getline(cin, x->idClass);
		if (checkMaLop(dsLop, x->idClass) == false)
			cout << "Ma lop chua ton tai, vui long kiem tra lai\n";
	} while (checkMaLop(dsLop, x->idClass) == false);

	do
	{
		cout << "Nhap diem trung binh: ";
		cin >> x->point;
		if (x->point < 0 || x->point>10)
			cout << "Dinh dang diem sai!!!\n";
	} while (x->point<0||x->point>10);
	cin.ignore(1);
	formatPoint(x->point);
	addLastHV(dsHV, x);
	SLHV++;
	Class* t;
	t = dsLop;
	while (t != NULL)
	{
		if (t->id == x->idClass)
		{
			HocVien* v = createHV();
			tranferHV(v, x);
			addFirstHV(t->first, v);
			t->SLHV++;
			break;
		}
		t = t->link;
	}
} 
//output theo ma lop                                      ----------lua chon 3
void searchHVbyNameClass(Class *first)
{
	if (first == NULL)
	{ 
		cout << "Danh sach lop rong, khong the tim kiem!" << endl;
		return;
	}
	string name;
	do
	{
		cout << "Nhap ten lop de tim kiem: ";
		getline(cin, name);
		formatName(name);
		if (checkNameClass(first, name) == false)
		{
			char key;
			cout << "Khong co ma lop nay! Ban muon tiep tuc tien kiem?(y/n)";
			cin >> key;
			cin.ignore(1);
			if (key == 'n' || key == 'N')
				return;
		}
	} while (checkNameClass(first, name) == false);
	Class* p = first;
	while (p != NULL)
	{
		if (p->name == name)
		{
			outputListHV(p->first);
			return;
		}
		p = p->link;
	}
}
// output theo ma hoc vien
void searchHVbyIdHV(HocVien* first)
{
	if (first == NULL)
	{
		cout << "Danh sach hoc vien rong, khong the tim kiem!" << endl;
		return;
	}
	int idHV;
	do
	{
		cout << "Nhap hoc vien de tim kiem: ";
		cin >> idHV;
		if (checkMaHV(first, idHV) == false)
		{
			char key;
			cout << "Khong co ma hoc vien nay! Ban muon tiep tuc tien kiem?(y/n)";
			cin >> key;
			cin.ignore(1);
			if (key == 'n' || key == 'N')
				return;
		}
	} while (checkMaHV(first, idHV) == false);
	HocVien* p = first;
	while (p != NULL)
	{
		if (p->id == idHV)
		{
			HocVien* e = createHV();
			tranferHV(e, p);
			outputListHV(e);
			return;
		}
		p = p->link;
	}
}
// output theo nam sinh
void searchHVbyBirthday(HocVien* first)
{
	if (first == NULL)
	{
		cout << "Danh sach hoc vien rong, khong the tim kiem!" << endl;
		return;
	}
	int year;
	do
	{
		cout << "Nhap nam sinh de tim kiem: ";
		cin >> year;
		if (year < 0 || year>2022)
		{
			char key;
			cout << "Nam sinh sai! Ban muon tiep tuc tien kiem?(y/n)";
			cin >> key;
			cin.ignore(1);
			if (key == 'n' || key == 'N')
				return;
		}
	} while (year < 0 || year>2022);
	HocVien* p = first;
	HocVien* t;
	initHV(t);
	while (p != NULL)
	{
		if (p->birthDay[2] == year)
		{
			HocVien* c = createHV();
			tranferHV(c, p);
			addFirstHV(t, c);
		}
		p = p->link;
	}
	if (t == NULL)
		cout << "Khong tim thay\n";
	else
		outputListHV(t);
}

//--------goi y tim kiem--------------//                              ------- lua chon 11
void formatCusor(string h)
{
	int size = h.length();
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Pos;
	Pos.X = 51 + size;
	Pos.Y = 0;
	SetConsoleCursorPosition(hStdout, Pos);
}
HocVien* findSuggest(HocVien* first, string key)
{
	HocVien* KQ;
	initHV(KQ);
	HocVien* p = first;
	int size = key.length();
	while (p != NULL)
	{
		string fullname = p->firstName + " " + p->lastName;
		if (formatLower(fullname.substr(0, size)) == formatLower(key))
		{
			HocVien* q = createHV();
			tranferHV(q, p);
			addFirstHV(KQ, q);
		}
			p = p->link;
	}
	return KQ;
}
void outputListHVsuggest(HocVien* first)
{
	if (first == NULL)
	{
		cout << "Khong co thong tin sinh vien nay!!!" << endl;
		return;
	}
	int i = 1;
	HocVien* p;
	p = first;
	cout << setw(12) << "STT" << setw(20) << "MSSV" << setw(20) << "Ho & ten dem" << setw(10) << "Ten" << setw(20) << "Ngay Sinh" << setw(11) << "Ma Lop" << setw(10) << "Diem" << endl;
	cout << "----------------------------------------------------------------------------------------------------------" << endl;
	while (p != NULL)
	{
		cout << setw(11) << i++ << "|" << setw(20) << p->id << setw(20) << p->firstName << setw(10) << p->lastName << setw(13) << p->birthDay[0] << "/" << setw(2) << p->birthDay[1] << "/" << setw(4) << p->birthDay[2] << setw(10) << p->idClass << setw(10) << p->point << endl;
		p = p->link;
	}
}
void searchSuggest(HocVien* first)
{
	char keyPress;
	string t = "";
	do
	{
		system("cls");
		cout << "Nhap ten tim kiem goi y (Enter hoac ESC de thoat): " << t << endl;
		cout << "Danh sach goi y: " << endl;
		if (t != "")
		{
			HocVien* p = findSuggest(first, t);
			outputListHVsuggest(p);
		}
		formatCusor(t);
		keyPress = _getch();
		if (keyPress == 8)
		{
			if (t.length() > 0)
				t.erase(t.length() - 1);
		}
		else
			t = t + keyPress;
	} while (keyPress != 27 && keyPress != 13);
}