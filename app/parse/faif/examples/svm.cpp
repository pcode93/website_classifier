#if defined(_MSC_VER) && (_MSC_VER >= 1700)
//msvc13.0 Boost.Ublas
#pragma warning(disable:4127)
//msvc12.0 Boost.Serialization warning
#pragma warning(disable:4512)

#endif

#include <iostream>
#include <faif/learning/Svm.hpp>

using namespace std;
using namespace faif;
using namespace faif::ml;

int main() {

    string C[] = {"good","bad"}; SvmClassifier<double, ValueNominal<string> >::AttrDomain cat = createDomain("", C, C+2);


    /** Create new svm classifier for 2D problem */
    unsigned int dimension = 2;
    SvmClassifier<double, ValueNominal<string> > svm(dimension, cat);

    /** Optional seeting parameters of SMO algorithm */ 
    svm.setC(2.0);
    svm.setMargin(0.1);
    svm.setGaussKernel();
    svm.setGaussParameter(1.0);
    svm.setFiniteStepsStopCondition(1.0);

    /** Prepare train examples */
    SvmClassifier<double, ValueNominal<string> >::ClassifyExample testVector[10];
    testVector[0] = {2, 6};
    testVector[1] = {2, 3};
    testVector[2] = {6, 4};
    testVector[3] = {8, 4};
    testVector[4] = {4, 4};
    testVector[5] = {4, 3};
    testVector[6] = {7, 5};
    testVector[7] = {6, 3};
    testVector[8] = {4, 7};
    testVector[9] = {4, 9};

    /** Add train examples to svm classifier */
    svm.addExample(testVector[0], "good");
    svm.addExample(testVector[1], "good");
    svm.addExample(testVector[2], "good");
    svm.addExample(testVector[3], "good");
    svm.addExample(testVector[4], "good");

    svm.addExample(testVector[5], "bad");
    svm.addExample(testVector[6], "bad");
    svm.addExample(testVector[7], "bad");
    svm.addExample(testVector[8], "bad");
    svm.addExample(testVector[9], "bad");

    /** Train svm classifier. Training is based on added examples */
    svm.train();

    /** Classify vectors */
    for(auto const& vec : testVector)
        auto beliefs = svm.getCategories(vec);

    return 0;
}
