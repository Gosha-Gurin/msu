#include <iostream>
#include <cmath>

#define MAX_LEXEMES 100


struct Lexeme{
	char op; //Если будет <=, то надо какой-то спец символ использовать
	double value;
	int priority;
};

void PrintLexemes(Lexeme* lexemes, int numLexemes){
	for (int k = 0; k < numLexemes; k++){
		if (lexemes[k].op != 0){
			std::cout << " - Lexeme('" << lexemes[k].op << "', "
					  << lexemes[k].priority << ")" << std::endl;
		} else{
			std::cout << " - Lexeme('value', "
					  << lexemes[k].value << ")" << std::endl;
		}
	}
}

int ScanLexemes(Lexeme* lexemes){
	char str[1024];
	char* ptr;
	int numLexemes = 0;

	if (!std::cin.getline(str, 1024)){
		std::cerr << "Шо-то не так =(" << std::endl;
		return -1;
		//Можно throw бросать, но мне лень обрабатывать =)
	}

	for (ptr = str; *ptr != 0;){
		//Читаем чиселку
		if (isdigit(*ptr) || *ptr == '.'){
			char* endPtr;

			if(numLexemes >= MAX_LEXEMES){
				std::cerr << "Слишком много лексем =(" << std::endl;
				return -1;
			}

			lexemes[numLexemes].value = strtod(ptr, &endPtr);
			//Видимо тут чиселка считывается до пробела, 
			lexemes[numLexemes].op = 0;
			lexemes[numLexemes].priority = 0;

			if (endPtr == ptr){
				std::cerr << "Шо-то не так с " << ptr << std::endl;
				return -1;
			}

			numLexemes++;

			ptr = endPtr;
		} else if (*ptr == '+' || *ptr == '-' ||
				*ptr == '*' || *ptr == '/' ||
				*ptr == '(' || *ptr == ')'){

			if(numLexemes >= MAX_LEXEMES){
				std::cerr << "Слишком много лексем =(" << std::endl;
				return -1;
			}

			lexemes[numLexemes].value = 0;

			if (*ptr == '-' && (numLexemes == 0 ||
				(numLexemes > 0 && lexemes[numLexemes - 1].op != 0))){
				lexemes[numLexemes].op = 'u';
				lexemes[numLexemes].priority = 3;
			} else if (*ptr == '*' || *ptr == '/'){
				lexemes[numLexemes].op = *ptr;
				lexemes[numLexemes].priority = 2;
			} else if (*ptr == '+' || *ptr == '-'){
				lexemes[numLexemes].op = *ptr;
				lexemes[numLexemes].priority = 1;
			} else if (*ptr == '('){
				lexemes[numLexemes].op = *ptr;
				lexemes[numLexemes].priority = 4;
			} else if (*ptr == ')'){
				lexemes[numLexemes].op = *ptr;
				lexemes[numLexemes].priority = 0;
			} else{
				std::cerr << "Шо-то не то засунул в лексемы (высунь!)" << std::endl;
				return -1;
			}

			numLexemes++;
			ptr++;
		} else if (std::isspace(*ptr)){
			ptr++;
		}
	}

	lexemes[numLexemes].op = '=';
	lexemes[numLexemes].value = 0;
	lexemes[numLexemes].priority = 0;

	numLexemes++;

	return numLexemes;
}

int ToPolandForm(Lexeme* lexemes, int numLexemes, Lexeme* polandLexemes){
	Lexeme stack[MAX_LEXEMES];
	int stackSize = 0;
	int numPolandLexemes = 0;

	// std::cout << "\n============================================\n";
	for (int k = 0; k < numLexemes; k++){
		if (lexemes[k].op == 0){
			polandLexemes[numPolandLexemes] = lexemes[k];
			numPolandLexemes++;
		} else{
			stack[stackSize] = lexemes[k];
			stackSize++;
		}

		bool working = true;

		while (stackSize >= 2 && working){
			working = false;

			if (stack[stackSize - 2].op == '(' && stack[stackSize - 1].op == ')'){
				stackSize -= 2;
				working = true;
			} else if (stack[stackSize - 2].op != '(' &&
				stack[stackSize - 2].priority >= stack[stackSize - 1].priority){
				// std::cout << "\nHi! " << stack[stackSize - 2].op << ", " << stack[stackSize - 1].op;
				polandLexemes[numPolandLexemes] = stack[stackSize - 2];
				numPolandLexemes++;
				stack[stackSize - 2] = stack[stackSize - 1];
				stackSize--;
				working = true;
			}
		}

		// std::cout << "\n";
		// std::cout << k << " stack: " << std::endl;
		// PrintLexemes(stack, stackSize);
		// std::cout << "\n";
		// std::cout << " polandLexemes: " << std::endl;
		// PrintLexemes(polandLexemes, numPolandLexemes);
	}

	// std::cout << "\n============================================\n";


	if (stackSize != 1){
		std::cerr << "Шо-то не то..." << std::endl;
		return -1;
	}

	if (stack[0].op != '='){
		std::cerr << "А где '='?" << std::endl;
		return -1;
	}

	return numPolandLexemes;
}

