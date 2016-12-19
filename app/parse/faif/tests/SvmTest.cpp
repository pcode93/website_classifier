/** file contains svm classifier test */
#if defined (_MSC_VER) && (_MSC_VER >= 1400)
//msvc8.0 generuje smieci dla boost::string
#pragma warning(disable:4512)
#pragma warning(disable:4127)
//msvc9.0 warnings for boost::concept_check
#pragma warning(disable:4100)
//msvc12.0 warnings for ublas
#pragma warning(disable:4996)
#endif

#include <iostream>
#include <fstream>
#include <string>

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>

#include "../src/learning/Svm.hpp"

#include <vector>
#include <algorithm>
#include <utility>

#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>


using namespace std;
using namespace faif;
using namespace faif::ml;
using boost::unit_test::test_suite;
using namespace boost;

BOOST_AUTO_TEST_SUITE( FAIF_SVM_classifier_test )

/** Test add train examples to classifier */
BOOST_AUTO_TEST_CASE( SvmAddTrainExamplesTest ) {

    string C[] = {"good","bad"}; SvmClassifier<double, ValueNominal<string> >::AttrDomain cat = createDomain("", C, C+2);

    /** Svm classifier for 2D and 3D vectors */
    unsigned int test_dimensions = 3;
    SvmClassifier<double, ValueNominal<string> > svm(test_dimensions, cat);
    BOOST_CHECK( svm.getDimension() == test_dimensions );
    unsigned int test_dimensions2 = 2;
    SvmClassifier<double, ValueNominal<string> > svm2(test_dimensions2, cat);
    BOOST_CHECK( svm2.getDimension() == test_dimensions2 );


    /** Prepare train examples */
    SvmClassifier<double, ValueNominal<string> >::ClassifyExample testVector1;
    testVector1.push_back(1);    testVector1.push_back(1);    testVector1.push_back(1);

    SvmClassifier<double, ValueNominal<string> >::ClassifyExample testVector2;
    testVector2.push_back(-1);        testVector2.push_back(-1);    testVector2.push_back(-1);

    /** Add train examples to Svm classifier */
    BOOST_CHECK_EQUAL( 0, svm.countTrainExamples() );
    BOOST_CHECK_EQUAL( 0, svm2.countTrainExamples() );

    svm.addExample(testVector1, "good");
    svm.addExample(testVector2, "bad");
    svm2.addExample(testVector1, "good");
    svm2.addExample(testVector2, "bad");

    BOOST_CHECK_EQUAL( 2, svm.countTrainExamples() );
    BOOST_CHECK_EQUAL( 0, svm2.countTrainExamples() ); /* Since dimensions not equal!*/

    svm.addExample( testVector1, "good" );
    svm2.addExample( testVector1, "good" );
    BOOST_CHECK_EQUAL( 3, svm.countTrainExamples() );
    BOOST_CHECK_EQUAL( 0, svm2.countTrainExamples() );
    svm.addExample( testVector2, "bad" );
    svm2.addExample( testVector2, "bad" );
    BOOST_CHECK_EQUAL( 4, svm.countTrainExamples() );
    BOOST_CHECK_EQUAL( 0, svm2.countTrainExamples() );
    svm.addExample( testVector1, "good" );
    svm2.addExample( testVector1, "good" );
    BOOST_CHECK_EQUAL( 5, svm.countTrainExamples() );
    BOOST_CHECK_EQUAL( 0, svm2.countTrainExamples() );
    svm.addExample( testVector2, "bad" );
    svm2.addExample( testVector2, "bad" );
    BOOST_CHECK_EQUAL( 6, svm.countTrainExamples() );
    BOOST_CHECK_EQUAL( 0, svm2.countTrainExamples() );

    /** Reset svm */
    svm.reset();
    svm2.reset();
    BOOST_CHECK_EQUAL( 0, svm.countTrainExamples() );
    BOOST_CHECK_EQUAL( 0, svm2.countTrainExamples() );

}

