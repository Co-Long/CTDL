#pragma once
#include<iostream>
#include<vector>
using namespace std;

typedef vector<float> vec;

vec Input();
void Output(vec& v);
vec addVec(vec& a, vec& b);	//Cộng 2 vector
void multiVec(vec& v, float a);	//Nhân vector với một số thực alpha