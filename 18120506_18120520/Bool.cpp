#include "Bool.h"
#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <unordered_set>
#include <stdlib.h>
#include <cmath>
using namespace std;

char token[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
int n;

// Chuyen Bin thanh dang Decimal (Su dung de chuyen bin sang minterm)
// input: chuoi Bin, output: So thap phan cua bin do 
int binToDec(string bin) {
	int dec = 0;
	for (int i = bin.length() - 1; i > -1; i--) {
		dec += (bin[i] - 48) * pow(2, bin.length() - 1 - i);
	}
	return dec;
}

// Chuyen Decimal sang Bin (Su dung de chuyen minterm sang bin)
// Input: So thap phan, output: chuoi bin cua so thap phan
string decToBin(int dec) {
	string bin = "";

	do {
		bin = (char)((dec & 1) + 48) + bin;
		dec >>= 1;
	} while (dec);

	while (bin.length() < n) {
		bin = '0' + bin;
	}

	return bin;
}

//Xoa cac Bin hoac Minterm trung nhau
//input: 1 vector cac bin hoac minterm, output: ko co
template <class T>
void deleteRepeat(vector<T>& a) {
	for (int i = 0; i < a.size(); i++) {
		for (int j = i + 1; j < a.size(); j++) {
			if (a[i] == a[j]) {
				for (int k = j; k < a.size() - 1; k++) {
					a[k] = a[k + 1];
				}
				a.pop_back();
				j--;
			}
		}
	}
}

//Ket hop 2 vector thanh 1
// Input: 2 vector can merge, output: merged vector
vector<string> mergeVector(vector<string> a, vector<string> b) {
	for (int i = 0; i < a.size(); i++) {
		b.push_back(a[i]);
	}

	return b;
}

//Generate cac Bin tu Bin bi khuyet (vd: 0_11 => 0111, 0011)
//Input: chuoi Bin bi khuyet, output: vector chua nhung chuoi bin hoan chinh
vector<string> binGenerator(string bin) {
	for (int i = 0; i < bin.length(); i++) {
		if (bin[i] == '2') {
			bin[i] = '0';
			vector<string> a = binGenerator(bin);
			bin[i] = '1';
			vector<string> b = binGenerator(bin);

			return mergeVector(a, b);
		}
	}

	vector<string> temp = { bin };
	return temp;
}

