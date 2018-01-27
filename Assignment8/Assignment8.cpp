//Assignment8.cpp by Sam Brind
//Class hierarchy of 2D and 3D shapes
#include <iostream>
#include <cmath>
#include <vector>
//use standard namespace
using namespace std;
//declare pi constant
const double pi{ 3.14159265359 };
//declare abstract base shape class
class Shape {
protected:
	int dimension;
public:
	//default constructor
	Shape() : dimension{ 0 } {}
	//parameterised constructor
	Shape(const int dimension_in) : dimension{ dimension_in } {}
	//destructor
	virtual ~Shape() { cout << "Destroying shape..." << endl; }
	//pure virtual functions
	virtual double area() const = 0;
	virtual double volume() const = 0;
	virtual void print() const = 0;
};
//abstract derived 2D shape class
class Two_Dimensional : public Shape {
protected:
	double height;
	double width;
public:
	//default constructor
	Two_Dimensional() : Shape(2) { height = 0; width = 0; }
	//parameterised constructor
	Two_Dimensional(const double height_in, const double width_in) : Shape(2) { height = height_in; width = width_in; }
	//destructor
	virtual ~Two_Dimensional() { cout << "Destroying 2-D shape..." << endl; }
	//function to return height
	double return_height() const {
		return height;
	}
	//function to return width
	double return_width() const {
		return width;
	}
	//pure virtual area
	virtual double area() const = 0;
	//2D shapes have zero volume
	double volume() const { return 0; }
	//pure virtual print
	virtual void print() const = 0;
};
//abstract derived 3D shape class
class Three_Dimensional : public Shape {
protected:
	double height;
	double width;
	double depth;
public:
	//default constructor
	Three_Dimensional() : Shape(3) { height = 0; width = 0; depth = 0; }
	//parameterised constructor
	Three_Dimensional(const double height_in, const double width_in, const double depth_in) : Shape(3) {
		height = height_in; width = width_in; depth = depth_in;
	}
	//destructor
	virtual ~Three_Dimensional() { cout << "Destroying 3-D shape..." << endl; }
	//pure virtual functions
	virtual double area() const = 0;
	virtual double volume() const = 0;
	virtual void print() const = 0;
};
//derived class for rectangle
class Rectangle : public Two_Dimensional {
public:
	//default constructor
	Rectangle() : Two_Dimensional() {}
	//parameterised constructor
	Rectangle(const double height_in, const double width_in) : Two_Dimensional(height_in, width_in) {}
	//destructor
	~Rectangle() { cout << "Destroying rectangle..." << endl; }
	//area function
	double area() const {
		return height*width; //A = hw
	}
	//print function
	void print() const {
		cout << "Rectangle:" << endl;
		cout << "	height: " << height << endl;
		cout << "	width: " << width << endl;
		cout << "	area: " << area() << endl;
		cout << "	volume: " << volume() << endl;
	}
};
//derived class for square
class Square : public Rectangle {
public:
	//default constructor
	Square() : Rectangle() {}
	//parameterised constructor
	Square(const double length_in) : Rectangle(length_in, length_in) {}
	//destructor
	~Square() { cout << "Destroying square..." << endl; }
	//print function
	void print() const {
		cout << "Square:" << endl;
		cout << "	length: " << height << endl;
		cout << "	area: " << area() << endl;
		cout << "	volume: " << volume() << endl;
	}
};
//derived class for ellipse
class Ellipse : public Two_Dimensional {
public:
	//default constructor
	Ellipse() : Two_Dimensional() {}
	//parameterised constructor
	Ellipse(const double height_in, const double width_in) : Two_Dimensional(height_in, width_in) {}
	//destructor
	~Ellipse() { cout << "Destroying ellipse..." << endl; }
	//area function
	double area() const {
		return pi*(height / 2)*(width / 2); //A = pi*ab
	}
	//print function
	void print() const {
		cout << "Ellipse:" << endl;
		cout << "	height: " << height << endl;
		cout << "	width: " << width << endl;
		cout << "	area: " << area() << endl;
		cout << "	volume: " << volume() << endl;
	}
};
//derived class for circle
class Circle : public Ellipse {
public:
	//default constructor
	Circle() : Ellipse() {}
	//parameterised constructor
	Circle(const double diameter_in) : Ellipse(diameter_in, diameter_in) {}
	//destructor
	~Circle() { cout << "Destroying circle..." << endl; }
	//print function
	void print() const {
		cout << "Circle:" << endl;
		cout << "	radius: " << height / 2 << endl;
		cout << "	area: " << area() << endl;
		cout << "	volume: " << volume() << endl;
	}
};
//derived class for cuboid
class Cuboid : public Three_Dimensional {
public:
	//default constructor
	Cuboid() : Three_Dimensional() {}
	//parameterised constructor
	Cuboid(const double height_in, const double width_in, const double depth_in) : Three_Dimensional(height_in, width_in, depth_in) {}
	//destructor
	~Cuboid() { cout << "Destroying cuboid..." << endl; }
	//area function
	double area() const {
		return 2 * (height*depth + height*width + width*depth); //A = 2hd + 2hw + 2wd
	}
	//volume function
	double volume() const {
		return height*width*depth; //V = hwd
	}
	//print function
	void print() const {
		cout << "Cuboid:" << endl;
		cout << "	height: " << height << endl;
		cout << "	width: " << width << endl;
		cout << "	depth: " << depth << endl;
		cout << "	area: " << area() << endl;
		cout << "	volume: " << volume() << endl;
	}
};
//derived class for cube
class Cube : public Cuboid {
public:
	//default constructor
	Cube() : Cuboid() {}
	//parameterised constructor
	Cube(const double length_in) : Cuboid(length_in, length_in, length_in) {}
	//destructor
	~Cube() { cout << "Destroying cube..." << endl; }
	//print function
	void print() const {
		cout << "Cube:" << endl;
		cout << "	length: " << height << endl;
		cout << "	area: " << area() << endl;
		cout << "	volume: " << volume() << endl;
	}
};
//derived class for ellipsoid
class Ellipsoid : public Three_Dimensional {
public:
	//default constructor
	Ellipsoid() : Three_Dimensional() {}
	//parameterised constructor
	Ellipsoid(const double height_in, const double width_in, const double depth_in) : Three_Dimensional(height_in, width_in, depth_in) {}
	//destructor
	~Ellipsoid() { cout << "Destroying ellipsoid..." << endl; }
	//area function
	double area() const {
		double sum = (1 / 3)*(pow(0.25*height*width, 1.6) + pow(0.25*height*depth, 1.6) + pow(0.25*width*depth, 1.6));
		return 4 * pi*pow(sum, 1 / 1.6); //A approx = 4pi*(1/3((hw)^1.6 + (hd)^1.6 + (wd)^1.6))1/1.6
	}
	//volume function
	double volume() const {
		return (4 / 3)*pi*(height / 2)*(width / 2)*(depth / 2); //V = 4/3pi*hwd
	}
	//print function
	void print() const {
		cout << "Ellipsoid:" << endl;
		cout << "	height: " << height << endl;
		cout << "	width: " << width << endl;
		cout << "	depth: " << depth << endl;
		cout << "	area: " << area() << endl;
		cout << "	volume: " << volume() << endl;
	}
};
//derived class for sphere
class Sphere : public Ellipsoid {
public:
	//default constructor
	Sphere() : Ellipsoid() {}
	//parameterised constructor
	Sphere(const double diameter_in) : Ellipsoid(diameter_in, diameter_in, diameter_in) {}
	//destructor
	~Sphere() { cout << "Destroying sphere..." << endl; }
	//area function
	double area() const {
		return 4 * pi*pow(height / 2, 2); //A = 4pi*r^2
	}
	//print function
	void print() const {
		cout << "Sphere:" << endl;
		cout << "	radius: " << height / 2 << endl;
		cout << "	area: " << area() << endl;
		cout << "	volume: " << volume() << endl;
	}
};
//derived prism class
class Prism : public Three_Dimensional {
protected:
	const Two_Dimensional* face;
public:
	//default constructor
	Prism() : Three_Dimensional() {}
	//parameterised constructor
	Prism(const double depth_in, const Two_Dimensional *area_pointer) : Three_Dimensional() {
		depth = depth_in;
		height = area_pointer->return_height();
		width = area_pointer->return_width();
		face = area_pointer;
	}
	//destructor
	~Prism() { cout << "Destroying prism..." << endl; }
	//area function
	double area() const { return 0; }
	//volume function
	double volume() const {
		return depth*face->area(); //V = Ad
	}
	//print function
	void print() const {
		cout << "Prism:" << endl;
		cout << "	face: [" << endl;
		cout << "	"; face->print();
		cout << "	]" << endl;
		cout << "	depth: " << depth << endl;
		cout << "	volume: " << volume() << endl;
	}
};
//main program function
int main() {
	//create vector to store pointers to shapes
	vector <Shape*> shapes;
	//create 8 shapes and assign pointers
	shapes.push_back(new Rectangle(2, 3)); //rectangle
	shapes.push_back(new Square(3)); //square
	shapes.push_back(new Ellipse(2, 3)); //ellipse
	shapes.push_back(new Circle(4)); //circle
	shapes.push_back(new Cuboid(2, 3, 0.5)); //cuboid
	shapes.push_back(new Cube(2)); //cube
	shapes.push_back(new Ellipsoid(4, 8, 1)); //ellipsoid
	shapes.push_back(new Sphere(2)); //sphere
	Two_Dimensional* square_pointer = new Square(2); //create a square pointer to use for a prism
	shapes.push_back(new Prism(5, square_pointer)); //square faced prism
	for (auto iterator = shapes.begin(); iterator != shapes.end(); iterator++) { //iterate over shapes vector
		(*iterator)->print(); //call shape's print function
		delete *iterator; //delete the shape
	}
	//delete the square pointer
	delete square_pointer;
	//clear the shapes vector
	shapes.clear();
	return 0;
}