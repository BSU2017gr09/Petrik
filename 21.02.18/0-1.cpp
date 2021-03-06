//В массиве размера N, заполненного случ.числами от 0 до 10, подсчитать количество элементов, встречающихся более одного раза.
#include <iostream>
#include <clocale>
using namespace std;

void initArray(int *, int, const int, const int);
void printArray(int *, int);
int howMuchNumbers(int *, int);

int main() {
	setlocale(LC_ALL, "Ru");
	int size;
	const int MAX_RAND = 10;
	const int MIN_RAND = 0;
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
	cout << "\n" << "Количество элементов, встречающихся более одного раза: " << howMuchNumbers(arr, size) << "\n";
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

int howMuchNumbers(int *arr, int size) {
	int count = 0;
	int bufferArray[11] = {};
	for (int *ptr = arr ; ptr < arr + size; ptr++) {
		if (bufferArray[*ptr] == 0) {
			bufferArray[*ptr]++;
		}
		else if (bufferArray[*ptr] == 1) {
			bufferArray[*ptr]++;
			count++;
		}
	}
	return count;
}