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

/**
 * Uses FAIF Naive Bayes Classifier for text classification.
 * Uses a hash map to improve performance.
 * @see init
 */
class TextClassifier {

public:
    TextClassifier(){}

    void add_category(const string& category) {
        classes.push_back(category);
    }

    void add_keyword(const string& attr) {
        keywords.push_back(attr);
    }

    /**
     * FAIF classifiers require a set of attributes and categories.
     * Every attribute must have a set of possible values.
     * In this case, the values used indicate whether a keyword appeared in the text or not.
     *
     * This creates a set of attributes that look like this:
     * keyword1     keyword2    keyword3    ...
     * yes/no       yes/no      yes/no
     *
     * When classifying text, it is important that values for keywords appear in the same order as remembered by the classifier.
     * However, keywords may appear in the text in a different order or not appear at all.
     * To avoid multiple regex calls, a hash map is used to map between keywords and their index in the set of attributes.
     * This makes the algorithm search through the text only once.
     */
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

    /**
     * Trains the classifier to associate a set of keywords with a category.
     */
    void add_training(const vector<string>& words, const string& category) {
        const vector<string> found_keywords = find_keywords(words);
        trainings.push_back(createExample(found_keywords.data(), found_keywords.data() + keywords.size(), category, *nb));
    }

    /**
     * Passes the training data to FAIF Naive Bayes.
     */
    void train() {
        add_training({}, "none");
        nb->train(trainings);
    }

    /**
     * Tries to find and return a category matching the text.
     * If no category is found, returns "none".
     */
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
    /**
     * Finds keywords in the collection of words.
     * Uses a hash map to improve performance.
     * @see init 
     */
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