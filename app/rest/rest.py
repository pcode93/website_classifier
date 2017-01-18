"""REST Module, handle REST requestss with /classify prefix"""


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
    """ Returns list of similar pages (urls) in json.
        @param url URL of page to classify.
    """
    try:
        category_name = tc.classify(website_parser.get_text(url))

        if category_name == "none": raise

        url_list = db_access.get_urls( category_name )
        db_access.add_url(category_name, url)
        
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

    except Exception, e:
        response = jsonify(error = 'The operation failed')
        return make_response(response, 404)
