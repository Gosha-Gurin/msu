#include <iostream>
#include <vector>
#include <map>
#include "svgclass.hpp"


/*Структура проги:

В цикле читаем теги и их аргументы. После (std::cin >> a) = EOF записываем все в файл. Звучит не сложно =)

Теги и их аргументы:
	- Общие для каждого объекта (цвет заливки, цвет линии, толщина линии, вывод объекта (cout))
	- Круг (центр х, центр у, радиус)
	- Ломанная (коорды в виде "x1,y1 x2,y2 x3,y3 ...")
	- Текст (слишком много, смотри в задаче) - done
*/


/*ТУДУ:
	- Считование цвета как слова (red, blue, green и т.п.)
	- Дабавить теги =/
	- Сделать нормальным вывод document
	- Для удобства сделать отдельную комманду для вывода имеющихся тегов
		(как сейчас принт документа)

*/

std::map<std::string, int> tegs = {
	{"text", 1},
};

int main(){

	std::string tegInput;

	document FineDoc;
	

	std::cout << "Tegs: text\n-_-" << std::endl;
	while(std::cin >> tegInput){
		try {
			switch(tegs[tegInput]){
				case 1:
					{
						double a_tmp;
						double b_tmp;
						double c_tmp;
						std::string str_tmp;

						std::cout << "Enter fill-color: " << std::endl;
						if (!(std::cin >> a_tmp >> b_tmp >> c_tmp)){
							throw std::invalid_argument("Wrong arg for some double.");
						}

						color fill = {a_tmp, b_tmp, c_tmp};

						std::cout << "\nEnter stroke-color: " << std::endl;
						if (!(std::cin >> a_tmp >> b_tmp >> c_tmp)){
							throw std::invalid_argument("Wrong arg for some double.");
						}

						color strokeCol = {a_tmp, b_tmp, c_tmp};

						std::cout << "\nEnter stroke-width: " << std::endl;
						if (!(std::cin >> a_tmp)){
							throw std::invalid_argument("Wrong arg for some double.");
						}

						double strokeWid = a_tmp;

						std::cout << "\nEnter point: " << std::endl;
						if (!(std::cin >> a_tmp >> b_tmp)){
							throw std::invalid_argument("Wrong arg for some double.");
						}

						Point point = {a_tmp, b_tmp};

						
						std::cout << "\nEnter offset: " << std::endl;
						if (!(std::cin >> a_tmp >> b_tmp)){
							throw std::invalid_argument("Wrong arg for some double.");
						}

						Point offset = {a_tmp, b_tmp};

						
						std::cout << "\nEnter font-size: " << std::endl;
						if (!(std::cin >> a_tmp)){
							throw std::invalid_argument("Wrong arg for some double.");
						}

						
						double fontSize = a_tmp;

						
						std::string fontFam;
						std::cin.ignore();

						
						std::cout << "\nEnter font-famaly: " << std::endl;
						std::getline(std::cin, fontFam);

						std::string data;

						std::cout << "\nEnter text: " << std::endl;
						std::getline(std::cin, data);

						
						FineDoc.AddObject(new text(fill, strokeCol, strokeWid,
												point, offset, fontSize, 
												fontFam, data));

						std::cout << "\nYou add new text-teg!\n" << std::endl;
						break;
					}
				default:{
					throw std::invalid_argument("Wrong teg.");
				}
			}
		}
		catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;
		}
	}

	FineDoc.print(std::cout);

	return 0;
}