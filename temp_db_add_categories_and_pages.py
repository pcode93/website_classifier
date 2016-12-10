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
db.session.commit()
categories = models.Category.query.all()
print categories

import datetime
u = models.Category.query.get(1)
p  = models.Page(url='www.sport.com', timestamp=datetime.datetime.utcnow(), category=u)
db.session.add(p)
p  = models.Page(url='www.sport.pl', timestamp=datetime.datetime.utcnow(), category=u)
db.session.add(p)
p  = models.Page(url='www.sport_xyz.com', timestamp=datetime.datetime.utcnow(), category=u)
db.session.add(p)

u = models.Category.query.get(2)
p  = models.Page(url='www.food.com', timestamp=datetime.datetime.utcnow(), category=u)
db.session.add(p)
p  = models.Page(url='www.food.pl', timestamp=datetime.datetime.utcnow(), category=u)
db.session.add(p)
p  = models.Page(url='www.food_xyz.com', timestamp=datetime.datetime.utcnow(), category=u)
db.session.add(p)

u = models.Category.query.get(3)
p  = models.Page(url='www.politics.com', timestamp=datetime.datetime.utcnow(), category=u)
db.session.add(p)
p  = models.Page(url='www.politics.pl', timestamp=datetime.datetime.utcnow(), category=u)
db.session.add(p)
p  = models.Page(url='www.politicsxxx.com', timestamp=datetime.datetime.utcnow(), category=u)
db.session.add(p)

u = models.Category.query.get(4)
p  = models.Page(url='www.health.com', timestamp=datetime.datetime.utcnow(), category=u)
db.session.add(p)
p  = models.Page(url='www.health.pl', timestamp=datetime.datetime.utcnow(), category=u)
db.session.add(p)
p  = models.Page(url='www.health.xx.com', timestamp=datetime.datetime.utcnow(), category=u)
db.session.add(p)

db.session.commit()
