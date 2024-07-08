#include "DataHolder.h"
#include <math.h>
#include <ctime>
#include <cstdlib> 

Formula3::~Formula3() {
}

double Formula3::Function(std::unique_ptr<double[]>& input) {
    //y = (1/pi)*(2+2*x3)*(1/3)*(atan(20*exp(x5)*(x1-0.5+x2/6))+pi/2) + (1/pi)*(2+2*x4)*(1/3)*(atan(20*exp(x5)*(x1-0.5-x2/6))+pi/2);
    double pi = 3.14159265359;
    double y = (1.0 / pi);
    y *= (2.0 + 2.0 * input[2]);
    y *= (1.0 / 3.0);
    y *= atan(20.0 * atan(input[4]) * (input[0] - 0.5 + input[1] / 6.0)) + pi / 2.0;

    double z = (1.0 / pi);
    z *= (2.0 + 2.0 * input[3]);
    z *= (1.0 / 3.0);
    z *= atan(20.0 * atan(input[4]) * (input[0] - 0.5 - input[1] / 6.0)) + pi / 2.0;

    return y + z;
}

void Formula3::GetInput(std::unique_ptr<double[]>& input) {
    for (int i = 0; i < nInputs; ++i) {
        input[i] = static_cast<double>((rand() % 1000) / 1000.0);
    }
}

double Formula3::GetTarget(std::unique_ptr<double[]>& input) {
    return Function(input);
}

void Formula3::GenerateData(int N) {
    _N = N;
    target = std::make_unique<double[]>(_N);
    inputs = std::make_unique<std::unique_ptr<double[]>[]>(_N);
 
    int counter = 0;
    while (true) {
        inputs[counter] = std::make_unique<double[]>(nInputs);
        GetInput(inputs[counter]);
        target[counter] = static_cast<double>(Function(inputs[counter]));
        if (++counter >= N) break;
    }
}

///////////////////////
Formula4::~Formula4() {
}

double Formula4::Function(double x1, double y1, double x2, double y2, double x3, double y3) {
    double X1 = fabs(x1 - x2);
    double Y1 = fabs(y1 - y2);
    double X2 = fabs(x1 - x3);
    double Y2 = fabs(y1 - y3);
    double X3 = fabs(x2 - x3);
    double Y3 = fabs(y2 - y3);

    double a = sqrt(X1 * X1 + Y1 * Y1);
    double b = sqrt(X2 * X2 + Y2 * Y2);
    double c = sqrt(X3 * X3 + Y3 * Y3);
    double s = (a + b + c) / 2.0;
    double rtn = sqrt(s * (s - a) * (s - b) * (s - c));
    return rtn;
}

double Formula4::GetValue() {
    double v = rand() % 1000 / 1000.0 * 100.0;
    return v;
}

void Formula4::GetInput(std::unique_ptr<double[]>& input)
{
    double x1 = GetValue();
    double x2 = GetValue();
    double x3 = GetValue();
    double y1 = GetValue();
    double y2 = GetValue();
    double y3 = GetValue();

    input[0] = static_cast<double>(x1);
    input[1] = static_cast<double>(y1);
    input[2] = static_cast<double>(x2);
    input[3] = static_cast<double>(y2);
    input[4] = static_cast<double>(x3);
    input[5] = static_cast<double>(y3);
}

double Formula4::GetTarget(std::unique_ptr<double[]>& input) {
    return Function(input[0], input[1], input[2], input[3], input[4], input[5]);
}

void Formula4::GenerateData(int N) {
    _N = N;
    target = std::make_unique<double[]>(_N);
    inputs = std::make_unique<std::unique_ptr<double[]>[]>(_N);

    int counter = 0;
    while (true) {
        inputs[counter] = std::make_unique<double[]>(nInputs);
        GetInput(inputs[counter]);
        target[counter] = static_cast<double>(Function(inputs[counter][0], inputs[counter][1], inputs[counter][2],
            inputs[counter][3], inputs[counter][4], inputs[counter][5]));
        if (++counter >= N) break;
    }
}

Formula1::~Formula1() {
}

double Formula1::Function(double x, double y) {
    return exp(sin(pi * x) + y * y);
}

double Formula1::GetTarget(std::unique_ptr<double[]>& input) {
    return Function(input[0], input[1]);
}

void Formula1::GetInput(std::unique_ptr<double[]>& input) {
    input[0] = rand() % 1000 / 1000.0 * (_max - _min) + _min;
    input[1] = rand() % 1000 / 1000.0 * (_max - _min) + _min;
}

void Formula1:: GenerateData(int N) {
    _N = N;
    target = std::make_unique<double[]>(_N);
    inputs = std::make_unique<std::unique_ptr<double[]>[]>(_N);

    int counter = 0;
    while (true) {
        inputs[counter] = std::make_unique<double[]>(nInputs);
        GetInput(inputs[counter]);
        target[counter] = static_cast<double>(Function(inputs[counter][0], inputs[counter][1]));
        if (++counter >= N) break;
    }
}


