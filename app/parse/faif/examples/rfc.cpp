#if defined(_MSC_VER) && (_MSC_VER >= 1700)
//msvc12.0 Boost.Serialization warning
#pragma warning(disable:4512)
#endif

#include <iostream>
#include <faif/learning/Validator.hpp>
#include <faif/learning/RandomForest.hpp>

using namespace std;
using namespace faif;
using namespace faif::ml;

int main() {

	typedef RandomForest< ValueNominal<string> > RFC;
	typedef RFC::AttrDomain AttrDomain;
	typedef RFC::Domains Domains;
	typedef RFC::ExampleTest ExampleTest;
	typedef RFC::ExamplesTrain ExamplesTrain;

	Domains attribs;
	string A1[] = {"sunny", "overcast", "rain" }; attribs.push_back( createDomain("outlook", A1, A1 + 3) );
	string A2[] = {"hot", "mild", "cold"};        attribs.push_back( createDomain("temperature", A2, A2 + 3) );
	string A3[] = {"normal", "high"};             attribs.push_back( createDomain("humidity", A3, A3 + 2) );
	string A4[] = {"strong", "weak"};             attribs.push_back( createDomain("wind", A4, A4 + 2) );

	string C[] = {"good","bad"}; AttrDomain cat = createDomain("", C, C+2);

	RFC rf( attribs, cat ); //create the 'empty' classifier

	ExamplesTrain ex;
	string E01[] = { "sunny", "hot", "high", "weak"};         ex.push_back( createExample( E01, E01 + 4, "bad", rf ) );
	string E02[] = { "sunny", "hot", "high", "strong"};       ex.push_back( createExample( E02, E02 + 4, "bad" , rf) );
	string E03[] = { "overcast", "hot", "high", "weak"};      ex.push_back( createExample( E03, E03 + 4, "good" , rf) );
	string E04[] = { "rain", "mild", "high", "weak"};         ex.push_back( createExample( E04, E04 + 4, "good" , rf) );
	string E05[] = { "rain", "cold", "normal", "weak"};       ex.push_back( createExample( E05, E05 + 4, "good" , rf) );
	string E06[] = { "rain", "cold", "normal", "strong"};     ex.push_back( createExample( E06, E06 + 4, "bad" , rf) );
	string E07[] = { "overcast", "cold", "normal", "strong"}; ex.push_back( createExample( E07, E07 + 4, "good" , rf) );
	string E08[] = { "sunny", "mild", "high", "weak"};        ex.push_back( createExample( E08, E08 + 4, "bad" , rf) );
	string E09[] = { "sunny", "cold", "normal", "weak"};      ex.push_back( createExample( E09, E09 + 4, "good" , rf) );
	string E10[] = { "rain", "mild", "normal", "weak"};       ex.push_back( createExample( E10, E10 + 4, "good" , rf) );
	string E11[] = { "sunny", "mild", "normal", "strong"};    ex.push_back( createExample( E11, E11 + 4, "good" , rf) );
	string E12[] = { "overcast", "mild", "high", "strong"};   ex.push_back( createExample( E12, E12 + 4, "good" , rf) );
	string E13[] = { "overcast", "hot", "normal", "weak"};    ex.push_back( createExample( E13, E13 + 4, "good" , rf) );
	string E14[] = { "rain", "mild", "high", "strong"};       ex.push_back( createExample( E14, E14 + 4, "bad" , rf) );

	int good_=0;
	for(int k=1;k<=10;k++)
	{
		rf.train( ex );  //train

		string ET[] = { "overcast", "hot", "high", "weak"}; ExampleTest et = createExample( ET, ET + 4, rf);

		if(rf.getCategory(et) == rf.getCategoryIdd("good"))
			good_++;
	}
	//the most appearing category should be the 'good'
	std::cout << ( good_>5 ) << std::endl; //true

	//cross-validation on given set of examples
	std::cout << checkCross(ex, 14, rf) << std::endl;

	return 0;
}
