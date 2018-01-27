//Assignment1.cpp by Sam Brind
//takes user input quantum nos and calculates transition energy from Bohr's formula for a single electron atom
#include <iostream>
#include <cmath>
#include <iomanip>
#include <limits>
#include <string>
#include <cctype>
//use standard namespace
using namespace std;
//function to calculate transition energy in eV
double transition_energy(int Z, int n_i, int n_f) {
	double E;
	E = 13.6*pow(Z, 2)*(pow(n_f, -2) - pow(n_i, -2)); //calculate energy using Bohr's formula
	return E;
}
//function to get a user input that is a positive integer
int int_validation(string value) {
	int input, check;
	cin >> input; //extract an integer from user input
	check = cin.peek(); //use next character after input to check more characters aren't following
	while (check != 10 && check != 32 || input < 1) { //only blank space and \n are allowed after the integer and integer must be 1 or more
		cerr << value << " must be a positive integer!" << endl;
		cin.clear(); //clear the fail bit
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ignore characters in buffer up to new line
		cin >> input; //take a new user input
		check = cin.peek();
	}
	return input;
}
//function to get a user input that is a single character equal to value1 or value2
char char_validation(string value, char value1, char value2) {
	char input{ 's' }; int check;
	cin >> input; //extract a character from user input
	input = tolower(input); //change input to lowercase
	check = cin.peek(); //use next character after input as a check
	while (check != 10 && check != 32 || (input != value1 && input != value2)) { //only blank space and \n are allowed after character and only two char values are allowed
		cerr << "Input isn't one of " << value << "!" << endl;
		cin.clear(); //clear the fail bit
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ignore characters in buffer up to new line
		cin >> input; //take a new user input
		input = tolower(input);
		check = cin.peek();
	}
	return input;
}
//main program function
int main() {
	int Z, n_i, n_f; double energy;
	const double eV{ 1.6e-19 }; //1eV = 1.6e-19J
	bool again{ true }; //boolean whether to do a calculation
	while (again) {
		//get a valid value for Z
		cout << "What is the atomic number, Z?" << endl;
		Z = int_validation("Z");
		//model predicts maximum Z=137
		while (Z > 137) {
			cerr << "Maximum possible Z is 137!" << endl;
			Z = int_validation("Z"); //repeat another input
		}
		//get valid values for n_i and n_f
		cout << "What is the initial quantum number, n_i?" << endl;
		n_i = int_validation("n_i");
		cout << "What is the final quantum number, n_f?" << endl;
		n_f = int_validation("n_f");
		//check for no transition or n_i less than n_f
		while ((n_i == n_f) || (n_i < n_f)) {
			if (n_i == n_f) {
				cerr << "There is no transition!" << endl;
			} else {
				cerr << "n_i must be greater than n_f for a transition!" << endl;
			}
			//take new inputs
			cout << "What is the initial quantum number, n_i?" << endl;
			n_i = int_validation("n_i");
			cout << "What is the final quantum number, n_f?" << endl;
			n_f = int_validation("n_f");
		}
		energy = transition_energy(Z, n_i, n_f); //calculate the transition energy
		cout << "Output in electronvolts or Joules (e/J)?" << endl;
		char store; //store a valid user input character
		store = char_validation("e/J", 'e', 'j');
		if (store == 'e') {
			cout << "The transition energy is " << fixed << setprecision(5) << energy << "eV" << endl; //output in eV
		} else {
			cout << "The transition energy is " << scientific << setprecision(5) << energy*eV << "J" << endl; //output in J
		}
		//ask whether the user wants to repeat
		cout << "Do you want to calculate again (y/n)?" << endl;
		store = char_validation("y/n", 'y', 'n');
		if (store == 'n') { again = false; }; //set again to false if user selects no								  
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	return 0;
}
