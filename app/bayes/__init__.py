"""
This module initializes a TextClassifier
with keywords, categories and training data
taken from bayes.json file.
"""
import json

from classifier import TextClassifier
from classifier import TrainingSet

config = {}
tc = TextClassifier()

with open('app/bayes/bayes.json') as config:
    config = json.load(config)

for category in config["categories"]:
    tc.add_category(category.encode('utf-8'))

for keyword in config["keywords"]:
    tc.add_keyword(keyword.encode('utf-8'))

tc.init()

for category, trainings in config["training"].iteritems():
    for training in trainings:
        ts = TrainingSet()
        ts[:] = map(lambda w: w.encode('utf-8'), training)
        tc.add_training(ts, category.encode('utf-8'))

tc.train()

if __name__ == '__main__':
    print(tc.classify("I prefer a burger to a pizza"))
    print(tc.classify("google is better than microsoft"))
    print(tc.classify("google software is awesome"))
    print(tc.classify("Some random words"))
