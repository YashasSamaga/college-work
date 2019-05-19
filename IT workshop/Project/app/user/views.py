from flask import render_template, request, session, redirect, url_for, flash

from app.project.models import Project
from app.user.forms import LoginForm, SignupForm
from app.user.models import User, Donation, Favorite

from app import app, db, mail
from flask_mail import Message

from itsdangerous import URLSafeTimedSerializer

def generate_confirmation_token(email):
	serializer = URLSafeTimedSerializer(app.config['SECRET_KEY'])
	return serializer.dumps(email, salt=app.config['SECURITY_PASSWORD_SALT'])

def confirm_token(token, expiration=3600):
	serializer = URLSafeTimedSerializer(app.config['SECRET_KEY'])
	try:
		email = serializer.loads(
			token,
			salt=app.config['SECURITY_PASSWORD_SALT'],
			max_age=expiration
        )
	except:
		return False
	return email

@app.route('/user/login/', methods=['GET', 'POST'])
def user_login():
	return_url = request.args.get('return_url', default = url_for("index"))	
	form = LoginForm()

	if request.method == 'POST' and form.validate() == True:
		user = User.check_account(form.name.data)			
		if user == None:
			form.name.errors.append("The account with the given username/email does not exist.")
		else:
			if user.check_password(form.password.data) == False:
				form.password.errors.append("Wrong password.")
			else:
				if user.confirmed:
					session['userid'] = user.userid
					session['username'] = user.username
					session['email'] = user.email
					session['reg_date'] = user.reg_date
					session['avatar'] = user.avatar
				else:
					return render_template('user/activate.html')
			
	if 'userid' in session:
			return redirect(return_url)			

	return render_template('user/login.html', form = form, return_url = return_url)

@app.route('/user/signup/', methods=['GET', 'POST'])
def user_signup():
	return_url = request.args.get('return_url', default = url_for("index"))
	form = SignupForm()
	
	if request.method == 'POST' and form.validate() == True:
		user = User.query.filter_by(username = form.username.data).first()
		if user:
			form.username.errors.append("This username is already taken.")
		else:
			user = User.query.filter_by(email = form.email.data.lower()).first()
			if user:
				form.email.errors.append("That email is already in use.")
			else:
				user = User(form.username.data, form.email.data, form.password.data)
				token = generate_confirmation_token(user.email)
				confirm_url = url_for('user_confirm_email', token=token, _external=True)
				
				msg = Message("Please confirm your email", sender = 'admin@fundmeplease.com', recipients = [form.email.data])
				msg.html = render_template('user/email.html', confirm_url=confirm_url)
				mail.send(msg)
				db.session.add(user)
				db.session.commit()
				return render_template('user/activate.html')
	
	if 'userid' in session:
			return redirect(return_url)
			
	return render_template('user/signup.html', form = form, return_url = return_url)

@app.route('/user/profile/confirm', methods = ['GET'])
def user_confirm_email():
	try:
		email = confirm_token(request.args['token'])
	except:
		flash('The confirmation link is invalid or has expired.', 'danger')
	user = User.query.filter_by(email=email).first_or_404()
	if user.confirmed:
		flash('Account already confirmed. Please login.', 'success')
	else:
		user.confirmed = True
		db.session.commit()
		flash('You have confirmed your account. Thanks!', 'success')
	return user_login()

@app.route('/user/logout/')
def user_logout():
	return_url = request.args.get('return_url', default = url_for("index"))
	
	session.pop('userid', None)
	session.pop('username', None)
	session.pop('email', None)
	session.pop('reg_date', None)
	session.pop('avatar', None)
	
	return redirect(return_url)
	
@app.route('/user/profile/')
@app.route('/user/profile/<int:userid>')
def user_profile(userid = None):
	if userid == None:
			if 'userid' not in session:
				return redirect(url_for('user_login') + '?return_url=' + url_for('profile'))
			userid = session['userid']
	
	user = User.query.filter_by(userid = userid).first()
	donations = Donation.query.filter_by(userid = userid).limit(10).all()
	for donation in donations:
		project = Project.query.filter_by(projectid = donation.projectid).first()
		donation.project_name = project.name
		
	favorites = Favorite.query.filter_by(userid = userid).limit(10).all()
	for favorite in favorites:
		project = Project.query.filter_by(projectid = favorite.projectid).first()
		favorite.project_name = project.name
	
	return render_template('user/profile.html', user = user, donations = donations, favorites = favorites)
	
@app.route('/user/profile/add_balance', methods = ['POST'])
def user_add_balance():
	if 'userid' in session:
		user = User.query.filter_by(userid = session['userid']).first()
		user.balance += 100000
		db.session.commit()
		return render_template('user/profile.html', user = user)
	return redirect(url_for('/'))

@app.route('/user/profile/add_favorite/<int:projectid>')
def user_favorite(projectid):
	fav = Favorite.query.filter_by(userid = session['userid']).first()
	if fav == None:
		fav = Favorite(session['userid'], projectid)
		db.session.add(fav)
		db.session.commit()
	else:
		db.session.delete(fav)
		db.session.commit()
	return redirect(url_for('project_view', projectid = projectid))
	