/** Test svm classification */
BOOST_AUTO_TEST_CASE( SvmClassifyTest ) {

    string C[] = {"good","bad"}; SvmClassifier<double, ValueNominal<string> >::AttrDomain cat = createDomain("", C, C+2);

    unsigned int test_dimensions = 3;
    SvmClassifier<double, ValueNominal<string> > svm(test_dimensions, cat);

    /** Prepare train examples */
    SvmClassifier<double, ValueNominal<string> >::ClassifyExample testVector1;
    testVector1.push_back(1);    testVector1.push_back(1);    testVector1.push_back(1);

    SvmClassifier<double, ValueNominal<string> >::ClassifyExample testVector2;
    testVector2.push_back(-1);    testVector2.push_back(-1);    testVector2.push_back(-1);

    svm.addExample(testVector1, "good");
    svm.addExample(testVector2, "bad");

    /** Classify */
    svm.train();

    SvmClassifier<double, ValueNominal<string> >::ClassifyExample classifyVector1;
    classifyVector1.push_back(1);    classifyVector1.push_back(0);    classifyVector1.push_back(0);
    SvmClassifier<double, ValueNominal<string> >::Beliefs beliefs = svm.getCategories(classifyVector1);
    BOOST_CHECK_EQUAL(beliefs[0].getValue()->get(), "good");
    BOOST_CHECK(beliefs[0].getProbability() > 0.5);

    SvmClassifier<double, ValueNominal<string> >::ClassifyExample classifyVector2;
    classifyVector2.push_back(0);    classifyVector2.push_back(-1);    classifyVector2.push_back(0);
    beliefs = svm.getCategories(classifyVector2);
    BOOST_CHECK_EQUAL(beliefs[0].getValue()->get(), "bad");
    BOOST_CHECK(beliefs[1].getProbability() < 0.5);
    BOOST_CHECK_EQUAL(svm.getCategory(classifyVector2).getValue()->get(), "bad");

    svm.reset();
    beliefs = svm.getCategories(classifyVector1);
    BOOST_CHECK_CLOSE_FRACTION(beliefs[0].getProbability(), 0.5, 0.01);
    BOOST_CHECK_CLOSE_FRACTION(beliefs[1].getProbability(), 0.5, 0.01);
    beliefs = svm.getCategories(classifyVector2);
    BOOST_CHECK_CLOSE_FRACTION(beliefs[0].getProbability(), 0.5, 0.01);
    BOOST_CHECK_CLOSE_FRACTION(beliefs[1].getProbability(), 0.5, 0.01);

}


