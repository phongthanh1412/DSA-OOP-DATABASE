#include<iostream>
#include<cmath>
using namespace std;

class Point3D {
private:
	double x, y, z;
public:
	Point3D();
	Point3D(double x, double y, double z);
	double distance(Point3D other);
	void move(double dx, double dy, double dz);
	void rotate();
};

Point3D::Point3D() {
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Point3D::Point3D(double x, double y, double z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

double Point3D::distance(Point3D other) {
	return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2) + pow(z - other.z, 2));
}

void Point3D::move(double dx, double dy, double dz) {
	x += dx;
	y += dy;
	z += dz;
	//cout << "(" << x << ";" << y << ";" << z << ")" << endl;
}

void Point3D::rotate() {
	double temp = x;
	x = -y;
	y = temp;
	//cout << "(" << x << ";" << y << ";" << z << ")" << endl;
}

#include "main.h"

//int main() {
//	double xa, ya, za;
//	cin >> xa >> ya >> za;
//	Point3D A(xa, ya, za);
//
//	double xb, yb, zb;
//	cin >> xb >> yb >> zb;
//	Point3D B(xb, yb, zb);
//
//	cout << A.distance(B) << endl;
//	A.move(3, 4, 5);
//	B.rotate();
//
//	return 0;
//}