//Assingment3.cpp by Sam Brind
//Takes physics course codes and names as input, stores and then prints the course list
#include <iostream>
#include <sstream>
#include <limits>
#include <string>
#include <vector>
#include <algorithm>
//use standard namespace
using namespace std;
//declare function to print out each element of a vector,v
void print_vector(const vector<string>& v) {
	//use iterator to loop through vector
	for (auto iterator = v.begin(); iterator != v.end(); iterator++) {
		cout << *iterator << endl; //output string
	}
}
//declare function to sort two strings based on 11th character
bool compare_char(string i, string j) {
	return tolower(i.at(11)) < tolower(j.at(11));
}
//main program function
int main() {
	const string degreeCode{ "PHYS" }; //all modules are for physics
	vector<string> courses; //declare vector to store courses
	//take user input courses
	string line; int course_code;
	cout << "Please enter a course code and title (or end to finish input):" << endl;
	while (true) {
		stringstream input_stream, course_stream;
		getline(cin, line); //read whole line
		if (line == "end") { //check for end of input
			break; //stop looping
		}
		//take course input if it isn't a blank line
		if (line.find_first_not_of(" ") != string::npos) {
			input_stream << line; //read line into input string stream
			input_stream >> course_code; //extract an integer
			if (input_stream.fail()) { //check for failure to read an integer
				cerr << "No course code found!" << endl;
				input_stream.clear(); //clear failbit
			} else {
				//make sure course code is 5 digits
				while (course_code < 10000) {
					course_code *= 10;
				}
				input_stream >> ws; //ignore whitespace
				if (input_stream.peek() == -1) { //check there is a character following course code
					cerr << "No course title found!" << endl;
				} else {
					getline(input_stream, line); //get the rest of line (the title)
					course_stream << degreeCode << " " << course_code << " " << line; //combine into a course string
					courses.push_back(course_stream.str()); //add course string to vector of courses
				}
			}
		}
	}
	//print full course list
	cout << "Full course list:" << endl;
	print_vector(courses);
	//print courses from a particular year
	cout << "Please enter a year:" << endl;
	int year; //take user input year
	cin >> year;
	while (year != 1 && year != 2 && year != 3 && year != 4) { //check year is valid (1st - 4th yr)
		cerr << "Error: Year must be 1-4!" << endl;
		cin.clear(); //clear failbit
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ignore characters up to new line
		cin >> year; //take new input
	}
	cin.clear(); //clear failbit
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ignore characters up to new line
	string course;
	cout << "Year " << year << " courses:" << endl;
	for (auto iterator = courses.begin(); iterator != courses.end(); iterator++) { //loop through courses
		course = *iterator; //course string from courses vector
		stringstream course_stream;
		course_stream << course.at(5); //read 6th char as a string stream
		course_stream >> course_code; //read an integer
		if (course_code == year) { //check if 6th char equals the user input year
			cout << course << endl;
		}
	}
	//print courses sorted by name or code
	cout << "Sort by code or title:" << endl;
	string type; //take user sort type input
	cin >> type;
	while (type != "code" && type != "title") { //check sort type is valid
		cerr << "Error: Must be code or title!" << endl;
		cin >> type;
	}
	cout << "Courses sorted by " << type << ":" << endl;
	vector<string>::iterator begin{ courses.begin() }, end{ courses.end() }; //set up iterator over courses vector
	if (type == "code") { //sort by course code
		sort(begin, end); //sort courses alphanumerically from 1st char
	} else { //sort by title of course
		sort(begin, end, compare_char); //sort courses using compare_char function
	}
	print_vector(courses); //print sorted vector
	return 0;
}