BOOST_AUTO_TEST_CASE( SvmClassifyTest2 ) {

    string C[] = {"good","bad"}; SvmClassifier<double, ValueNominal<string> >::AttrDomain cat = createDomain("", C, C+2);

    unsigned int test_dimensions = 2;
    SvmClassifier<double, ValueNominal<string> > svm(test_dimensions, cat);

    /** Prepare train examples */
    SvmClassifier<double, ValueNominal<string> >::ClassifyExample testVector1 = {1, 9};
    SvmClassifier<double, ValueNominal<string> >::ClassifyExample testVector2 = {3, 1};
    SvmClassifier<double, ValueNominal<string> >::ClassifyExample testVector3 = {6, 3};
    SvmClassifier<double, ValueNominal<string> >::ClassifyExample testVector4 = {6, 4};
    SvmClassifier<double, ValueNominal<string> >::ClassifyExample testVector5 = {3, 5};
    SvmClassifier<double, ValueNominal<string> >::ClassifyExample testVector6 = {4, 2};
    SvmClassifier<double, ValueNominal<string> >::ClassifyExample testVector7 = {7, 7};
    SvmClassifier<double, ValueNominal<string> >::ClassifyExample testVector8 = {7, 3};
    SvmClassifier<double, ValueNominal<string> >::ClassifyExample testVector9 = {8, 5};
    SvmClassifier<double, ValueNominal<string> >::ClassifyExample testVector10= {3, 9};

    svm.addExample(testVector1, "good");
    svm.addExample(testVector2, "good");
    svm.addExample(testVector3, "good");
    svm.addExample(testVector4, "good");
    svm.addExample(testVector5, "good");

    svm.addExample(testVector6, "bad");
    svm.addExample(testVector7, "bad");
    svm.addExample(testVector8, "bad");
    svm.addExample(testVector9, "bad");
    svm.addExample(testVector10, "bad");

    /** Train and classify */
    svm.train();

    SvmClassifier<double, ValueNominal<string> >::Beliefs beliefs = svm.getCategories(testVector1);
    BOOST_CHECK_EQUAL( beliefs.size(), 2 );
    BOOST_CHECK_EQUAL( beliefs[0].getValue()->get(), "good");
    BOOST_CHECK_EQUAL( beliefs[1].getValue()->get(), "bad");
    BOOST_CHECK( beliefs[0].getProbability() > 0.5);
    BOOST_CHECK( beliefs[1].getProbability() < 0.5);

    beliefs = svm.getCategories(testVector2);
    BOOST_CHECK_EQUAL( beliefs.size(), 2 );
    BOOST_CHECK_EQUAL( beliefs[0].getValue()->get(), "good");
    BOOST_CHECK_EQUAL( beliefs[1].getValue()->get(), "bad");
    BOOST_CHECK( beliefs[0].getProbability() > 0.5);
    BOOST_CHECK( beliefs[1].getProbability() < 0.5);

    beliefs = svm.getCategories(testVector3);
    BOOST_CHECK_EQUAL( beliefs.size(), 2 );
    BOOST_CHECK_EQUAL( beliefs[0].getValue()->get(), "good");
    BOOST_CHECK_EQUAL( beliefs[1].getValue()->get(), "bad");
    BOOST_CHECK( beliefs[0].getProbability() > 0.5);
    BOOST_CHECK( beliefs[1].getProbability() < 0.5);

    beliefs = svm.getCategories(testVector4);
    BOOST_CHECK_EQUAL( beliefs.size(), 2 );
    BOOST_CHECK_EQUAL( beliefs[0].getValue()->get(), "good");
    BOOST_CHECK_EQUAL( beliefs[1].getValue()->get(), "bad");
    BOOST_CHECK( beliefs[0].getProbability() > 0.5);
    BOOST_CHECK( beliefs[1].getProbability() < 0.5);

    beliefs = svm.getCategories(testVector5);
    BOOST_CHECK_EQUAL( beliefs.size(), 2 );
    BOOST_CHECK_EQUAL( beliefs[0].getValue()->get(), "good");
    BOOST_CHECK_EQUAL( beliefs[1].getValue()->get(), "bad");
    BOOST_CHECK( beliefs[0].getProbability() > 0.5);
    BOOST_CHECK( beliefs[1].getProbability() < 0.5);

    beliefs = svm.getCategories(testVector6);
    BOOST_CHECK_EQUAL( beliefs.size(), 2 );
    BOOST_CHECK_EQUAL( beliefs[1].getValue()->get(), "good");
    BOOST_CHECK_EQUAL( beliefs[0].getValue()->get(), "bad");
    BOOST_CHECK( beliefs[0].getProbability() > 0.5);
    BOOST_CHECK( beliefs[1].getProbability() < 0.5);

    beliefs = svm.getCategories(testVector7);
    BOOST_CHECK_EQUAL( beliefs.size(), 2 );
    BOOST_CHECK_EQUAL( beliefs[1].getValue()->get(), "good");
    BOOST_CHECK_EQUAL( beliefs[0].getValue()->get(), "bad");
    BOOST_CHECK( beliefs[0].getProbability() > 0.5);
    BOOST_CHECK( beliefs[1].getProbability() < 0.5);

    beliefs = svm.getCategories(testVector8);
    BOOST_CHECK_EQUAL( beliefs.size(), 2 );
    BOOST_CHECK_EQUAL( beliefs[1].getValue()->get(), "good");
    BOOST_CHECK_EQUAL( beliefs[0].getValue()->get(), "bad");
    BOOST_CHECK( beliefs[0].getProbability() > 0.5);
    BOOST_CHECK( beliefs[1].getProbability() < 0.5);

    beliefs = svm.getCategories(testVector9);
    BOOST_CHECK_EQUAL( beliefs.size(), 2 );
    BOOST_CHECK_EQUAL( beliefs[1].getValue()->get(), "good");
    BOOST_CHECK_EQUAL( beliefs[0].getValue()->get(), "bad");
    BOOST_CHECK( beliefs[0].getProbability() > 0.5);
    BOOST_CHECK( beliefs[1].getProbability() < 0.5);

    beliefs = svm.getCategories(testVector10);
    BOOST_CHECK_EQUAL( beliefs.size(), 2 );
    BOOST_CHECK_EQUAL( beliefs[1].getValue()->get(), "good");
    BOOST_CHECK_EQUAL( beliefs[0].getValue()->get(), "bad");
    BOOST_CHECK( beliefs[0].getProbability() > 0.5);
    BOOST_CHECK( beliefs[1].getProbability() < 0.5);

}

