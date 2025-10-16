#include <iostream>
#include <vector>
#include "LagrangeClass.hpp"


namespace LagrangeClass{


	std::vector<double> MultipluingPolynomials(
		const std::vector<double> FirstPoly,
		const std::vector<double> Second_Poly)
	{

		if (Second_Poly.size() != 2){
			std::cerr << "Умножаешь не на скобку, "
						 << "а на что-то сложнее. "
						 << "Либо перепиши, либо что-то не так."
						 << std::endl;
			abort();
		}

		/*	Вот это надо реализовать:
		-----------   ------    --------------------------
		|a|b|c|d|1| x |-u|1| -> |-au|a-bu|b-cu|c-du|d-u|1|
		-----------   ------    --------------------------	

		Предпологается, что у нас второй 
		массив (мб вектор? Да,
		ибо тогда я сразу имеюдоступ ко всей инфе,
		что мне нужно: size, resize... Ну и все =) )
		всегда имеет 2 элемента, где последний = 1,
		т.е. это (x-c)
		*/

		int PolySize = FirstPoly.size() + 1;

		std::vector<double> FinePoly;

		FinePoly.resize(PolySize);

		for (int i = 1; i < PolySize; i++){
			FinePoly[i] = FirstPoly[i - 1];
		}

		/*
		Здесь у нас будет такой вид выходного вектора:
		-------------
		|0|a|b|c|d|1|
		-------------
		*/



		//Теперь надо вычесть c * на соотв. коэфф.
		// 										FirstPoly
		for (int i = 0; i < PolySize - 1; i++){
			FinePoly[i] += Second_Poly[0]*FirstPoly[i];
		}

		//Усе
		return FinePoly;
	}


/*
=================================================================
=================================================================
*/

	//Начинается класс

	Polynomial::Polynomial(){};
	//Конструктор по умолчанию ничего не делает

	/*
	Polynomial::Polynomial(const int NewSize):
	CoefficientsValues(),
	XDots(nullptr),
	YDots(nullptr)
	{
		if (NewSize > 0){
			CoefficientsValues.resize(NewSize-1);
			XDots = new double[NewSize];
			YDots = new double[NewSize];
			for (int i = 0; i < NewSize; i++){
				XDots[i] = 0;
				YDots[i] = 0;
			}
		} else {
			std::cerr
			<< "Количество точек не положительное."
			<< std::endl;
			abort();
		}
	};*/
	/*
	Спец конструктор: подовая кол-во точек, 
	мы задаем полином степени n-1
	Т.к. полином на одну степень меньше,
	чем кол-во точек на 1
	*/
	
	Polynomial::Polynomial(const Polynomial& other):
	CoefficientsValues(other.CoefficientsValues),
	XDots(other.XDots),
	YDots(other.YDots)
	{};
	//Конструктор копирования просто копирует vector

	Polynomial& Polynomial::operator= (const Polynomial& other){
		if (&other == this){
			return *this;
		}

		CoefficientsValues = other.CoefficientsValues;

		XDots = other.XDots;
		YDots = other.YDots;
		//Надеюсь нормально скопируется, проверь.

		return *this;
	}

	//Вбиваем точку
	void Polynomial::AddDot(double x, double y){
		int i = 0;

		for (i = 0; i < XDots.size(); i++){
			if (XDots[i] == x){
				YDots[i] = y;
				break;
			}
		}

		XDots.insert(XDots.end(), x);
		YDots.resize(YDots.size() + 1);

		YDots[YDots.size() - 1] = y;
	}

	/*
	== Короче я тут поэлементно проверяю схожесть векторов,
	а потом проверяю у большего ветктора,
	есть ли у него не нулевые значения после MinSize
	(ну тип если у нас старшие коэфф являются 0, а у другого
	у нас меньше размер (без нулей), то полиномы все равно будут равны)

	!= точно такой же, просто поменял выход 0 <-> 1

	Я проверяю только многочлен, ибо захотелось,
	да и вроде точки проверять незачем
	*/
	bool Polynomial::operator== (const Polynomial& other) const{
		// int MinSize = (CoefficientsValues.size() <= other.CoefficientsValues.size()) ?
		// CoefficientsValues.size() : other.CoefficientsValues.size();

		// int MaxSize = (CoefficientsValues.size() >= other.CoefficientsValues.size()) ?
		// CoefficientsValues.size() : other.CoefficientsValues.size();

		if (CoefficientsValues.size() != other.CoefficientsValues.size()){
			return 0;
		}

		for (int i = 0; i < CoefficientsValues.size(); i ++){
			if (CoefficientsValues[i] != other.CoefficientsValues[i]) {
				return 0;
			}
		}



		// for (int i = MinSize; i < MaxSize; i ++){
		// 	if (CoefficientsValues.size() == MaxSize) {
		// 		if (CoefficientsValues[i] != 0){
		// 			return 0;
		// 		} 
		// 	} else{
		// 		if (other.CoefficientsValues[i] != 0){
		// 			return 0;
		// 		} 
		// 	}
		// }

		return 1;
	}



