from naiveBayesClassifier import tokenizer
from naiveBayesClassifier.trainer import Trainer
from naiveBayesClassifier.classifier import Classifier

trainer = Trainer(tokenizer.Tokenizer(stop_words = [], signs_to_remove = ["?!#%&"]))

training_set = [
    {'text': 'not to eat too much is not enough to lose weight', 'category': 'health'},
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
    newsClassifier = Classifier(trainer.data, tokenizer.Tokenizer(stop_words = [], signs_to_remove = ["?!#%&"]))
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
