from flask_wtf import Form
from wtforms import TextField, PasswordField, BooleanField, SubmitField, ValidationError
from wtforms.validators import *
from wtforms.fields.html5 import EmailField
from flask_wtf.file import FileField, FileRequired, FileAllowed

from app.category.models import Category 

class AddCategoryForm(Form):
	title = "Add Category"
	name = TextField("Category Name",  [Required()], render_kw={ "placeholder" : "Enter category name", "required" : "required" })
	description = TextField("Description",  [Required()], render_kw={ "placeholder" : "Enter category description", "required" : "required" })
	default_project_cover = FileField("Default Project Cover")
	material_icon_id = TextField("Material Icons Id",  [Required()], render_kw={ "placeholder" : "Enter material icon id", "required" : "required" })
	submit = SubmitField("Add")
	
	def __init__(self, *args, **kwargs):
		Form.__init__(self, *args, **kwargs)

	def validate(self):
		if not Form.validate(self):
			return False

		category = Category.query.filter_by(name = self.name.data).first()			
		if category != None:
			self.name.errors.append("A category with the given name already exists.")
			return False
		return True
