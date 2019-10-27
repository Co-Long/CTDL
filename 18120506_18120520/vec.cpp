#include"vec.h"

vec Input() {
	vec v;
	unsigned short number = 0;
	cout << "Nhap so phan tu: ";
	cin >> number;
	v.resize(number);
	cout << "Nhap vector: " << endl;
	for (int i = 0; i < v.size(); i++) {
		cin >> v[i];
	}
	return v;
}

void Output(vec& v) {
	cout << endl;
	for (int i = 0; i < v.size(); i++) {
		cout << v[i] << " ";
	}
}

vec addVec(vec& a, vec& b) {
	vec c;
	c.resize(0);
	if (a.size() != b.size())
		return c;
	c.resize(a.size());
	for (int i = 0; i < a.size(); i++) {
		c[i] = a[i] + b[i];
	}
	return c;
}

void multiVec(vec& v, float a) {
	for (int i = 0; i < v.size(); i++) {
		v[i] = v[i] * a;
	}
}