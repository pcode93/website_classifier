import json

from classifier import TextClassifier
from classifier import TrainingSet

config = {}
tc = TextClassifier()

with open('app/bayes/bayes.json') as config:
    config = json.load(config)

for category in config["categories"]:
    tc.add_category(str(category))

for keyword in config["keywords"]:
    tc.add_keyword(str(keyword))

tc.init()

for category, trainings in config["training"].iteritems():
    for training in trainings:
        ts = TrainingSet()
        ts[:] = map(lambda w: str(w), training)
        tc.add_training(ts, str(category))

tc.train()

if __name__ == '__main__':
    print(tc.classify("I prefer a burger to a pizza"))
    print(tc.classify("google is better than microsoft"))
    print(tc.classify("google software is awesome"))
