from app import app
from app.bayes import classifier
from app.parse import website_parser
from app.dbs import db_access
from urllib2 import URLError, HTTPError
from flask import jsonify, make_response

@app.route('/classify')
def api_articles():
    return ' '

@app.route('/classify/<path:url>')
def api_article(url):
    try:
        category_name = classifier.classify(website_parser.get_text(url))
        print
        print category_name
        url_list = db_access.get_urls( category_name )
        return jsonify(category=category_name,
                       websites=url_list)
    
    except HTTPError, e:
        response = jsonify(error = 'The server couldn\'t fulfill the request.')
        return make_response(response, e.code)
    
    except URLError, e:
        return make_response(jsonify(error = 'URL Error'), 404)
    
    except ValueError, e:
        response = jsonify(error = 'We failed to reach a server. \n\r Did you selected http?')
        return make_response(response, 404)

    except:
        response = jsonify(error = 'The operation failed')
        return make_response(response, 404)
