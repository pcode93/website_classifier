from app import db
from app.dbs import models
import datetime

def get_pages( category_name ):
    """ Returns Pages from Category (selected by name).
        @category_name Category name (string).
    """
    category_ = models.Category.query.filter_by(name = category_name ).first()
    return category_.pages.all()

def get_urls( category_name ):
    """ Returns pages URLs from Category.
        @category_name Category name (string).
    """
    urls = []
    for page in get_pages( category_name ):
        urls.append(page.url)
    return urls

def add_url( category_name, url ):
    """ Adds Page to DB (if page do not exist in Database) .
        @category_name Category name (string).
        @url Page URL
    """
    page = models.Page.query.filter_by(url = url ).first()
    if page == None:
        category_ = models.Category.query.filter_by(name = category_name ).first()
        if category_ != None:
            p = models.Page(url=url, timestamp=datetime.datetime.utcnow(), category= category_)
            db.session.add(p)
            db.session.commit()

