from flask import render_template, request, session, redirect, url_for

from app import app
from app import db

from app.project.models import Project
from app.category.models import Category
from app.category.forms import CProjectSearch

@app.route('/category/')
def category():
	return render_template('category/category.html', categories = Category.query.all())

@app.route('/category/<string:category>', methods=['GET'])
def category_view(category = None):
	form = CProjectSearch()
	cat = Category.query.filter_by(name = category).first()
	projects = Project.query.filter_by(categoryid = cat.categoryid).limit(8).all()
	return render_template('category/view.html', projects = projects, category = cat, form = form)
	
@app.route('/category/<string:category>/search', methods=['GET'])
def category_psearch(category = None):
	cat = Category.query.filter_by(name = category).first()
	projects = None
	form = CProjectSearch()
	if 'query' in request.args:
		query = request.args['query']
		prefix = query.split(':')[0].strip()
		print(prefix, query, '\n\n\n\n')
		if prefix and prefix == "tag":
			sstr = '%' + ''.join(query.split(':')[1:]).strip() + '%'
			projects = Project.query.filter_by(categoryid = cat.categoryid).filter(Project.tags.like(sstr)).limit(10).all()
		elif prefix and prefix == 'location':
			sstr = '%' + ''.join(query.split(':')[1:]).strip() + '%'
			projects = Project.query.filter_by(categoryid = cat.categoryid).filter(Project.location.like(sstr)).limit(10).all()
		elif prefix and prefix == 'userid':
			sstr = '%' + ''.join(query.split(':')[1:]).strip() + '%'
			uid = int(sstr)
			projects = Project.query.filter_by(and_(categoryid = cat.categoryid, userid = uid)).limit(10).all()
		else:
			projects = Project.query.filter_by(categoryid = cat.categoryid).filter(Project.name.like('%{}%'.format(query))).limit(10).all()
	return render_template('category/search_results.html', projects = projects, category = cat, form = form)
