#include<iostream>
#include<vector>
#include<iomanip>
#include<math.h>
using namespace std;

class Point {
private:
	float x;
	float y;
public:
	Point();
	Point(float x, float y);
	void displayCoordinates();
	float distanceTo(const Point& other);
};

class PointManager {
private:
	std::vector<Point> points;
public:
	void addPoint(const Point& point);
	void removePoint(int index);
	void displayAllPoints();
	float totalDistance();
};

Point::Point() : x(0), y(0) {}
Point::Point(float x, float y) : x(x), y(y) {}
void Point::displayCoordinates() {
	cout << "(" << fixed << setprecision(1) << x << ", " << fixed << setprecision(1) << y << ")" << endl;
}
float Point::distanceTo(const Point& other) {
	return sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
}

void PointManager::addPoint(const Point& point) {
	points.push_back(point);
}
void PointManager::removePoint(int index) {
	for (int i = 0; i < points.size(); i++) {
		if (i == index) {
			points.erase(points.begin() + i);
		}
	}
}
void PointManager::displayAllPoints() {
	cout << "All points:\n";
	for (int i = 0; i < points.size(); i++) {
		cout << "Point " << i << ": ";
		points[i].displayCoordinates();
		if (i != points.size() - 1) {
			cout << "==========\n";
		}
	}
}
float PointManager::totalDistance() {
	float sumDistance = 0.0f;
	for (int i = 0; i < points.size(); i++) {
		for (int j = 0; j < points.size(); j++)
			sumDistance += points[i].distanceTo(points[j]);
	}
	return sumDistance;
}

#include "main.h"
//int main() {
//	Point p1(1.5, 2.5);
//	Point p2(-3.5, 4.2);
//	Point p3(0.0, 0.0);
//	Point p4(-2.8, -1.3);
//	PointManager pm;
//	pm.addPoint(p1);
//	pm.addPoint(p2);
//	pm.addPoint(p3);
//	pm.addPoint(p4);
//	pm.displayAllPoints();
//
//}