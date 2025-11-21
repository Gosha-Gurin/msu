#include<iostream>
#include "Vecs.hpp"

using namespace MyVec;


namespace LagrangeClass{

	Vec MultipluingPolynomials(
		const Vec& FirstPoly,
		const Vec& Second_Poly);

	class Polynomial{
		Vec CoefficientsValues;
		Vec XDots;
		Vec YDots;

		friend std::ostream& operator<<(
			std::ostream& stream, const Polynomial& Poly);

	public:
		Polynomial();
		
		Polynomial(const Polynomial& other);



		Polynomial& operator= (const Polynomial& other);
		bool operator== (const Polynomial& other) const;
		bool operator!= (const Polynomial& other) const;
		double& operator[](const double& Arg);


		void CoeffCalc();
		void AddDot(double x, double y);
		void DotDelete(int x, int y);


		double PolyCalc(double x);

		~Polynomial();


	};
	
	std::ostream& operator<<(std::ostream& stream, const Polynomial& Poly);

}
