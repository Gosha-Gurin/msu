#include <iostream>
#include <vector>
#include <map>
#include "svgclass.hpp"
#include "reader.hpp"


/*Структура проги:

В цикле читаем теги и их аргументы. После (std::cin >> a) = EOF записываем все в файл. Звучит не сложно =)

Теги и их аргументы:
	- Общие для каждого объекта (цвет заливки, цвет линии, толщина линии, вывод объекта (cout)) - done
	- Круг (центр х, центр у, радиус)
	- Ломанная (коорды в виде "x1,y1 x2,y2 x3,y3 ...") - done
	- Текст (слишком много, смотри в задаче) - done
*/


/*ТУДУ:
	- Дабавить теги =/
	- Сделать нормальным вывод document

*/

std::map<std::string, int> tegs = {
	{"print", 1},
	{"test", 2},
	{"text", 3},
	{"polyline", 4},
	{"circle", 5}
};

int main(){

	std::string tegInput;

	document FineDoc;
	

	std::cout << "Tegs: test, print, text, polyline, circle\n" << std::endl;
	while(std::cin >> tegInput){
		try {
			switch(tegs[tegInput]){
				case 1:
				{
					FineDoc.print(std::cout);
					break;
				}


				case 2:
				{
					std::cout << "\nTest!\n" << std::endl;
					break;
				}


				case 3:
				{
					color fill = InColor(std::cin, "Enter fill-color: ");

					color strokeCol = InColor(std::cin, "Enter stroke-color: ");
					
					double strokeWid = InDouble(std::cin, "Enter stroke-width: ");
					
					Point point = InPoint(std::cin, "Enter start-point: ");

					Point offset = InPoint(std::cin, "Enter offset: ");

					double fontSize = InDouble(std::cin, "Enter font-size: ");
					
					std::string fontFam;
					std::cin.ignore();
					
					std::cout << "Enter font-famaly: " << std::endl;
					std::getline(std::cin, fontFam);

					std::string data;

					std::cout << "Enter text: " << std::endl;
					std::getline(std::cin, data);

					

					FineDoc.AddObject(new text(fill, strokeCol, strokeWid,
											point, offset, fontSize, 
											fontFam, data));

					std::cout << "\nYou add new text-teg!\n" << std::endl;
					break;
				}


				case 4:
				{
					color fill = InColor(std::cin, "Enter fill-color: ");

					color strokeCol = InColor(std::cin, "Enter stroke-color: ");
					
					double strokeWid = InDouble(std::cin, "Enter stroke-width: ");

					std::string points;
					
					std::cout << "Enter points: " << std::endl;
					std::cin.ignore();
					std::getline(std::cin, points);

					// std::cout << points << std::endl;

					FineDoc.AddObject(new polyline(fill, strokeCol, strokeWid, polyPoints(points)));					

					std::cout << "\nYou add new polyline-teg!\n" << std::endl;
					break;
				}


				case 5:
				{
					color fill = InColor(std::cin, "Enter fill-color: ");

					color strokeCol = InColor(std::cin, "Enter stroke-color: ");
					
					double strokeWid = InDouble(std::cin, "Enter stroke-width: ");

					Point center = InPoint(std::cin, "Enter center: ");

					double radius = InDouble(std::cin, "Enter radius: ");

					FineDoc.AddObject(new circle(fill, strokeCol, strokeWid, center, radius));

					std::cout << "\nYou add new circle-teg!\n" << std::endl;
					break;
				}


				default:
				{
					throw std::invalid_argument("Wrong teg.");
					break;
				}
			}
		}

		catch (const std::exception& e) {
			std::cerr << "\nError with this:\n" << e.what() << std::endl;
		}

	}

	FineDoc.print(std::cout);

	return 0;
}