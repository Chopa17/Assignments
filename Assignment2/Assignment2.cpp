//Assingment2.cpp by Sam Brind
//Reads in a data file of numbers from Millikan's experiment and computes mean,standard deviation and standard error of the e charge
#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <limits>
#include <string>
//use standard namespace
using namespace std;
//function to calculate mean from an array of N points
double calculate_mean(double points[], int N) {
	double sum{ 0 }; int error{ 0 };
	//loop over all the points
	for (int n{ 0 }; n < N; n++) {
		//check if nth point is erroneous
		if (points[n] == 100) {
			error++; //increment count of erroneous points
		} else {
			sum += points[n]; //add nth point to the sum
		}
	}
	N -= error; //reduce N for erroreneous points not included
	return sum / N;
}
//function to calculte standard deviation from an array of N points and a mean value
double calculate_deviation(double points[], int N, double mean) {
	double sum{ 0 }; int error{ 0 };
	//loop over all the points
	for (int n{ 0 }; n < N; n++) {
		//check if nth point is erroneous
		if (points[n] == 100) {
			error++; //increment count of erroneous points
		} else {
			sum += pow(points[n] - mean, 2); //add square deviation of nth point from mean
		}
	}
	N -= error; //reduce N for erroreneous points not included
	sum = pow(sum / (N - 1), 0.5); //calculate standard deviation
	return sum;
}
//function to calculate standard error of an array of N points and a standard deviation
double calculate_error(double points[], double N, double deviation) {
	int error{ 0 };
	//loop over all the points
	for (int n{ 0 }; n < N; n++) {
		//check if nth point is erroneous
		if (points[n] == 100) {
			error++; //increment count of erroneous points
		}
	}
	N -= error; //reduce N for erroreneous points not included
	return deviation / pow(N, 0.5);
}
//main program function
int main() {
	ifstream Input_file("millikan2.dat"); //declare and open file to be read					  
	if (!Input_file.good()) { //check the file opened successfully
		cerr << "Error: Unable to open input file!" << endl;
		return 1; //program ran with error
	}
	//determine no of data points/lines (N) in the file
	int N{ 0 }; string line;
	//read a new file line and loop until it isn't good
	while (getline(Input_file, line)) { N++; };
	//reset the file stream
	Input_file.clear();
	Input_file.seekg(0, Input_file.beg);
	//allocate memory for an array of N doubles
	double *points = new double[N];
	//read in the data
	for (int n{ 0 }; n < N; n++) {
		Input_file >> points[n];
		if (Input_file.fail()) { // check if it failed to read a double
			cerr << "Error: data point " << n + 1 << " is invalid!" << endl;
			points[n] = 100; //set value to 100 to represent an invalid point
			//reset the file stream
			Input_file.clear();
			Input_file.ignore(numeric_limits<streamsize>::max(), '\n');
		} else { //a double was read successfully
			getline(Input_file, line); //get the rest of the line
			//check if there is anything but whitespace contained in the rest of line
			if (line.find_first_not_of(" ") != string::npos) {
				cerr << "Error: data point " << n + 1 << " is invalid!" << endl;
				points[n] = 100; //set to 100 to represent an invalid point
			}
		}
	}
	Input_file.close(); //close the input file
	//calculate mean, standard deviation and standard error
	double mean, deviation, error;
	mean = calculate_mean(points, N);
	deviation = calculate_deviation(points, N, mean);
	error = calculate_error(points, N, deviation);
	//output values
	cout << "Electron charge:" << endl << "Mean =  -";
	cout << fixed << setprecision(5) << mean;
	cout << "e-19C" << endl << "Standard deviation =  ";
	cout << fixed << setprecision(5) << deviation;
	cout << "e-19C" << endl << "Standard error =  ";
	cout << fixed << setprecision(5) << error;
	cout << "e-19C" << endl;
	//free up memory
	delete[] points;
	return 0;
}