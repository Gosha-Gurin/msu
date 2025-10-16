#include <iostream>


namespace MyVec{

	#ifndef VECS_HPP
	#define VECS_HPP

	class Vec{
		double* data;
		size_t data_size;

		friend std::ostream& operator<<(
			std::ostream& stream, const Vec& Vec);
		
	public:
		Vec();

		Vec(const double Arg);

		Vec(const double FirstArg, const double SecArg);//Двойной

		size_t size() const;

		Vec& operator=(const Vec& other);

		void resize(const int NewSize);

		double& operator[] (int i) const;

		void insert(const double& Arg);

		void clear();


		~Vec();
	};

	#endif

}
