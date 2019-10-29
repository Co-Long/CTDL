#include"matrix.h"
#include<time.h>
using namespace std;


Matrix::Matrix() {
	ma.resize(0);
	row = 0;
	col = 0;
}

Matrix::Matrix(int n) {
	row = n;
	col = n;
	ma.resize(row);

	for (int i = 0; i < row; i++) {
		ma[i].resize(col);
	}

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if(i==j)
				ma[i][j] = 1;
			else
				ma[i][j] = 0;
		}
	}
	
}

Matrix::Matrix(const Matrix& src) {
	this->row = src.row;
	this->col = src.col;
	this->ma.resize(row);

	for (int i = 0; i < row; i++) {
		ma[i].resize(col);
	}

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			this->ma[i][j] = src.ma[i][j];
		}
	}
	
}

Matrix::Matrix(unsigned short row, unsigned short col) {
	this->row = row;
	this->col = col;
	ma.resize(row);
	for (int i = 0; i < row; i++) {
		ma[i].resize(col, 0);
	}
}

Matrix::~Matrix() {
	for (int i = 0; i < row; i++) {
		ma[i].clear();
		ma[i].shrink_to_fit();
	}
	ma.clear();
	ma.shrink_to_fit();
}

Matrix& Matrix::operator=(const Matrix& src) {
	for (int i = 0; i < row; i++) {
		ma[i].clear();
		ma[i].shrink_to_fit();
	}
	ma.clear();
	ma.shrink_to_fit();

	this->row = src.row;
	this->col = src.col;
	this->ma.resize(row);

	for (int i = 0; i < row; i++) {
		ma[i].resize(col);
	}

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			this->ma[i][j] = src.ma[i][j];
		}
	}
	return *this;
}

void Matrix::matrixRandom() {
	srand((int)time(0));
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			float sign = rand() % 2;
			ma[i][j] = rand() % 11;
			if (sign == 0) {
				ma[i][j] = -ma[i][j];
			}
		}
	}
}

void Matrix::matrixInput() {
	if (row == 0 || col == 0) {
		cout << "Matrix is empty" << endl;
		return;
	}
		
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cout << "(" << i + 1 << "," << j + 1 << "): ";
			cin >> ma[i][j];
		}
	}
}

void Matrix::matrixInput(int row, int col) {
	//Kiểm tra nếu ma trận không rỗng thì xóa vùng nhớ cũ
	if (this->row != 0 || this->col != 0) {
		for (int i = 0; i < row; i++) {
			ma[i].clear();
			ma[i].shrink_to_fit();
		}
		ma.clear();
		ma.shrink_to_fit();
	}
	//Cấp phát vùng nhớ mới
	this->row = row;
	this->col = col;
	ma.resize(row);
	for (int i = 0; i < row; i++) {
		ma[i].resize(col, 0);
	}
	//Nhập dữ liệu
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cout << "(" << i + 1 << "," << j + 1 << "): ";
			cin >> ma[i][j];
		}
	}
}

void Matrix::matrixOutput() {
	if (row == 0 || col == 0) {
		cout << "Matrix is empty" << endl;
		return;
	}

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cout<< ma[i][j]<<"		";
		}
		cout << endl;
	}
}

unsigned short Matrix::getRow() {
	return row;
}
unsigned short Matrix::getCol() {
	return col;
}
float Matrix::getMa(int row, int col) {
	return ma[row][col];
}
void  Matrix::setMa(int row, int col, float n) {
	ma[row][col] = n;
}

void Matrix::swapRow(int row1, int row2) {
	if (row1 >= row || row2 >= row) {
		cout << "Your row is out of range" << endl;
		return;
	}
		
	for (int i = 0; i < col; i++) {
		float temp = ma[row1][i];
		ma[row1][i] = ma[row2][i];
		ma[row2][i] = temp;
	}
}

