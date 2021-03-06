/*Даны точки плоскости своими координатами в виде двух одномерных массивов.
Точки плоскости рассортировать по возрастанию расстояния до прямой ax + by + c = 0.*/
#include <iostream>
#include <clocale>
using namespace std;

void initArrayInt(int *, int, const int, const int);
void printArrayInt(int *, int);
void printArrayDouble(double *, int);
void* giveMemory(int *, int);
void* giveMemory(double *, int);
void freeMemoryInt(int *);
void freeMemoryDouble(double *);
double countDist(int, int, int, int *, int *);
void insertionSort(double *, int, int *, int *);
void swap(int *, int *);

int main() {
	setlocale(LC_ALL, "Ru");
	int size = 0, a = 0, b = 0, c = 0;
	const int MAX_RAND_X = 10;
	const int MIN_RAND_X = -10;
	const int MAX_RAND_Y = 15;
	const int MIN_RAND_Y = -15;
	int *arrX = nullptr;
	int *arrY = nullptr;
	double *distArr = nullptr;
	cout << "Введите требуемый размер массива: ";
	cin >> size;
	arrX = (int*)giveMemory(arrX, size);
	arrY = (int*)giveMemory(arrY, size);
	distArr = (double*)giveMemory(distArr, size);
	cout << "Введите коэффициенты прямой (a, b, c): \n";
	cin >> a >> b >> c;
	initArrayInt(arrX, size, MAX_RAND_X, MIN_RAND_X);
	initArrayInt(arrY, size, MAX_RAND_Y, MIN_RAND_Y);
	cout << "\nМассив координат X: ";
	printArrayInt(arrX, size);
	cout << "\nМассив координат Y: ";
	printArrayInt(arrY, size);
	double *ptrDist = distArr;
	for (int *ptrX = arrX, *ptrY = arrY; ptrX < arrX + size, ptrY < arrY + size; ptrX++, ptrY++) {
		*ptrDist = countDist(a, b, c, ptrX, ptrY);
		ptrDist++;
	}
	cout << "\nИсходный массив значений расстояний до прямой: ";
	printArrayDouble(distArr, size);
	insertionSort(distArr, size, arrX, arrY);
	cout << "\nОтсортированный массив значений расстояний до прямой: ";
	printArrayDouble(distArr, size);
	cout << "\nКоординаты точек, отсортированных по расстоянию до прямой:";
	cout << "\n" << "Массив координат X: ";
	printArrayInt(arrX, size);
	cout << "\n" << "Массив координат Y: ";
	printArrayInt(arrY, size);
	freeMemoryInt(arrX);
	freeMemoryInt(arrY);
	freeMemoryDouble(distArr);
	system("pause");
	return 0;
}

void initArrayInt(int *arr, int size, const int MAX_RAND, const int MIN_RAND) {
	for (int *ptr = arr; ptr < arr + size; ptr++) {
		*ptr = rand() % (MAX_RAND - MIN_RAND + 1) + MIN_RAND;
	}
}

void printArrayInt(int *arr, int size) {
	for (int *ptr = arr; ptr < arr + size; ptr++) {
		cout << *ptr << " ";
	}
}

void printArrayDouble(double *arr, int size) {
	for (double *ptr = arr; ptr < arr + size; ptr++) {
		cout << *ptr << " ";
	}
}

void* giveMemory(int *arr, int size) {
	try {
		arr = new int[size];
	}
	catch (...) {
		cout << "Ошибка выделения памяти!" << "\n";
		system("pause");
		exit(1);
	}
	return arr;
}

void* giveMemory(double *arr, int size) {
	try {
		arr = new double[size];
	}
	catch (...) {
		cout << "Ошибка выделения памяти!" << "\n";
		system("pause");
		exit(1);
	}
	return arr;
}

void freeMemoryInt(int *arr) {
	delete[] arr;
}

void freeMemoryDouble(double *arr) {
	delete[] arr;
}

double countDist(int a, int b, int c, int *x, int *y) {
	double dist = (abs(a * (*x) + b * (*y) + c)) / (sqrt(a * a + b * b));
	return dist;
}

void insertionSort(double *distArr, int size, int *arrX, int *arrY) {
	double key;
	int j;
	for (double *ptr = distArr + 1; ptr < distArr + size; ptr++) {
		key = *ptr;
		j = ptr - (distArr + 1);
		while ((j > -1) && (distArr[j] > key)) {
			distArr[j + 1] = distArr[j];
			swap(arrX[j + 1], arrX[j]);
			swap(arrY[j + 1], arrY[j]);
			j--;
		}
		distArr[j + 1] = key;
	}
}

void swap(int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}