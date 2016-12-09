from flask import render_template, flash, redirect
from app import app
from app import index_file


@app.route('/')
@app.route('/index')
def index():
    return index_file.read()
                #render_template('index.html')
                 #,
                 #                  title='Home',
                 #                  user=user,
                 #                  posts=posts)
