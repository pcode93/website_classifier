from app.dbs import models
import json

def get_pages( category_name ):
    category = models.Category.query.filter_by(name = category_name ).first()
    return category.pages.all()

def get_urls( category_name ):
    urls = []
    for page in get_pages( category_name ):
        urls.append(page.url)
    return urls

def get_urls_as_json( category_name ):
    data = get_urls( category_name )
    return json.dumps({'category': category_name, 'websites': data}, sort_keys=True, indent=4, separators=(',',':'))
