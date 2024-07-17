//Concept: Andrew Polar and Mike Poluektov
//Developer Andrew Polar

//License
//In case if end user finds the way of making a profit by using this code and earns
//billions of US dollars and meet developer bagging change in the street near McDonalds,
//he or she is not in obligation to buy him a sandwich.

//Symmetricity
//In case developer became rich and famous by publishing this code and meet misfortunate
//end user who went bankrupt by using this code, he is also not in obligation to buy
//end user a sandwich.

//Publications:
//https://www.sciencedirect.com/science/article/abs/pii/S0016003220301149
//https://www.sciencedirect.com/science/article/abs/pii/S0952197620303742
//https://arxiv.org/abs/2305.08194

//Formula4 is area of triangles as a function of vertices.
//Formula3 is Mike's formula.

#include <iostream>
#include <thread>
#include "DataHolder.h"
#include "KANAddend.h"

void ShowMatrix(std::unique_ptr<std::unique_ptr<double[]>[]>& matrix, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            printf("%5.3f ", matrix[i][j]);
        }
        printf("\n");
    }
}

void ShowVector(std::unique_ptr<double[]>& ptr, int N) {
    int cnt = 0;
    for (int i = 0; i < N; ++i) {
        printf("%5.2f ", ptr[i]);
        if (++cnt >= 10) {
            printf("\n");
            cnt = 0;
        }
    }
}

void FindMinMax(std::unique_ptr<double[]>& xmin, std::unique_ptr<double[]>& xmax,
    double& targetMin, double& targetMax,
    std::unique_ptr<std::unique_ptr<double[]>[]>& matrix,
    std::unique_ptr<double[]>& target, int nRows, int nCols) {

    for (int i = 0; i < nCols; ++i) {
        xmin[i] = DBL_MAX;
        xmax[i] = -DBL_MIN;
    }

    for (int i = 0; i < nRows; ++i) {
        for (int j = 0; j < nCols; ++j) {
            if (matrix[i][j] < xmin[j]) xmin[j] = static_cast<double>(matrix[i][j]);
            if (matrix[i][j] > xmax[j]) xmax[j] = static_cast<double>(matrix[i][j]);
        }
    }

    targetMin = DBL_MAX;
    targetMax = -DBL_MIN;
    for (int j = 0; j < nRows; ++j) {
        if (target[j] < targetMin) targetMin = target[j];
        if (target[j] > targetMax) targetMax = target[j];
    }
}

void Training(std::unique_ptr<std::unique_ptr<double[]>[]>& inputs, std::unique_ptr<double[]>& target, 
    std::unique_ptr<std::unique_ptr<KANAddend>[]>& addends, int nRecords, int nEpochs, int nModels,
    int marginStart, int marginEnd, double sensitivity) {

    auto residualError = std::make_unique<double[]>(nRecords);
    int end = nEpochs - marginEnd;
    for (int epoch = 0; epoch < nEpochs; ++epoch) {
        double error2 = 0.0;
        int cnt = 0;
        for (int i = 0; i < nRecords; ++i) {
            if (epoch >= marginStart && epoch < end && residualError[i] < sensitivity) continue;
            double residual = target[i];
            for (int j = 0; j < nModels; ++j) {
                residual -= addends[j]->ComputeUsingInput(inputs[i]);
            }
            for (int j = 0; j < nModels; ++j) {
                addends[j]->UpdateUsingMemory(residual);
            }
            error2 += residual * residual;
            residualError[i] = static_cast<double>(fabs(residual));
            ++cnt;
        }
        if (0 == cnt) error2 = 0.0;
        else {
            error2 /= cnt;
            error2 = sqrt(error2);
        }
        printf("Training step %d, current RMSE %4.4f\n", epoch, error2);
    }
}

int main() {
    //Next instantiates data, it can be Formula1, Formula3 or Formula4

    //Initialization of KAN and training for Formula1
    //int nRecords = 1000;
    //int nModels = 5;
    //int nEpochs = 26;
    //int marginStart = 6;
    //int marginEnd = 6;
    //double sensitivity = 0.001;
    //int innerPoints = 16;
    //int outerPoints = 16;
    //double muInner = 0.1;
    //double muOuter = 0.1;
    //auto f = std::make_unique<Formula1>();

    //Initialization of KAN and training for Formula3
    int nRecords = 10000;
    int nModels = 11;
    int nEpochs = 36;
    int marginStart = 6;
    int marginEnd = 6;
    double sensitivity = 0.06;
    int innerPoints = 6;
    int outerPoints = 12;
    double muInner = 0.01;
    double muOuter = 0.01;
    auto f = std::make_unique<Formula3>();

    //Initialization of KAN and training for Formula4
    //int nRecords = 10000;
    //int nModels = 32;
    //int nEpochs = 46;
    //int marginStart = 6;
    //int marginEnd = 10;
    //double sensitivity = 120.0;
    //int innerPoints = 8;
    //int outerPoints = 12;
    //double muInner = 0.15;
    //double muOuter = 0.01;
    //auto f = std::make_unique<Formula4>();

    f->GenerateData(nRecords);

    //ShowMatrix(f->inputs, f->_N, f->nInputs);
    //ShowVector(f->target, nRecords);

    clock_t start_encoding = clock();
    srand((unsigned int)time(NULL));

    auto xmin = std::make_unique<double[]>(f->nInputs);
    auto xmax = std::make_unique<double[]>(f->nInputs);
    double targetMin;
    double targetMax;

    FindMinMax(xmin, xmax, targetMin, targetMax, f->inputs, f->target, f->_N, f->nInputs);

    double zmin = targetMin / nModels;
    double zmax = targetMax / nModels;
    auto addends = std::make_unique<std::unique_ptr<KANAddend>[]>(nModels);
    for (int i = 0; i < nModels; ++i) {
        addends[i] = std::make_unique<KANAddend>(xmin, xmax, zmin, zmax, innerPoints, 
            outerPoints, muInner, muOuter, f->nInputs);
    }

    std::thread t(Training, std::ref(f->inputs), std::ref(f->target), std::ref(addends), 
        nRecords, nEpochs, nModels, marginStart, marginEnd, sensitivity);
    t.join();

    clock_t end_encoding = clock();
    printf("Time for training %2.3f sec.\n", (double)(end_encoding - start_encoding) / CLOCKS_PER_SEC);

    //////// Object copy test //////
    auto addendsCopy = std::make_unique<std::unique_ptr<KANAddend>[]>(nModels);
    for (int i = 0; i < nModels; ++i) {
         addendsCopy[i] = std::make_unique<KANAddend>(*addends[i]);
    }

    double error = 0.0;
    double error3 = 0.0;
    int NTests = 1000;
    std::unique_ptr<double[]> test_input = std::make_unique<double[]>(f->nInputs);
    for (int i = 0; i < NTests; ++i) {
        f->GetInput(test_input);
        double test_target = f->GetTarget(test_input);

        double model1 = 0.0;
        for (int j = 0; j < nModels; ++j) {
            model1 += addends[j]->ComputeUsingInput(test_input);
        }

        double model2 = 0.0;
        for (int j = 0; j < nModels; ++j) {
            model2 += addendsCopy[j]->ComputeUsingInput(test_input);
        }

        error += (test_target - model1) * (test_target - model1);
        error3 += (test_target - model2) * (test_target - model2);
    }
    error /= NTests;
    error = sqrt(error);
    error /= (targetMax - targetMin);
    error3 /= NTests;
    error3 = sqrt(error3);
    error3 /= (targetMax - targetMin);
    printf("\nRelative RMSE for unseen data %f, RMSE for copy object %f\n", error, error3);
}



