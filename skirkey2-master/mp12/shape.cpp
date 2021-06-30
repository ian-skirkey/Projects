#include "shape.hpp"
 

//Base class
//Please implement Shape's member functions
//constructor, getName()
//
//Base class' constructor should be called in derived classes'
//constructor to initizlize Shape's private variable 

Shape :: Shape(string newName) {
	name_ = newName ;
}

string Shape :: getName() {
	return name_ ;
}

//Rectangle
//Please implement the member functions of Rectangle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

Rectangle :: Rectangle(double width, double length) : Shape("Rectangle") {
	length_ = length ;
	width_ = width ;
}

double Rectangle :: getVolume() const {
	return 0 ;
}

double Rectangle :: getArea() const {
	return length_ * width_ ;
}

Rectangle Rectangle :: operator + (const Rectangle &a) {
	Rectangle sum = Rectangle(0.0, 0.0) ;
	sum.length_ = a.length_ + length_ ;
	sum.width_ = a.width_ + width_ ;
	return sum ;
}

Rectangle Rectangle :: operator - (const Rectangle &a) {
	Rectangle dif = Rectangle(0.0, 0.0) ;
	dif.length_ = max(0.0, length_ - a.length_) ;
	dif.width_ = max(0.0, width_ - a.width_) ;
	return dif ;
}



double Rectangle::getWidth()const{return width_;}
double Rectangle::getLength()const{return length_;}


//Circle
//Please implement the member functions of Circle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

Circle :: Circle(double r) : Shape("Circle") {
	radius_ = r ;
}

double Circle :: getVolume() const {
	return 0 ;
}

double Circle :: getArea() const {
	return M_PI * radius_ * radius_ ;
}

Circle Circle :: operator + (const Circle &a) {
	Circle sum = Circle(0.0) ;
	sum.radius_ = a.radius_ + radius_ ; 
	return sum ;
}

Circle Circle :: operator - (const Circle &a) {
	Circle dif = Circle(0.0) ;
	dif.radius_ = max(0.0, radius_ - a.radius_) ;
	return dif ;
}

double Circle::getRadius()const{return radius_;}

//Sphere
//Please implement the member functions of Sphere:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

Sphere :: Sphere(double r) : Shape("Sphere") {
	radius_ = r ;
}

double Sphere :: getVolume() const {
	return (4.0/3.0) * M_PI * radius_ * radius_ * radius_ ;
}

double Sphere :: getArea() const {
	return 4 * M_PI * radius_ * radius_ ;
}

Sphere Sphere :: operator + (const Sphere &a) {
	Sphere sum = Sphere(0.0) ;
	sum.radius_ = a.radius_ + radius_ ;
	return sum ;
}

Sphere Sphere :: operator - (const Sphere &a) { 
	Sphere dif = Sphere(0.0) ;
	dif.radius_ = max(0.0, radius_ - a.radius_) ;
	return dif ;
}



double Sphere::getRadius()const{return radius_;}

//Rectprism
//Please implement the member functions of RectPrism:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

RectPrism :: RectPrism(double w, double l, double h) : Shape("RectPrism") {
	length_ = l ;
	width_ = w ;
	height_ = h ;
}

double RectPrism :: getVolume() const {
	return length_ * width_ * height_ ;
}

double RectPrism :: getArea() const {
	return 2 * (length_ * width_ + length_ * height_ + width_ * height_) ;
}

RectPrism RectPrism :: operator + (const RectPrism &a) {
	RectPrism sum = RectPrism(0.0, 0.0, 0.0) ;
	sum.length_ = length_ + a.length_ ;
	sum.width_ = width_ + a.width_ ;
	sum.height_ = height_ + a.height_ ;
	return sum ;
}

RectPrism RectPrism :: operator - (const RectPrism &a) {
	RectPrism dif = RectPrism(0.0, 0.0, 0.0) ;
	dif.length_ = max(0.0, length_ - a.length_) ;
	dif.width_ = max(0.0, width_ - a.width_) ;
	dif.height_ = max(0.0, height_ - a.height_) ;
	return dif ;
}


double RectPrism::getWidth()const{return width_;}
double RectPrism::getHeight()const{return height_;}
double RectPrism::getLength()const{return length_;}


 
// Read shapes from test.txt and initialize the objects
// Return a vector of pointers that points to the objects 
vector<Shape*> CreateShapes(char* file_name){
	//@@Insert your code here
	
	vector<Shape*> vect ;
	int k, size ;
	double a, b, c ;
	string name ;
	
	ifstream ifs (file_name, std::ifstream::in) ;
	ifs >> size ;
	
	for (k = 0; k < size; k++) {
		
		ifs >> name ;
		Shape *n ;
		
	if (name == "Sphere") {
		ifs >> a ;
		n = new Sphere(a) ;
	}
	if (name == "RectPrism") {
		ifs >> a >> b >> c ;
		n = new RectPrism(a, b, c) ;
	}
	if (name == "Circle") {
		ifs >> a ;
		n = new Circle(a) ;
	}
	if (name == "Rectangle") {
		ifs >> a >> b ;
		n = new Rectangle(a, b) ;
	}
	
	vect.push_back(n) ;
	
	}
	
	return vect; // please remeber to modify this line to return the correct value
}

// call getArea() of each object 
// return the max area
double MaxArea(vector<Shape*> shapes){
	double max_area = 0;
	//@@Insert your code here
int k ;

for (k = 0; k < shapes.size(); k++) {
	if (shapes[k]->getArea() > max_area) {
		max_area = shapes[k]->getArea() ;
	}
}
	
	return max_area ;
}


// call getVolume() of each object 
// return the max volume
double MaxVolume(vector<Shape*> shapes){
	double max_volume = 0;
	//@@Insert your code here
int k ;

for (k = 0; k < shapes.size(); k++) {
	if (shapes[k]->getVolume() > max_volume) {
		max_volume = shapes[k]->getVolume() ;
	}
}
	
	return max_volume;
}

