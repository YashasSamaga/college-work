from flask_wtf import Form
from wtforms import TextField, PasswordField, ValidationError
from wtforms.validators import *
from wtforms.fields.html5 import EmailField

from config import user_config
from app.user.models import User
from app.common.forms import InlineSubmitField

class LoginForm(Form):
	title = "Login"
	name = TextField("Username/Email",  [Required()], render_kw = { "placeholder" : "Enter your username/email", "required" : "required" })
	password = PasswordField("Password",  [Required()], render_kw = { "placeholder" : "Enter your password", "required" : "required" })
	submit = InlineSubmitField("Login")
	
	def __init__(self, *args, **kwargs):
		Form.__init__(self, *args, **kwargs)

class SignupForm(Form):
	title = "Sign Up"
	username = TextField("Username",  [Required()], render_kw={ "placeholder" : "Enter your username", "required" : "required" })
	email = EmailField("Email",  [Required(), Email()], render_kw={ "placeholder" : "Enter your email", "required" : "required" })
	password = PasswordField("Password",  [Required(), Length(user_config["password_min_length"], user_config["password_max_length"])], render_kw={ "placeholder" : "Enter your password", "required" : "required"})
	password_retype = PasswordField("Re-type Password",  [Required(), EqualTo("password", "Passwords do not match.")], render_kw={ "placeholder" : "Enter your password again", "required" : "required" })
	agreement = "By signing up, you agree to our terms of use, privacy policy and cookie policy."
	submit = InlineSubmitField("Signup")

	def __init__(self, *args, **kwargs):
		Form.__init__(self, *args, **kwargs)
