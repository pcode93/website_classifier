#if defined(_MSC_VER) && (_MSC_VER >= 1700)
//msvc12.0 Boost.Serialization warning
#pragma warning(disable:4512)
#endif

#include <iostream>
#include <fstream>

#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>

#include "../src/learning/Validator.hpp"
#include "../src/learning/RandomForest.hpp"
#include "../src/learning/NaiveBayesian.hpp"
#include "../src/learning/DecisionTree.hpp"

const int NR_OF_ATTRS_TITANIC = 5;

using namespace std;
using namespace faif;
using namespace faif::ml;
using boost::unit_test::test_suite;

template<typename Val> typename Classifier<Val>::ExampleTrain getNextExample(std::string line, const Classifier<Val>& cl) {

    std::vector<std::string> result;
    std::stringstream lineStream(line);
    std::string cell;

    while(std::getline(lineStream,cell,',')){
        result.push_back(cell);
    }
    if(line.back() == ','){
        result.push_back("");
    }
    std::string ex[NR_OF_ATTRS_TITANIC];
    for (unsigned i = 1; i < result.size(); ++i) {
        if(result[i] == ""){
            result[i] = "NULL";
        }
        ex[i-1] = result[i];
    }
    return  createExample(ex, ex + result.size() -1, result[0], cl );

}

BOOST_AUTO_TEST_SUITE( FAIF_classifiers_test )

BOOST_AUTO_TEST_CASE( four_rules_one_attribute_nbc  ) {

    typedef NaiveBayesian< ValueNominal<int> > NBC;

    NBC::AttrDomain cat("cat"); cat.insert(0); cat.insert(1);
    NBC::AttrDomain a("a"); a.insert(0); a.insert(1);
    NBC::Domains attribs; attribs.push_back( a );
    NBC nb(attribs, cat);

    vector<pair<string,int> > va0;  va0.push_back( make_pair<string,int>("a", 0) );
    vector<pair<string,int> > va1;  va1.push_back( make_pair<string,int>("a", 1) );

    NBC::ExamplesTrain ex;
    ex.push_back( createExample( va0, 0, nb ) );
    ex.push_back( createExample( va0, 0, nb ) );
    ex.push_back( createExample( va1, 1, nb ) );
    ex.push_back( createExample( va1, 1, nb ) );

    nb.train(ex);

    NBC::Beliefs ca0 = nb.getCategories( createExample(va0, nb) );
    BOOST_CHECK_EQUAL( ca0.size(), 2U );
    BOOST_CHECK_EQUAL( ca0[0].getValue()->get(), 0);
    BOOST_CHECK_CLOSE_FRACTION( ca0[0].getProbability(), 0.75, 0.01 );
    BOOST_CHECK_EQUAL( ca0[1].getValue()->get(), 1);
    BOOST_CHECK_CLOSE_FRACTION( ca0[1].getProbability(), 0.25, 0.01 );

    NBC::Beliefs ca1 = nb.getCategories( createExample(va1, nb) );
    BOOST_CHECK_EQUAL( ca1.size(), 2U );
    BOOST_CHECK_EQUAL( ca1[0].getValue()->get(), 1);
    BOOST_CHECK_CLOSE_FRACTION( ca1[0].getProbability(), 0.75, 0.01 );
    BOOST_CHECK_EQUAL( ca1[1].getValue()->get(), 0);
    BOOST_CHECK_CLOSE_FRACTION( ca1[1].getProbability(), 0.25, 0.01 );

}

