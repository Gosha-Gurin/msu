#include <iostream>
#include <cmath>

#define BUFFER_LEN 256

double CalculuExpression(char* str, int len){
	double value;
	char* ptr;//Нужно для проверки нормального считывания...

	/*Читаем(кВеРх НоГаМи) сначала низкоприоритетные операторы ->
			разделяем на 2 подстроки -> вычесляем их по рекурии ->
			фиксируем прибыль*/


	
	if (str[0] == '!'){
		return bool(!CalculuExpression(str + 1, len - 1));
	}

	for (int i = len-1; i >= 0; i--){
		if (str[i] == '<'){
			if (str[i+1] == '='){
				return bool(CalculuExpression(str, i) <=
				CalculuExpression(str + i + 2, len - i - 2));
			} else{
				return bool(CalculuExpression(str, i) <
				CalculuExpression(str + i + 1, len - i - 1));
			}
		}
	}	

	for (int i = len-1; i >= 0; i--){
		if (str[i] == '-' && i == 0){
			return -CalculuExpression(str + 1, len - 1);
		} else if (str[i] == '+'){
			return CalculuExpression(str, i) +
				CalculuExpression(str + i + 1, len - i - 1);
		} else if (str[i] == '-'){
			return CalculuExpression(str, i) -
				CalculuExpression(str + i + 1, len - i - 1);
			//Гошин код (и опять же - это я =) )
		}
	}

	for (int i = len-1; i >= 0; i--){
		if (str[i] == '*'){
			return CalculuExpression(str, i) *
				CalculuExpression(str + i + 1, len - i - 1);
		} else if (str[i] == '/'){
			return CalculuExpression(str, i) /
				CalculuExpression(str + i + 1, len - i - 1);
		}
	}


	//Сухой остаток - чиселка


	if (len == 0){
		std::cerr << "Пустая строчка..." << std::endl;
		return NAN;
	}

	value = strtod(str, &ptr);

	if (ptr != str + len){
		std::cerr << "Шо-то пошло не так 1=(" << std::endl;
		return NAN;
	}

	return value;
}

int RemoveSpace(char* str){
	int newLen = 0;

	for (int i = 0; str[i] != 0; i++){
		if (isspace(str[i])){ continue; }

		str[newLen++] = str[i];
	}

	str[newLen] = 0;
	return newLen;
}

int main(){
	char str[BUFFER_LEN];
	int len;

	if (!std::cin.getline(str, BUFFER_LEN)){
		std::cerr << "Шо-то пошло не так 2=(" << std::endl;
		return 1;
	}

	len = RemoveSpace(str);

	double result;
	result = CalculuExpression(str, len);

	std::cout << "Result: " << result << std::endl;

	return 0;
}