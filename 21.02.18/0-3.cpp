/*Массив чисел размера N проинициализировать случайными числами из промежутка от -N до N.
Написать функцию циклического сдвига элементов массива вправо на k элементов.*/
#include <iostream>
#include <clocale>
using namespace std;

void initArray(int *, int, const int, const int);
void printArray(int *, int);
void swap(int *, int *);
void rightShift(int *, int, int);


int main() {
	setlocale(LC_ALL, "Ru");
	int size;
	int k = 0;
	int *arr;
	while (true) {
		cout << "Введите не отрицательное число, на которое хотите сдвинуть вправо элементы массива: ";
		cin >> k;
		if (k > -1) {
			break;
		}
	}
	cout << "Введите требуемый размер массива: ";
	cin >> size;
	const int MAX_RAND = size;
	const int MIN_RAND = -size;
	try {
		arr = new int[size];
	}
	catch (...) {
		cout << "Ошибка выделения памяти!" << "\n";
		system("pause");
		return 0;
	}
	initArray(arr, size, MAX_RAND, MIN_RAND);
	cout << "Первоначальный массив: ";
	printArray(arr, size);
	cout << "\n";
	rightShift(arr, size, k);
	cout << "Изменённый массив: ";
	printArray(arr, size);
	cout << "\n";
	delete[] arr;
	system("pause");
	return 0;
}

void initArray(int *arr, int size, const int MAX_RAND, const int MIN_RAND) {
	for (int *ptr = arr; ptr < arr + size; ptr++) {
		*ptr = rand() % (MAX_RAND - MIN_RAND + 1) + MIN_RAND;
	}
}

void printArray(int *arr, int size) {
	for (int *ptr = arr; ptr < arr + size; ptr++) {
		cout << *ptr << " ";
	}
}

void swap(int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void rightShift(int *arr, int size, int k) {
	int *end = arr + (size - 1);
	for (int *ptr = arr; ptr < arr + (size / 2); ptr++) {
		swap(ptr, end);
		end--;
	}
 	end = arr + k - 1;
	for (int *ptr = arr; ptr < arr + (k / 2); ptr++) {
		swap(ptr, end);
		end--;
	}
	end = arr + (size - 1);
	for (int *ptr = arr + k; ptr < arr + k + ((size - k) / 2); ptr++) {
		swap(ptr, end);
		end--;
	}
}
