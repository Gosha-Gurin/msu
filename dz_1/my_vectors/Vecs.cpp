#include "LagrangeClass.hpp"
#include "Vecs.hpp"
#include <iostream>

/*
	Нужны классы векторов 
	(просто для записи точек - я с ними ничего такого не делаю)
	и класс коэффициентов. При вызове operator[] класса векторов точек
	будем вызывать еще и функцию подсчета коэффициентов. Тогда не надо
	писать после смены точки calc poly или как он там называется...

*/



/*
Для коэфф нужно:
	- Конструкторы (стандартный, копирования, ?специальные?)
	- Деконструктор
	- Перегрузка операторов?
		- Оператор присваивания (поэлементное)
		- Оператор сравнения
	-Функции:
		- insert
		- resize
		- size (просто вывод size_t size;)
		- calc poly


Для точек нужно:
	- Конструкторы (стандартный, копирования) + 
	- Деконструктор +
	- Перегрузка операторов:
		- Оператор присваивания (поэлиментное) +
	- Функции:
		- insert (в конце)+
		- resize +
		- size (просто вывод size_t size;) +
*/



/*
тодо
	Буду хранить и X и Y в VecDots. +
*/



namespace MyVec{
	
	Vec::Vec():
		data(nullptr),
		data_size(0)
	{}


	//ЭТОТ специальный конструктор работает только для одноэлементного массива.
	//Если доработаешь - будет круто
	Vec::Vec(const double Arg):
		data(new double[1]),
		data_size(1)
	{
		data[0] = Arg;
	}

    Vec::Vec(const Vec& other):
        data(nullptr),
        data_size(other.data_size)
    {
        data = new double[data_size];
//         if (!data){
//         }
        // Мне лень на \той клаве писать проверку
        for (int i = 0; i < data_size; i++){
            data[i] = other.data[i];
        }
    }

	// А этот только для 2 элемента

	//Да-да, так делать нельзя и вообще плохо быть Гошей
	//Мне пофиг, ща полпервого ночи и я дико хочу спать
	Vec::Vec(const double FirstArg, const double SecArg):
		data(new double[2]),
		data_size(2)
	{
		data[0] = FirstArg;
		data[1] = SecArg;
	}

	int Vec::size() const{
		return data_size;
	}

	Vec& Vec::operator=(const Vec& other){

		if (&other == this){
			return *this;
		}

		data_size = other.data_size;

		data = new double[data_size];

		if (data == nullptr){
			std::cerr << "Ошибка выделения памяти data "
					  << std::endl;
		}

		for (int i = 0; i < data_size; i++){
			data[i] = other.data[i];
		}

		return *this;
	}

	void Vec::resize(const int NewSize){
		if (NewSize >= data_size){
			double* tmp = new double[data_size];

			if (tmp == nullptr){
				std::cerr << "Ошибка выделения памяти data "
					  	  << std::endl;
			}

			for (int i = 0; i < data_size; i++){
				tmp[i] = data[i];
			}

			delete [] data;

			data = new double[NewSize];

			for (int i = 0; i < data_size; i++){
				data[i] = tmp[i];
			}

			for (int i = data_size; i < NewSize; i++){
				data[i] = 0;
			}

			data_size = NewSize;

			delete [] tmp;

		} else {
			double* tmp = new double[NewSize];

			if (tmp == nullptr){
				std::cerr << "Ошибка выделения памяти data "
					  	  << std::endl;
			}

			for (int i = 0; i < NewSize; i++){
				tmp[i] = data[i];
			}

			delete [] data;

			data = new double[NewSize];

			for (int i = 0; i < NewSize; i++){
				data[i] = tmp[i];
			}

			data_size = NewSize;

			delete [] tmp;
		}
	}

	double& Vec::operator[] (int i) const {
		return data[i];
	}

	void Vec::insert(const double& Arg){
		double* tmp = new double[data_size];

		if (tmp == nullptr){
			std::cerr << "Ошибка выделения памяти tmp"
					  << std::endl;
			std::exit(EXIT_FAILURE);
		}

		for (int i = 0; i < data_size; i++){
			tmp[i] = data[i];
		}

		delete [] data;

		data_size++;

		data = new double[data_size+1];

		for (int i = 0; i < data_size-1; i++){
			data[i] = tmp[i];
		}

		data[data_size - 1] = Arg;

		delete [] tmp;
	}

	std::ostream& operator<<(
			std::ostream& stream, const Vec& MyVec){
		for (int i = 0; i < MyVec.size(); i++){
			stream << i << ": " << MyVec[i] << std::endl;
		}
		return stream;
	}

	Vec::~Vec(){
		delete [] data;
	}
}
