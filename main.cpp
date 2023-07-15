#include<iostream>
#include "QLSV.h"
using namespace std;
void runMenu(HocVien*& dsHV, int& slhv, Class*& dsLop, int& slclass);
void menu();
void menuTimKiem();
void menuSapXep();
void menuTypeSapXep();
int main()
{
	HocVien* dsHV;
	Class* dsLop;
	initHV(dsHV);
	initClass(dsLop);
	int slhv = 0, slclass = 0;
	runMenu(dsHV, slhv, dsLop, slclass);
	system("pause");
	return 0;
}
void menu()
{
	cout << "\n\t\t\tGiao vien huong dan: ThS.NCS. Vo Thi Hong Tuyet\n\n";
	cout << "=================================== QUAN LY HOC VIEN ====================================\n";
	cout << " 1. Lay du lieu lop va hoc vien tu file\n";
	cout << " 2. Them 1 hoc vien vao danh sach (nhap tu ban phim).\n";
	cout << " 3. Tim kiem thong tin hoc vien.\n";
	cout << " 4. In danh sach lop.\n";
	cout << " 5. In toan bo hoc vien.\n";
	cout << " 6. In hoc vien theo lop.\n";
	cout << " 7. In nhung hoc vien diem cao nhat.\n";
	cout << " 8. In hoc vien o lop co hoc phi cao nhat.\n";
	cout << " 9. Sap xep (HeapSort/MergeSort/CoutingSort).\n";
	cout << "10. In thong tin hoc vien co diem chua dat (<5) & sap xep giam dan theo ten hoc vien.\n";
	cout << "11. In ra danh sach hoc bong (diem>=8) & ghi ra file dshocbong.txt.\n";
	cout << "12. Tim kiem ten co goi y.\n";
	cout << " 0. Thoat\n";
	cout << "-----------------------------------------------------------------------------------------\n";

}
void menuTimKiem()
{
	cout << "========================= MENU TIM KIEM HOC VIEN =========================\n";
	cout << " 1. Tim kiem theo ten lop\n";
	cout << " 2. Tim kiem theo ma hoc vien\n";
	cout << " 3. Tim kiem theo nam sinh\n";
	cout << " 0. Thoat\n";
	cout << "--------------------------------------------------------------------------\n";
}
void menuSapXep()
{
	cout << "========================== MENU SAP XEP HOC VIEN =========================\n";
	cout << " 1. Sap xep ma lop giam dan va hoc vien tung lop giam dan theo diem.\n";
	cout << " 2. Sap xep theo ten toan bo Hoc Vien giam dan.\n";
	cout << " 3. Sap xep theo diem so toan bo Hoc Vien giam dan.\n";
	cout << " 0. Thoat\n";
	cout << "--------------------------------------------------------------------------\n";
}
void menuTypeSapXep()
{
	cout << "========================== MENU SAP XEP HOC VIEN =========================\n";
	cout << " 1. HeapSort.\n";
	cout << " 2. MergeSort.\n";
	cout << " 3. CountingSort.\n";
	cout << " 0. Thoat\n";
	cout << "--------------------------------------------------------------------------\n";
}
void runMenu(HocVien*& dsHV, int& slhv, Class*& dsLop, int& slclass)
{
	bool KTreadfile = false;
	int n;
	do
	{
		system("cls");
		menu();
		do
		{
			cout << "Nhap lua chon (chi nhan phim so va enter): ";
			getNulchar(n);
			if (n < 0 || n>12)
				cout << "Lua chon cua ban khong co trong danh sach!!!" << endl;
		} while (n < 0 || n>12);
		system("cls");
		switch (n)
		{
		case 1:
			if (KTreadfile == false)
			{
				inputClassFromFile(dsLop, slclass);
				inputHVFromFile(dsHV, slhv, dsLop);
				KTreadfile = true;
			}
			else
				cout << "Da doc file truoc do!!!" << endl;
			break;
		case 2:
			cout << "Nhap cac muc sau:" << endl;
			inputFromKeyboard(dsHV, slhv, dsLop);
			break;
		case 3:
			if (dsLop == NULL || dsHV == NULL)
			{
				cout << "Hay doc file de lay du lieu truoc!!!\n";
				break;
			}
			int i;
			do
			{
				system("cls");
				menuTimKiem();
				do
				{
					cout << "Nhap lua chon (chi nhan phim so va enter): ";
					getNulchar(i);
					if (i < 0 || i > 3)
						cout << "Lua chon cua ban khong co trong danh sach!!!" << endl;
				} while (i < 0 || i > 3);
				system("cls");
				switch (i)
				{
				case 1:
					searchHVbyNameClass(dsLop);
					system("pause");
					break;
				case 2:
					searchHVbyIdHV(dsHV);
					system("pause");
					break;
				case 3:
					searchHVbyBirthday(dsHV);
					system("pause");
					break;
				case 0:
					i = 0;
					break;
				}
			} while (i > 0 && i <= 3);
			break;
		case 4:
			if (dsLop == NULL || dsHV == NULL)
			{
				cout << "Hay doc file de lay du lieu truoc!!!\n";
				break;
			}
			cout << "\n\t\t\t\t\t\tDANH SACH LOP\n\n";
			outputListClass(dsLop);
			break;
		case 5:
			if (dsLop == NULL || dsHV == NULL)
			{
				cout << "Hay doc file de lay du lieu truoc!!!\n";
				break;
			}
			cout << "\n\t\t\t\t\t DANH SACH HOC VIEN\n\n";
			outputListHV(dsHV);
			break;
		case 6:
			if (dsLop == NULL || dsHV == NULL)
			{
				cout << "Hay doc file de lay du lieu truoc!!!\n";
				break;
			}
			cout << "\n\t\t\t\tDANH SACH HOC VIEN THEO LOP\n\n";
			outputHocVienOfClass(dsLop);
			break;
		case 7:
			if (dsLop == NULL || dsHV == NULL)
			{
				cout << "Hay doc file de lay du lieu truoc!!!\n";
				break;
			}
			cout << "\n\t\t\t DANH SACH HOC VIEN DIEM CAO NHAT\n\n";
			outputHocVienMax(dsHV);
			break;
		case 8:
			if (dsLop == NULL || dsHV == NULL)
			{
				cout << "Hay doc file de lay du lieu truoc!!!\n";
				break;
			}
			cout << "\n\t\t\t\t\t\tLOP HOC PHI CAO NHAT\n\n";
			ouputMaxFeeHocVien(dsLop);
			break;
		case 9:
			if (dsLop == NULL || dsHV == NULL)
			{
				cout << "Hay doc file de lay du lieu truoc!!!\n";
				break;
			}
			int e;
			do
			{
				system("cls");
				menuSapXep();
				do
				{
					cout << "Nhap lua chon (chi nhan phim so va enter): ";
					getNulchar(e);
					if (e < 0 || e > 3)
						cout << "Lua chon cua ban khong co trong danh sach!!!" << endl;
				} while (e < 0 || e > 3);
				system("cls");
				switch (e)
				{
				case 1:
					int e1;
					do
					{
						system("cls");
						menuTypeSapXep();
						do
						{
							cout << "Nhap lua chon: ";
							getNulchar(e1);
							if (e1 < 0 || e1 > 3)
								cout << "Lua chon cua ban khong co trong danh sach!!!" << endl;
						} while (e1 < 0 || e1 > 3);
						system("cls");
						switch (e1)
						{
						case 1:
							HeapSortIdClass(dsLop, slclass);
							HeapSortPointHVofClass(dsLop);
							outputHocVienOfClass(dsLop);
							system("pause");
							break;
						case 2:
						{
							dsLop = mergeSortIdClass(dsLop, slclass);
							mergeSortPointHVofClass(dsLop);
							outputHocVienOfClass(dsLop);
							system("pause");
							break;
						}
						case 3:
						{
							dsLop = CountingSortIdClass(dsLop);
							countingSortHVofClass(dsLop);
							outputHocVienOfClass(dsLop);
							system("pause");
							break;
						}
						case 0:
							e1 = 0;
							break;
						}
					} while (e1 != 0);
					break;
				case 2:
					int e2;
					do
					{
						system("cls");
						menuTypeSapXep();
						do
						{
							cout << "Nhap lua chon: ";
							getNulchar(e2);
							if (e2 < 0 || e2 > 3)
								cout << "Lua chon cua ban khong co trong danh sach!!!" << endl;
						} while (e2 < 0 || e2 > 3);
						system("cls");
						switch (e2)
						{
						case 1:
							HeapSortNameHV(dsHV, slhv);
							outputListHV(dsHV);
							system("pause");
							break;
						case 2:
						{
							dsHV = mergeSortNameHV(dsHV, slhv);
							outputListHV(dsHV);
							system("pause");
							break;
						}
						case 3:
						{
							dsHV = CountingSortNameHV(dsHV);
							outputListHV(dsHV);
							system("pause");
							break;
						}
						case 0:
							e2 = 0;
							break;
						}
					} while (e2 != 0);
					break;
				case 3:
					int e3;
					do
					{
						system("cls");
						menuTypeSapXep();
						do
						{
							cout << "Nhap lua chon: ";
							getNulchar(e3);
							if (e3 < 0 || e3 > 3)
								cout << "Lua chon cua ban khong co trong danh sach!!!" << endl;
						} while (e3 < 0 || e3 > 3);
						system("cls");
						switch (e3)
						{
						case 1:
							HeapSortHV(dsHV, slhv);
							outputListHV(dsHV);
							system("pause");
							break;
						case 2:
						{
							dsHV = mergeSortPointHV(dsHV, slhv);
							outputListHV(dsHV);
							system("pause");
							break;
						}
						case 3:
						{
							dsHV = countingSortHV(dsHV);
							outputListHV(dsHV);
							system("pause");
							break;
						}
						case 0:
							e3 = 0;
							break;
						}
					} while (e3 != 0);
					break;
				case 0:
					e = 0;
					break;
				}
			} while (e != 0);
			break;
		case 10:
			if (dsLop == NULL || dsHV == NULL)
			{
				cout << "Hay doc file de lay du lieu truoc!!!\n";
				break;
			}
			outputHVbad(dsHV);
			break;
		case 11:
			if (dsLop == NULL || dsHV == NULL)
			{
				cout << "Hay doc file de lay du lieu truoc!!!\n";
				break;
			}
			outputHVgood(dsHV);
			break;
		case 12:
			if (dsHV == NULL)
			{
				cout << "Hay tien hanh doc file truoc!!!" << endl;
				break;
			}
			searchSuggest(dsHV);
			break;
		case 0:
			char t;
			cout << "Ban muon thoat?(y/n)\n";
			cin >> t;
			if (t == 'y' || t == 'Y')
				return;
			break;
		}
		system("pause");
	} while (1);
}