BOOST_AUTO_TEST_CASE( four_rules_one_attribute_dtc  ) {

    typedef DecisionTree< ValueNominal<int> > DTC;

    DTC::AttrDomain cat("cat"); cat.insert(0); cat.insert(1);
    DTC::AttrDomain a("a"); a.insert(0); a.insert(1);
    DTC::Domains attribs; attribs.push_back( a );
    DTC dt(attribs, cat);

    vector<pair<string,int> > va0;  va0.push_back( make_pair<string,int>("a", 0) );
    vector<pair<string,int> > va1;  va1.push_back( make_pair<string,int>("a", 1) );

    DTC::ExamplesTrain ex;
    ex.push_back( createExample( va0, 0, dt ) );
    ex.push_back( createExample( va0, 0, dt ) );
    ex.push_back( createExample( va1, 1, dt ) );
    ex.push_back( createExample( va1, 1, dt ) );

    dt.train(ex);

    DTC::Beliefs ca0 = dt.getCategories( createExample(va0, dt) );
    BOOST_CHECK_EQUAL( ca0.size(), 1U );
    BOOST_CHECK_EQUAL( ca0[0].getValue()->get(), 0);
    BOOST_CHECK_CLOSE_FRACTION( ca0[0].getProbability(), 1.0, 0.01 );

    DTC::Beliefs ca1 = dt.getCategories( createExample(va1, dt) );
    BOOST_CHECK_EQUAL( ca1.size(), 1U );
    BOOST_CHECK_EQUAL( ca1[0].getValue()->get(), 1);
    BOOST_CHECK_CLOSE_FRACTION( ca1[0].getProbability(), 1.0, 0.01 );
}

