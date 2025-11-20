#include <iostream>
#include <vector>
#include "svgclass.hpp"

#ifndef READER_HPP
#define READER_HPP

color InColor (std::istream& in, std::string EnterMessege);

double InDouble (std::istream& in, std::string EnterMessege);

Point InPoint (std::istream& in, std::string EnterMessege);

std::vector<Point> polyPoints(std::string& input);
#endif