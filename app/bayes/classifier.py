# -*- coding: utf-8 -*-
from naiveBayesClassifier import tokenizer
from naiveBayesClassifier.trainer import Trainer
from naiveBayesClassifier.classifier import Classifier

trainer = Trainer(tokenizer.Tokenizer(stop_words = [], signs_to_remove = ["?!#%&|"]))


def get_file_data(path):
    with open(path, 'r') as file:
        return file.read().replace('\n', '')


training_set = [
    {'text': get_file_data('app/bayes/training_data/food/1.txt'), 'category': 'food'},
    {'text': get_file_data('app/bayes/training_data/food/2.txt'), 'category': 'food'},
    {'text': get_file_data('app/bayes/training_data/food/3.txt'), 'category': 'food'},
    {'text': get_file_data('app/bayes/training_data/food/4.txt'), 'category': 'food'},
    {'text': get_file_data('app/bayes/training_data/food/5.txt'), 'category': 'food'},
    {'text': get_file_data('app/bayes/training_data/food/6.txt'), 'category': 'food'},
    {'text': get_file_data('app/bayes/training_data/food/7.txt'), 'category': 'food'},
    {'text': get_file_data('app/bayes/training_data/food/8.txt'), 'category': 'food'},
    {'text': get_file_data('app/bayes/training_data/food/9.txt'), 'category': 'food'},
    {'text': get_file_data('app/bayes/training_data/food/10.txt'), 'category': 'food'},
    {'text': get_file_data('app/bayes/training_data/sport/1.txt'), 'category': 'sport'},
    {'text': get_file_data('app/bayes/training_data/sport/2.txt'), 'category': 'sport'},
    {'text': get_file_data('app/bayes/training_data/sport/3.txt'), 'category': 'sport'},
    {'text': get_file_data('app/bayes/training_data/sport/4.txt'), 'category': 'sport'},
    {'text': get_file_data('app/bayes/training_data/sport/5.txt'), 'category': 'sport'},
    {'text': get_file_data('app/bayes/training_data/sport/6.txt'), 'category': 'sport'},
    {'text': get_file_data('app/bayes/training_data/sport/7.txt'), 'category': 'sport'},
    {'text': get_file_data('app/bayes/training_data/sport/8.txt'), 'category': 'sport'},
    {'text': get_file_data('app/bayes/training_data/sport/9.txt'), 'category': 'sport'},
    {'text': get_file_data('app/bayes/training_data/sport/10.txt'), 'category': 'sport'},
    {'text': get_file_data('app/bayes/training_data/travel/1.txt'), 'category': 'travel'},
    {'text': get_file_data('app/bayes/training_data/travel/2.txt'), 'category': 'travel'},
    {'text': get_file_data('app/bayes/training_data/travel/3.txt'), 'category': 'travel'},
    {'text': get_file_data('app/bayes/training_data/travel/4.txt'), 'category': 'travel'},
    {'text': get_file_data('app/bayes/training_data/travel/5.txt'), 'category': 'travel'},
    {'text': get_file_data('app/bayes/training_data/travel/6.txt'), 'category': 'travel'},
    {'text': get_file_data('app/bayes/training_data/travel/7.txt'), 'category': 'travel'},
    {'text': get_file_data('app/bayes/training_data/travel/8.txt'), 'category': 'travel'},
    {'text': get_file_data('app/bayes/training_data/travel/9.txt'), 'category': 'travel'},

    
                
                
    {'text': 'Russia is trying to invade Ukraine', 'category': 'politics'},
    {'text': 'do not neglect exercise', 'category': 'health'},
    {'text': 'Syria is the main issue, Obama says', 'category': 'politics'},
    {'text': 'eat to lose weight', 'category': 'health'},
    {'text': 'you should not eat much', 'category': 'health'},
    {'text': 'Google is awesome', 'category': 'technology'}
]

                
    

for training in training_set:
    trainer.train(training['text'], training['category'])

def classify(text):
    newsClassifier = Classifier(trainer.data, tokenizer.Tokenizer(stop_words = [], signs_to_remove = ["?!#%&|"]))
    # Now you have a classifier which can give a try to classifiy text of news whose
    # category is unknown, yet.
    classification = newsClassifier.classify(text)

    # the classification variable holds the possible categories sorted by 
    # their probablity value
    probablity = 0
    result = 'No category'
    for category, val in classification:
        if val > probablity:
            probablity = val
            result = category

    return result

if __name__ == '__main__':
    print classify("Even if I eat too much, is not it possible to lose some weight")
