g++ -std=c++11 -I /usr/include/python2.7 -fpic -c -o classifier.o classifier.cpp
g++ -o classifier.so -shared classifier.o -lboost_python -lpython2.7 -lboost_system