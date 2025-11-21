#include <iostream>
#include <vector>
#include "svgclass.hpp"
#include "reader.hpp"



color InColor (std::istream& in, std::string EnterMessege){
	double a_tmp = 0;
	double b_tmp = 0;
	double c_tmp = 0;

	std::cout << EnterMessege << std::endl;
	if (!(in >> a_tmp >> b_tmp >> c_tmp)){
		std::string tmp;
		in.clear();
		in >> tmp;
		return {tmp};
	}

	return {a_tmp, b_tmp, c_tmp};
}

double InDouble (std::istream& in, std::string EnterMessege){
	double a_tmp = 0;
	std::cout << EnterMessege << std::endl;
	if (!(in >> a_tmp)){
		throw std::invalid_argument("Wrong arg for some double.");
	}
	return a_tmp;
}

Point InPoint(std::istream& in, std::string EnterMessege){
	double a_tmp = 0;
	double b_tmp = 0;

	std::cout << EnterMessege << std::endl;
	if (!(in >> a_tmp >> b_tmp)){
		throw std::invalid_argument("Wrong arg for some Point.");
	}
	return {a_tmp, b_tmp};
}

std::vector<Point> polyPoints(std::string& input){
	if (input == ""){
		throw std::invalid_argument("Empty point-line.");
	}


	std::string xNum = "";
	std::string yNum = "";

	std::vector<Point> finalVec;

	int flag = 0;

	char letter;

	// std::cout << input.size() << std::endl;

	for (int i = 0; i < (int)input.size(); i++){
		letter = input[i];

		// std::cout << i << " " << xNum << " " << yNum << std::endl;
		if (letter == ','){
			// std::cout << "hi! 1 " << std::endl;
			flag = 1;
		} else if(letter == ' '){
			// std::cout << "hi! 2 " << xNum << " " << yNum << std::endl;
			finalVec.push_back({std::stod(xNum), std::stod(yNum)});
			xNum = "";
			yNum = "";
			flag = 0;
		} else if(flag == 0){
			// std::cout << "hi! 3 " << std::endl;
			xNum += letter;
		} else if(flag == 1){
			// std::cout << "hi! 4 " << std::endl;
			yNum += letter;
		} else{
			throw std::invalid_argument("Wrong char to double.");
			break;
		}

		// std::cout << "hi! 5 " << std::endl;
	}
	
	finalVec.push_back({std::stod(xNum), std::stod(yNum)});

	// for (int i = 0; i < finalVec.size(); i++){
	// 	finalVec[i].get();
	// }

	return finalVec;
}
