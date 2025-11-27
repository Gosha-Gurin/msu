#include "LagrangeClass.hpp"
#include <iostream>

/*

Поехали!
========


У нас есть точки функции и надо вычислить 
коэффициенты из многочлена Лагранжа.

--------------------


Базисный полином:
	l_i (x) = prod_{j = 0; j != i}^{n} ((x - x_j) / (x_i - x_j))

Итоговый многочлен:
	P(x) = sum_{i = 0}^{n}(y_i * l_i(x))

--------------------

 - Как мы будем все хранить? Точки хранить
(вроде) не придется, а вот коэффициенты - 
в массиве по-порядку степени (удобно ли?
								- вроде да)

 - Посик коэфф:
	Сразу в лоб считаем все из многочлена
	Лагранжа (получается вроде несложно, 
						но сомнительно...)

	Не понятно, как считать коэффициенты...

	Надо подумать, как организавить сумму
	произведений, где часть элементов 
	уходит...

	Короче предыдущая мысль была верна:
	2 варика и надо было выбрать второй,
	умножаем по-порядку скобки. Все просто
	как грабли.

	-----------   ------    --------------------------
	|a|b|c|d|1| x |-u|1| -> |-au|a-bu|b-cu|c-du|d-u|1|
	-----------   ------    --------------------------
	
*/

/*
 Что здесь есть:
    - Создание полинома (конструкторы стандартный и копирующий)
    - Перегруженны операторы =, ==, !=
                    и [] (запись точки формата poly[x] = y)
    - Функция AddDot (аналогично poly.Adddot(x, y))
    - Функция DotDelete (Удаляет введенную точку)
    - После изменения точек надо считать коэфф CoeffCalc();
    - Расчет значения в точке
 */

int main(){
	LagrangeClass::Polynomial poly1;
	LagrangeClass::Polynomial poly2;

	poly1[1] = 2;
	poly1.AddDot(2, 3);

	poly1.CoeffCalc();
	std::cout << "poly1: \n" << poly1;
    std::cout << "poly1(2.5) = " << poly1.PolyCalc(2.5) << std::endl;

	std::cout << std::endl;

	poly1[4] = 4;
	poly1.CoeffCalc();

	std::cout << "poly1: \n" << poly1;

	std::cout << std::endl;

	poly2[1] = 2;
	poly2[2] = 3;
	poly2[4] = 4;
    poly2[10] = -(1.7);
	poly2.CoeffCalc();

	std::cout << "poly2: \n" << poly2;

	std::cout << std::endl;

//     LagrangeClass::Polynomial poly3(poly2);
	LagrangeClass::Polynomial poly3;
    poly3 = poly2;
    
    if(poly3 == poly2){        
        std::cout << "True \n" << "poly3: \n" << poly3 << std::endl << "poly2: \n" << poly2;
    }
    
	std::cout << std::endl;
	
	poly3.DotDelete(4, 4);
	poly3.CoeffCalc();

    
    if(poly3 != poly2){        
        std::cout << "False \n" << "poly3: \n" << poly3 << std::endl << "poly2: \n" << poly2;
    }

	return 0;
}
