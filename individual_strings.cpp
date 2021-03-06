/*Индивидуальная задача №17. (7 - 8) В строке найти и вывести на экран слова, длина которых - простое
число.Вставить после первого слова, длина которого простое число, заданную
подстроку.*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <clocale>
using namespace std;
typedef void function(char *&);
typedef function* ptrfunction;
const int MAX_SIZE = 255;

void menu(char *&);
void forEach(char *&,ptrfunction);
bool isPrime(unsigned long long int);
void taskInfo(char *&);
void solveProblem(char *&);
void giveMemory(char *&);
void inputString(char *&);
void outputString(char *&);
void exit(char *&);
void freeMemory(char *);

int main() {
	setlocale(LC_ALL, "Ru");
	char *str = nullptr;
	giveMemory(str);
	menu(str);
	freeMemory(str);
	system("pause");
	return 0;
}

void menu(char *&str) {
	ptrfunction Fmenu[5] = { taskInfo, inputString, solveProblem, outputString, exit };
	int inputNumber = 0;
	while (true) {
		cout << "==============MENU==============\n";
		cout << "Enter the following operation: \n";
		cout << "0 - Task information\n";
		cout << "1 - Enter a string\n";
		cout << "2 - Solve the problem\n";
		cout << "3 - Print the string\n";
		cout << "4 - Exit\n";
		cout << "================================\n";
		cin >> inputNumber;
		if (inputNumber > -1 && inputNumber < 5) {
			forEach(str, Fmenu[inputNumber]);
		}
		else {
			cout << "Wrong operation, retry\n";
		}
	}
}

void forEach(char *&str,ptrfunction fun) {
	fun(str);
}

bool isPrime(unsigned long long int number) {
	int tmp;
	switch (number) {
	case 1: return false;
		break;
	case 2: return true;
		break;
	default:
		switch (number % 2) {
		case true: tmp = (int)(sqrt(number));
			for (int i = 3; i <= tmp; i += 2) {
				if ((number % i) > 0) {
					continue;
				}
				else {
					return false;
				}
			}
			return true;
			break;
		case false: return false;
			break;
		}
		break;
	}
	return false;
}

void taskInfo(char *&str) {
	cout << "В строке найти и вывести на экран слова, длина которых - простое число.Вставить после первого слова, длина которого простое число, заданную подстроку.\n";
}

void solveProblem(char *&str) {
	char *tmp = nullptr;
	char *substr = nullptr;
	giveMemory(tmp);
	giveMemory(substr);
	inputString(substr);
	char pat[] = " ,.?!();:";
	int len = 0, count = 0;
	char *ptr = nullptr;
	ptr = str;
	cout << "Words whose measure is prime number: ";
	while (true) {
		ptr = ptr + strspn(ptr, pat);
		len = strcspn(ptr, pat);
		if (isPrime(len)) {
			count++;
			if (count == 1) {
				strcpy(tmp, str);
				tmp[ptr - str + len] = '\0';
				str = &str[ptr - str + len];
			}
			for (char *sptr = ptr; sptr < ptr + len; sptr++) {
				cout << *sptr;
			}
			cout << " ";
		}
		if (strlen(ptr) == 0) {
			break;
		}
		ptr = ptr + len;
	}
	ptr = nullptr;
	if (count) {
		strcat(tmp, substr);
		strcat(tmp, str);
		strcpy(str, tmp);
	}
	cout << endl;
	freeMemory(tmp);
	freeMemory(substr);
}

void giveMemory(char *&str) {
	try {
		str = new char[MAX_SIZE];
	}
	catch (...) {
		cout << "Memory allocation error\n";
		system("pause");
		exit(1);
	}
}

void inputString(char *&str) {
	fflush(stdin);
	cout << "Enter the string: ";
	cin.ignore();
	cin.getline(str, MAX_SIZE);
}

void outputString(char *&str) {
	cout << str << endl;
}

void exit(char *&str) {
	exit(1);
}

void freeMemory(char *str) {
	delete[] str;
}