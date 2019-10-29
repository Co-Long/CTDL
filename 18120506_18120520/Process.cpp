#include"Process.h"
using namespace std;

void Vecmenu(unsigned short& k) {
	cout << "Chon 1 de cong 2 vector " << endl;
	cout << "Chon 2 de nhan vector voi 1 so alpha " << endl;
	cout << "Chon 3 de ve Main menu" << endl;
	cout << "Chon chuc nang: ";
	cin >> k;

	if (k == 1) {
		system("cls");
		vec v1, v2, v3;
		v1 = Input();
		v2 = Input();
		v3 = addVec(v1, v2);
		Output(v3);
		cout << endl;
	}
	else if (k == 2) {
		system("cls");
		vec v1;
		float a;
		v1 = Input();
		cout << "Nhap so alpha: ";
		cin >> a;
		multiVec(v1, a);
		cout << "vector sau khi nhan voi alpha: " << endl;
		Output(v1);
		cout << endl;
	}
	else if (k == 3)
		Mainmenu();
	else
		return;
	Vecmenu(k);
}

void Mamenu(Matrix& a, unsigned short& k) {
	cout << "Chon 0 de tao ma tran bat ky " << endl;
	cout << "Chon 1 de nhap ma tran moi " << endl;
	cout << "Chon 2 de tim ma tran chuyen vi " << endl;
	cout << "Chon 3 de tim hang cua ma tran RANK " << endl;
	cout << "Chon 4 de tim dinh thuc DET " << endl;
	cout << "Chon 5 de tim ma tran nghich dao Inverse " << endl;
	cout << "Chon 6 de tinh tich hai ma tran " << endl;
	cout << "Chon 7 de giai he phuong trinh tuyen tinh " << endl;
	cout << "Chon 8 de ve lai main menu " << endl;
	cout << "Chon chuc nang: ";
	cin >> k;

	if (a.getCol() == 0 || a.getRow() == 0)
		if (k != 0 && k != 6 && k != 7 && k != 8)
			k = 1;

	if (k == 0) {
		system("cls");
		int row, col;
		cout << "Row= ";
		cin >> row;
		cout << "Col= ";
		cin >> col;
		a.matrixRandom(row,col);
		cout << endl;
		/*a.matrixOutput();*/
	}
	else if (k == 1) {
		system("cls");
		int row, col;
		cout << "Row= ";
		cin >> row;
		cout << "Col= ";
		cin >> col;
		a.matrixInput(row, col);
		cout << endl;
		a.matrixOutput();
	}
	else if (k == 2) {
		cout << endl;
		cout << "=== Trans ===" << endl;
		trans(a).matrixOutput();
		cout << endl;
	}
	else if (k == 3) {
		cout << endl;
		cout << "=== Rank ===" << endl;
		cout << "Hang cua ma tran Rank= " << rk(a) << endl;
		cout << endl;
	}
	else if (k == 4) {
		cout << endl;
		cout << "=== Det ===" << endl;
		cout << "Dinh thuc cua ma tran la det= " << det(a) << endl;
		cout << endl;
	}
	else if (k == 5) {
		cout << endl;
		cout << "=== Inverse ===" << endl;
		cout << "Ma tran nghich dao: " << endl;
		inverse(a).matrixOutput();
		cout << endl;
	}
	else if (k == 6) {
		system("cls");
		multiMatrix();
		cout << endl;
	}
	else if (k == 7) {
		system("cls");
		SLE();
		cout << "=== System of Linear Equations ===" << endl;
		cout << endl;
	}
	else if (k == 8) {
		Mainmenu();
	}
	else
		return;
	
	Mamenu(a, k);
}

void boolMenu() {
	cout << "Chon 1 de tim da thuc toi tieu cua ham bool " << endl;
	cout << "Chon 2 de ve lai main menu " << endl;
	char c;
	cin >> c;
	if (c == '1') {
		boolSolver();
		cout << "\n";
		boolMenu();
	}
	else {
		Mainmenu();
	}
}

void Mainmenu() {
	unsigned short k = 0;
	system("cls");
	cout << "Chon 1 de tinh Vector" << endl;
	cout << "Chon 2 de tinh toan Ma Tran va gia He Phuong Trinh" << endl;
	cout << "Chon 3 de tinh toan ham Bool" << endl;
	cout << "Chon 0 de thoat chuong trinh" << endl;
	cout << "Chon chuc nang: ";
	cin >> k;
	if (k == 1) {
		system("cls");
		Vecmenu(k);
	}
	else if (k == 2) {
		system("cls");
		Matrix a;
		Mamenu(a, k);
	}
	else if (k == 3) {
		system("cls");
		boolMenu();
	}
	else
		exit(0);
}