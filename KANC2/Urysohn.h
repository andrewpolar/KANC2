#pragma once
#include "Univariate.h"
#include <memory>

class Urysohn
{
public:
	int _length;
	std::unique_ptr<std::unique_ptr<Univariate>[]> _univariateList;
	Urysohn(std::unique_ptr<double[]>& xmin, std::unique_ptr<double[]>& xmax, 
		double targetMin, double targetMax,
		std::unique_ptr<int[]>& layers, int len);
	~Urysohn();
	Urysohn(const Urysohn& uri);
	void UpdateUsingInput(double delta, std::unique_ptr<double[]>& inputs, double mu);
	void UpdateUsingMemory(double delta, double mu);
	double GetValueUsingInput(std::unique_ptr<double[]>& inputs);
};