	bool Polynomial::operator!= (const Polynomial& other) const{
		// int MinSize = (CoefficientsValues.size() <= 
		// 	other.CoefficientsValues.size()) ?
		// 	CoefficientsValues.size() : 
		// 	other.CoefficientsValues.size();

		// int MaxSize = (CoefficientsValues.size() >= 
		// 	other.CoefficientsValues.size()) ?
		// 	CoefficientsValues.size() : 
		// 	other.CoefficientsValues.size();

		if (CoefficientsValues.size() != other.CoefficientsValues.size()){
			return 1;
		}

		for (int i = 0; i < CoefficientsValues.size(); i ++){
			if (CoefficientsValues[i] != other.CoefficientsValues[i]) {
				return 1;
			}
		}

		// for (int i = MinSize; i < MaxSize; i ++){
		// 	if (CoefficientsValues.size() == MaxSize) {
		// 		if (CoefficientsValues[i] != 0){
		// 			return 1;
		// 		} 
		// 	} else{
		// 		if (CoefficientsValues[i] != 0){
		// 			return 1;
		// 		} 
		// 	}
		// }

		return 0;
	}

	Polynomial::~Polynomial(){
		CoefficientsValues.clear();

		XDots.clear();
		YDots.clear();
	};
	//Деструктор освобождает пямять вектора (я надеюсь...
	//Мб там есть отдельный метод "delete" для такого, хз)

	//Записываем в вектора точек X и Y сами точки через []
	double& Polynomial::operator[](const double& Arg){
		int i = 0;

		for (i = 0; i < XDots.size(); i++){
			if (XDots[i] == Arg){
				return YDots[i];
			}
		}

		XDots.insert(XDots.end(), Arg);
		YDots.resize(YDots.size() + 1);

		return YDots[YDots.size() - 1];
	}

	//Выводим многочлен и точки
	std::ostream& operator<<(
			std::ostream& stream, const Polynomial& Poly)
		{
			if (Poly.XDots.size() != 0) {
				for (int i = 0; i < Poly.XDots.size(); i++){
					std::cout << i << ": L("
					<< Poly.XDots[i] << ") = "
					<< Poly.YDots[i] << std::endl;
				}
			}

			//Там выводятся точки

			for (int i = 0; i < Poly.CoefficientsValues.size(); i++){

				stream << Poly.CoefficientsValues[i];

				if (i == 0){
					stream << " + ";
				} else if (i == Poly.CoefficientsValues.size() - 1){
					stream << "*x^" << i << std::endl;
				} else {
					stream << "*x^" << i << " + ";
				}
			}

			// stream << std::endl;

			return stream;
		}


	//Собственно тут будет отдельно функция расчета многочлена
	//и его коэффициентов

	/*
	Схема такая: мы сначала считаем
		prod_{j = 0, j != i -> n} (x - x_j) (1)

	Потом умножаем на 
		prod_{j = 0, j != i -> n} (x_i - x_j)
	*/
	void Polynomial::CoeffCalc(){
		int size = XDots.size();

		CoefficientsValues.clear();
		CoefficientsValues.resize(size);

		std::vector<double> VecTmp = {1};
		std::vector<double> bar = {1};

		double FracTmp = 1;

		for (int i = 0; i < size; i++){
			for (int j = 0; (j < size); j++){
				if (j != i){	
					bar = {-XDots[j], 1};
					VecTmp = MultipluingPolynomials(VecTmp, bar);
				// Вот тут мы уже имеем готовый вариант (1)

					FracTmp *= XDots[i] - XDots[j];
				}
			}

			for (int q = 0; q < VecTmp.size(); q++){
				VecTmp[q] /= FracTmp;// Тут умножаем на (x_i - x_j)
				VecTmp[q] *= YDots[i];// Тут умножаем на y_i
				CoefficientsValues[q] += VecTmp[q]; //Дабавляем в итоговый вектор
			}

			FracTmp = 1;
			VecTmp = {1};
			bar = {1};
		}

	}

	double pow(double a, int b){
		double ans = 1;
		for (int i = 0; i < b; i++){
			ans *= a;
		}
		return ans;
	}

	double Polynomial::PolyCalc(double x){
		double ans = 0;
		for (int i = 0; i < CoefficientsValues.size(); i++){
			ans += CoefficientsValues[i] * pow(x, i);
		}
		return ans;
	}

	void ChangeVec (int i, std::vector<double>& tmp, std::vector<double>& A){
		for (int j = 0 ; j < A.size(); j++){
			if (j < i){
				tmp[j] = A[j];
			} else if (j > i){
				tmp[j-1] = A[j];
			}
		}

		A.clear();
		A.resize(tmp.size());

		for (int j = 0 ; j < A.size(); j++){
			A[j] = tmp[j];
		}
	}

	void Polynomial::DotDelete(int x, int y){
		int i = 0;
		bool flag = 1;
		for (i = 0; i < XDots.size(); i++){
			if ((XDots[i] == x) && ((YDots[i] == y))){
				std::vector<double> tmp;

				tmp.resize(XDots.size() - 1);

				ChangeVec(i, tmp, XDots);

				tmp.clear();
				tmp.resize(YDots.size() - 1);

				ChangeVec(i, tmp, YDots);

				flag = 0;
				break;
			}
		}
		if (flag){
			std::cerr << "Удаляешь точку, которой нет." << std::endl;
		}
	}
}