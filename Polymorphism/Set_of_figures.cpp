#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <iomanip> 
#include <memory>
#include <sstream>

using std::string;
using std::cout;
using std::vector;
using std::cin;
using std::endl;
using std::fixed;

class Figure
{
public:
	Figure(const string& name): name(name){}
	virtual string Name() = 0;
	virtual double Perimeter() = 0;
	virtual double Area() = 0;
protected:
	const string name;
};

class Triangle : public Figure
{
public:
	Triangle (const string& name, const int& a, const int& b, const int& c):
		Figure(name), a(a), b(b), c(c){}

	string Name() override {
		return name;
	}
	double Perimeter() override {
		return a + b + c;
	}
	double Area() override {
		return sqrt(Perimeter()/2 * (Perimeter()/2 - a) * (Perimeter()/2 - b) * (Perimeter()/2 - c));
	}
private:
	const double a;
	const double b;
	const double c;
};

class Rect : public Figure
{
public:
	Rect(const string& name, const int& width , const int& height) :
		Figure(name), width(width), height(height){}
	string Name() override {
		return  name;
	}
	double Perimeter() override {
		return (width + height) * 2;
	}
	double Area() override {
		return width * height;
	}

private:
	const double width;
	const double height;
};

class Circle : public Figure
{
public:
	Circle(const string& name, const int& r) :
		Figure(name), r(r) {}
	string Name() override {
		return name;
	}
	double Perimeter() override {
		return 2 * 3.14 * r;
	}
	double Area() override {
		return 3.14 * r * r;
	}

private:
	const double r;
};

std::shared_ptr<Figure> CreateFigure(std::istringstream& line) {
	string name;
	line >> name;

	if (name == "RECT") {
		double width, height;

		line >> width >> height;

		return std::make_shared<Rect>(name, width, height);
	}

	else if (name == "TRIANGLE") {
		double a, b, c;

		line >> a >> b >> c;
		return std::make_shared<Triangle>(name, a, b, c);
	}

	else if (name == "CIRCLE") {
		double r;

		line >> r;

		return std::make_shared<Circle>(name, r);
	}

	return 0;
}

//int main() {
//	vector<std::shared_ptr<Figure>> figures;
//	for (string line; getline(cin, line); ) {
//		std::istringstream is(line);
//
//		string command;
//		is >> command;
//		if (command == "ADD") {
//			is >> std::ws;
//			figures.push_back(CreateFigure(is));
//		}
//		else if (command == "PRINT") {
//			for (const auto& current_figure : figures) {
//				cout << fixed << std::setprecision(3)
//					<< current_figure->Name() << " "
//					<< current_figure->Perimeter() << " "
//					<< current_figure->Area() << endl;
//			}
//		}
//	}
//	return 0;
//}