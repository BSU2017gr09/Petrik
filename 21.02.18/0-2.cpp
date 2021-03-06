//В массиве размера N, заполненного случ.числами от 0 до 10, определить максимальную длину последовательности равных элементов.
#include <iostream>
#include <clocale>
using namespace std;

void initArray(int *, int, const int, const int);
void printArray(int *, int);
int lenMax(int *, int);

int main() {
	setlocale(LC_ALL, "Ru");
	int size;
	const int MAX_RAND = 10;
	const int MIN_RAND = 0;
	int length = 0;
	int *arr;
	cout << "Введите требуемый размер массива: ";
	cin >> size;
	try {
		arr = new int[size];
	}
	catch (...) {
		cout << "Ошибка выделения памяти!" << "\n";
		system("pause");
		return 0;
	}
	initArray(arr, size, MAX_RAND, MIN_RAND);
	printArray(arr, size);
	length = lenMax(arr, size);
	delete[] arr;
	cout << "\n" << "Длина максимальной серии: " << length << "\n";
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

int lenMax(int *arr, int size) {
	int length_max = 1, length_cur = 1, tmp = 0;
	for (int *ptr = arr; ptr < arr + size; ptr++) {
		tmp = *ptr;
		if (tmp == *(ptr + 1)) {
			tmp = *(ptr + 1);
			length_cur++;
		}
		else {
			if (length_cur > length_max) {
				length_max = length_cur;
			}
			length_cur = 1;
		}
	}
	return length_max;
}