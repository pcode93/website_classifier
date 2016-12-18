#!flask/bin/python

from app import db
from app.dbs import models

u = models.Category(name='sport')
db.session.add(u)
u = models.Category(name='food')
db.session.add(u)
u = models.Category(name='politics')
db.session.add(u)
u = models.Category(name='health')
db.session.add(u)
u = models.Category(name='travel')
db.session.add(u)
db.session.commit()
categories = models.Category.query.all()
print categories

import datetime
u = models.Category.query.get(1)
p  = models.Page(url='http://www.bbc.com/sport', timestamp=datetime.datetime.utcnow(), category=u)
db.session.add(p)
p  = models.Page(url='http://www.businessinsider.com/sportspage?IR=T', timestamp=datetime.datetime.utcnow(), category=u)
db.session.add(p)
p  = models.Page(url='http://www.sport-english.com/en/', timestamp=datetime.datetime.utcnow(), category=u)
db.session.add(p)

u = models.Category.query.get(2)
p  = models.Page(url='http://www.food.com', timestamp=datetime.datetime.utcnow(), category=u)
db.session.add(p)
p  = models.Page(url='http://www.foodnetwork.com/recipes.html', timestamp=datetime.datetime.utcnow(), category=u)
db.session.add(p)
p  = models.Page(url='http://www.taste.com.au', timestamp=datetime.datetime.utcnow(), category=u)
db.session.add(p)
p  = models.Page(url='http://www.self.com/food', timestamp=datetime.datetime.utcnow(), category=u)
db.session.add(p)

u = models.Category.query.get(3)
p  = models.Page(url='http://www.politics.com', timestamp=datetime.datetime.utcnow(), category=u)
db.session.add(p)
p  = models.Page(url='http://www.businessinsider.com/politics?IR=T', timestamp=datetime.datetime.utcnow(), category=u)
db.session.add(p)
p  = models.Page(url='http://www.telegraph.co.uk/news/politics/', timestamp=datetime.datetime.utcnow(), category=u)
db.session.add(p)

u = models.Category.query.get(4)
p  = models.Page(url='http://www.health.com', timestamp=datetime.datetime.utcnow(), category=u)
db.session.add(p)
p  = models.Page(url='http://www.menshealth.com/health', timestamp=datetime.datetime.utcnow(), category=u)
db.session.add(p)
p  = models.Page(url='http://www.myhealthtips.in', timestamp=datetime.datetime.utcnow(), category=u)
db.session.add(p)

u = models.Category.query.get(5)
p  = models.Page(url='http://www.bbc.com/travel/', timestamp=datetime.datetime.utcnow(), category=u)
db.session.add(p)
p  = models.Page(url='http://www.menshealth.com/health', timestamp=datetime.datetime.utcnow(), category=u)
db.session.add(p)
p  = models.Page(url='http://www.myhealthtips.in', timestamp=datetime.datetime.utcnow(), category=u)
db.session.add(p)

db.session.commit()
