#if defined(_MSC_VER) && (_MSC_VER >= 1700)
//msvc12.0 Boost.Serialization warning
#pragma warning(disable:4512)
#endif

#include <iostream>
#include <sstream>
#include <string>

#include <boost/serialization/nvp.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>

#include <faif/learning/DecisionTree.hpp>


using namespace std;
using namespace faif;
using namespace faif::ml;

int main() {

	typedef DecisionTree< ValueNominal<string> > DTC;
	typedef DTC::AttrDomain AttrDomain;
	typedef DTC::Domains Domains;
	typedef DTC::ExampleTest ExampleTest;
	typedef DTC::ExamplesTrain ExamplesTrain;

	Domains attribs;
	string A1[] = {"sunny", "overcast", "rain" }; attribs.push_back( createDomain("outlook", A1, A1 + 3) );
	string A2[] = {"hot", "mild", "cold"};        attribs.push_back( createDomain("temperature", A2, A2 + 3) );
	string A3[] = {"normal", "high"};             attribs.push_back( createDomain("humidity", A3, A3 + 2) );
	string A4[] = {"strong", "weak"};             attribs.push_back( createDomain("wind", A4, A4 + 2) );

	string C[] = {"good","bad"}; AttrDomain cat = createDomain("", C, C+2);

	DTC dt( attribs, cat ); //create the 'empty' classifier

	ExamplesTrain ex;
	string E01[] = { "sunny", "hot", "high", "weak"};         ex.push_back( createExample( E01, E01 + 4, "bad", dt ) );
	string E02[] = { "sunny", "hot", "high", "strong"};       ex.push_back( createExample( E02, E02 + 4, "bad" , dt) );
	string E03[] = { "overcast", "hot", "high", "weak"};      ex.push_back( createExample( E03, E03 + 4, "good" , dt) );
	string E04[] = { "rain", "mild", "high", "weak"};         ex.push_back( createExample( E04, E04 + 4, "good" , dt) );
	string E05[] = { "rain", "cold", "normal", "weak"};       ex.push_back( createExample( E05, E05 + 4, "good" , dt) );
	string E06[] = { "rain", "cold", "normal", "strong"};     ex.push_back( createExample( E06, E06 + 4, "bad" , dt) );
	string E07[] = { "overcast", "cold", "normal", "strong"}; ex.push_back( createExample( E07, E07 + 4, "good" , dt) );
	string E08[] = { "sunny", "mild", "high", "weak"};        ex.push_back( createExample( E08, E08 + 4, "bad" , dt) );
	string E09[] = { "sunny", "cold", "normal", "weak"};      ex.push_back( createExample( E09, E09 + 4, "good" , dt) );
	string E10[] = { "rain", "mild", "normal", "weak"};       ex.push_back( createExample( E10, E10 + 4, "good" , dt) );
	string E11[] = { "sunny", "mild", "normal", "strong"};    ex.push_back( createExample( E11, E11 + 4, "good" , dt) );
	string E12[] = { "overcast", "mild", "high", "strong"};   ex.push_back( createExample( E12, E12 + 4, "good" , dt) );
	string E13[] = { "overcast", "hot", "normal", "weak"};    ex.push_back( createExample( E13, E13 + 4, "good" , dt) );
	string E14[] = { "rain", "mild", "high", "strong"};       ex.push_back( createExample( E14, E14 + 4, "bad" , dt) );

	dt.train( ex );  //train

	ostringstream oss;
	boost::archive::xml_oarchive oa(oss);
	oa << boost::serialization::make_nvp("DTC", dt );
	//the serialized DTC is stored in oss.str() string
	//uncomment if You want to see the xml
	//cout << oss.str();
	DTC empty(attribs, cat); //crete the 'empty' classifier

	string ET[] = { "overcast", "hot", "high", "weak"};
	ExampleTest et1 = createExample( ET, ET + 4, empty);
	std::cout << empty.getCategory(et1) << std::endl; // should be null (for empty classifier)

	std::istringstream iss(oss.str());
	boost::archive::xml_iarchive ia(iss);
	ia >> boost::serialization::make_nvp("DTC", empty ); //de-serialize the stored object

	ExampleTest et2 = createExample( ET, ET + 4, empty );
	std::cout << *empty.getCategory(et2) << std::endl; // should be "good"
	std::cout << empty.getCategories(et2) << std::endl; // all categories with probabilities
	return 0;
}
