//Assignment7.cpp by Sam Brind
//Using classes and inheritance for vectors
#include <iostream>
#include <cmath>
#include <algorithm>
//use standard namespace
using namespace std;
//constants
const double c{ 3e08 }; //c = 3x10^8 m/s
const double Mev{ 1.6e-13 }; //1MeV = 1.6x10^-13 J
//declare base vector class
class Vector {
protected:
	int length;
	double *vector;
public:
	//default constructor
	Vector() : length{ 0 }, vector{ 0 } {}
	//declare a parameterised constructor
	Vector(const int length_in);
	//destructor
	~Vector() { delete vector; cout << "Destroying vector..." << endl; }
	//function to return vector length
	int return_length() const {
		return length;
	}
	//overload multiplication by double
	Vector operator*(const double x) const {
		Vector product(length);
		for (int i = 0; i < length; i++) {
			product[i + 1] = x*vector[i]; //multiply elements by x
		}
		return product;
	}
	//overload addition of vectors
	Vector operator+(const Vector &v) const {
		//addition must involve same length vectors
		if (length != v.length) {
			cerr << "Error: Vectors must be same dimension for addition!" << endl;
			exit(4); //exit program
		}
		Vector sum(length);
		for (int i = 0; i < length; i++) {
			sum[i + 1] = vector[i] + v[i + 1]; //add elements
		}
		return sum;
	}
	//overload element [] operator
	double& operator[](const int i) const {
		//check if i is within the vector range
		if (i < 1 || i > length) {
			cerr << "Error: Vector element is out of range!" << endl;
			exit(2); //exit program
		}
		return vector[i - 1]; //return vector element
	}
	//copy constructor
	Vector(const Vector &v) {
		vector = 0;
		//copy length
		length = v.length;
		if (length > 0) {
			vector = new double[length]; //create new vector
			for (int i = 0; i < length; i++) {
				vector[i] = v[i + 1]; //copy ith element
			}
		}
	}
	//move constructor
	Vector(Vector &&v) {
		//take all the properties
		length = v.length; vector = v.vector;
		//set v properties to zero
		v.length = 0; v.vector = nullptr;
	}
	//copy assignment
	Vector& operator=(const Vector &v) {
		//check for self-assignment
		if (&v == this) { return *this; }
		//delete this vector
		delete[] vector; length = 0; vector = 0;
		length = v.length; //copy length
		if (length > 0) {
			vector = new double[length]; //create new vector
			for (int i = 0; i < length; i++) {
				vector[i] = v[i + 1]; //copy ith element
			}
		}
		return *this;
	}
	//move assignment
	Vector& operator=(Vector &&v) {
		//swap all the properties with vector, v
		swap(length, v.length);
		swap(vector, v.vector);
		return *this;
	}
	//declare friend function overloading insertion operator
	friend ostream& operator<<(ostream &os, const Vector &v);
	//function to calculate dot product with vector v
	double dot_product(const Vector &v) const {
		//check vectors are the same length
		if (length != v.length) {
			cerr << "Error: Vectors must be the same length to calculate a dot product!" << endl;
			exit(3); //exit program
		}
		double sum{ 0 };
		//loop through elements
		for (int i = 0; i < length; i++) {
			sum += vector[i] * v.vector[i]; // a.b = sum(a_i . b_i)
		}
		return sum;
	}
};
//parameterised constructor implementation
Vector::Vector(const int length_in) {
	//check Vector has valid size
	if (length_in < 1) {
		cerr << "Error: Vector must have positive size!" << endl;
		exit(1); //exit program
	}
	length = length_in; //set vector length
	vector = new double[length]; //allocate memory for vector
	for (int i = 0; i < length; i++) { vector[i] = 0; } //loop through and set all elements to zero
}
//overloaded insertion operator
ostream& operator<<(ostream &os, const Vector &v) {
	//print the vector v
	cout << v.length << "-vector" << endl;
	//check vector size
	if (v.length > 0) {
		cout << "	(";
		for (int i = 0; i < v.length; i++) { //loop over vector
			cout << v.vector[i]; //print ith element
			if (i != v.length - 1) { cout << ","; } //print comma if needed
		}
		cout << ")" << endl;
	}
	return os;
}
//declare derived 4-vector class
class Four_Vector : protected Vector {
public:
	//default constructor
	Four_Vector() : Vector(4) {}
	//parameterised constructors
	Four_Vector(const double ct_in, const double x_in, const double y_in, const double z_in) : Vector(4) {
		vector[0] = ct_in; vector[1] = x_in; vector[2] = y_in; vector[3] = z_in;
	}
	Four_Vector(const double ct_in, const Vector r_in) : Vector(4) {
		//make sure r_in is a 3-vector
		if (r_in.return_length() != 3) {
			cerr << "Error: 3-Vector must be used as an argument for 4-Vector construction!" << endl;
			exit(5); //exit program
		}
		vector[0] = ct_in; vector[1] = r_in[1]; vector[2] = r_in[2]; vector[3] = r_in[3];
	}
	//destructor
	~Four_Vector() { cout << "Destroying Four-Vector..." << endl; }
	//declare friend function overloading insertion operator
	friend ostream& operator<<(ostream &os, const Four_Vector &f);
	//overload element [] operator
	double& operator[](const int i) const {
		//check if i is within range
		if (i < 1 || i > 4) {
			cerr << "Error: Four-vector element is out of range!" << endl;
			exit(2); //exit program
		}
		return vector[i - 1]; //return vector element
	}
	//copy constructor
	Four_Vector(const Four_Vector &f) :Vector(4) {
		vector = new double[4]; //create new four vector
		for (int i = 0; i < length; i++) {
			vector[i] = f[i + 1]; //copy ith element
		}
	}
	//move constructor
	Four_Vector(Four_Vector &&f) :Vector(4) {
		//take all the properties
		swap(vector, f.vector);
	}
	//copy assignment
	Four_Vector& operator=(const Four_Vector &f) {
		//check for self-assignment
		if (&f == this) { return *this; }
		//delete this vector
		delete[] vector; vector = 0;
		vector = new double[4]; //create new four vector
		for (int i = 0; i < 4; i++) {
			vector[i] = f[i + 1]; //copy ith element
		}
		return *this;
	}
	//move assignment
	Four_Vector& operator=(Four_Vector &&f) {
		//swap the vector with four vector, f
		swap(vector, f.vector);
		return *this;
	}
	//overriding four-vector dot product
	double dot_product(const Four_Vector &f) const {
		double sum{ vector[0] * f[1] }; //(ct1).(ct2)
		for (int i = 1; i < 4; i++) { sum -= vector[i] * f[i + 1]; } //-(x1_i)(x2_i)
		return sum;
	}
	//function to calculate lorentz boost of four-vector
	Four_Vector lorentz_boost(const Vector &beta) const {
		//make sure beta is a 3-vector
		if (beta.return_length() != 3) {
			cerr << "Error: Beta must be a 3-vector to calculate lorentz boost!" << endl;
			exit(6); //exit program
		}
		double ct_prime; Vector r_prime(3);
		double mod_beta = pow(beta.dot_product(beta), 0.5); //|beta| = sqrt(beta.beta)
		double gamma = pow(1 - pow(mod_beta, 2), -0.5); //gamma = 1/sqrt(1-beta^2)
		Vector r(3); r[1] = vector[1]; r[2] = vector[2]; r[3] = vector[3];
		ct_prime = gamma*(vector[0] - beta.dot_product(r)); //ct' = gamma(ct - beta.r)
	    //r' = r + ((gamma -1)/beta^2 r.beta - gamma ct)beta
		r_prime = r + (beta*(((gamma - 1) / pow(mod_beta, 2))*r.dot_product(beta) - gamma*vector[0]));
		Four_Vector f(ct_prime, r_prime);
		return f;
	}
};
//overriding four-vector insertion operator
ostream& operator<<(ostream &os, const Four_Vector &f) {
	cout << "Four-vector" << endl;
	if (f.vector != nullptr) {
		cout << "	(";
		//print elements of four vector
		cout << f[1] << "," << f[2] << "," << f[3] << "," << f[4];
		cout << ")";
	}
	return os;
}
//declare particle class
class Particle {
private:
	double mass; //in Mev/c^2
	Four_Vector position;
	Vector beta;
public:
	//parameterised constructor
	Particle(const Four_Vector position_in, const double mass_in, const Vector beta_in) {
		//make sure beta_in is a 3-vector
		if (beta_in.return_length() != 3) {
			cerr << "Error: Beta must be a 3-Vector to use for particle construction!" << endl;
			exit(7); //exit program
		}
		mass = mass_in; beta = beta_in; position = position_in; //assign values
	}
	//destructor
	~Particle() { cout << "Destroying particle..." << endl; }
	//function to calculate gamma factor
	double calculate_gamma() const {
		double mod_beta = pow(beta.dot_product(beta), 0.5); //modulus of beta
		return pow(1 - pow(mod_beta, 2), -0.5); //gamma = 1/sqrt(1-beta^2)
	}
	//function to calculate energy
	double calculate_energy() const {
		//E = gamma(v)mc^2
		return mass*calculate_gamma(); //return E in Mev
	}
	//function to calculate momentum
	Four_Vector calculate_momentum() const {
		//P = (E/c,p), E/c = gamma(v)mc, p = gamma(v)mv, v = beta*c
		Four_Vector four_momenta(mass*calculate_gamma(), beta*mass*calculate_gamma());
		return four_momenta; //return P in Mev/c
	}
};
//main program function
int main() {
	//demonstrate vector class
	cout << "Vectors:" << endl;
	//constructors demonstration
	Vector v1;
	Vector v2(3);
	cout << "v1 = " << v1;
	cout << "v2 = " << v2;
	//element accessor demonstration
	v2[1] = -3; v2[2] = 1; v2[3] = 0.5;
	cout << "v2 = " << v2;
	cout << "v2[2] = " << v2[2] << endl;
	//copy demonstration
	Vector v3(v2); //constructor
	cout << "v3(v2)" << endl;
	cout << "v3 = " << v3;
	v2[3] = 3; //change an original value
	cout << "v2 = " << v2;
	cout << "v3 = " << v3;
	Vector v4(3);
	v4 = v2; //assignment
	cout << "v4 = v2" << endl;
	cout << "v4 = " << v4;
	v2[3] = 0; //change an original value
	cout << "v2 = " << v2;
	cout << "v4 = " << v4;
	//move demonstration
	Vector v5(move(v4)); //constructor
	cout << "v5(move(v4))" << endl;
	cout << "v4 = " << v4;
	cout << "v5 = " << v5;
	Vector v6;
	v6 = move(v2); //assignment
	cout << "v6 = move(v2)" << endl;
	cout << "v2 = " << v2;
	cout << "v6 = " << v6;
	//dot product demonstration
	cout << "v5.v6 = " << v5.dot_product(v6) << endl;
	//demonstrate 4-vector class
	cout << "4-Vectors:" << endl;
	//constructors demonstration
	Four_Vector f1;
	Four_Vector f2(3, 5, 5, 5);
	Vector r(3);
	r[1] = 1; r[2] = -0.5; r[3] = 1.5;
	Four_Vector f3(0, r);
	cout << "f1 = " << f1 << endl;
	cout << "f2 = " << f2 << endl;
	cout << "f3 = " << f3 << endl;
	//element accessor demonstration
	cout << "f3[3] = " << f3[3] << endl;
	//copy demonstration
	Four_Vector f4(f2); //constructor
	cout << "f4(f2)" << endl;
	cout << "f4 = " << f4 << endl;
	f2[3] = 7; //change an original value
	cout << "f2 = " << f2 << endl;
	cout << "f4 = " << f4 << endl;
	Four_Vector f5;
	f5 = f3; //assignment
	cout << "f5 = f3" << endl;
	cout << "f5 = " << f5 << endl;
	f3[1] = 0.5; //change an original value
	cout << "f3 = " << f3 << endl;
	cout << "f5 = " << f5 << endl;
	//move demonstration
	Four_Vector f6(move(f3)); //constructor
	cout << "f6(move(f3))" << endl;
	cout << "f3 = " << f3 << endl;
	cout << "f6 = " << f6 << endl;
	Four_Vector f7;
	f7 = move(f5); //assignment
	cout << "f7 = move(f5)" << endl;
	cout << "f5 = " << f5 << endl;
	cout << "f7 = " << f7 << endl;
	//dot product demonstration
	cout << "f6.f7 = " << f6.dot_product(f7) << endl;
	//lorentz boost demonstration
	Vector beta(3);
	beta[1] = 0.95; beta[2] = 0; beta[3] = 0.2;
	cout << "Lorentz boost by beta = " << beta;
	cout << "f6' = " << f6.lorentz_boost(beta) << endl;
	//demonstrate particle class
	cout << "Particles:" << endl;
	//constructors demonstration
	Particle electron(f7, 0.511, beta);
	cout << "electron:" << endl;
	cout << "	position = " << f7 << endl;
	cout << "	mass = " << 0.511 << "MeV/c^2" << endl;
	cout << "	beta = " << beta;
	//gamma demonstration
	cout << "	gamma = " << electron.calculate_gamma() << endl;
	//energy and momentum demonstration
	cout << "	E = " << electron.calculate_energy() << " Mev" << endl;
	cout << " P = " << electron.calculate_momentum() << " Mev/c" << endl;
	return 0;
}