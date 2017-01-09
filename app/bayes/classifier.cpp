#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

#include "classifier.hpp"

BOOST_PYTHON_MODULE(classifier) {
    using namespace boost::python;

    class_<TextClassifier>("TextClassifier")
        .def("add_category", &TextClassifier::add_category)
        .def("add_keyword", &TextClassifier::add_keyword)
        .def("add_training", &TextClassifier::add_training)
        .def("init", &TextClassifier::init)
        .def("train", &TextClassifier::train)
        .def("classify", &TextClassifier::classify);

    class_<vector<string>>("TrainingSet")
        .def(vector_indexing_suite<vector<string>>());
}