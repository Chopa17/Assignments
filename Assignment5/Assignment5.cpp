//Assignment5.cpp by Sam Brind
//Demonstrating use of classes and overloading operators for complex numbers
#include <iostream>
#include <cmath>
//use standard namespace
using namespace std;
//declare complex number class
class Complex {
private:
	double real;
	double imaginary;
public:
	//default constructor
	Complex() : real{ 0 }, imaginary{ 0 } {}
	//parameterised constructor
	Complex(double real_in, double imaginary_in) : real{ real_in }, imaginary{ imaginary_in } {}
	//destructor
	~Complex() { cout << "Destroying complex number" << endl; }
	//function to return real part
	double return_real() const {
		return real;
	}
	//function to return imaginary part
	double return_imaginary() const {
		return imaginary;
	}
	//function to calculate modulus
	double modulus() const {
		return pow(pow(real, 2) + pow(imaginary, 2), 0.5); //|z|=sqrt(re^2 + im^2)
	}
	//function to calculate principal argument [-pi,pi]
	double argument() const {
		return atan2(imaginary, real); //theta = tan^-1(im/re) taking into account quadrant
	}
	//function to return complex conjugate
	Complex conjugate() const {
		return Complex(real, -imaginary); //return z = re - im
	}
	//declare overloaded addition
	Complex operator+(const Complex &c) {
		//z1 + z2 = (x1 + x2)+i(y1 + y2)
		Complex sum(real + c.real, imaginary + c.imaginary);
		return sum;
	};
	//declare other overloaded operators as friends
	friend Complex operator-(const Complex &c1, const Complex &c2);
	friend Complex operator*(const Complex &c1, const Complex &c2);
	friend Complex operator/(const Complex &c1, const Complex &c2);
	friend ostream& operator<<(ostream &os, const Complex &c);
	friend istream& operator>>(istream &is, Complex &c);
};
//overloaded subtraction
Complex operator-(const Complex &c1, const Complex &c2) {
	//z1 + z2 = (x1 - x2)+i(y1 - y2)
	Complex difference(c1.real - c2.real, c1.imaginary - c2.imaginary);
	return difference;
}
//overloaded multiplication
Complex operator*(const Complex &c1, const Complex &c2) {
	//z1 * z2 = (x1x2 - y1y2)+i(y1x2 + x1y2)
	Complex product((c1.real*c2.real) - (c1.imaginary*c2.imaginary), (c1.imaginary*c2.real) + (c1.real*c2.imaginary));
	return product;
}
//overloaded division
Complex operator/(const Complex &c1, const Complex &c2) {
	//z1 / z2 = (x1x2 + y1y2)+i(x2y1 - x1y2)/(x2^2 + y2^2)
	double denominator{ pow(c2.real, 2) + pow(c2.imaginary, 2) };
	Complex divisor((c1.real*c2.real + c1.imaginary*c2.imaginary) / denominator, (c2.real*c1.imaginary - c1.real*c2.imaginary) / denominator);
	return divisor;
}
//overloaded insertion operator
ostream& operator<<(ostream &os, const Complex &c) {
	if (c.imaginary > 0) {
		os << c.real << " + " << c.imaginary << "i"; //x + yi
	} else if (c.imaginary < 0) {
		os << c.real << " - " << -c.imaginary << "i"; //x - yi
	} else {
		os << c.real << " + 0i"; //make sure 0 isn't presented with weird signs
	}
	return os;
}
//overloaded extraction operator
istream& operator>>(istream &is, Complex &c) {
	double real_in, imaginary_in; char sign, i;
	is >> real_in >> ws >> sign >> ws >> imaginary_in >> i; //read real part, whitespace, sign, whitespace, imaginary part and the i
	c.real = real_in; //assign real part
	if (real_in == 0) { c.real = 0; } //make sure 0 isn't -0
    //assign imaginary part taking into account the sign
	if (sign == '+') {
		c.imaginary = imaginary_in;
	}
	if (sign == '-') {
		c.imaginary = -imaginary_in;
	}
	return is;
}
//main program function
int main() {
	Complex a;
	//demonstrate overloaded extraction and insertion
	cout << "Please enter a complex number (a)..." << endl;
	cin >> a; //extract a user input complex number
	cout << "a = " << a << endl; //insert user input complex number
	cout << "Re(a) = " << a.return_real() << endl; //return real part
	cout << "Im(a) = " << a.return_imaginary() << endl; //return imaginary part
	cout << "Mod(a) = " << a.modulus() << endl; //return modulus
	cout << "Arg(a) = " << a.argument() << endl; //return argument
	cout << "a* = " << a.conjugate() << endl; //return conjugate
	//declare second complex number
	Complex b(1, -2);
	cout << "b = " << b << endl;
	//demonstrate operator overloading
	Complex sum{ a + b };
	Complex difference{ a - b };
	Complex product{ a*b };
	Complex divisor{ a / b };
	cout << "a+b = " << sum << endl;
	cout << "a-b = " << difference << endl;
	cout << "a*b = " << product << endl;
	cout << "a/b = " << divisor << endl;
	return 0;
}