""" Handle request with /index and / prefix"""

from flask import render_template, flash, redirect
from flask import make_response
from app import app
from app import index_file


@app.route('/')
@app.route('/index')
def index():
    """Function return index.html file"""
    try:
        return index_file.read()
    except:
        return make_response("ERROR 404 can not find page", 404)


