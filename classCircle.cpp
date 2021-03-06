﻿#include <iostream>
#include <cmath>
#include <clocale>
using namespace std;

class Circle {
private:
	double x;
	double y;
	double r;
public:
	Circle(double coordX = 0, double coordY = 0, double radius = 0.0) : x(coordX), y(coordY), r(radius) {
		//cout << "Сработал конструктор c параметром по умолчанию - " << this << endl;
	};
	Circle(const Circle &other) {
		x = other.x;
		y = other.y;
		r = other.r;
		//cout << "Сработал конструктор копирования - " << this << endl;
	};
	Circle(const Circle &&other) {
		x = other.x;
		y = other.y;
		r = other.r;
		//cout << "Сработал конструктор перемещения - " << this << endl;
	};
	~Circle() {
		//cout << "Сработал деструктор - " << this << endl;
	};
	Circle operator=(const Circle &other) {
		x = other.x;
		y = other.y;
		r = other.r;
		//cout << "Сработал оператор перемещения - " << this << endl;
		return *this;
	};
	Circle operator=(const Circle &&other) {// Бессмысленно. Совпадает код с copy
		x = other.x;
		y = other.y;
		r = other.r;
		//cout << "Сработал оператор перемещения - " << this << endl;
		return *this;
	};
	Circle operator+(const Circle &other) {
		Circle tmp;
		tmp.r = r + other.r;
		return tmp;
	};
	Circle operator-(const Circle &other) {
		Circle tmp;
		tmp.r = abs(r - other.r);
		return tmp;
	};
	Circle operator*(const Circle &other) {
		Circle tmp;
		tmp.r = r * other.r;
		return tmp;
	};
	Circle operator/(const Circle &other) {
		Circle tmp;
		tmp.r = r / other.r;
		return tmp;
	};
	bool operator==(const Circle &other) {
		if (r == other.r) { //достаточно 1 строки: return (r == other.r);
			return true;
		}
		else {
			return false;
		}
	};
	bool operator!=(const Circle &other) {
		if (r != other.r) {
			return true;
		}
		else {
			return false;
		}
	};
	bool operator<(const Circle &other) {
		if (r < other.r) {
			return true;
		}
		else {
			return false;
		}
	}
	bool operator<=(const Circle &other) {
		if (r <= other.r) {
			return true;
		}
		else {
			return false;
		}
	}
	bool operator>(const Circle &other) {
		if (r > other.r) {
			return true;
		}
		else {
			return false;
		}
	}
	bool operator>=(const Circle &other) {
		if (r >= other.r) {
			return true;
		}
		else {
			return false;
		}
	}
	friend ostream &operator<<(ostream &outStream, Circle &other) {
		outStream << "Центр окружности - (" << other.x << ";" << other.y << ")\n";
		outStream << "Радиус окружности - " << other.r << " ед.\n";
		return outStream;
	};
	friend istream &operator>>(istream &inputStream, Circle &other) {
		cout << "Введите координаты X и Y (центр окружности) и её радиус:\n";
		inputStream >> other.x >> other.y >> other.r;
		return inputStream;
	};
	void setX(double value) {
		x = value;
	};
	void setY(double value) {
		y = value;
	};
	void setRadius(double value) {
		r = value;
	};
	double getX() {
		return x;
	};
	double getY() {
		return y;
	};
	double getRadius() {
		return r;
	};
};

double distanceBtwCntr(Circle c1, Circle c2) {
	return (sqrt((c1.getX() - c2.getX()) * (c1.getX() - c2.getX()) + (c1.getY() - c2.getY()) * (c1.getY() - c2.getY())));
}

void checkLocation(Circle c1, Circle c2) {
	double dist = distanceBtwCntr(c1, c2);
	if (dist == c1.getRadius() + c2.getRadius()) {
		cout << "Окружности касаются внешним образом.\n";
	}
	else if (dist == abs(c1.getRadius() - c2.getRadius())) {
		cout << "Окружности касаются внутренним образом.\n";
	}
	else if (dist < abs(c1.getRadius() - c2.getRadius())) {
		if (dist == 0) {
			cout << "Окружности являются концентрическими.\n";
		}
		else {
			cout << "Окружность с меньшим радиусом лежит внутри окружности с большим радиусом, не касаясь.\n";
		}
	}
	else if (dist > c1.getRadius() + c2.getRadius()) {
		cout << "Окружности расположены одна вне другой, не касаясь.\n";
	}
	else if ((dist < c1.getRadius() + c2.getRadius()) &&(dist > abs(c1.getRadius() - c2.getRadius()))) {
		cout << "Окружности пересекаются.\n";
	}
}

void initArray(Circle *arr, int SIZE, const double MAX_RAND, const double MIN_RAND) {
	for (int i = 0; i < SIZE; i++) {
		arr[i].setX(double(rand()) / RAND_MAX * (MAX_RAND - MIN_RAND) + MIN_RAND);
		arr[i].setY(double(rand()) / RAND_MAX * (MAX_RAND - MIN_RAND) + MIN_RAND);
		arr[i].setRadius(double(rand()) / RAND_MAX * MAX_RAND);
	}
}

void printArray(Circle *arr, int SIZE) {
	for (int i = 0; i < SIZE; i++) {
		cout << arr[i];
	}
}

Circle findMax(Circle *arr, int SIZE) {
	Circle max = arr[0];
	for (int i = 1; i < SIZE; i++) {
		if (max < arr[i]) {
			max = arr[i];
		}
	}
	return max;
}

Circle findMin(Circle *arr, int SIZE) {
	Circle min = arr[0];
	for (int i = 1; i < SIZE; i++) {
		if (min > arr[i]) {
			min = arr[i];
		}
	}
	return min;
}

int main() {
	int SIZE;
	const double MAX_RAND = 100;
	const double MIN_RAND = -100;
	setlocale(LC_ALL, "Ru");
	cout << "Введите размер массива: \n";
	cin >> SIZE;
	Circle a;
	Circle b;
	cin >> a;
	cin >> b;
	Circle *arr = new Circle[SIZE];
	initArray(arr, SIZE, MAX_RAND, MIN_RAND);
	printArray(arr, SIZE);
	cout << "Окружность с наибольшим радиусом:\n" << findMax(arr, SIZE);
	cout << "Окружность с наименьшим радиусом:\n" << findMin(arr, SIZE);
	cout << "Расстояние между центрами окружностей: " << distanceBtwCntr(a, b) << endl;
	checkLocation(a, b);
	system("pause");
	return 0;
}
