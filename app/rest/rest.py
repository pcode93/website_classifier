from app import app
from app.bayes import classifier
from app.parse import website_parser

@app.route('/classify')
def api_articles():
    return 'List of api_articles'

@app.route('/classify/<path:url>')
def api_article(url):
    return classifier.classify(website_parser.get_text(url))
