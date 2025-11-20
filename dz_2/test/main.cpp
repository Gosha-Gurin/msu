#include <iostream>
#include <vector>

std::vector<double> fun(std::string str){
	int i = 0;
	char letter = str[0];
	std::string word = "";
	std::vector<double> fin;
	while(letter != EOF){
		if (letter == ',' || letter == ' '){
			fin.push_back(std::stod(word));
			word = "";
			i+=1;
		} else {
			word += letter;
			i += 1;
		}

		letter = str[i];
	}
	return fin;
}


int main(){
	std::string tmp;
	std::vector<double> split;
	std::getline(std::cin, tmp);
	split = fun(tmp);
	for (int i = 0; i < split.size(); i++){
		std::cout << split[i] << std::endl;
	}
	return 0;
}