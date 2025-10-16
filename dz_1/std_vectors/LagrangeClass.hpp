#include<iostream>
#include<vector>


namespace LagrangeClass{

	std::vector<double> MultipluingPolynomials(
		const std::vector<double> FirstPoly,
		const std::vector<double> Second_Poly);

	class Polynomial{
		std::vector<double> CoefficientsValues;
		std::vector<double> XDots;
		std::vector<double> YDots;

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