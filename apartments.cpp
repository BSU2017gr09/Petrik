﻿/*
В объекте хранится картотека бюро обмена квартир, содержащая
сведения о каждой квартире: адрес, этаж, площадь, количество комнат.
a) Ввести заявку на обмен и произвести поиск в картотеке
подходящего варианта: при равенстве количества комнат и этажа и
различии площадей в пределах 10% вывести соответствующую
карточку, в противном случае поступившую заявку записать в
картотеку.
b) Вывести список квартир по заданному количеству комнат,
упорядочив его по площади.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <clocale>
#include <fstream>
using namespace std;

const int SIZE = 12;
const int MAX_LEN = 50;
const char *path = "apartments.dat";
int rooms = 0;

class Apartment {
private:
	char *address;
	int floor;
	int area;
	int rooms;
public:
	Apartment() : address(nullptr), floor(0), area(0), rooms(0) {
		//cout << "Сработал конструктор по умолчанию - " << this << endl;
	};

	Apartment(char *str, int flr = 0, int ar = 0, int rms = 0): address(nullptr), floor(flr), area(ar), rooms(rms)  {
		if (str != nullptr) {
			try {
				address = new char[strlen(str) + 1];
			}
			catch (...) {
				cout << "Ошибка при выделении памяти!\n";
			}
			strcpy(address, str);
		}
		//cout << "Сработал конструктор c параметром - " << this << endl;
	};

	Apartment(const Apartment &other) : address(nullptr) {
		delete[] address;
		if (other.address != nullptr) {
			try {
				address = new char[strlen(other.address) + 1];
			}
			catch (...) {
				cout << "Ошибка при выделении памяти!\n";
			}
			strcpy(address, other.address);
		}
		floor = other.floor;
		area = other.area;
		rooms = other.rooms;
		//cout << "Сработал конструктор копирования - " << this << endl;
	};

	Apartment(Apartment &&other): address(nullptr) {
		Apartment tmp(other);
		my_swap(tmp);
		//cout << "Сработал конструктор перемещения - " << this << endl;
	};

	~Apartment() {
		delete[] address;// для перестраховки address=nullptr;
		//cout << "Сработал деструктор - " << this << endl;
	};

	void my_swap(Apartment &other) {
		using std::swap;
		swap(address, other.address);
		swap(floor, other.floor);
		swap(area, other.area);
		swap(rooms, other.rooms);
	};

	Apartment operator=(const Apartment &other) {
		Apartment tmp(other);
		my_swap(tmp);
		return (*this);
	};

	Apartment operator=(const Apartment &&other) {
		Apartment tmp(other);
		my_swap(tmp);
		return (*this);
	};

	friend ostream &operator<<(ostream &outputStream, Apartment &other) {
		if (other.address) {
			outputStream << "Адрес дома: " << other.address << endl;
		}
		else {
			outputStream << "Адрес дома: неопределено" << endl;
		}
		outputStream << "Этаж: " << other.floor << endl;
		outputStream << "Площадь квартиры: " << other.area << endl;
		outputStream << "Количество комнат: " << other.rooms << endl;
		return outputStream;
	};

	friend istream &operator>>(istream &inputStream, Apartment &other) {
		char tmp[MAX_LEN];
		cout << "Адрес дома: ";
		fflush(stdin);
		inputStream.getline(tmp, MAX_LEN);
		other.setAddress(tmp);
		cout << "Этаж: ";
		inputStream >> other.floor;
		cout << "Площадь квартиры: ";
		inputStream >> other.area;
		cout << "Количество комнат: ";
		inputStream >> other.rooms;
		return inputStream;
	};

	void setAddress(char *str) {
		delete[] address; 
		try {
			address = new char[strlen(str) + 1];
		}
		catch (...) {
			cout << "Ошибка при выделении памяти!\n";
		}
		strcpy(address, str);
	};

	void setFloor(int value) {
		if (value > 0) {
			floor = value;
		}
		else {
			floor = 0;
		}
	};

	void setArea(int value) {
		if (value > 0) {
			area = value;
		}
		else {
			area = 0;
		}
	};

	void setRooms(int value) {
		if (value > 0) {
			rooms = value;
		}
		else {
			rooms = 0;
		}
	};

	char* getAddress() {
		return address;
	};

	int getFloor() {
		return floor;
	};

	int getArea() {
		return area;
	};

	int getRooms() {
		return rooms;
	};

	void save(ofstream& fout) {
		fout.write(address, strlen(address) + 1);
		fout.write((char*)&floor, sizeof(floor));
		fout.write((char*)&area, sizeof(area));
		fout.write((char*)&rooms, sizeof(rooms));
	};

	void load(ifstream& fin) {
		char tmp[MAX_LEN];
		char tmp1 = 0;
		fin.getline(tmp, MAX_LEN, '\0');
		setAddress(tmp);
		fin.get(tmp1); // не сработатет!!!!!!
		setFloor(tmp1);
		fin.get(tmp1);
		setArea(tmp1);
		fin.get(tmp1);
		setRooms(tmp1);
	};
};

typedef Apartment* fun(Apartment *, int &);
typedef fun* ptrfun;

Apartment *giveMemory();
void pushCardFile(Apartment *, Apartment, int &);
Apartment request(Apartment);
void insertionSort(Apartment *, int);
void menu(Apartment *, int &);
void forEach(Apartment *, int &, ptrfun);

Apartment* writeApartments(Apartment *, int &);
Apartment* readApartments(Apartment *, int &);
Apartment* initCardFiles(Apartment *, int &);
Apartment* printCardFiles(Apartment *, int &);
Apartment* searchCardFile(Apartment *, int &);
Apartment* getCardFilesByRooms(Apartment *, int &);
Apartment* exit(Apartment *, int &);

int main(){
	setlocale(LC_ALL, "Ru");
	int capasity = 10;
	Apartment *flats1 = nullptr;
	flats1 = giveMemory();
	menu(flats1, capasity);
	system("pause");
	return 0;
}

Apartment* writeApartments(Apartment *apartments, int &capasity) {
	ofstream fout(path, ios::out | ios::binary);
	if (fout.is_open()) {
		for (int i = 0; i < capasity; i++)
		apartments[i].save(fout);
	}
	else {
		cout << "Не удалось открыть файл!\n";
	}
	fout.close();
	return nullptr;
}

Apartment* readApartments(Apartment *apartments, int &capasity) {
	ifstream fin (path, ios::in | ios::binary);
	if (fin.is_open()) {
		for (int i = 0; i < capasity; i++) {
			apartments[i].load(fin);
		}
	}
	else {
		cout << "Не удалось открыть файл!\n";
	}
	fin.close();
	return apartments;
}

Apartment *giveMemory() {
	Apartment *arr = new Apartment[SIZE];
	return arr;
}

Apartment request(Apartment src) {
	int f = 0;
	int r = 0;
	int a = 0;
	cout << "Введите желаемый этаж: ";
	cin >> f;
	src.setFloor(f);
	cout << "Введите желаемое количество комнат: ";
	cin >> r;
	src.setRooms(r);
	cout << "Введите желаемую площадь квартиры: ";
	cin >> a;
	src.setArea(a);
	return src;
}

Apartment* initCardFiles(Apartment *arr, int &capasity) {
	char *addresses[10] = { "г. Минск, ул. Октябрьская 10а", "г. Минск, ул. Бобруйская 12", "г. Минск, пр. Независимости 100", "г. Минск, ул. Сухая 29", "г. Минск, ул. Белорусская 102б", "г. Минск, пр. Машерова 11", "г. Минск, ул. Могилёвская 38", "г. Минск, ул. Свердлова 2", "г. Минск, ул. Козлова 76", "г. Минск, ул. Сторожовская 119" };
	for (int i = 0; i < capasity; i++) {
		arr[i].setAddress(addresses[i]);
		arr[i].setFloor(rand() % 20 + 1);
		arr[i].setArea(rand() % 127 + 1);
		arr[i].setRooms(rand() % 8 + 1);
	}
	return arr;
}

Apartment* printCardFiles(Apartment *apartments, int &capasity) {
	for (int i = 0; i < capasity; i++) {
		cout << "\n==========================================\n";
		cout << apartments[i];
		cout << "==========================================\n";
	}
	return nullptr;
}

Apartment* searchCardFile(Apartment *arr, int &capasity) {
	Apartment *tmp = nullptr;
	Apartment src;
	tmp = giveMemory();
	src = request(src);
	int j = 0;
	for (int i = 0; i < capasity; i++) {
		double h = arr[i].getArea() * 0.1;
		if ((arr[i].getFloor() == src.getFloor()) && (arr[i].getRooms() == src.getRooms()) && (abs(arr[i].getArea() - src.getArea()) <= h)) {
			 tmp[j] = arr[i];
			 j++;
		}
	}
	if (j == 0) {
		pushCardFile(arr, src, capasity);
		return arr;
	}
	else {
		printCardFiles(tmp, j);
		return tmp;
	}
}

void pushCardFile(Apartment *arr, Apartment src, int &capasity) {
	if (capasity < SIZE) {
		arr[capasity] = src;
		capasity++;
		cout << "Поиск не дал результатов! Ваша заявка внесена в картотеку.\n";
	}
	else {
		cout << "Поиск не дал результатов! В картотеке недостаточно места для добавления вашей заявки!\n";	
	}
}

Apartment* getCardFilesByRooms(Apartment *arr, int &capasity) {
	Apartment *tmp = nullptr;
	tmp = giveMemory();
	int tmpCapasity = 0;
	cout << "Введите число комнат: ";
	cin >> rooms;
	for (int i = 0; i < capasity; i++) {
		if (arr[i].getRooms() == rooms) {
			tmp[tmpCapasity] = arr[i];
			tmpCapasity++;
		}
	}
	insertionSort(tmp, tmpCapasity);
	printCardFiles(tmp, tmpCapasity);
	return tmp;
}

Apartment* exit(Apartment *apartments, int &capasity) {
	exit(1);
}

void menu(Apartment *apartments, int &capasity) {
	ptrfun Fmenu[7] = { writeApartments, readApartments, initCardFiles, printCardFiles, searchCardFile, getCardFilesByRooms, exit };
	int inputNum = 0;
	while (true) {
		cout << "############################################  MENU  ############################################\n";
		cout << "Выберите одну из следующих операций: \n";
		cout << "1 - Запись данных картотеки в файл\n";
		cout << "2 - Чтение данных картотеки из файла\n";
		cout << "3 - Инициализировать картотеку случайными данными\n";
		cout << "4 - Вывод на экран данных картотеки\n";
		cout << "5 - Найти подходящую квартиру в картотеке\n";
		cout << "6 - Получить квартиры с заданными числом комнат, отсортированных по площади\n";
		cout << "7 - Выход\n";
		cout << "################################################################################################\n";
		cout << "Ввод: ";
		cin >> inputNum;
		if (inputNum > 0 && inputNum < 8) {
			forEach(apartments, capasity, Fmenu[inputNum - 1]);
		}
		else {
			cout << "Неверная операция, попробуйте ещё раз\n";
		}
	}
}

void forEach(Apartment *apartments, int &capasity, ptrfun funс) {
	funс(apartments, capasity);
}

void insertionSort(Apartment *arr, int tmpCapasity) {
	Apartment key;
	int j;
	for (int i = 1; i < tmpCapasity; i++) {
		key = arr[i];
		j = i - 1;
		while ((j > -1) && (arr[j].getArea() > key.getArea())) {
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = key;
	}
}
