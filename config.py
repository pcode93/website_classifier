import os
basedir = os.path.abspath(os.path.dirname(__file__))

SQLALCHEMY_DATABASE_URI = 'sqlite:///' + os.path.join(basedir, 'app/dbs/app.db')
print SQLALCHEMY_DATABASE_URI
SQLALCHEMY_TRACK_MODIFICATIONS = True
