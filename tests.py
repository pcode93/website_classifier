# -*- coding: utf-8 -*-
import unittest
from app import db
from app.dbs import models
from app.dbs import db_access

class TestApp(unittest.TestCase):
    
    def DatabaseCreate(self):
        db.create_all()
    
    def testAreCategoriesEgzisti(self):
        category_ = models.Category.query.filter_by(name = 'sport' ).first()
        assert category_ != None, "category sport did not exist"
        category_ = models.Category.query.filter_by(name = 'food' ).first()
        assert category_ != None, "category food did not exist"
        category_ = models.Category.query.filter_by(name = 'politics' ).first()
        assert category_ != None, "category politics did not exist"
        category_ = models.Category.query.filter_by(name = 'health' ).first()
        assert category_ != None, "category health did not exist"
        category_ = models.Category.query.filter_by(name = 'travel' ).first()
        assert category_ != None, "category travel did not exist"
        category_ = models.Category.query.filter_by(name = 'not_exist_category' ).first()
        assert category_ == None, "category not_exist_category is exist"
        
    def testTryToAddExistingURL(self):
        page = models.Page.query.filter_by(url = 'http://www.bbc.com/sport' ).first()
        assert page != None, "http://www.bbc.com/sport not existing in Database"
        ret = db_access.add_url('sport','http://www.bbc.com/sport')
        assert ret == "error", "db_access.add_url not return error on existing url"
 
"""
    def testAddExistingSite(self):
        assert 4.6 == 4.6, "calculator pound_exchange_rate did not set correctly"


def testAddCategories(self):
    try:
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
        except:
            assert 1, "categories can exist"

"""

if __name__=="__main__":
    unittest.main()


