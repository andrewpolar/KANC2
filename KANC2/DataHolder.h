#pragma once
#include <memory>

class Formula3 {
public:
	~Formula3();
	std::unique_ptr<std::unique_ptr<double[]>[]> inputs;
	std::unique_ptr<double[]> target;
	int _N;
	const int nInputs = 5;
	void GetInput(std::unique_ptr<double[]>& input);
	double GetTarget(std::unique_ptr<double[]>& input);
	void GenerateData(int N);
private:
	double Function(std::unique_ptr<double[]>& input);
};

////////////////
class Formula4 {
public:
	~Formula4();
	std::unique_ptr<std::unique_ptr<double[]>[]> inputs;
	std::unique_ptr<double[]> target;
	void GenerateData(int N);
	int _N;
	const int nInputs = 6;
	void GetInput(std::unique_ptr<double[]>& input);
	double GetTarget(std::unique_ptr<double[]>& input);
private:
	double Function(double x1, double y1, double x2, double y2, double x3, double y3);
	double GetValue();
};

////////////////
//Source:  https://kindxiaoming.github.io/pykan/Examples/Example_1_function_fitting.html
class Formula1 {
public:
	~Formula1();
	std::unique_ptr<std::unique_ptr<double[]>[]> inputs;
	std::unique_ptr<double[]> target;
	void GenerateData(int N);
	int _N;
	const int nInputs = 2;
	void GetInput(std::unique_ptr<double[]>& input);
	double GetTarget(std::unique_ptr<double[]>& input);
private:
	double Function(double x, double y);
	const double pi = 3.141592653589793;
	const double _min = -1.0;
	const double _max = 1.0;
};