Matrix Gauss(Matrix &a) {
	Matrix g(a);
	int c = 0;

	for (int r = 0;;) {

		if (g.ma[r][c] == 0) {
			int k = r + 1;
			for (; k < g.row;k++ ) {

				if (g.ma[k][c] != 0) {
					g.swapRow(r, k);
					break;
				}
	
			}

			if(k>=g.row)
				c = c + 1;
		}

		if (r >= g.row || c >= g.col)
			break;

		if (g.ma[r][c] != 0) {
			int k = r + 1;
			for (; k < g.row; k++) {
				if (g.ma[k][c] == 0)
					continue;
				float d = g.ma[k][c] / g.ma[r][c];
				for (int j = 0; j < g.col; j++) {
					g.ma[k][j] = g.ma[k][j] - g.ma[r][j] * d;
				}
			}
		}

		c = c + 1;
		r = r + 1;
		if (r >= g.row || c >= g.col)
			break;
	}
	return g;
}

Matrix Gauss(Matrix& a, int &nswap) {
	Matrix g(a);
	int c = 0;
	nswap = 0;
	for (int r = 0;;) {

		if (g.ma[r][c] == 0) {
			int k = r + 1;
			for (; k < g.row; k++) {

				if (g.ma[k][c] != 0) {
					g.swapRow(r, k);
					nswap++;
					break;
				}

			}

			if (k >= g.row)
				c = c + 1;
		}

		if (r >= g.row || c >= g.col)
			break;

		if (g.ma[r][c] != 0) {
			int k = r + 1;
			for (; k < g.row; k++) {
				if (g.ma[k][c] == 0)
					continue;
				float d = g.ma[k][c] / g.ma[r][c];
				for (int j = 0; j < g.col; j++) {
					g.ma[k][j] = g.ma[k][j] - g.ma[r][j] * d;
				}
			}
		}

		c = c + 1;
		r = r + 1;
		if (r >= g.row || c >= g.col)
			break;
	}
	return g;
}
		
Matrix GauJor(Matrix& a) {
	Matrix g(a);
	int c = 0;

	for (int r = 0;;) {

		if (g.ma[r][c] == 0) {
			int k = r + 1;
			for (; k < g.row; k++) {

				if (g.ma[k][c] != 0) {
					g.swapRow(r, k);
					break;
				}

			}

			if (k >= g.row)
				c = c + 1;
		}

		if (r >= g.row || c >= g.col)
			break;

		if (g.ma[r][c] != 0) {
			int k = 0;
			for (; k < g.row; k++) {
				if (k != r) {
					if (g.ma[k][c] == 0)
						continue;
					float d = g.ma[k][c] / g.ma[r][c];
					float e = 1 / g.ma[r][c];
					for (int j = 0; j < g.col; j++) {
						g.ma[k][j] = g.ma[k][j] - g.ma[r][j] * d;
						g.ma[r][j] = g.ma[r][j] * e;
					}
				}
			}
		}

		c = c + 1;
		r = r + 1;
		if (r >= g.row || c >= g.col)
			break;
	}
	return g;
}

unsigned short rk(Matrix& a) {
	Matrix g(a.row, a.col);
	g = Gauss(a);
	int ra = 0;
	for (int i = 0; i < g.row; i++) {
		for (int j = 0; j < g.col; j++) {
			if (g.ma[i][j] != 0) {
				ra++;
				break;
			}
		}
	}
	return ra;
}

Matrix inverse(Matrix& a) {
	if ((a.row != a.col)|| (a.row == 0 || a.col == 0)) {
		cout << endl;
		cout << "matrix doesn't have inverse" << endl;
		return a;
	}
	unsigned short ra = rk(a);
	if (ra != a.col) {
		cout << endl;
		cout << "matrix doesn't have inverse" << endl;
		return a;
	}

	Matrix g(a);
	Matrix v(a.row);
	int c = 0;

	for (int r = 0;;) {

		if (g.ma[r][c] == 0) {
			int k = r + 1;
			for (; k < g.row; k++) {

				if (g.ma[k][c] != 0) {
					g.swapRow(r, k);
					v.swapRow(r, k);
					break;
				}

			}

			if (k >= g.row)
				c = c + 1;
		}

		if (r >= g.row || c >= g.col)
			break;

		if (g.ma[r][c] != 0) {
			int k = 0;
			for (; k < g.row; k++) {
				if (k != r) {
					if (g.ma[k][c] == 0)
						continue;
					float d = g.ma[k][c] / g.ma[r][c];
					float e = 1 / g.ma[r][c];
					for (int j = 0; j < g.col; j++) {
						g.ma[k][j] = g.ma[k][j] - g.ma[r][j] * d;
						v.ma[k][j] = v.ma[k][j] - v.ma[r][j] * d;
						g.ma[r][j] = g.ma[r][j] * e;
						v.ma[r][j] = v.ma[r][j] * e;
					}
				}
			}
		}

		c = c + 1;
		r = r + 1;
		if (r >= g.row || c >= g.col)
			break;
	}
	return v;
}

