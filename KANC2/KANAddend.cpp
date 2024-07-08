#include "KANAddend.h"
#include <memory>

KANAddend::KANAddend(std::unique_ptr<double[]>& xmin, std::unique_ptr<double[]>& xmax, 
    double targetMin, double targetMax,
    int inner, int outer, double muInner, double muOuter, int number_of_inputs) {

    _muInner = muInner;
    _muInner = muInner;
    _muOuter = muOuter;
    _targetMin = targetMin;
    _targetMax = targetMax;
    _lastInnerValue = 0.0;

    std::unique_ptr<int[]> interior_structure = std::make_unique<int[]>(number_of_inputs);
    for (int i = 0; i < number_of_inputs; i++)
    {
        interior_structure[i] = static_cast<int>(inner);
    }
    _u = std::make_unique<Urysohn>(xmin, xmax, _targetMin, _targetMax, interior_structure, number_of_inputs);
    _univariate = std::make_unique<Univariate>(_targetMin, _targetMax, _targetMin, _targetMax, outer);
}

KANAddend::~KANAddend() {
}

KANAddend::KANAddend(const KANAddend& addend) {
    _muInner = addend._muInner;
    _muOuter = addend._muOuter;
    _targetMin = addend._targetMin;
    _targetMax = addend._targetMax;
    _lastInnerValue = addend._lastInnerValue;
    _univariate = std::make_unique<Univariate>(*addend._univariate);
    _u = std::make_unique<Urysohn>(*addend._u);
}

void KANAddend::UpdateUsingMemory(double diff) {
    double derrivative = _univariate->GetDerivative(_lastInnerValue);
    _u->UpdateUsingMemory(diff * derrivative, _muInner);
    _univariate->UpdateUsingMemory(diff, _muOuter);
}

void KANAddend::UpdateUsingInput(std::unique_ptr<double[]>& input, double diff) {
    double value = _u->GetValueUsingInput(input);
    double derrivative = _univariate->GetDerivative(value);
    _u->UpdateUsingInput(diff * derrivative, input, _muInner);
    _univariate->UpdateUsingInput(value, diff, _muOuter);
}

double KANAddend::ComputeUsingInput(std::unique_ptr<double[]>& input) {
    _lastInnerValue = _u->GetValueUsingInput(input);
    return _univariate->GetFunctionUsingInput(_lastInnerValue);
}