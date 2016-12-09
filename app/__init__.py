from flask import Flask, url_for
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)
app.config.from_object('config')
db = SQLAlchemy(app)

index_file = open('app/templates/index.html', 'r')

from app.dbs import models
from app.templates import views
from app.rest import rest