Matrix trans(Matrix& a) {
	if (a.row == 0 || a.col == 0)
		return a;
	Matrix b(a.col, a.row);
	for (int i = 0; i < b.row; i++) {
		for (int j = 0; j < b.col; j++) {
			b.ma[i][j] = a.ma[j][i];
		}
	}
	return b;
}

float det(Matrix& a) {
	if ((a.col != a.row) || (a.row == 0 || a.col == 0)) {
		cout << "unable to calculate det " << endl;
		return 0;
	}

	Matrix b(a.col, a.row);
	float d = 1;
	int nswap = 0;
	unsigned char i = 0;
	unsigned char j = 0;
	b = Gauss(a,nswap);
	
	while (i < b.row && j<b.col ) {
		d = d * b.ma[i][j];
		i++;
		j++;
	}

	if (nswap % 2 == 1) {
		return -d;
	}
	else
		return d;
	
}

Matrix multiMatrix(Matrix& a, Matrix& b) {
	Matrix s;
	if (a.col != b.row) {
		cout << endl;
		cout << "Can't multiply" << endl;
		return s;
	}
	
	Matrix g(a.row, b.col);
	for (int i = 0; i < a.row; i++) {
		for (int j = 0; j < b.col; j++) {
			float sum = 0;
			for (int k = 0; k < a.col; k++) {
				sum = sum + a.ma[i][k] * b.ma[k][j];
			}
			g.ma[i][j] = sum;
		}
	}
	return g;
}

void multiMatrix() {
	Matrix a, b;
	int r, c;

	cout << "==== Ma tran A ====" << endl;
	cout << "Row= ";
	cin >> r;
	cout << "Col= ";
	cin >> c;
	a.matrixInput(r, c);

	cout << "==== Ma tran B ====" << endl;
	cout << "Row= ";
	cin >> r;
	cout << "Col= ";
	cin >> c;
	b.matrixInput(r, c);

	cout << endl;
	a.matrixOutput();
	b.matrixOutput();
	cout << "AxB= " << endl;
	multiMatrix(a, b).matrixOutput();
}

void SLE() {
	unsigned short row, col;
	cout << "Nhap so phuong trinh: ";
	cin >> row;
	cout << "Nhap so bien: ";
	cin >> col;
	Matrix a(row, col + 1);
	Matrix b(row, col);

	//Nhập ma trận hệ số
	cout << endl;
	cout << "Nhap ma tran he so" << endl;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			float n = 0;
			cout << "(" << i + 1 << "," << j + 1 << "): ";
			cin >> n;
			a.setMa(i, j, n);
			b.setMa(i, j, n);
		}
	}
	//Nhập cột hệ số tự do
	cout << endl;
	cout << "Nhap cot he so tu do" << endl;
	for (int i = 0; i < row; i++) {
		float n = 0;
		cout << "(" << i + 1 << "," << col+1 << "): ";
		cin >> n;
		a.setMa(i, col, n);
	}
	
	unsigned short rk1, rk2;
	rk1 = rk(a);
	rk2 = rk(b);
	if ( rk1== rk2 + 1) {
		cout << endl;
		cout << "He vo nghiem" << endl;
		return;
	}
	if ((rk1 == rk2) && (rk2 < col)) {
		cout << endl;
		cout << "He co vo so nghiem" << endl;
		return;
	}

	a = GauJor(a);
	int c = 0;
	for (int r = 0; r < row; r++) {
		cout << "X" << r + 1 << "= " << a.getMa(r, col) / a.getMa(r, c)<<endl;
		c++;
		if (c >= col)
			break;
	}

}
