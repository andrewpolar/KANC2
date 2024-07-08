#pragma once
#include <cstddef>
#include <memory>

class Univariate
{
public:
	Univariate(double xmin, double xmax, double ymin, double ymax, int points);
    ~Univariate();
    Univariate(const Univariate& uni);
    int _points;
    double _xmin;
    double _xmax;
    double _ymin;
    double _ymax;
    double GetDerivative(double x);
    void UpdateUsingInput(double x, double delta, double mu);
    void UpdateUsingMemory(double delta, double mu);
    double GetFunctionUsingInput(double x);
private:
    std::unique_ptr<double[]> _y;
    double _deltax;
    int _lastLeftIndex;
    double _lastLeftOffset;
    void SetLimits();
    void SetRandomFunction();
    void FitDefinition(double x);
};
