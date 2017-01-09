#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE TextClassifier

#include <boost/test/unit_test.hpp>

#include "classifier.hpp"

using boost::unit_test::test_suite;

BOOST_AUTO_TEST_CASE(classifier_test) {
    TextClassifier tc;

    tc.add_category("technology");
    tc.add_category("food");

    tc.add_keyword("google");
    tc.add_keyword("microsoft");
    tc.add_keyword("pizza");
    tc.add_keyword("burger");

    tc.init();

    tc.add_training({"google","microsoft"}, "technology");
    tc.add_training({"burger", "pizza"}, "food");

    tc.train();

    BOOST_CHECK(tc.classify("I love google") == "technology");
    BOOST_CHECK(tc.classify("I prefer google to microsoft") == "technology");

    BOOST_CHECK(tc.classify("I love a good burger") == "food");
    BOOST_CHECK(tc.classify("I love a good burger as well as a pizza") == "food");

    BOOST_CHECK(tc.classify("A friend from google asked whether he should get a burger or a pizza") == "food");

    BOOST_CHECK(tc.classify("Some random words") == "none");
}