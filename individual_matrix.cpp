/*Симметричную матрицу А(N,N), заданную нижним треугольником в
виде одномерного массива относительно побочной диагонали, умножить на
вектор В(N). В памяти матрицу не получать.*/
#include <iostream>
#include <iomanip>
#include <clocale>
using namespace std;
typedef void fun(int **, int **, int **, int);
typedef fun* ptrfun;

void taskInfo(int **, int **, int **, int);
int** giveMemoryTriangleMatrix(int);
int** giveMemoryVector(int);
void initTriangleMatrix(int **, int **, int **, int);
void initVector(int **, int **, int **, int);
void mult(int **, int **, int **, int);
void printTriangleMatrix(int **, int **, int **, int);
void printVector(int **, int **, int **, int);
void freeMemory(int **, int);
void exit(int **, int **, int **, int);
void menu(int **, int **, int**, int);
void forEach(int **, int **, int **, int, ptrfun);

int main() {
	setlocale(LC_ALL, "Ru");
	int N = 0;
	cout << "Введите размер квадратной матрицы: ";
	cin >> N;
	int **A = nullptr;
	int **B = nullptr;
	int **C = nullptr;
	A = giveMemoryTriangleMatrix(N);
	B = giveMemoryVector(N);
	C = giveMemoryVector(N);
	menu(A, B, C, N);
	freeMemory(A, N);
	freeMemory(B, N);
	freeMemory(C, N);
	system("pause");
	return 0;
}

void taskInfo(int **A, int **B, int **C, int) {
	cout << "Симметричную матрицу А(N,N), заданную нижним треугольником в виде одномерного";
	cout <<	"массива относительно побочной диагонали, умножить на вектор В(N).В памяти матрицу не получать.\n\n";
	cout << "Правило заполнения нижнетреугольной матрицы A: \n";
	cout << "0 0 0 x\n";
	cout << "0 0 x x\n";
	cout << "0 x x x\n";
	cout << "x x x x\n";
	cout << "Элементы последовательно записываются слева направо в ячейку x, начиная с первой строки последовательно двигаясь вниз до последней строки.\n\n";
	cout << "Правило заполнения вектора B: \n";
	cout << "x\n";
	cout << "x\n";
	cout << "x\n";
	cout << "x\n";
	cout << "Элементы последовательно записываются в ячейку x сверху вниз.\n\n";
	cout << "При умножении матрицы A на вектор B получится вектор C.\n";
}

int** giveMemoryTriangleMatrix(int N) {
	try {
		int **tmp = new int*[N];
		for (int i = 0; i < N; i++) {
			tmp[i] = new int[i + 1];
		}
		return tmp;
	}
	catch (...) {
		cout << "Ошибка при выделении памяти!\n";
		system("pause");
		exit(1);
	}
}

int** giveMemoryVector(int N) {
	try {
		int **tmp = new int*[N];
		for (int i = 0; i < N; i++) {
			tmp[i] = new int[1];
		}
		return tmp;
	}
	catch (...) {
		cout << "Ошибка при выделении памяти!\n";
		system("pause");
		exit(1);
	}
}

void initTriangleMatrix(int **A, int **B, int **C, int N) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < i + 1; j++) {
			cin >> A[i][j];
		}
	}
}

void initVector(int **A, int **B, int **C, int N) {
	for (int i = 0; i < N; i++) {
		cin >> B[i][0];
	}
}

void mult(int **A, int **B, int **C, int N) {
	int sum = 0, product = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < i + 1; j++) {
			product = (A[i][j]) * (B[N - i + j - 1][0]);
			sum += product;
		}
		C[i][0] = sum;
		sum = 0;
	}
}

void printTriangleMatrix(int **A, int **B, int **C, int N) {
	int i, j, k;
	cout << "Матрица А: \n";
	for (i = 0; i < N; i++) {
		for (j = 0; j < N - i; j++) {
			if (j != N - i - 1) {
				cout << setw(5) << "0";
			}
			else {
				for (k = 0; k < i + 1; k++) {
					cout << setw(5) << A[i][k];
				}
			}
		}
		cout << endl;
	}
}

void printVector(int **A, int **B, int **C, int N) {
	char inputChar = '\0';
	cout << "Вы хотите вывести на экран элементы вектора B или C: \n";
	cout << "Ввод: ";
	cin >> inputChar;
	switch (inputChar) {
	case 'B':
	case 'b':
		cout << "\nВектор B: \n";
		for (int i = 0; i < N; i++) {
			cout << setw(5) << B[i][0] << endl;
		}
		break;
	case 'C':
	case 'c':
		cout << "\nРезультат умножения матрицы A на вектор B - вектор C: \n";
		for (int i = 0; i < N; i++) {
			cout << setw(5) << C[i][0] << endl;
		}
		break;
	default: cout << "Убедитесь, что введённое вами значение правильное!\n";
	}
}

void freeMemory(int **Arr, int N) {
	for (int i = 0; i < N; i++) {
		delete[]Arr[i];
	}
}

void exit(int **A, int **B, int **C, int N) {
	exit(1);
}

void menu(int **A, int **B, int **C, int N) {
	ptrfun Fmenu[7] = { taskInfo, initTriangleMatrix, printTriangleMatrix, initVector, printVector, mult, exit };
	int inputNum = 0;
	while (true) {
		cout << "===========================MENU===========================\n";
		cout << "Выберите одну из следующих операций: \n";
		cout << "0 - Информация о задании и инструкция по использованию\n";
		cout << "1 - Инициализация нижнетреугольной матрицы A\n";
		cout << "2 - Вывод на экран элементов нижнетреугольной матрицы A\n";
		cout << "3 - Инициализация вектора B\n";
		cout << "4 - Вывод на экран элементов вектора(B или C)\n";
		cout << "5 - Умножить матрицу A на вектор B\n";
		cout << "6 - Выход\n";
		cout << "==========================================================\n";
		cout << "Ввод: ";
		cin >> inputNum;
		if (inputNum > -1 && inputNum < 7) {
			forEach(A, B, C, N, Fmenu[inputNum]);
		}
		else {
			cout << "Неверная операция, попробуйте ещё раз\n";
		}
	}
}

void forEach(int **A, int **B, int **C, int N, ptrfun fun) {
	fun(A, B, C, N);
}