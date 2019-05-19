from flask import url_for
from datetime import datetime

from config import category_config

from app import db

class Project(db.Model):
	__tablename__ = "projects"
	
	projectid = db.Column(db.Integer, primary_key=True)
	categoryid = db.Column(db.Integer, db.ForeignKey('category.categoryid'))
	userid = db.Column(db.Integer, db.ForeignKey('users.userid'))
	name = db.Column(db.String(64), unique=True, nullable=False)
	cover = db.Column(db.String(100))
	description = db.Column(db.String(1024), nullable=False)
	story = db.Column(db.String(4096), nullable=False)	
	location = db.Column(db.String(256), nullable=True)	
	target_fund = db.Column(db.Integer(), nullable=False)
	current_fund = db.Column(db.Integer())
	tags = db.Column(db.String(1024))
	start_date = db.Column(db.DateTime())

	def __init__(self, name, userid, category, description, story, location, target_fund, tags):
		self.name = name
		self.userid = userid
		self.categoryid = category
		self.description = description
		self.story = story
		self.location = location
		self.target_fund = target_fund
		self.tags = tags
		self.cover = url_for('static', filename = category_config['default_project_cover_url'].format(category))
		self.current_fund = 0
		self.start_date = datetime.now()
		
	@staticmethod
	def check_project(projectid):
		project = Project.query.filter_by(projectid = projectid).first()
		return project
		
class Comment(db.Model):
	__tablename__ = "comments"

	commentid = db.Column(db.Integer, primary_key=True)
	projectid = db.Column(db.Integer, db.ForeignKey('projects.projectid'))
	userid = db.Column(db.Integer, db.ForeignKey('users.userid'))
	comment = db.Column(db.String(144), nullable=False)
	
	def __init__(self, projectid, userid, comment):
		self.projectid = projectid
		self.userid = userid
		self.comment = comment
	
