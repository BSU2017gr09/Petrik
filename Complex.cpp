#include <iostream>
#include <clocale>
using namespace std;

struct Complex {
private:
	double Re;
	double Im;
public:
	Complex() : Re(0), Im(0) {
		cout << "Конструктор сработал!\n";
	};
	Complex(double a, double b) : Re(a), Im(b) {
		cout << "Конструктор с параметром сработал!\n";
	};
	Complex(const Complex &other) {
		this->Re = other.Re;
		this->Im = other.Im;
		cout << "Конструктор копирования сработал!\n";
	};
	~Complex() {
		cout << "Деструктор сработал!\n";
	};
	Complex operator=(const Complex &other) {
		this->Re = other.Re;
		this->Im = other.Im;
		return *this;
	};
	Complex operator+(const Complex &other) {
		Complex tmp;
		tmp.Re = this->Re + other.Re;
		tmp.Im = this->Im + other.Im;
		return tmp;
	};
	Complex operator-(const Complex &other) {
		Complex tmp;
		tmp.Re = this->Re - other.Re;
		tmp.Im = this->Im - other.Im;
		return tmp;
	};
	Complex operator*(const Complex &other) {
		Complex tmp;
		tmp.Re = this->Re * other.Re - this->Im * other.Im;
		tmp.Im = this->Im * other.Re + this->Re * other.Im;
		return tmp;
	};
	Complex operator/(const Complex &other) {
		Complex tmp;
		tmp.Re = (this->Re * other.Re + this->Im * other.Im) / (other.Re * other.Re + other.Im * other.Im);
		tmp.Im = (this->Im * other.Re - this->Re * other.Im) / (other.Re * other.Re + other.Im * other.Im);
		return tmp;
	}
	friend ostream& operator<<(ostream &myStream, Complex &other) {
		myStream << other.Re;
		if (other.Im >= 0) {
			myStream << " + ";
		}
		myStream << other.Im << "i" << endl;
		return(myStream);
	};
	friend istream& operator>>(istream &myStream, Complex &other) {
		myStream >> other.Re >> other.Im;
		return myStream;
	};
};

int main() {
	setlocale(LC_ALL, "Ru");
	Complex z1;
	Complex z2;
	Complex z3;
	cin >> z1;
	cin >> z2;
	z3 = z1 * z2;
	cout << z3 << endl;
	system("pause");
	return 0;
}