# -*- coding: utf-8 -*-
import unittest
from app import db
from app.dbs import models
from app.dbs import db_access
from app.parse import website_parser

TEST_CATEGORY_NAME = 'test_catgory'
TEST_PAGE_URL = 'test.test.test'

def add_category( category_name ):
    
    u = models.Category(name = category_name )
    db.session.add(u)
    db.session.commit()
    return "ok"

class TestApp(unittest.TestCase):
    
    def DatabaseDeleteTestPagesAndCategory(self):
        """ Deletes Test pages and Category
        """
        category_ = models.Category.query.filter_by(name = TEST_CATEGORY_NAME ).first()
        if category_ != None:
            for page in db_access.get_pages( TEST_CATEGORY_NAME ):
                db.session.delete(page)
            db.session.delete(category_)
            db.session.commit()
    
    def testAddTestCategory(self):
        """Test: ADD Category
        """
        self.DatabaseDeleteTestPagesAndCategory()
        ret = add_category(TEST_CATEGORY_NAME)
        assert ret == "ok", "Can not add TEST category to Database"
        category_ = models.Category.query.filter_by(name = TEST_CATEGORY_NAME ).first()
        assert category_ != None, "TEST category do not exist in Database"
        self.DatabaseDeleteTestPagesAndCategory()
    
    def testAddTestPage(self):
        """Test: ADD Page
        """
        self.DatabaseDeleteTestPagesAndCategory()
        ret = add_category(TEST_CATEGORY_NAME)
        assert ret == "ok", "Can not add TEST category to Database"
        category_ = models.Category.query.filter_by(name = TEST_CATEGORY_NAME ).first()
        assert category_ != None, "TEST category do not exist in Database"
        db_access.add_url(TEST_CATEGORY_NAME , TEST_PAGE_URL)
        page = models.Page.query.filter_by(url = TEST_PAGE_URL ).first()
        assert page != None, "Page with url: TEST_PAGE_URL not existing in Database"
        self.DatabaseDeleteTestPagesAndCategory()
    
    def testTryToAddExistingPage(self):
        def testAddTestPage(self):
        """Test: Try to ADD existing Page
        """
        self.DatabaseDeleteTestPagesAndCategory()
        ret = add_category(TEST_CATEGORY_NAME)
        assert ret == "ok", "Can not add TEST category to Database"
        category_ = models.Category.query.filter_by(name = TEST_CATEGORY_NAME ).first()
        assert category_ != None, "TEST category do not exist in Database"
        db_access.add_url(TEST_CATEGORY_NAME , TEST_PAGE_URL)
        db_access.add_url(TEST_CATEGORY_NAME , TEST_PAGE_URL)
        pages = models.Page.query.filter_by(url = TEST_PAGE_URL ).all()
        assert len(pages) == 1, "Amount of pages with TEST_PAGE_URL not equal 1 Database"
        self.DatabaseDeleteTestPagesAndCategory()
    
    def testAreCategoriesEgzisti(self):
        """Test: If needed catgories exist
        """
        category_ = models.Category.query.filter_by(name = 'sport' ).first()
        assert category_ != None, "Category sport do not exist in Database"
        category_ = models.Category.query.filter_by(name = 'food' ).first()
        assert category_ != None, "Category food do not exist in Database"
        category_ = models.Category.query.filter_by(name = 'politics' ).first()
        assert category_ != None, "Category politics do not exist in Database"
        category_ = models.Category.query.filter_by(name = 'health' ).first()
        assert category_ != None, "Category health do not exist in Database"
        category_ = models.Category.query.filter_by(name = 'travel' ).first()
        assert category_ != None, "Category travel do not exist in Database"
        category_ = models.Category.query.filter_by(name = 'not_exist_category' ).first()
        assert category_ == None, "Category not_exist_category exist in Database"
    
    def testIsWebContentIsString(self):
        """Test: If website_parser returns content (as string)
        """
        ret = website_parser.get_text('http://www.google.pl')
        assert isinstance(ret, basestring), "Return of website_parser.get_text is not basestring"


if __name__=="__main__":
    unittest.main()


