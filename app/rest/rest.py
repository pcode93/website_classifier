from app import app
from app.bayes import tc
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
        category_name = tc.classify(website_parser.get_text(url))
        url_list = db_access.get_urls( category_name )
        if category_name != "none":
            db_access.add_url(category_name, url)
        return jsonify(category=category_name, 
                        websites=url_list) if category_name != "none" else make_response(
                        jsonify(error = 'Couldn\'t classify the website'), 404)
    
    except HTTPError, e:
        print e
        response = jsonify(error = 'The server couldn\'t fulfill the request.')
        return make_response(response, e.code)
    
    except URLError, e:
        print e
        return make_response(jsonify(error = 'URL Error'), 404)
    
    except ValueError, e:
        print e
        response = jsonify(error = 'We failed to reach a server. \n\r Did you selected http?')
        return make_response(response, 404)

    except Exception, e:
        print e
        response = jsonify(error = 'The operation failed')
        return make_response(response, 404)
