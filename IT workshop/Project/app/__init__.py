from flask import Flask
from flask_mail import Mail
from flask_sqlalchemy import SQLAlchemy

from config import flask_config, jinja2_globals

app = Flask(__name__)
mail = Mail()
db = SQLAlchemy()
   
from app.user.models import User
from app.category.models import Category
from app.project.models import Project

def start_app():
	app.config.update(flask_config);
	app.jinja_env.globals.update(jinja2_globals);
	
	mail.init_app(app)
	
	db.init_app(app=app)
	db.create_all(app=app)	
	
	from app import errorhandlers
	from app import routes
	return app
