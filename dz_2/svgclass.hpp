#include <iostream>
// #include <map>
#include <vector>
// #include <string>

#ifndef SVGCLASS_HPP
#define SVGCLASS_HPP

struct Point {
	double x;
	double y;

	double getX() const{
		return x;
	}

	double getY() const{
		return x;
	}
};

// struct RGB{
// 	int red;
// 	int green;
// 	int blue;
// };


// none, white, black, red, green, blue, rgb (*, *, *)
class color
{
	double red;
	double green;
	double blue;
	std::string TextColor;
public:
	color() {};
	color(std::string color);
	color(double r, double g, double b);

	~color() {};

	void print(std::ostream& out) const;
};


class object{
	color fillColor;
	color strokeColor;
	double strokeWidth;
public:

	object(color fillCol, color strokeCol, double strokeWid):
	fillColor(fillCol),
	strokeColor(strokeCol),
	strokeWidth(strokeWid)
	{};

	void obj_print(std::ostream& out) const;//Принтуем общие значения для объедков.
	virtual void print(std::ostream& out) const = 0;

	virtual ~object() {};
};


class text : public object{
	Point point; //x и y
	Point offset; //dx и dy
	double fontSize; // font-size
	std::string fontFamaly; // font-famaly
	std::string data; //Сам текст
public:
	text(color fillCol, color strokeCol,
		double strokeWid, Point p,
		Point o, double size,
		std::string fontFam, std::string value):
	object(fillCol, strokeCol, strokeWid),
	point(p),
	offset(o),
	fontSize(size),
	fontFamaly(fontFam),
	data(value)
	{};

	void print(std::ostream& out) const override;


	~text() {};
};


class polyline : public object{
	std::vector<Point> points;
public:
	polyline(color fillCol, color strokeCol,
		double strokeWid, std::vector<Point> data):
	object(fillCol, strokeCol, strokeWid),
	points(data)
	{};

	void print(std::ostream& out) const override;

	~polyline(){};//По идее в векторе уже все реализовано, так что с деструктором возиться не нужно
	//по той же причине нам не нужна отдельная переменная для количества (существует .size() )
};

class circle : public object{
	Point center;
	double radius;
public:
	circle(color fillCol, color strokeCol,
		double strokeWid, Point cen, double r):
	object(fillCol, strokeCol, strokeWid),
	center(cen),
	radius(r)
	{};

	void print(std::ostream& out) const override;

	~circle(){};
};

class document{
	object** list;
	size_t count;
public:
	document():
		list(nullptr),
		count(0)
	{};

	void AddObject(object* obj);

	void print(std::ostream& out) const;

	~document();
};

#endif