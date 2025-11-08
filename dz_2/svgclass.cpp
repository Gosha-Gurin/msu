#include <iostream>
#include "svgclass.hpp"



color::color(double r, double g, double b):
	red(r),
	green(g),
	blue(b)
{
	if ( !(((red >= 0) && (red <= 255))
		&& ((green >= 0) && (green <= 255))
		&& ((blue >= 0) && (blue <= 255)))){
		throw std::invalid_argument("RGB value must be >= 0 or <= 255.");
	}
}

void color::print(std::ostream& out) const {
	out << "("<< red << ", "
			<< green << ", "
			<< blue << ")" << std::endl;
}

void object::obj_print(std::ostream& out) const {
	out << "fill-color: ";
	fillColor.print(out);

	out << "stroke-color: ";
	strokeColor.print(out);

	out << "stroke-width" << strokeWidth << std::endl;
}


void text::print(std::ostream& out) const {
	
	obj_print(out); //Значения из класса-прообраза
	

	out <<
	"point: " << point.x << " " << point.y << "\n" <<
	"offset: "  << offset.x << " " << offset.y << "\n" <<
	"font-size: "  << fontSize << "\n" <<
	"font-famaly: "  << fontFamaly << "\n" <<
	"text: " << data << std::endl;
}

void document::AddObject(object* obj){
	object** tmp;
	if (count != 0){
		tmp = new object*[count];
		for (int i = 0; i < count; i++){
			tmp[i] = list[i];
		}
		delete [] list;

		count++;

		list = new object*[count];

		for (int i = 0; i < count-1; i++){
			list[i] = tmp[i];
		}

		list[count] = obj;

		delete [] tmp;
	} else{
		count+=1;
		list = new object*[count];
		list[count-1] = obj;
	}
}

document::~document(){
	delete [] list;
}

void document::print(std::ostream& out) const {
	for (int i = 0; i < count; i++){
		list[i]->print(out);
	}
}