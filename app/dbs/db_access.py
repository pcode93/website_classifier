from app import db
from app.dbs import models
import datetime

def get_pages( category_name ):
    category_ = models.Category.query.filter_by(name = category_name ).first()
    return category_.pages.all()

def get_urls( category_name ):
    urls = []
    for page in get_pages( category_name ):
        urls.append(page.url)
    return urls

def add_url( category_name, url ):
    category_ = models.Category.query.filter_by(name = category_name ).first()
    p  = models.Page(url='url', timestamp=datetime.datetime.utcnow(), category= category_)
    db.session.add(p)
    db.session.commit()

