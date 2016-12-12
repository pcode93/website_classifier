from app import app
from app.bayes import classifier
from app.parse import website_parser
from app.dbs import db_access

@app.route('/classify')
def api_articles():
    return ' '

@app.route('/classify/<path:url>')
def api_article(url):
    return db_access.get_urls_as_json(classifier.classify(website_parser.get_text(url)))
