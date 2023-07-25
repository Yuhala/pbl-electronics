#
# RPI home automation web control dashboard
# Peterson Yuhala
#

from flask import Flask, render_template, request, session, redirect, url_for
# from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)
#app.config[ ' SECRET_KEY ' ] = ' secret_key '
#app.config[ ' SQLALCHEMY_DATABASE_URI ' ] = ' sqlite:///chat.db '
#db = SQLAlchemy(app)

@app.route('/')
def show_dashboard():
    return render_template('layout.html')