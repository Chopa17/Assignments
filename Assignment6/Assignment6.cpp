//Assignment6.cpp by Sam Brind
//Using classes for matrices
#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <algorithm>
#include <iomanip>
//use standard namespace
using namespace std;
//declare matrix class
class Matrix {
private:
	int rows;
	int columns;
	double *matrix;
public:
	//default constructor
	Matrix() : rows{ 0 }, columns{ 0 }, matrix{ 0 } {}
	//declare a parameterised constructor
	Matrix(int rows_in, int columns_in);
	//destructor
	~Matrix() { delete matrix; cout << "Destroying matrix..." << endl; }
	//declare overloaded I/O operators as friends
	friend ostream& operator<<(ostream &os, const Matrix &m);
	friend istream& operator>>(istream &is, Matrix &m);
	//function to get matrix index of element ij
	int index(const int i, const int j) const {
		return (j - 1) + (i - 1)*columns; //position of element at ij
	}
	//overload element () operator
	double& operator()(const int i, const int j) const {
		//check if i and j are within matrix range
		if (i < 1 || j < 1 || i > rows || j > columns) {
			cerr << "Error: Matrix element is out of range!" << endl;
			exit(1); //exit program
		}
		return matrix[index(i, j)]; //return matrix element at ij
	}
	//overloaded deep copy assignment operator
	Matrix& operator=(const Matrix &m) {
		//check for self-assignment
		if (&m == this) { return *this; }
		//delete this matrix
		delete[] matrix; rows = 0; columns = 0; matrix = 0;
		//copy rows, columns
		rows = m.rows; columns = m.columns;
		//copy matrix if non-zero
		if (rows > 0 && columns > 0) {
			matrix = new double[rows*columns]; //create new matrix
			for (int i = 1; i <= rows; i++) { //loop over rows
				for (int j = 1; j <= columns; j++) { //loop over columns
					matrix[index(i, j)] = m(i, j); //copy element at ij
				}
			}
		}
		return *this;
	}
	//deep copy constructor
	Matrix(const Matrix &m) {
		matrix = 0;
		//copy rows, columns
		rows = m.rows; columns = m.columns;
		//copy matrix if non-zero
		if (rows > 0 && columns > 0) {
			matrix = new double[rows*columns]; //create new matrix
			for (int i = 1; i <= rows; i++) { //loop over rows
				for (int j = 1; j <= columns; j++) { //loop over columns
					matrix[index(i, j)] = m(i, j); //copy element at ij
				}
			}
		}
	}
	//move constructor
	Matrix(Matrix &&m) {
		//take all the properties of m
		rows = m.rows;
		columns = m.columns;
		matrix = m.matrix;
		//set m properties to zero
		m.rows = m.columns = 0;
		m.matrix = nullptr;
	}
	//move assignment
	Matrix& operator=(Matrix &&m) {
		//swap all the properties with matrix, m
		swap(rows, m.rows);
		swap(columns, m.columns);
		swap(matrix, m.matrix);
		return *this;
	}
	//overloaded addition
	Matrix operator+(const Matrix &m) const {
		//check matrix dimensions
		if ((rows != m.rows) || (columns != m.columns)) {
			cerr << "Error: Matrices must be same dimension for addition!" << endl;
			exit(3); //exit program
		}
		//sum the matrices
		Matrix sum(rows, columns);
		for (int i = 1; i <= rows; i++) { //loop over rows
			for (int j = 1; j <= columns; j++) { //loop over columns
				sum(i, j) = matrix[index(i, j)] + m(i, j); //add elements at ij
			}
		}
		return sum;
	}
	//overloaded subtraction
	Matrix operator-(const Matrix &m) const {
		//check matrix dimensions
		if ((rows != m.rows) || (columns != m.columns)) {
			cerr << "Error: Matrices must be same dimension for subtraction!" << endl;
			exit(3); //exit program
		}
		//subtract the matrices
		Matrix difference(rows, columns);
		for (int i = 1; i <= rows; i++) { //loop over rows
			for (int j = 1; j <= columns; j++) { //loop over columns
				difference(i, j) = matrix[index(i, j)] - m(i, j); //subtract elements at ij
			}
		}
		return difference;
	}
	//overloaded multiplication
	Matrix operator*(const Matrix &m) const {
		//check if dimensions allow multiplication
		if (columns != m.rows) {
			cerr << "Error: Left acting matrix must have same number of columns as the right matrices rows, for multiplication!" << endl;
			exit(4); //exit program
		}
		//multiply the matrices
		Matrix product(rows, m.columns);
		for (int i = 1; i <= rows; i++) { //loop over rows
			for (int j = 1; j <= columns; j++) { //loop over columns
				double sum{ 0 }; //delcare a temporary sum
				for (int k = 1; k <= columns; k++) { //loop through multiplication with dummy k variable
					sum += (matrix[index(i, k)] * m(k, j)); //p_ij = m1_ik * m2_kj
				}
				product(i, j) = sum;
			}
		}
		return product;
	}
	//function to calculate minor of the matrix (remove ath row and bth column)
	Matrix calculate_minor(const int a, const int b) const {
		//check that matrix is big enough for minor to be taken
		if (rows == 1 || columns == 1) {
			cerr << "Error: Matrix is too small for a minor to be taken!" << endl;
			exit(5); //exit program
		}
		Matrix minor(rows - 1, columns - 1);
		int row_offset{ 0 }, column_offset{ 0 };
		for (int i = 1; i <= rows; i++) { //loop over rows
			if (a == i) { //ignore ath row
				row_offset = 1;
			} else {
				column_offset = 0;
				for (int j = 1; j <= columns; j++) { //loop over columns
					if (b == j) { //ignore bth column
						column_offset = 1;
					} else {
						minor(i - row_offset, j - column_offset) = matrix[index(i, j)]; //set offset element equal to matrix element at ij
					}
				}
			}
		}
		return minor;
	}
	//function to calculate the determinant
	double determinant() const {
		//check matrix is square
		if (rows != columns) {
			cerr << "Error: Matrix must be square to use determinant() function!" << endl;
			exit(6); //exit program
		}
		//check if matrix is 2x2
		if (rows == 2) {
			return (matrix[index(1, 1)] * matrix[index(2, 2)]) - (matrix[index(1, 2)] * matrix[index(2, 1)]); //det(2x2) = ad-bc
		}
		//expand in minors, recursively calling determinant()
		double sum{ 0 }; //declare temporary sum
		for (int j = 1; j <= columns; j++) { //loop over first row, i=1
			sum += pow(-1, j + 1)*matrix[index(1, j)] * this->calculate_minor(1, j).determinant(); //det(M) = (-1)^i+j m_ij det(Minor(i,j))
		}
		return sum;
	}
};
//parameterised constructor implementation
Matrix::Matrix(const int rows_in, const int columns_in) {
	//check matrix has valid size
	if (rows_in < 1 || columns_in < 1) {
		cerr << "Error: matrix must have positive size!" << endl;
		exit(2); //exit program
	}
	//set no of rows and columns
	rows = rows_in; columns = columns_in;
	matrix = new double[rows*columns]; //allocate memory for matrix
	for (int i = 0; i < rows*columns; i++) { matrix[i] = 0; } //loop through and set all matrix values to zero
}
//overloaded insertion operator
ostream& operator<<(ostream &os, const Matrix &m) {
	//print the matrix dimensions
	cout << m.rows << " x " << m.columns << " Matrix" << endl;
	//print matrix values if non-zero size
	if (m.rows > 0 && m.columns > 0) {
		//find the longest number in the matrix
		string element_max;
		for (int i = 1; i <= m.rows; i++) { //loop over rows
			for (int j = 1; j <= m.columns; j++) { //loop over columns
				stringstream element_stream; string element;
				element_stream << m(i, j); //read element ij into the stream
				element_stream >> element; //read stream into a string
				if (element.length() > element_max.length()) { element_max = element; } //check if element is longest element
			}
		}
		//print the elements
		int max_width = element_max.length() + 1; //set width of output fields
		for (int i = 1; i <= m.rows; i++) { //loop over rows
			cout << "	[ ";
			for (int j = 1; j <= m.columns; j++) { //loop over columns
				cout << setw(max_width) << right << m(i, j) << " "; //print element at ij
			}
			cout << "]" << endl;
		}
	}
	return os;
}
//overloaded extraction operator
istream& operator>>(istream &is, Matrix &m) {
	cout << "Please enter " << m.rows << " rows of " << m.columns << " elements, seperated by whitespace..." << endl;
	for (int i = 1; i <= m.rows; i++) { //loop over rows
		string row;
		getline(is, row); //take a line of input
		stringstream input;
		input << row; //read input line into a string stream
		for (int j = 1; j <= m.columns; j++) { //loop over columns
			input >> ws; //read whitespace
			double element;
			input >> element; //read an element of data
			m.matrix[m.index(i, j)] = element; //assign element at ij
		}
	}
	return is;
}
//main program function
int main() {
	//First part: constructing, copying and moving
	//Default constructor
	Matrix m1;
	cout << "m1 = " << m1;
	//Parameterised constructor
	Matrix m2(3, 3);
	cout << "m2 = " << m2;
	//extraction operator
	Matrix m3(3, 3);
	cin >> m3;
	cout << "m3 = " << m3;
	//copy assignment
	Matrix m4(3, 3);
	cout << "m4 = " << m4;
	cout << "copy assignment, m4 = m3" << endl;
	m4 = m3; //copy m3 into m4
	m3(1, 1) = 0;
	m3(2, 3) = 9; //changed original matrix values
	cout << "changed m3(1,1) and m3(2,3)..." << endl;
	//output original and copy
	cout << "m3 = " << m3;
	cout << "m4 = " << m4;
	//copy constructor
	Matrix m5(m3); //intialies m5 as copy of m3
	cout << "copy constructor, m5(m3)" << endl;
	cout << "m5 = " << m5;
	m3(1, 3) = -1;
	m3(3, 3) = 0; //changed original matrix values
	cout << "changed m3(1,3) and m3(3,3)..." << endl;
	//output original and copy
	cout << "m3 = " << m3;
	cout << "m5 = " << m5;
	//move constructor
	Matrix m6(move(m3));
	cout << "move constructor, m6(move(m3))" << endl;
	cout << "m3 = " << m3;
	cout << "m6 = " << m6;
	//move assignment
	Matrix m7;
	m7 = move(m5);
	cout << "move assignment, m7 = move(m5)" << endl;
	cout << "m5 = " << m5;
	cout << "m7 = " << m7;
	//Second part: matrix operations
	Matrix add{ m6 + m7 };
	Matrix subtract{ m6 - m7 };
	Matrix multiply{ m6 * m7 };
	Matrix minor{ m7.calculate_minor(1, 3) };
	double determinant{ m7.determinant() };
	cout << "m6 + m7 = " << add;
	cout << "m6 - m7 = " << subtract;
	cout << "m6*m7 = " << multiply;
	cout << "m7.minor(1,3) = " << minor;
	cout << "Det(m7) = " << determinant << endl;
	return 0;
}