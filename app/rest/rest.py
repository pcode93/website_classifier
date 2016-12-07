from app import app

@app.route('/classify')
def api_articles():
    return 'List of api_articles'

@app.route('/classify/<path:articleid>')
def api_article(articleid):
    return 'You are reading ' + articleid
