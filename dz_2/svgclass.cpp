#include <iostream>
#include <vector>
#include "svgclass.hpp"



color::color(double r, double g, double b):
	red(r),
	green(g),
	blue(b),
	TextColor("")
{
	if ( !(((red >= 0) && (red <= 255))
		&& ((green >= 0) && (green <= 255))
		&& ((blue >= 0) && (blue <= 255)))){
		throw std::invalid_argument("RGB value must be >= 0 or <= 255.");
	}
}


color::color(std::string color):
	red(0),
	green(0),
	blue(0),
	TextColor(color){
		if ((TextColor != "red") &&
			(TextColor != "green") &&
			(TextColor != "blue") &&
			(TextColor != "white") &&
			(TextColor != "black") &&
			(TextColor != "pink") &&
			(TextColor != "purple") &&
			(TextColor != "grey") &&
			(TextColor != "none")){
			throw std::invalid_argument("Wrong color arg.");
		}
}


void color::print(std::ostream& out) const {
	if (TextColor == ""){
		out << "rgb("<< red << ","
				<< green << ","
				<< blue << ")";
	} else{
		out << TextColor;
	}
}


void object::obj_print(std::ostream& out) const {
	out << "fill=\"";
	fillColor.print(out);
	out << "\" stroke=\"";
	strokeColor.print(out);
	out << "\" stroke-width=\"" << strokeWidth << "\"";
}


void text::print(std::ostream& out) const{
	out << "    <text x=\"" << point.getX() << "\" y=\""
		<< point.getY() << "\" "
		<< "dx=\"" << point.getX() << "\" dy=\""
		<< point.getY() << "\" "
		<< "font-size=\"" << fontSize << "\" "
		<< "font-family=\"" << fontFamaly << "\" ";

	obj_print(out);
	out << ">\n"
		<< "    " << data << "\n    </text>" << std::endl;
}


void polyline::print(std::ostream& out) const{
	out << "    <polyline points=\"";
	for (int i = 0; i < (int)points.size(); i++){
		if (i != (int)points.size() - 1){
			out << points[i].getX() << "," << points[i].getY() << " ";
		} else{
			out << points[i].getX() << "," << points[i].getY() << "\" ";
		}
	}

	obj_print(out);
	out << ">" << std::endl;
}

void circle::print(std::ostream& out) const{
	out << "    <circle cx=\"" << center.getX() << "\" "
		<< "cy=\"" << center.getX() << "\" ";

	obj_print(out);
	out << ">" << std::endl;
}


void document::AddObject(object* obj){
	object** tmp;
	if (count != 0){
// 		std::cout << "hi!" << std::endl;
		tmp = new object*[count];
		for (int i = 0; i < count; i++){
			tmp[i] = list[i];
		}
		delete [] list;

		count++;

		list = new object*[count];

		for (int i = 0; i < count - 1; i++){
			list[i] = tmp[i];
		}

		list[count-1] = obj;


		delete [] tmp;

		std::cout << "\n";
	} else{
		list = new object*[1];
		list[0] = obj;
		count = 1;
	}
}


void document::print(std::ostream& out) const {
	out << "\n<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n" << std::endl;

	out << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">" << std::endl;

	for (int i = 0; i < count; i++){
        std::cout << "\n";
		list[i]->print(out);
	}

	out << "\n</svg>\n" << std::endl;
}


document::~document(){
    for (int i = 0; i < count; i++){
		delete list[i];
	}
	delete [] list;
}
