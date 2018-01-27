//Assingment4.cpp by Sam Brind
//Demonstrates classes using the example of galaxies
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
//use standard namespace
using namespace std;
//declare array of hubble types for printing
const string Types[]{ "E0", "E1", "E2", "E3", "E4", "E5", "E6", "E7", "S0", "Sa", "Sb", "Sc", "SBa", "SBb", "SBc", "Irr" };
//declare hubble type datatype
enum Hubble_type { E0, E1, E2, E3, E4, E5, E6, E7, S0, Sa, Sb, Sc, SBa, SBb, SBc, Irr };
//declare galaxy class
class Galaxy {
private:
	Hubble_type Type;
	double Z;
	double M_tot;
	double Stellar_fraction;
	vector <Galaxy> Satellites;
public:
	//default constructor
	Galaxy() : Type{ E0 }, Z{ 0 }, M_tot{ 0 }, Stellar_fraction{ 0 } {}
	//parameterised constructor
	Galaxy(Hubble_type type_in, double Z_in, double M_in, double fraction_in) :
		Type{ type_in }, Z{ Z_in }, M_tot{ M_in }, Stellar_fraction{ fraction_in } {}
	//destructor
	~Galaxy() { cout << "Destroying " << Types[Type] << " Galaxy" << endl; }
	//function to change hubble type
	void change_type(Hubble_type new_type) {
		Type = new_type;
	}
	//function to return stellar mass
	double stellar_mass() {
		return Stellar_fraction*M_tot;
	}
	//function to add a satellite galaxy
	void add_satellite(Hubble_type type, double Z, double M, double fraction, int max) {
		Satellites.reserve(max); //reserve memory for no of satellites to be added
		Satellites.emplace_back(type, Z, M, fraction); //place new satellite into satellites vector
	}
	//declare a data printing function
	void print_data();
};
//define data printing function
void Galaxy::print_data() {
	cout.precision(4); //set output precision
	//print the galaxie's properties
	cout << "Galaxy:" << endl << "type = " << Types[Type] << endl;
	cout << "redshift = " << fixed << Z << endl;
	cout << "total mass = " << scientific << M_tot << " Solar masses" << endl;
	cout << "stellar mass fraction = " << fixed << Stellar_fraction << endl;
	cout << "stellar mass = " << scientific << stellar_mass() << " Solar masses " << endl;
	unsigned int size{ Satellites.size() };
	cout << "No of satellites = " << size << endl;
	//print the properties of satellite galaxies if there are any								   
	if (size > 0) {
		cout << "Satellites:" << endl;
		for (unsigned int n{ 0 }; n < size; n++) { //loop through satellites
			Satellites[n].print_data(); //print satellite details
		}
	} else {
		cout << endl; //leave a blank line before next galaxy
	}
}
//main program function
int main() {
	//demonstrate galaxy class
	vector<Galaxy> galaxies; //declare vector of type galaxy
	galaxies.reserve(4); // reserve memory for galaxies
	//add some example galaxies into the vector
	galaxies.emplace_back(E0, 5, 2e7, 0.01);
	galaxies.emplace_back(Irr, 1.1, 26.5e8, 0.05);
	galaxies.emplace_back(Sb, 0, 1.001e9, 0.005);
	galaxies.emplace_back(E2, 4, 5e12, 0.0001);
	galaxies[0].change_type(E6); //change type of the first galaxy
	//add some example satellite galaxies
	galaxies[1].add_satellite(E3, 2.34, 3.67e7, 0.001, 1);
	galaxies[3].add_satellite(E1, 1.019, 23e8, 0.0001, 3);
	galaxies[3].add_satellite(E1, 1.003, 3.102e10, 0.0001, 3);
	galaxies[3].add_satellite(SBc, 4, 2.999e7, 0.005, 3);
	//iterate through the galaxies and print data for each galaxy
	for (auto iterator = galaxies.begin(); iterator != galaxies.end(); iterator++) {
		iterator->print_data();
	}
	return 0;
}