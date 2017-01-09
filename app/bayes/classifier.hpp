#include <unordered_map>
#include <iostream>
#include <vector>
#include <memory>

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>

#include <faif/learning/NaiveBayesian.hpp>

using namespace std;
using namespace faif;
using namespace faif::ml;

typedef NaiveBayesian< ValueNominal<string> > NB;
typedef NB::AttrDomain AttrDomain;
typedef NB::Domains Domains;
typedef NB::ExampleTest ExampleTest;
typedef NB::ExamplesTrain ExamplesTrain;

class TextClassifier {

public:
    TextClassifier(){}

    void add_category(const string& category) {
        classes.push_back(category);
    }

    void add_keyword(const string& attr) {
        keywords.push_back(attr);
    }

    void init() {
        string vals[] = {"yes", "no"};
        Domains attribs;

        for(int i = 0; i < keywords.size(); ++i) {
            keyword_to_index_map[keywords[i]] = i;
            attribs.push_back(createDomain(keywords[i], vals, vals + 2));
        }

        add_category("none");

        nb = make_shared<NB>(attribs, createDomain("", classes.data(), classes.data() + classes.size()));
    }

    void add_training(const vector<string>& words, const string& category) {
        const vector<string> found_keywords = find_keywords(words);
        trainings.push_back(createExample(found_keywords.data(), found_keywords.data() + keywords.size(), category, *nb));
    }

    void train() {
        add_training({}, "none");
        nb->train(trainings);
    }

    string classify(const string& text) {
        vector<string> words;
        boost::split(words, text, boost::is_any_of(" "));

        const vector<string> found_keywords = find_keywords(words);
        auto category = nb->getCategory(createExample(found_keywords.data(), found_keywords.data() + keywords.size(), *nb));

        for(string clazz : classes) {
            if(category == nb->getCategoryIdd(clazz)) {
                return clazz;
            }
        }

        return "none";
    }

private:
    const vector<string> find_keywords(const vector<string>& words) {
        vector<string> found_keywords(keywords.size(), "no");

        for(string word : words) {
            auto entry = keyword_to_index_map.find(word);
            if(entry != keyword_to_index_map.end()) {
                found_keywords[entry->second] = "yes";
            }
        }

        return found_keywords;
    }

    vector<string> classes;
    vector<string> keywords;
    unordered_map<string, int> keyword_to_index_map;
    ExamplesTrain trainings;
    shared_ptr<NB> nb;
};