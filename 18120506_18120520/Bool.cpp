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

//Chuyen tu Normal term sang Minterm va Bin
//input: dang normal term (vd: ab + bc), output: minterm va bin tuong ung
void toMinTerm(string str, vector<int>& minterm, vector<string>& bins) {
	vector<string> stack(0);
	vector<string> stackBin(0);
	string temp = "";

	for (int i = 0; i < str.length(); i++) {
		if (str[i] != ' ' && str[i] != '+') {
			temp += str[i];
		}
		else {
			if (temp == "") continue;
			stack.push_back(temp);
			temp = "";
		}
	}
	stack.push_back(temp);

	while (stack.size() > 0) {
		temp = stack.back();
		stack.pop_back();
		string bin = "";

		for (int i = 0, j = 0; i < temp.length(); j++, i++) {
			if (temp[i] != '\'') {
				if (temp[i] == token[j] && temp[i + 1] != '\'') {
					bin += '1';
				}
				else if (temp[i] == token[j] && temp[i + 1] == '\'') {
					bin += '0';
					i++;
				}
				else {
					bin += '2';
					i--;
				}
			}
		}

		while (bin.length() < n) {
			bin += '2';
		}

		vector<string> binList = binGenerator(bin);
		for (int i = 0; i < binList.size(); i++) {
			minterm.push_back(binToDec(binList[i]));
			bins.push_back(binList[i]);
		}
	}
}

//Phan chia cac group Bin theo so 1
//Input: list Bin, output: List group cac bin da phan chia
vector<vector<string>> divideToGroup(vector<string> bin) {
	vector<vector<string>> group(10);
	int count = 0;

	for (int i = 0; i < bin.size(); i++) {
		count = 0;
		for (int j = 0; j < bin[i].length(); j++) {
			if (bin[i][j] == '1') count++;
		}

		group[count].push_back(bin[i]);
	}

	return group;
}

//So sanh 2 Bin tim 1 bit duy nhat khac nhau (vd: 0101, 0001 => 0_01)
//Input: 2 Bin can so sanh, output: tra ve vi tri khac biet duy nhat (neu ko co tra ve -1)
int compareBit(string a, string b) {
	int index = -1;

	for (int i = 0; i < a.length(); i++) {
		if (a[i] != b[i]) {
			if (index == -1) index = i;
			else return -1;
		}
	}

	return index;
}

//Danh dau bit duy nhat khac nhau trong 2 bin giua cac group
//Input: Group cac Bin, output: Nhung Bin da doc danh dau va ko danh dau
vector<string> markBit(vector<vector<string>> group) {
	vector<string> result(0);
	unordered_set<string> set;

	for (int i = 0; i < group.size() - 1; i++) {
		if (group[i].size() == 0 || group[i + 1].size() == 0) {
			continue;
		}

		int index;
		for (int j = 0; j < group[i].size(); j++) {
			for (int k = 0; k < group[i + 1].size(); k++) {
				index = compareBit(group[i][j], group[i + 1][k]);
				if (index != -1) {
					string temp = group[i][j];
					temp[index] = '2';
					set.insert(group[i][j]);
					set.insert(group[i + 1][k]);
					result.push_back(temp);
				}
			}
		}
	}

	//Them cac Bin con lai vao result
	for (int i = 0; i < group.size(); i++) {
		for (int j = 0; j < group[i].size(); j++) {
			if (set.find(group[i][j]) == set.end()) {
				result.push_back(group[i][j]);
			}
		}
	}

	return result;
}