BOOST_AUTO_TEST_CASE( six_rules_2_one_attribute_nbc  ) {

    typedef NaiveBayesian< ValueNominal<int> > NBC;

    NBC::AttrDomain cat("cat"); cat.insert(0); cat.insert(1);
    NBC::AttrDomain a("a"); a.insert(0); a.insert(1); a.insert(2);
    NBC::Domains attribs; attribs.push_back( a );
    NBC nb(attribs, cat);

    vector<pair<string,int> > va0;  va0.push_back( make_pair<string,int>("a", 0) );
    vector<pair<string,int> > va1;  va1.push_back( make_pair<string,int>("a", 1) );
    vector<pair<string,int> > va2;  va2.push_back( make_pair<string,int>("a", 2) );

    NBC::ExamplesTrain ex;
    ex.push_back( createExample( va0, 0, nb ) );
    ex.push_back( createExample( va0, 0, nb ) );
    ex.push_back( createExample( va1, 1, nb ) );
    ex.push_back( createExample( va1, 1, nb ) );
    ex.push_back( createExample( va2, 0, nb ) );
    ex.push_back( createExample( va2, 1, nb ) );

    nb.train(ex);

    NBC::Beliefs ca0 = nb.getCategories( createExample(va0, nb) );
    BOOST_CHECK_EQUAL( ca0.size(), 2U );
    BOOST_CHECK_EQUAL( ca0[0].getValue()->get(), 0);
    BOOST_CHECK_CLOSE_FRACTION( ca0[0].getProbability(), 0.75, 0.01 );
    BOOST_CHECK_EQUAL( ca0[1].getValue()->get(), 1);
    BOOST_CHECK_CLOSE_FRACTION( ca0[1].getProbability(), 0.25, 0.01 );

    NBC::Beliefs ca1 = nb.getCategories( createExample(va1, nb) );
    BOOST_CHECK_EQUAL( ca1.size(), 2U );
    BOOST_CHECK_EQUAL( ca1[0].getValue()->get(), 1);
    BOOST_CHECK_CLOSE_FRACTION( ca1[0].getProbability(), 0.75, 0.01 );
    BOOST_CHECK_EQUAL( ca1[1].getValue()->get(), 0);
    BOOST_CHECK_CLOSE_FRACTION( ca1[1].getProbability(), 0.25, 0.01 );

    NBC::Beliefs ca2 = nb.getCategories( createExample(va2, nb) );
    BOOST_CHECK_EQUAL( ca2.size(), 2U );
    //BOOST_CHECK_EQUAL( ca2[0].getValue()->get(), 1); dont known which is first, which is second
    BOOST_CHECK_CLOSE_FRACTION( ca2[0].getProbability(), 0.5, 0.01 );
    //BOOST_CHECK_EQUAL( ca2[1].getValue()->get(), 0); dont known which is first, which is second
    BOOST_CHECK_CLOSE_FRACTION( ca2[1].getProbability(), 0.5, 0.01 );


}
BOOST_AUTO_TEST_CASE( eight_rules_one_attribute_dtc  ) {

    typedef DecisionTree< ValueNominal<int> > DTC;

    DTC::AttrDomain cat("cat"); cat.insert(0); cat.insert(1);
    DTC::AttrDomain a("a"); a.insert(0); a.insert(1); a.insert(2);
    DTC::Domains attribs; attribs.push_back( a );
    DTC dt(attribs, cat);

    vector<pair<string,int> > va0;  va0.push_back( make_pair<string,int>("a", 0) );
    vector<pair<string,int> > va1;  va1.push_back( make_pair<string,int>("a", 1) );
    vector<pair<string,int> > va2;  va2.push_back( make_pair<string,int>("a", 2) );

    DTC::ExamplesTrain ex;
    ex.push_back( createExample( va0, 0, dt ) );
    ex.push_back( createExample( va0, 0, dt ) );
    ex.push_back( createExample( va1, 1, dt ) );
    ex.push_back( createExample( va1, 1, dt ) );
    ex.push_back( createExample( va2, 1, dt ) );
    ex.push_back( createExample( va2, 1, dt ) );
    ex.push_back( createExample( va2, 0, dt ) );
    ex.push_back( createExample( va2, 0, dt ) );

    dt.train(ex);
    //cout << dt << endl;

    DTC::Beliefs ca0 = dt.getCategories( createExample(va0, dt) );
    BOOST_CHECK_EQUAL( ca0.size(), 1U );
    BOOST_CHECK_EQUAL( ca0[0].getValue()->get(), 0);
    BOOST_CHECK_CLOSE_FRACTION( ca0[0].getProbability(), 1.0, 0.01 );

    DTC::Beliefs ca1 = dt.getCategories( createExample(va1, dt) );
    BOOST_CHECK_EQUAL( ca1.size(), 1U );
    BOOST_CHECK_EQUAL( ca1[0].getValue()->get(), 1);
    BOOST_CHECK_CLOSE_FRACTION( ca1[0].getProbability(), 1.0, 0.01 );

    DTC::Beliefs ca2 = dt.getCategories( createExample(va2, dt) );
    BOOST_CHECK_EQUAL( ca2.size(), 2U );
    //BOOST_CHECK_EQUAL( ca2[0].getValue()->get(), 1); //dont known which is first, which is second
    BOOST_CHECK_CLOSE_FRACTION( ca2[0].getProbability(), 0.5, 0.01 );
    //BOOST_CHECK_EQUAL( ca2[1].getValue()->get(), 0); //dont known which is first, which is second
    BOOST_CHECK_CLOSE_FRACTION( ca2[1].getProbability(), 0.5, 0.01 );


}
BOOST_AUTO_TEST_CASE( four_rules_one_attribute_rfc  ) {

    typedef RandomForest< ValueNominal<int> > RFC;

    RFC::AttrDomain cat("cat"); cat.insert(0); cat.insert(1);
    RFC::AttrDomain a("a"); a.insert(0); a.insert(1);
    RFC::Domains attribs; attribs.push_back( a );
    RFC rf(attribs, cat);

    vector<pair<string,int> > va0;  va0.push_back( make_pair<string,int>("a", 0) );
    vector<pair<string,int> > va1;  va1.push_back( make_pair<string,int>("a", 1) );

    RFC::ExamplesTrain ex;
    ex.push_back( createExample( va0, 0, rf ) );
    ex.push_back( createExample( va0, 0, rf ) );
    ex.push_back( createExample( va0, 0, rf ) );
    ex.push_back( createExample( va0, 0, rf ) );

    rf.train(ex);

    RFC::Beliefs ca0 = rf.getCategories( createExample(va0, rf) );
    BOOST_CHECK_EQUAL( ca0.size(), 1U );
    BOOST_CHECK_EQUAL( ca0[0].getValue()->get(), 0);
    BOOST_CHECK_CLOSE_FRACTION( ca0[0].getProbability(), 1, 0.01 );


}

