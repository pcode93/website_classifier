#!flask/bin/python

""" Database initiation
"""


from app import db
from app.dbs import models
from app.dbs import db_access
import datetime

db.create_all()
"""Database create (if not exist)"""


categories_ = ['sport','food','politics','health','travel']
"""Categories Definition"""


for category_string in categories_:
    category_ = models.Category.query.filter_by(name = category_string ).first()
    if category_ == None:
        u = models.Category(name = category_string )
        db.session.add(u)

db.session.commit()
categories = models.Category.query.all()
print '\nCategories:'
print categories
print '\n'

sport_urls = ['http://www.bbc.com/sport','http://www.businessinsider.com/sportspage?IR=T','http://www.sport-english.com/en/']

for url in sport_urls:
    page = models.Page.query.filter_by(url = url ).first()
    if page == None:
        db_access.add_url('sport',url)


food_urls = ['http://www.food.com','http://www.foodnetwork.com/recipes.html','http://www.taste.com.au','http://www.self.com/food']

for url in food_urls:
    db_access.add_url('food',url)

politics_urls = ['http://www.politics.com', 'http://www.businessinsider.com/politics?IR=T', 'http://www.telegraph.co.uk/news/politics/']

for url in politics_urls:
    db_access.add_url('politics',url)


health_urls = ['http://www.health.com','http://www.menshealth.com/health', 'http://www.myhealthtips.in']

for url in health_urls:
    db_access.add_url('health',url)


travel_urls = ['http://www.bbc.com/travel/', 'http://www.thetravelmagazine.net', 'https://www.buzzfeed.com/travel']

for url in travel_urls:
    db_access.add_url('travel',url)

for category_string in categories_:
    print '\n\n'
    print category_string
    u = models.Category.query.filter_by(name = category_string ).first()
    print u.pages.all()
    print '\n\n'
