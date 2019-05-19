from flask import render_template, request, session, redirect, url_for

from flask_mail import Message
import codecs

from app import app
from app import mail
from app import db

from sqlalchemy import and_

import pdfkit

from app.user.models import User, Donation, Favorite
from app.project.models import Project, Comment
from app.category.models import Category
from app.project.forms import CreateProjectForm, FundForm, CommentForm

@app.route('/project/create', methods=['GET', 'POST'])
def project_create():
	if 'userid' not in session:
		return redirect(url_for('user_login') + '?return_url=' + url_for('project_create'))

	form = CreateProjectForm()
	form.category.choices = [(category.categoryid, category.name) for category in Category.query.all()]

	if request.method == 'POST' and form.validate() == True:
		project = Project.query.filter_by(name = form.name.data).first()
		if project != None:
			form.name.errors.append("A project with the given name already exists.")
		else:
			project = Project(form.name.data, session['userid'], form.category.data, form.description.data, form.story.data, form.location.data,
							  form.target_fund.data, form.tags.data)
			db.session.add(project)
			db.session.commit()
			return redirect(url_for('project_view', projectid = project.projectid))

	return render_template('project/create.html', form = form)

@app.route('/project/view/<int:projectid>', methods = ['GET', 'POST'])
def project_view(projectid = None):
	cform = CommentForm()
	form = FundForm()
	project = Project.check_project(projectid)
	if project != None:
		project.author = User.query.filter_by(userid = project.userid).first().username
		project.category_name = Category.query.filter_by(categoryid = project.categoryid).first().name
	
	if request.method == 'POST' and form.validate() == True:
		if 'userid' not in session:
			return redirect(url_for('user_login') + '?return_url=' + url_for('project_view', projectid = projectid))
			
		user = User.query.filter_by(userid = session['userid']).first()
		if user.balance < form.amount.data:
			form.amount.errors = (*form.amount.errors, "You do not have that much money in your account.")
		else:
			project = Project.check_project(projectid)
			if project != None:
				user.balance -= form.amount.data
				project.current_fund += form.amount.data
				donation = Donation(user.userid, projectid, form.amount.data)
				
				owner = User.query.filter_by(userid = project.userid).first()
				
				msg = Message("[FMP] Donation Receipt", sender = 'donations@fundmeplease.com', recipients = [user.email])
				msg.html = render_template('project/donor-donation-mail.html', donor_name = user.username, donor_id = user.userid,
										amount = form.amount.data, project_name = project.name, project_id = project.projectid)
				
				with open("receipt.html", "w") as outFile:
					outFile.write(msg.html)
					
				pdfkit.from_file("receipt.html", 'receipt.pdf')
				with open("receipt.pdf", "rb") as fdata:		
					msg.attach('receipt.pdf', 'application/pdf', fdata.read())
				mail.send(msg)				
				
				msg = Message("[FMP] Donation Receipt", sender = 'donations@fundmeplease.com', recipients = [owner.email])
				msg.html = render_template('project/owner-donation-mail.html', donor_name = user.username, donor_id = user.userid,
											amount = form.amount.data, project_name = project.name, project_id = project.projectid)
											
				with open("receipt.html", "w") as outFile:
					outFile.write(msg.html)
					
				pdfkit.from_file("receipt.html", 'receipt.pdf')
				with open("receipt.pdf", "rb") as fdata:			
					msg.attach('receipt.pdf', 'application/pdf', fdata.read())
				mail.send(msg)
				
				db.session.add(donation)
				db.session.commit()
	
	micon = None
	if 'userid' in session:	
		fav = Favorite.query.filter_by(userid = session['userid']).filter_by(projectid = projectid).first()
		if fav == None:
			micon =	"favorite_border"
		else:
			micon = "favorite"
			
	comments = Comment.query.filter_by(projectid = project.projectid).limit(10).all()
	for comment in comments:
		comment.uname = User.query.filter_by(userid = comment.userid).first().username
		
	return render_template('project/view.html', project = project, form = form, cform = cform, micon = micon, comments = comments)
	
@app.route('/project/add_comment/<int:projectid>/<int:userid>', methods = ['POST'])
def add_comment(projectid, userid):
	form = CommentForm()
	comment = Comment(projectid, userid, form.comment.data)
	db.session.add(comment)
	db.session.commit()
	return redirect(url_for('project_view', projectid = projectid))
