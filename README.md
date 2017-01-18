cd to directory

sudo easy_install virtualenv
virtualenv flask

flask/bin/pip install -I flask==0.11.1
flask/bin/pip install -I flask-sqlalchemy==2.1
flask/bin/pip install -I bs4==0.0.1

flask/bin/python ./build.py
flask/bin/python ./run.py
