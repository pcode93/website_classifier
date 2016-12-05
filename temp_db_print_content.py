#!flask/bin/python

from app import db
from app.dbs import models

categories = models.Category.query.all()
print ' \r\nCategories:'
print categories

pages = models.Page.query.all()
print ' \r\nPages:'
print pages

print ' \r\nCategory:'
u = models.Category.query.get(1)
print u
print ' \r\nPages in category:'
pages_in_category = u.pages.all()
print pages_in_category
