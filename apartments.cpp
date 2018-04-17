/*
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
#include <clocale>
using namespace std;

const int SIZE = 30;

class Apartment {
private:
	char *address;
	int floor;
	double area;
	unsigned int rooms;
public:
	Apartment() : address(nullptr), floor(0), area(0.0), rooms(0) {
		//cout << "Сработал конструктор по умолчанию - " << this << endl;
	};

	Apartment(char *str, int flr = 0, double ar = 0.0, unsigned int rms = 0): address(nullptr), floor(flr), area(ar), rooms(rms)  {
		try {
			address = new char[strlen(str) + 1];
		}
		catch (...) {
			cout << "Ошибка при выделении памяти!\n";
		}
		strcpy(address, str);
		//cout << "Сработал конструктор c параметром - " << this << endl;
	};

	Apartment(const Apartment &other): address(nullptr) {
		delete[] address;
		try {
			address = new char[strlen(other.address) + 1];
		}
		catch (...) {
			cout << "Ошибка при выделении памяти!\n";
		}
		strcpy(address, other.address);
		floor = other.floor;
		area = other.area;
		rooms = other.rooms;
		//cout << "Сработал конструктор копирования - " << this << endl;
	};

	Apartment(const Apartment &&other): address(nullptr) {
		delete[] address;
		try {
			address = new char[strlen(other.address) + 1];
		}
		catch (...) {
			cout << "Ошибка при выделении памяти!\n";
		}
		strcpy(address, other.address);
		floor = other.floor;
		area = other.area;
		rooms = other.rooms;
		//cout << "Сработал конструктор перемещения - " << this << endl;
	};

	~Apartment() {
		delete[] address;
		//cout << "Сработал деструктор - " << this << endl;
	};

	Apartment operator=(const Apartment &other) {
		delete[] address;
		if (this != &other) {
			try {
				address = new char[strlen(other.address) + 1];
			}
			catch (...) {
				cout << "Ошибка при выделении памяти!\n";
			}
			strcpy(address, other.address);
			floor = other.floor;
			area = other.area;
			rooms = other.rooms;
			return (*this);
		}
		else {
			return (*this);
		}
	};

	Apartment operator=(const Apartment &&other) {
		delete[] address;
		if (this != &other) {
			try {
				address = new char[strlen(other.address) + 1];
			}
			catch (...) {
				cout << "Ошибка при выделении памяти!\n";
			}
			strcpy(address, other.address);
			floor = other.floor;
			area = other.area;
			rooms = other.rooms;
			return (*this);
		}
		else {
			return (*this);
		}
	};

	friend ostream &operator<<(ostream &outputStream, Apartment &other) {
		outputStream << "Адрес дома: " << other.address << endl;
		outputStream << "Этаж: " << other.floor << endl;
		outputStream << "Площадь квартиры: " << other.area << endl;
		outputStream << "Количество комнат: " << other.rooms << endl;
		return outputStream;
	};

	friend istream &operator>>(istream &inputStream, Apartment &other) {
		const int MAX_LEN = 50;
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
		floor = value;
	};

	void setArea(double value) {
		area = value;
	};

	void setRooms(unsigned int value) {
		rooms = value;
	};

	char* getAddress() {
		return address;
	};

	int getFloor() {
		return floor;
	};

	double getArea() {
		return area;
	};

	unsigned int getRooms() {
		return rooms;
	};
};

char **giveMemoryPtrArr();
Apartment *giveMemory();
void request(Apartment &);
void initCardFiles(Apartment *, int, char **);
void printCardFiles(Apartment *, int);
void searchCardFile(Apartment *, Apartment, int &);
void pushCardFile(Apartment *, Apartment, int &);
Apartment *getCardFilesByRooms(Apartment *, int, int);
void insertionSort(Apartment *, int);

int main(){
	int capasity = 10;
	int rooms = 0;
	char dft[] = "default";
	setlocale(LC_ALL, "Ru");
	char **chptr = nullptr;
	Apartment *arr = nullptr;
	Apartment *tmp = nullptr;
	Apartment src(dft);
	request(src);
	//cout << "Введите количество комнат для поиска подходящих квартир: ";
	//cin >> rooms;
	chptr = giveMemoryPtrArr();
	arr = giveMemory();
	initCardFiles(arr, capasity, chptr);
	//tmp = getCardFilesByRooms(arr, rooms, capasity);	
	searchCardFile(arr, src, capasity);
	printCardFiles(arr, capasity);
	system("pause");
	return 0;
}

char **giveMemoryPtrArr() {
	char **chptr = new char*[10];
	chptr[0] = "г. Минск, ул. Октябрьская 10а";
	chptr[1] = "г. Минск, ул. Бобруйская 12";
	chptr[2] = "г. Минск, пр. Независимости 100";
	chptr[3] = "г. Минск, ул. Сухая 29";
	chptr[4] = "г. Минск, ул. Белорусская 102б";
	chptr[5] = "г. Минск, пр. Машерова 11";
	chptr[6] = "г. Минск, ул. Могилёвская 38";
	chptr[7] = "г. Минск, ул. Свердлова 2";
	chptr[8] = "г. Минск, ул. Козлова 76";
	chptr[9] = "г. Минск, ул. Сторожовская 119";
	return chptr;
}

Apartment *giveMemory() {
	Apartment *arr = new Apartment[SIZE];
	return arr;
}

void request(Apartment &src) {
	int f = 0;
	int r = 0;
	double a = 0.0;
	cout << "Введите желаемый этаж: ";
	cin >> f;
	src.setFloor(f);
	cout << "Введите желаемое количество комнат: ";
	cin >> r;
	src.setRooms(r);
	cout << "Введите желаемую площадь квартиры: ";
	cin >> a;
	src.setArea(a);
}

void initCardFiles(Apartment *arr, int capasity, char **chptr) {
	for (int i = 0; i < capasity; i++) {
		arr[i].setAddress(chptr[i]);
		arr[i].setFloor(rand() % 19 + 1);
		arr[i].setArea(double(rand()) / RAND_MAX * 280.0 + 20.0);
		arr[i].setRooms(rand() % 8 + 1);
	}
}

void printCardFiles(Apartment *arr, int capasity) {
	bool flag = false;
	for (int i = 0; i < capasity; i++) {
		if (arr[i].getAddress() != nullptr) {

			cout << "\n==========================================\n";
			cout << arr[i];
			cout << "==========================================\n";
			flag = true;
		}
	}
	if (flag == false) {
		cout << "Картотека пуста!\n";
	}
}

void searchCardFile(Apartment *arr, Apartment src, int &capasity) {
	bool flag = false;
	for (int i = 0; i < capasity; i++) {
		double tenper = arr[i].getArea() * 0.1;
		if ((arr[i].getFloor() == src.getFloor()) && (arr[i].getRooms() == src.getRooms()) && (abs(arr[i].getArea() - src.getArea()) <= tenper)) {
			cout << arr[i];
			flag = true;
		}
	}
	if (flag == false) {
		pushCardFile(arr, src, capasity);
		cout << "Поиск не дал результатов!\n";
	}
}

void pushCardFile(Apartment *arr, Apartment src, int &capasity) {
	if (capasity < SIZE) {
		arr[capasity] = src;
		capasity++;
	}
	else {
		cout << "В картотеке недостаточно места!";	
	}
}

Apartment *getCardFilesByRooms(Apartment *arr, int rooms, int capasity) {
	Apartment *tmp = nullptr;
	tmp = giveMemory();
	int tmpCapasity = 0;
	for (int i = 0; i < capasity; i++) {
		if (arr[i].getRooms() == rooms) {
			tmp[tmpCapasity] = arr[i];
			tmpCapasity++;
		}
	}
	insertionSort(tmp, tmpCapasity);
	return tmp;
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