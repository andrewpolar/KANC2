#pragma once
#include "Urysohn.h"
#include "Univariate.h"
#include <memory>

class KANAddend
{
public:
    double _targetMin;
    double _targetMax;
    double _muOuter;
    double _muInner;
    KANAddend(std::unique_ptr<double[]>& xmin, std::unique_ptr<double[]>& xmax, 
        double targetMin, double targetMax,
        int inner, int outer, double muInner, double muOuter, int number_of_inputs);
    KANAddend(const KANAddend& obj);
    ~KANAddend();
    void UpdateUsingMemory(double diff);
    void UpdateUsingInput(std::unique_ptr<double[]>& input, double diff);
    double ComputeUsingInput(std::unique_ptr<double[]>& input);
private:
    double _lastInnerValue;
    std::unique_ptr<Urysohn> _u;
    std::unique_ptr<Univariate> _univariate;
};