BOOST_AUTO_TEST_CASE( most_common_result_rfc  ) {

    int  ITER=50;
    typedef RandomForest< ValueNominal<int> > RFC;
    typedef RFC::AttrDomain AttrDomain;
    typedef RFC::ExampleTest ExampleTest;
    typedef RFC::ExamplesTrain ExamplesTrain;
    typedef RFC::Domains Domains;

    int C[] = {1,0}; AttrDomain cat = createDomain("", C, C+2);

    Domains attribs;
    int A1[] = { 0, 1, 2};	attribs.push_back( createDomain("a", A1, A1 + 3) );
    int A2[] = { 0, 1, 2};	attribs.push_back( createDomain("b", A2, A2 + 3) );
    int A3[] = { 0, 1};		attribs.push_back( createDomain("c", A3, A3 + 2) );
    int A4[] = { 0, 1};		attribs.push_back( createDomain("d", A4, A4 + 2) );
    RFC rf(attribs, cat);

    ExamplesTrain ex; 
    int E01[] = { 0, 0, 1, 1};	ex.push_back( createExample( E01, E01 + 4, 0, rf ) );
    int E02[] = { 0, 0, 1, 0};	ex.push_back( createExample( E02, E02 + 4, 0 , rf) );
    int E03[] = { 1, 0, 1, 1};	ex.push_back( createExample( E03, E03 + 4, 1 , rf) );
    int E04[] = { 2, 1, 1, 1};	ex.push_back( createExample( E04, E04 + 4, 1 , rf) );
    int E05[] = { 2, 2, 0, 1};	ex.push_back( createExample( E05, E05 + 4, 1 , rf) );
    int E06[] = { 2, 2, 0, 0};	ex.push_back( createExample( E06, E06 + 4, 0 , rf) );
    int E07[] = { 1, 2, 0, 0};	ex.push_back( createExample( E07, E07 + 4, 1 , rf) );
    int E08[] = { 0, 1, 1, 1};	ex.push_back( createExample( E08, E08 + 4, 0 , rf) );
    int E09[] = { 0, 2, 0, 1};	ex.push_back( createExample( E09, E09 + 4, 1 , rf) );
    int E10[] = { 2, 1, 0, 1};	ex.push_back( createExample( E10, E10 + 4, 1 , rf) );
    int E11[] = { 0, 1, 0, 0};	ex.push_back( createExample( E11, E11 + 4, 1 , rf) );
    int E12[] = { 1, 1, 1, 0};	ex.push_back( createExample( E12, E12 + 4, 1 , rf) );
    int E13[] = { 1, 0, 0, 1};	ex.push_back( createExample( E13, E13 + 4, 1 , rf) );
    int E14[] = { 2, 1, 1, 0};	ex.push_back( createExample( E14, E14 + 4, 0 , rf) );

    int good_=0;
    for(int k=1;k<=ITER;k++)
    {
	rf.train( ex );  //train

	int ET[] = { 1, 0, 1, 1}; ExampleTest et = createExample( ET, ET + 4, rf);

	if(rf.getCategory(et) == rf.getCategoryIdd(1))
		good_++;
    }

    // statistically most popular category should be "1"(good)
    BOOST_CHECK( good_>(ITER-good_) );

}
BOOST_AUTO_TEST_CASE( titanic_test_nbc  ) {

    typedef NaiveBayesian< ValueNominal<std::string> > NBC;
    typedef NBC::AttrDomain AttrDomain;
    typedef NBC::ExamplesTrain ExamplesTrain;
    typedef NBC::Domains Domains;

    ExamplesTrain exs;
    Domains attribs;
    std::string A1[] = {"NULL","3","1","2"}; attribs.push_back( createDomain( "pclass", A1, A1 + 4));
    std::string A2[] = {"NULL","male","female"}; attribs.push_back( createDomain("sex", A2, A2 + 3));
    std::string A3[] = {"NULL","1","0","3","4","2","5","8"}; attribs.push_back( createDomain( "sibsp", A3, A3 + 8));
    std::string A4[] = {"NULL","0","1","2","5","3","4","6"}; attribs.push_back( createDomain( "parch", A4, A4 + 8));
    std::string A5[] = {"NULL","S","C","Q"}; attribs.push_back( createDomain("embarked", A5, A5 + 4 ));

    std::string C[] = {"0","1"}; AttrDomain cat = createDomain("survived", C, C+2);
    NBC rf( attribs, cat );
    std::ifstream fs;
    fs.open("tests/data/titanic.csv", std::ios::in);
    std::string line;
    //get rid of column names
    getline(fs,line);
    while(getline(fs, line)){
        exs.push_back(getNextExample(line, rf));
        // std::cout << getNextExample(line, rf) << std::endl;
    }
    unsigned trainSetSize = exs.size()*0.3;
    ExamplesTrain testSet;
    for (unsigned i = 0; i < trainSetSize; ++i) {
        testSet.push_back(exs.back());
        exs.pop_back();
    }
    rf.train(exs);
    unsigned success = checkClassifier(testSet, rf);
    std::cout<<"Bayes: " << success<<"/"<<trainSetSize << std::endl;

    // the classification correctness greater than 70 percent
    BOOST_CHECK( success > trainSetSize*0.7  );
}
BOOST_AUTO_TEST_CASE( titanic_test_dtc  ) {

    typedef DecisionTree< ValueNominal<std::string> > DTC;
    typedef DTC::AttrDomain AttrDomain;
    typedef DTC::ExamplesTrain ExamplesTrain;
    typedef DTC::Domains Domains;

    ExamplesTrain exs;
    Domains attribs;
    std::string A1[] = {"NULL","3","1","2"}; attribs.push_back( createDomain( "pclass", A1, A1 + 4));
    std::string A2[] = {"NULL","male","female"}; attribs.push_back( createDomain("sex", A2, A2 + 3));
    std::string A3[] = {"NULL","1","0","3","4","2","5","8"}; attribs.push_back( createDomain( "sibsp", A3, A3 + 8));
    std::string A4[] = {"NULL","0","1","2","5","3","4","6"}; attribs.push_back( createDomain( "parch", A4, A4 + 8));
    std::string A5[] = {"NULL","S","C","Q"}; attribs.push_back( createDomain("embarked", A5, A5 + 4 ));

    std::string C[] = {"0","1"}; AttrDomain cat = createDomain("survived", C, C+2);
    DTC rf( attribs, cat );
    std::ifstream fs;
    fs.open("tests/data/titanic.csv", std::ios::in);
    std::string line;
    //get rid of column names
    getline(fs,line);
    while(getline(fs, line)){
        exs.push_back(getNextExample(line, rf));
        // std::cout << getNextExample(line, rf) << std::endl;
    }
    unsigned trainSetSize = exs.size()*0.3;
    ExamplesTrain testSet;
    for (unsigned i = 0; i < trainSetSize; ++i) {
        testSet.push_back(exs.back());
        exs.pop_back();
    }
    rf.train(exs);
    unsigned success = checkClassifier(testSet, rf);
    std::cout<<"DecisionTree: " << success<<"/"<<trainSetSize << std::endl;

    // the classification correctness greater than 70 percent
    BOOST_CHECK( success > trainSetSize*0.7  );
}
BOOST_AUTO_TEST_CASE( titanic_test_rfc  ) {

    typedef RandomForest< ValueNominal<std::string> > RFC;
    typedef RFC::AttrDomain AttrDomain;
    typedef RFC::ExamplesTrain ExamplesTrain;
    typedef RFC::Domains Domains;

    ExamplesTrain exs;
    Domains attribs;
    std::string A1[] = {"NULL","3","1","2"}; attribs.push_back( createDomain( "pclass", A1, A1 + 4));
    std::string A2[] = {"NULL","male","female"}; attribs.push_back( createDomain("sex", A2, A2 + 3));
    std::string A3[] = {"NULL","1","0","3","4","2","5","8"}; attribs.push_back( createDomain( "sibsp", A3, A3 + 8));
    std::string A4[] = {"NULL","0","1","2","5","3","4","6"}; attribs.push_back( createDomain( "parch", A4, A4 + 8));
    std::string A5[] = {"NULL","S","C","Q"}; attribs.push_back( createDomain("embarked", A5, A5 + 4 ));

    std::string C[] = {"0","1"}; AttrDomain cat = createDomain("survived", C, C+2);
    RFC rf( attribs, cat );
    std::ifstream fs;
    fs.open("tests/data/titanic.csv", std::ios::in);
    std::string line;
    //get rid of column names
    getline(fs,line);
    while(getline(fs, line)){
        exs.push_back(getNextExample(line, rf));
        // std::cout << getNextExample(line, rf) << std::endl;
    }
    unsigned trainSetSize = exs.size()*0.3;
    ExamplesTrain testSet;
    for (unsigned i = 0; i < trainSetSize; ++i) {
        testSet.push_back(exs.back());
        exs.pop_back();
    }
    rf.train(exs);
    unsigned success = checkClassifier(testSet, rf);
    std::cout <<"RandomForest: "<< success<<"/"<<trainSetSize << std::endl;

    // the classification correctness greater than 70 percent
    BOOST_CHECK( success > trainSetSize*0.7  );
}

BOOST_AUTO_TEST_SUITE_END()
