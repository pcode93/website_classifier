#include <boost/python.hpp>
#include <boost/thread.hpp>

char* const classify(const std::string& text, boost::python::object callback) {

}

BOOST_PYTHON_MODULE(classify) {
    using namespace boost::python;
    def('classify', classify);
}