BOOST_AUTO_TEST_CASE( SvmSerializeTest ) {

    string C[] = {"good","bad"}; SvmClassifier<double, ValueNominal<string> >::AttrDomain cat = createDomain("", C, C+2);

    /** Prepare SVM classifier and its parameters */
    SvmClassifier<double, ValueNominal<string> > svm(3, cat);
    svm.resetAndChangeDimension(2);
    svm.setC(2.1);
    svm.setMargin(0.1);
    svm.setGaussKernel();
    svm.setGaussParameter(1.5);
    svm.setFiniteStepsStopCondition(12.5);

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

    /** Train classifier */
    svm.train();

    /** Serialize classifier */
    std::ostringstream oss;
    boost::archive::xml_oarchive oa(oss);
    oa << boost::serialization::make_nvp("SVM", svm );
    string svmSerialString = oss.str();

    /** De-serialize classifier to create new object: svm2 */
    std::istringstream iss(svmSerialString);
    boost::archive::xml_iarchive ia(iss);
    SvmClassifier<double, ValueNominal<string> > svm2;
    ia >> boost::serialization::make_nvp("SVM", svm2);


    /** Serialize svm2 and compare it with svm  */
    ostringstream oss2;
    boost::archive::xml_oarchive oa2(oss2);
    oa2 << boost::serialization::make_nvp("SVM", svm2 );
    string svm2SerialString = oss2.str();

    /** Both classifiers should be the same and classify alike */
    BOOST_CHECK(svmSerialString == svm2SerialString);
    for(const auto& v: testVector){
        SvmClassifier<double, ValueNominal<string> >::Beliefs beliefs = svm.getCategories(v);
        SvmClassifier<double, ValueNominal<string> >::Beliefs beliefs2 = svm2.getCategories(v);

        BOOST_CHECK_EQUAL( beliefs.size(), beliefs2.size() );
        BOOST_CHECK_EQUAL( beliefs[0].getValue()->get(), beliefs2[0].getValue()->get());
        BOOST_CHECK_EQUAL( beliefs[1].getValue()->get(), beliefs2[1].getValue()->get());
        BOOST_CHECK_CLOSE_FRACTION( beliefs[0].getProbability(), beliefs2[0].getProbability(), 0.001);
        BOOST_CHECK_CLOSE_FRACTION( beliefs[1].getProbability(), beliefs2[1].getProbability(), 0.001);
    }


}

BOOST_AUTO_TEST_CASE( SvmClassifyTestLinearSimple ) {

    string C[] = {"good","bad"}; SvmClassifier<double, ValueNominal<string> >::AttrDomain cat = createDomain("", C, C+2);

    SvmClassifier<double, ValueNominal<string> > svm(2, cat);
    svm.setLinearKernel();
    SvmClassifier<double, ValueNominal<string> >::ClassifyExample pos = {1, 1};
    SvmClassifier<double, ValueNominal<string> >::ClassifyExample neg = {2, 2};
    svm.addExample(pos, "good");
    svm.addExample(neg, "bad");
    svm.setFiniteStepsStopCondition(100);
    svm.train();
    SvmClassifier<double, ValueNominal<string> >::Beliefs beliefs = svm.getCategories(pos);
    SvmClassifier<double, ValueNominal<string> >::Beliefs beliefs2 = svm.getCategories(neg);

    BOOST_CHECK_EQUAL( beliefs[0].getValue()->get(), "good");
    BOOST_CHECK_EQUAL( beliefs2[0].getValue()->get(), "bad");

}

BOOST_AUTO_TEST_CASE( SvmWronglyInitializedTest ) {
    /* SvmClassifier constructor accept only category domains of size two */
    string C[] = {"good","bad","ugly"};
    SvmClassifier<double, ValueNominal<string> >::AttrDomain cat = createDomain("", C, C+3);
    typedef SvmClassifier<double, ValueNominal<string> > SVM;
    BOOST_CHECK_THROW( SVM(2, cat), std::domain_error);
}

BOOST_AUTO_TEST_CASE( SvmWrongClassificationCategoryTest ) {
    /* SvmClassifier addExample method accept only examples from one of two domain categories */
    string C[] = {"good","bad"};
    SvmClassifier<double, ValueNominal<string> >::AttrDomain cat = createDomain("", C, C+2);
    SvmClassifier<double, ValueNominal<string> > svm(2, cat);
    SvmClassifier<double, ValueNominal<string> >::ClassifyExample pos = {1, 1};
    SvmClassifier<double, ValueNominal<string> >::ClassifyExample neg = {2, 2};
    svm.addExample(pos, "good");
    svm.addExample(neg, "bad");
    BOOST_CHECK_THROW( svm.addExample(neg, "ugly"), std::domain_error);
    BOOST_CHECK_EQUAL(2, svm.countTrainExamples());
}

BOOST_AUTO_TEST_SUITE_END()