double CalculuPolandExpression(Lexeme* expression, int num){
	std::cout << "\n";
	std::cout << "PolandLexemes:" << std::endl;
	PrintLexemes(expression, num);
	std::cout << "\n";

	double stack[MAX_LEXEMES];
	int stackSize = 0;

	if (num <= 0){
		return 0;
	}

	for (int k = 0; k < num; k++){
		if (expression[k].op == 0){
			stack[stackSize] = expression[k].value;
			// std::cout << k << " 'value' " << stack[stackSize] << "\n";
			stackSize++;
		} else if (expression[k].op == '+' && stackSize >= 2){
			//Если у нас не 2 аргумента, то мы выкидываем ошибку.
			stack[stackSize - 2] = stack[stackSize - 2] + stack[stackSize - 1];
			// std::cout << k << " '+' " << stack[stackSize - 2] << "\n";
			stackSize--;
		} else if (expression[k].op == '-' && stackSize >= 2){
			//Если у нас не 2 аргумента, то мы выкидываем ошибку.
			stack[stackSize - 2] = stack[stackSize - 2] - stack[stackSize - 1];
			// std::cout << k << " '-' " << stack[stackSize - 2] << "\n";
			stackSize--;
		} else if (expression[k].op == '*' && stackSize >= 2){
			//Если у нас не 2 аргумента, то мы выкидываем ошибку.
			stack[stackSize - 2] = stack[stackSize - 2] * stack[stackSize - 1];
			// std::cout << k << " '*' " << stack[stackSize - 2] << "\n";
			stackSize--;
		} else if (expression[k].op == '/' && stackSize >= 2){
			//Если у нас не 2 аргумента, то мы выкидываем ошибку.
			stack[stackSize - 2] = stack[stackSize - 2] / stack[stackSize - 1];
			// std::cout << k << " '/' " << stack[stackSize - 2] << "\n";
			stackSize--;
		} else if (expression[k].op == 'u'){
			//Если у нас не 2 аргумента, то мы выкидываем ошибку.
			stack[stackSize - 1] = -stack[stackSize - 1];
			// std::cout << k << " 'u' " << stack[stackSize - 1] << "\n";
		} else{
			return NAN;
		}
	}

	if (stackSize == 1){ return	stack[0]; }

	return NAN;
}

int main(){
	Lexeme lexemes[MAX_LEXEMES] = {0};
	int numLexemes = 0;
	Lexeme polandLexemes[MAX_LEXEMES] = {0};
	int numPolandLexemes = 0;

	numLexemes = ScanLexemes(lexemes);

	std::cout << "numLexemes = " << numLexemes << std::endl;

	std::cout << "\n";
	std::cout << "Lexemes:" << std::endl;
	PrintLexemes(lexemes, numLexemes);
	std::cout << "\n";

	numPolandLexemes = ToPolandForm(lexemes, numLexemes, polandLexemes);

	std::cout << "\n";
	std::cout << "numPolandLexemes = " << numPolandLexemes << std::endl;

	// std::cout << "\n";
	// std::cout << "PolandLexemes:" << std::endl;
	// PrintLexemes(polandLexemes, numPolandLexemes);
	// std::cout << "\n";
	
	double result = CalculuPolandExpression(polandLexemes, numPolandLexemes);

	std::cout << "\nResult: " << result << "\n" << std::endl;

	return 0;
}