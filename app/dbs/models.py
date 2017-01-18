"""Database models of Category and Page."""

from app import db


class Category(db.Model):
    """ Database model of Category.
    """
    id = db.Column(db.Integer, primary_key=True)
    name = db.Column(db.String(64), index=True, unique=True)
    pages = db.relationship('Page', backref='category', lazy='dynamic')

    def __repr__(self):
        return '<Category %r>' % (self.name)


class Page(db.Model):
    """ Database model of Page.
    """
    id = db.Column(db.Integer, primary_key=True)
    url = db.Column(db.String(140), unique=True)#, index=True, unique=True)
    timestamp = db.Column(db.DateTime)
    categroy_id = db.Column(db.Integer, db.ForeignKey('category.id'))

    def __repr__(self):
        return '<URL: %r>' % (self.url)
