//Расположить в порядке возрастания элементы массива А(N), начиная с k-го элемента.
#include <iostream>
#include <clocale>
using namespace std;

void initArray(int *, int, const int, const int);
void printArray(int *, int);
void* giveMemory(int *, int);
void freeMemory(int *);
void insertionSort_k(int *, int, int);

int main() {
	setlocale(LC_ALL, "Ru");
	int size, k;
	const int MAX_RAND = 50;
	const int MIN_RAND = -20;
	int *arr = nullptr;
	cout << "Введите требуемый размер массива: ";
	cin >> size;
	cout << "Введите индекс элемента, с которого хотите начать сортировку массива: ";
	cin >> k;
	arr = (int*) giveMemory(arr, size);
	initArray(arr, size, MAX_RAND, MIN_RAND);
	cout << "Исходный массив: ";
	printArray(arr, size);
	cout << "\n";
	insertionSort_k(arr, size, k);
	cout << "Отсортированный массив: ";
	printArray(arr, size);
	cout << "\n";
	freeMemory(arr);
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

void freeMemory(int *arr) {
	delete[] arr;
}

void insertionSort_k(int *arr, int size, int k) {
	int key, j;
	for (int *ptr = arr + k + 1; ptr < arr + size; ptr++) {
		key = *ptr;
		j = ptr - (arr + 1);
		while ((j > k - 1) && (arr[j] > key)) {
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = key;
	}
}