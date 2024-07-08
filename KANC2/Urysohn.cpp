#include "Urysohn.h"
#include <cstdlib> 
#include <iostream>

Urysohn::Urysohn(std::unique_ptr<double[]>& xmin, std::unique_ptr<double[]>& xmax, 
	double targetMin, double targetMax,
	std::unique_ptr<int[]>&  layers, int len) {
	_length = len;
	double ymin = targetMin / _length;
	double ymax = targetMax / _length;
	_univariateList = std::make_unique<std::unique_ptr<Univariate>[]>(_length);
	for (int i = 0; i < _length; ++i) {
		_univariateList[i] = std::make_unique<Univariate>(xmin[i], xmax[i], ymin, ymax, layers[i]);
	}
}

Urysohn::~Urysohn() {
}

Urysohn::Urysohn(const Urysohn& uri) {
	_length = uri._length;
	_univariateList = std::make_unique<std::unique_ptr<Univariate>[]>(_length);
	for (int i = 0; i < _length; ++i) {
		_univariateList[i] = std::make_unique<Univariate>(*uri._univariateList[i]);
	}
}

void Urysohn::UpdateUsingInput(double delta, std::unique_ptr<double[]>& inputs, double mu) {
	delta /= _length;
	for (int i = 0; i < _length; ++i) {
		_univariateList[i]->UpdateUsingInput(inputs[i], delta, mu);
	}
}

void Urysohn::UpdateUsingMemory(double delta, double mu) {
	delta /= _length;
	for (int i = 0; i < _length; ++i) {
		_univariateList[i]->UpdateUsingMemory(delta, mu);
	}
}

double Urysohn::GetValueUsingInput(std::unique_ptr<double[]>& inputs) {
	double f = 0.0;
	for (int i = 0; i < _length; ++i) {
		f += _univariateList[i]->GetFunctionUsingInput(inputs[i]);
	}
	return f;
}
