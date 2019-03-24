#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Qint
{
private:
	int a1, a2, a3, a4;
public:
	//hung
	Qint();
	~Qint();

	// binh
	Qint operator+(Qint x);
	Qint operator-(Qint x);
	Qint operator*(Qint x);// hung

	Qint operator / (Qint x);// quang huy

	bool operator == (Qint x);
	bool operator >= (Qint x);
	bool operator <= (Qint x);
	bool operator > (Qint x);
	bool operator < (Qint x);

	// van huy
	Qint operator &(Qint x);
	Qint operator | (Qint x);
	Qint operator ^(Qint x);
	Qint operator ~();

	//hung
	Qint operator <<(Qint a);
	Qint operator >> (Qint a);
	Qint Qint_rol();
	Qint Qint_ror();
};


void ScanQint(Qint &x) {};
void PrintQint(Qint x) {};// anh huy
void ScanQintFile(ifstream &is, Qint &x) {};//hung


//nhap
bool* StringDecToBin(string dec) {}; //binh xong
bool* StringHexToBin(char* hex) {};//anh huy

//Trung gian
Qint BinToQint(bool* bit) {};
bool* QintToBin(Qint x) {};

//xuat
char * BinToHex(bool bit[]) {}; // anh huy
string BinToDec(bool bit[]) {};// van huy


Qint::Qint() {
	a1 = 0;
	a2 = 0;
	a3 = 0;
	a4 = 0;
}

Qint Qint::operator << (Qint a) {
	bool *dummy = QintToBin(*this);
	bool *dummy2 = QintToBin(a);
	int b = 0;
	for (int i = 0; i < 128; i++)
		if (dummy[i] == 1) {
			for (int j = i; j < 128; j++)
				b += pow(2, i);
			break;
		}
	for (int i = 0; i < 128; i++) {
		if (dummy[i] == 1) {
			for (int j = i; j < 128; j++)
				dummy[j - b] = dummy[j];
			for (int j = b; j >= 0; j--) {
				dummy[127 - b] = 0;
			}
			break;
		}
	}
	*this = BinToQint(dummy);
	return *this;
}

Qint Qint::operator >> (Qint a) {
	bool *dummy = QintToBin(*this);
	bool *dummy2 = QintToBin(a);
	int b = 0;
	for (int i = 0; i < 128;i++)
		if (dummy[i] == 1) {
			for (int j = i; j < 128; j++)
				b += pow(2, i);
			break;
		}
	for (int i = b; i < 128; i++) {
		dummy[127 - i - b] = dummy[127 -i];
	}
	for (int i = 0; i < b; i++)
		dummy[i] = 0;
	*this = BinToQint(dummy);
	return *this;
}

Qint Qint::Qint_rol() {
	bool *dummy = QintToBin(*this);
	bool kq[128] = { 0 };
	kq[127] = dummy[0];
	for (int i =1; i < 128; i++) {
		kq[127 - i] = dummy[127 - i + 1];
	}
	*this = BinToQint(kq);
	return *this;
}

Qint Qint::Qint_ror() {
	bool *dummy = QintToBin(*this);
	bool kq[128] = { 0 };
	kq[0] = dummy[127];
	for (int i = 1; i < 128; i++) {
		kq[i] = dummy[i - 1];
	}
	*this = BinToQint(kq);
	return *this;
}

void ScanQintFile(ifstream is, ofstream &os) {
	string s;
	string opr1;
	string opr2;
	string sign;
	char p1 = 0, p2 = 0;
	is.open("input.txt", ios::in);
	getline(is, s);
	p1 = s[0];
	int i;
	if (s[3] == ' ' && s[2] == '2') {
		p2 = s[2];
		i = 4;
	}
	else {
		if (s[4] = ' ' && s[2] == '1') {
			p2 = s[2];
			p2 += s[3];
			i = 5;
		}
		else
			i = 2;
	}
	for (i; s[i] != ' '; i++) {
		opr1 += s[i];
	}
	i++;
	if (i >= s.length())
		return;
	for (i; s[i] != ' '; i++) {
		sign += s[i];
	}
	i++;
	if (i >= s.length())
		return;
	for (i; i < s.length(); i++) {
		opr2 += s[i];
	}

	Qint b1;
	Qint b2;
	Qint kq;
	if (p1 == 2) {
		bool bit1[128] = { 0 };
		bool bit2[128] = { 0 };
		for (int j = 0; j < opr1.length(); j++)
			bit1[127 - i] = opr1[opr1.length() - 1 - i];
		for (int j = 0; j < opr2.length(); j++)
			bit2[127 - i] = opr1[opr2.length() - 1 - i];
		b1 = BinToQint(bit1);
		b2 = BinToQint(bit2);
	}


	if (p1 == 16) {
		char hex1[32] = { 0 };
		char hex2[32] = { 0 };
		for (int j = 0; j < opr1.length(); j++)
			hex1[31 - i] = opr1[opr1.length() - 1 - i];
		for (int j = 0; j < opr2.length(); j++)
			hex2[31 - i] = opr2[opr2.length() - 1 - i];
		bool *bit1 = StringHexToBin(hex1);
		bool *bit2 = StringHexToBin(hex2);
		b1 = BinToQint(bit1);
		b2 = BinToQint(bit2);
	}

	if (p1 == 10) {
		bool *bit1 = StringDecToBin(opr1);
		bool *bit2 = StringDecToBin(opr2);
		b1 = BinToQint(bit1);
		b2 = BinToQint(bit2);
	}

	if (sign == "+")
		kq = b1 + b2;
	if (sign == "-")
		kq = b1 - b2;
	if (sign == "*")
		kq = b1 * b2;
	if (sign == "/")
		kq = b1 / b2;
	if (sign == "<<")
		kq = b1 << b2;
	if (sign == ">>")
		kq = b1 >> b2;
	if (sign == "ror")
		kq = b1.Qint_ror();
	if (sign == "rol")
		kq = b1.Qint_rol();

	bool* kqbit;
	kqbit = QintToBin(kq);
	os.open("output.txt", ios::out);

	if ((p1 == 2 && p2 == 0) | p2 == 2) {
		for (int i = 0; i < 128; i++)
			os << kqbit[i];
	}

	if ((p1 == 10 && p2 == 0) | p2 == 10) {
		string kqdec = BinToDec(kqbit);
		os << kqdec;
	}

	if ((p1 == 16 && p2 == 0) | p2 == 16) {
		char *kqhex = BinToHex(kqbit);
		for (int i = 0; i < 32; i++)
			os << kqhex[i];
	}


	os.close();

	return;
}


void main() {
	string s;
	string sign;
	string opr1;
	string opr2;
	fstream is;
	char p1 = 0, p2 = 0;
	is.open("input.txt", ios::in);
	getline(is, s);
	is.close();
	cout << s << endl;
	p1 = s[0];
	int i;
	if (s[3] == ' ' && s[2] == '2') {
		p2 = s[2];
		i = 4;
	}
	else {
		if (s[4] = ' ' && s[2] == '1') {
			p2 = s[2];
			p2 += s[3];
			i = 5;
		}
		else
			i = 2;
	}
	for (i; s[i] != ' '; i++) {
		opr1 += s[i];
	}
	i++;
	if (i >= s.length())
		return;
	for (i; s[i] != ' '; i++) {
		sign += s[i];
	}
	i++;
	if (i >= s.length())
		return;
	for (i; i < s.length(); i++) {
		opr2 += s[i];
	}


	system("pause");
}
