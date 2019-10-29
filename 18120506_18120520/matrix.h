﻿#pragma once
#include<iostream>
#include<vector>
#include"vec.h"

using namespace std;

typedef vector<vec> matrix;

class Matrix
{
private:
	matrix ma;
	unsigned short row;
	unsigned short col;
public:
	
	Matrix();
	Matrix(int n);	//Tạo ma trận đơn vị cấp n
	Matrix(const Matrix& src);
	Matrix(unsigned short row, unsigned short col);	//Tạo ma trận kích thước width x height
	~Matrix();

	Matrix& operator=(const Matrix& src);

	unsigned short getRow();
	unsigned short getCol();
	float getMa(unsigned short row, unsigned short col);
	void setMa(unsigned short row, unsigned short col, float n);

	void matrixRandom(unsigned short row, unsigned short col);  //Tạo giá trị ngẫu nhiên cho ma trận
	void matrixInput();	//Nhập giá trị cho ma trận
	void matrixInput(unsigned short row, unsigned short col);
	void matrixOutput();

	void swapRow(unsigned short row1, unsigned short row2);	//Hoán vị 2 dòng của ma trận

	friend Matrix Gauss(Matrix &a);		//Trả về ma trận bậc thang
	friend Matrix Gauss(Matrix& a, int &nswap);		//Trả về ma trận bậc thang và số lần hoán vị dòng
	friend Matrix GauJor(Matrix& a);	//Trả về ma trận bậc thang rút gọn
	friend Matrix inverse(Matrix& a);
	friend Matrix trans(Matrix& a);		//Trả về ma trận chuyển vị 
	friend Matrix multiMatrix(Matrix& a, Matrix& b);	//Nhân 2 ma trận
	friend unsigned short rk(Matrix& a);	//Trả về hạng của ma trận
	friend float det(Matrix& a);
};

void multiMatrix();
void SLE();	// System of Linear Equations




